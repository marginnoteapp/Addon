//
//  JSBMNFileSystem.h
//  MindBooks
//
//  MN Virtual File System - Provides Unix-like API for MN data operations
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

@class MbTopic;
@class MbBookNote;

@interface JSBMNFileSystem : NSObject

/**
 * Add MNFileSystem scripting support to a JSContext
 * This loads MNFileSystem.js and sets up the MN global object
 */
+ (void)addScriptingSupportToContext:(JSContext *)context;

/**
 * Set the current context for MN operations
 * @param notebook - Current notebook (MbTopic)
 * @param note - Current note position (MbBookNote, optional)
 * @param selectedNotes - Currently selected notes (NSArray of MbBookNote)
 * @param window - Current window reference
 * @param context - JSContext to update
 */
+ (void)setContextWithNotebook:(MbTopic *)notebook
                          note:(MbBookNote *)note
                 selectedNotes:(NSArray *)selectedNotes
                        window:(id)window
                     inContext:(JSContext *)context;

/**
 * Execute MN code and capture results
 * @param code - JavaScript code to execute
 * @param context - JSContext to use
 * @return Dictionary with 'success', 'result', 'logs', 'error' keys
 */
+ (NSDictionary *)executeCode:(NSString *)code inContext:(JSContext *)context;

/**
 * Get the shared JSContext for MN operations
 * Creates one if not exists
 */
+ (JSContext *)sharedContext;

@end
