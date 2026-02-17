//
//  JSBMNFileSystem.m
//  MindBooks
//
//  MN Virtual File System - Provides Unix-like API for MN data operations
//

#import "JSBMNFileSystem.h"
#import "JSBMarginNote.h"
#import "MbTopic.h"
#import "MbBookNote.h"
#import "MbModelTool.h"

@implementation JSBMNFileSystem

static JSContext *_sharedMNContext = nil;

+ (JSContext *)sharedContext
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedMNContext = [[JSContext alloc] init];
        _sharedMNContext.exceptionHandler = ^(JSContext *context, JSValue *value) {
            NSLog(@"[MNFileSystem] JS Exception: %@", value);
        };

        // Add MarginNote scripting support (Database, Note, Notebook classes)
        [JSBMarginNote addScriptingSupportToContext:_sharedMNContext];

        // Add MNFileSystem
        [self addScriptingSupportToContext:_sharedMNContext];
    });

    return _sharedMNContext;
}

+ (void)addScriptingSupportToContext:(JSContext *)context
{
    // Load MNFileSystem.js from bundle
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSString *path = [mainBundle pathForResource:@"MNFileSystem" ofType:@"js"];

    if (!path) {
        // Try to find it in the JSC directory
        path = [mainBundle pathForResource:@"MNFileSystem" ofType:@"js" inDirectory:@"JSC"];
    }

    if (!path) {
        // Fallback: construct path manually
        NSString *bundlePath = mainBundle.resourcePath;
        path = [bundlePath stringByAppendingPathComponent:@"MNFileSystem.js"];
    }

    NSError *readError = nil;
    NSString *script = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&readError];

    if (script && script.length > 0) {
        [context evaluateScript:script withSourceURL:[NSURL fileURLWithPath:path]];
        NSLog(@"[MNFileSystem] Loaded from: %@", path);
    } else {
        NSLog(@"[MNFileSystem] Warning: Could not load MNFileSystem.js");

        // Create a minimal fallback MN object
        [context evaluateScript:@"var MN = { version: '1.0.0-fallback', pwd: function() { return 'notebook://'; } };"];
    }

    // Add helper function for console.log capture
    [self setupConsoleCapture:context];
}

+ (void)setupConsoleCapture:(JSContext *)context
{
    // Create a logs array to capture console.log output
    [context evaluateScript:@"var __MN_LOGS__ = [];"];

    // Create JS functions that can handle multiple arguments
    // This approach uses JS to join arguments, then calls native
    NSString *consoleSetup = @"\
        (function() {\
            var originalConsole = console || {};\
            var logs = __MN_LOGS__;\
            \
            function formatArgs(args) {\
                var parts = [];\
                for (var i = 0; i < args.length; i++) {\
                    var arg = args[i];\
                    if (typeof arg === 'object') {\
                        try { parts.push(JSON.stringify(arg)); }\
                        catch(e) { parts.push(String(arg)); }\
                    } else {\
                        parts.push(String(arg));\
                    }\
                }\
                return parts.join(' ');\
            }\
            \
            console = {\
                log: function() {\
                    var msg = formatArgs(arguments);\
                    logs.push(msg);\
                    if (typeof __MN_NATIVE_LOG__ === 'function') __MN_NATIVE_LOG__(msg);\
                },\
                warn: function() {\
                    var msg = '[WARN] ' + formatArgs(arguments);\
                    logs.push(msg);\
                    if (typeof __MN_NATIVE_LOG__ === 'function') __MN_NATIVE_LOG__(msg);\
                },\
                error: function() {\
                    var msg = '[ERROR] ' + formatArgs(arguments);\
                    logs.push(msg);\
                    if (typeof __MN_NATIVE_LOG__ === 'function') __MN_NATIVE_LOG__(msg);\
                },\
                info: function() {\
                    var msg = '[INFO] ' + formatArgs(arguments);\
                    logs.push(msg);\
                    if (typeof __MN_NATIVE_LOG__ === 'function') __MN_NATIVE_LOG__(msg);\
                }\
            };\
        })();\
    ";

    // Add native log function
    context[@"__MN_NATIVE_LOG__"] = ^(NSString *message) {
        NSLog(@"[MN] %@", message ?: @"");
    };

    [context evaluateScript:consoleSetup];
}

