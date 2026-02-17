#import "JSBMarginNote.h"
#import "JSBMbBook.h"
#import "JSBMbBookNote.h"
#import "JSBMbTopic.h"
#import "JSBMbModelTool.h"
#import "JSBZipArchive.h"
#import "JSBApplication.h"
#import "JSBJSExtension.h"
#import "JSBMenuController.h"
#import "JSBUndoManager.h"
#import "JSBSpeechManager.h"
#import "JSBOutlineView.h"
#import "JSBPopupMenu.h"
#import "JSBPopupMenuItem.h"
#import "JSBSQLite.h"
#import "JSBSearchManager.h"

#if TARGET_OS_IPHONE
#import "AppDelegate_iPad.h"
#else
#import "AppDelegate.h"
#endif

#import "JSBStudyController.h"
#import "JSBNotebookController.h"
#import "JSBReaderController.h"
#import "JSBDocumentController.h"
#import "MbUIStudyboardController.h"
#import "MbUIDetailViewController.h"
#import "MbUndoManager.h"
#import "NoteSearchViewController.h"
#import "MbUIMenuController.h"
#import "JSBMindMapNode.h"
#import "JSBMindMapView.h"
#import "MindMapScrollView.h"
#import "MindMapNote.h"
#import "JSExtension.h"
#import "SpeechManager.h"
#import "FMDatabase.h"
#import "QBPopupMenu.h"

@import ObjectiveC;

@implementation JSBMarginNote

+ (void)addScriptingSupportToContext:(JSContext *)context
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    class_addProtocol([MbBook class], @protocol(JSBMbBook));
    context[@"Document"] = [MbBook class];

    class_addProtocol([MbBookNote class], @protocol(JSBMbBookNote));
    context[@"Note"] = [MbBookNote class];

    class_addProtocol([MbTopic class], @protocol(JSBMbTopic));
    context[@"Notebook"] = [MbTopic class];

    class_addProtocol([MbModelTool class], @protocol(JSBMbModelTool));
    context[@"Database"] = [MbModelTool class];

    class_addProtocol([SSZipArchive class], @protocol(JSBSSZipArchive));
    context[@"ZipArchive"] = [SSZipArchive class];

    class_addProtocol([MbUIStudyboardController class], @protocol(JSBStudyController));
    context[@"StudyController"] = [MbUIStudyboardController class];

    class_addProtocol([NoteSearchViewController class], @protocol(JSBNotebookController));
    context[@"NotebookController"] = [NoteSearchViewController class];

    class_addProtocol([MbUIDetailViewController class], @protocol(JSBReaderController));
    context[@"ReaderController"] = [MbUIDetailViewController class];

    class_addProtocol([BookViewController class], @protocol(JSBDocumentController));
    context[@"DocumentController"] = [BookViewController class];

    class_addProtocol([MindMapScrollView class], @protocol(JSBMindMapView));
    context[@"MindMapView"] = [MindMapScrollView class];

    class_addProtocol([DigestTableView class], @protocol(JSBOutlineView));
    context[@"OutlineView"] = [DigestTableView class];

    class_addProtocol([MindMapNote class], @protocol(JSBMindMapNode));
    context[@"MindMapNode"] = [MindMapNote class];

    class_addProtocol([MbUIMenuController class], @protocol(JSBMenuController));
    context[@"MenuController"] = [MbUIMenuController class];

    class_addProtocol([MbUndoManager class], @protocol(JSBUndoManager));
    context[@"UndoManager"] = [MbUndoManager class];

    class_addProtocol([SpeechManager class], @protocol(JSBSpeechManager));
    context[@"SpeechManager"] = [SpeechManager class];

    class_addProtocol([JSExtension class], @protocol(JSBJSExtension));
    context[@"JSExtension"] = [JSExtension class];

    class_addProtocol([FMDatabase class], @protocol(JSBSQLiteDatabase));
    context[@"SQLiteDatabase"] = [FMDatabase class];

    class_addProtocol([QBPopupMenu class], @protocol(JSBPopupMenu));
    context[@"PopupMenu"] = [QBPopupMenu class];

    class_addProtocol([QBPopupMenuItem class], @protocol(JSBPopupMenuItem));
    context[@"PopupMenuItem"] = [QBPopupMenuItem class];

    class_addProtocol([FMStatement class], @protocol(JSBSQLiteStatement));
    context[@"SQLiteStatement"] = [FMStatement class];

    class_addProtocol([FMResultSet class], @protocol(JSBSQLiteResultSet));
    context[@"SQLiteResultSet"] = [FMResultSet class];

    class_addProtocol([SearchManager class], @protocol(JSBSearchManager));
    context[@"SearchManager"] = [SearchManager class];

