#import "MbAppDelegate.h"
#import "JSBMindMapView.h"
#import "JSBUIViewController.h"

@import Foundation;
@import JavaScriptCore;

@protocol JSBDocumentController <JSExport,JSBUIViewController>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@property (nonatomic, readonly, getter=currBook) MbBook* document;
@property (nonatomic, readonly, getter=currentBookMd5) NSString* docMd5;
@property (nonatomic, readonly, getter=currTopicId) NSString* notebookId;
@property (nonatomic, readonly, getter=focusNote) MbBookNote* focusNote;
@property (nonatomic, readonly, getter=visibleFocusNote) MbBookNote* visibleFocusNote;
@property (nonatomic, readonly, getter=selectionText) NSString* selectionText;
@property (nonatomic, readonly, getter=lastFocusNote) MbBookNote* lastFocusNote;
@property (nonatomic, readonly) int currPageNo;
@property (nonatomic, readonly) int currPageIndex;
@property (nonatomic, readonly) BOOL isSelectionText;

#pragma clang diagnostic pop
- (NSData*)imageFromSelection;
- (NSData*)imageFromFocusNote;
- (void)setPageAtIndex:(NSUInteger)index;
- (NSArray<NSNumber*>*)indicesFromPageNo:(NSInteger)pageNo;
- (NSInteger)indexFromPageNo:(NSInteger)pageNo;
- (NSInteger)pageNoFromIndex:(NSInteger)index;
- (id)highlightFromSelection;

@end
