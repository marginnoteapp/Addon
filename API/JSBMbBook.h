#import "MbBook.h"

@import Foundation;
@import JavaScriptCore;

@protocol JSBMbBook <JSExport>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic,readonly,getter=currenttopicid) NSString * currentTopicId;
@property (nonatomic,readonly,getter=lastvisit) NSDate * lastVisit;
@property (nonatomic,readonly,getter=md5real) NSString * docMd5;
@property (nonatomic,readonly) NSString * pathFile;
@property (nonatomic,readonly) NSString * fullPathFileName;
@property (nonatomic,readonly,getter=bookTitle) NSString * docTitle;
@property (nonatomic,readonly) NSInteger pageCount;
- (NSArray*)textContentsForPageNo:(NSInteger)pageNo;
- (NSArray*)tocAll;   // 获取文档目录 (Table of Contents)
#pragma clang diagnostic pop

@end