#if !TARGET_OS_IPHONE
    class_addProtocol([AppDelegate class], @protocol(JSBApplication));
    context[@"Application"] = [AppDelegate class];
#else
    class_addProtocol([AppDelegate_iPad class], @protocol(JSBApplication));
    context[@"Application"] = [AppDelegate_iPad class];
#endif

    NSString *agentToolsScript =
    @"(function(){\n"
    @"  var tools = globalThis.__agent_tools_store__ || {};\n"
    @"  globalThis.__agent_tools_store__ = tools;\n"
    @"  function register(tool){ if(!tool||!tool.name){ return; } tools[tool.name]=tool; }\n"
    @"  function normalizeString(v, fallback){\n"
    @"    if (v === null || v === undefined) { return fallback || ''; }\n"
    @"    var s = String(v).trim();\n"
    @"    if (!s || s === 'null' || s === '(null)' || s === '<null>' || s === 'nil' || s === 'undefined') { return fallback || ''; }\n"
    @"    return s;\n"
    @"  }\n"
    @"  function normalizeNullable(v){\n"
    @"    var s = normalizeString(v, '');\n"
    @"    return s ? s : null;\n"
    @"  }\n"
    @"  function ensureBuiltins(){\n"
    @"    if (tools['mn.search']) { return; }\n"
    @"    if (!(globalThis.Application && Application.sharedInstance)) { return; }\n"
    @"    var app = null;\n"
    @"    try { app = Application.sharedInstance(); } catch (e) { return; }\n"
    @"    var mgr = app && app.searchManager ? app.searchManager : null;\n"
    @"    if (!mgr) { return; }\n"
    @"    register({\n"
    @"      name: 'mn.search',\n"
    @"      info: {name:'mn.search', kind:'search', scopes:['topic','all','page'], description:'Search notes or pages via SearchManager'},\n"
    @"      run: function(input){\n"
    @"        input = input || {};\n"
    @"        var app2 = null;\n"
    @"        try { app2 = Application.sharedInstance(); } catch (e2) {}\n"
    @"        var mgr2 = app2 && app2.searchManager ? app2.searchManager : null;\n"
    @"        if (!mgr2) { throw new Error('search_manager_unavailable'); }\n"
    @"        var q = normalizeString(input.query, '');\n"
    @"        var scope = normalizeString(input.scope, 'topic').toLowerCase();\n"
    @"        if (scope !== 'topic' && scope !== 'all' && scope !== 'page') { scope = 'topic'; }\n"
    @"        var titleOnly = !!input.titleOnly;\n"
    @"        var beginsWith = !!input.beginsWith;\n"
    @"        var limit = (input.limit != null) ? input.limit : 50;\n"
    @"        var noteOnly = (input.noteOnly != null) ? !!input.noteOnly : false;\n"
    @"        var topicid = normalizeNullable(input.topicid);\n"
    @"        if (scope === 'page') {\n"
    @"          return mgr2.searchPage(q, beginsWith, limit);\n"
    @"        }\n"
    @"        if (input.useFts) {\n"
    @"          return mgr2.searchFts3Text(q, titleOnly, topicid, limit, noteOnly);\n"
    @"        }\n"
    @"        return mgr2.searchText(q, titleOnly, topicid, beginsWith, limit);\n"
    @"      }\n"
    @"    });\n"
    @"  }\n"
    @"  function list(){ ensureBuiltins(); return Object.keys(tools).map(function(k){ return tools[k].info || {name:k}; }); }\n"
    @"  function get(name){ ensureBuiltins(); return tools[name]; }\n"
    @"  async function run(name, input){ ensureBuiltins(); var t=tools[name]; if(!t){ throw new Error('Tool not found: '+name); } return t.run? t.run(input): null; }\n"
    @"  globalThis.AgentTools = {register:register, list:list, get:get, run:run};\n"
    @"  ensureBuiltins();\n"
    @"})();\n";
    [context evaluateScript:agentToolsScript];
#pragma clang diagnostic pop
}

@end