+ (void)setContextWithNotebook:(MbTopic *)notebook
                          note:(MbBookNote *)note
                 selectedNotes:(NSArray *)selectedNotes
                        window:(id)window
                     inContext:(JSContext *)context
{
    JSValue *mn = context[@"MN"];
    if (!mn || mn.isUndefined) {
        NSLog(@"[MNFileSystem] Warning: MN object not found in context");
        return;
    }

    // Build context object
    NSMutableDictionary *contextDict = [NSMutableDictionary dictionary];

    if (notebook) {
        contextDict[@"notebook"] = notebook;
    }

    if (note) {
        contextDict[@"note"] = note;
    }

    if (selectedNotes && selectedNotes.count > 0) {
        contextDict[@"selectedNotes"] = selectedNotes;
    }

    if (window) {
        contextDict[@"window"] = window;
    }

    // Call MN.setContext()
    JSValue *setContext = mn[@"setContext"];
    if (setContext && !setContext.isUndefined) {
        [setContext callWithArguments:@[contextDict]];
    }
}

+ (NSDictionary *)executeCode:(NSString *)code inContext:(JSContext *)context
{
    NSMutableDictionary *result = [NSMutableDictionary dictionary];
    result[@"success"] = @NO;
    result[@"logs"] = @[];

    if (!code || code.length == 0) {
        result[@"error"] = @"Empty code";
        return result;
    }

    @try {
        // Clear previous logs
        [context evaluateScript:@"__MN_LOGS__ = [];"];

        // Store any exception
        __block NSString *exceptionMessage = nil;
        context.exceptionHandler = ^(JSContext *ctx, JSValue *exception) {
            exceptionMessage = [exception toString];
            NSLog(@"[MNFileSystem] Exception: %@", exceptionMessage);
        };

        // Wrap code in IIFE to create a new scope for each execution
        // This prevents "duplicate variable" errors when the same code is executed multiple times
        // because `let` and `const` declarations are scoped to the IIFE, not the global context
        NSString *wrappedCode = [NSString stringWithFormat:@"(function() {\n%@\n})();", code];

        // Execute the wrapped code
        JSValue *returnValue = [context evaluateScript:wrappedCode];

        // Check for exception
        if (exceptionMessage) {
            result[@"error"] = exceptionMessage;
            result[@"success"] = @NO;
        } else {
            result[@"success"] = @YES;

            // Convert return value
            if (returnValue && !returnValue.isUndefined && !returnValue.isNull) {
                id nativeValue = [self jsValueToNative:returnValue];
                if (nativeValue) {
                    result[@"result"] = nativeValue;
                }
            }
        }

        // Collect logs
        JSValue *logs = context[@"__MN_LOGS__"];
        if (logs && !logs.isUndefined) {
            NSArray *logsArray = [logs toArray];
            if (logsArray) {
                result[@"logs"] = logsArray;
            }
        }

    } @catch (NSException *exception) {
        result[@"error"] = exception.reason ?: @"Unknown exception";
        result[@"success"] = @NO;
        NSLog(@"[MNFileSystem] Native exception: %@", exception);
    }

    return result;
}

+ (id)jsValueToNative:(JSValue *)value
{
    if (!value || value.isUndefined || value.isNull) {
        return nil;
    }

    if (value.isBoolean) {
        return @([value toBool]);
    }

    if (value.isNumber) {
        return [value toNumber];
    }

    if (value.isString) {
        return [value toString];
    }

    if (value.isArray) {
        return [value toArray];
    }

    if (value.isObject) {
        // Try to convert to dictionary
        NSDictionary *dict = [value toDictionary];
        if (dict) {
            return dict;
        }
        // Fallback to string representation
        return [value toString];
    }

    return [value toString];
}

@end
