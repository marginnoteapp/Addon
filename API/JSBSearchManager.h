#import "SearchManager.h"

@import Foundation;
@import JavaScriptCore;

@protocol JSBSearchManager <JSExport>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (void)syncTopic:(NSString*)topicid force:(BOOL)force block:(JSValue*)block;
- (void)syncDBAfterMigration;
- (void)syncDB;

JSExportAs(searchTextWordList,
- (NSArray*)searchTextWordList:(NSArray*)textWordLst titleOnly:(BOOL)titleOnly topicid:(NSString*)topicid beginsWith:(BOOL)beginsWith limit:(NSInteger)limit);
JSExportAs(searchText,
- (NSArray*)searchText:(NSString*)searchText titleOnly:(BOOL)titleOnly topicid:(NSString*)topicid beginsWith:(BOOL)beginsWith limit:(NSInteger)limit);
JSExportAs(searchTextNoteOnly,
- (NSArray*)searchText:(NSString*)searchText titleOnly:(BOOL)titleOnly topicid:(NSString*)topicid beginsWith:(BOOL)beginsWith limit:(NSInteger)limit noteOnly:(BOOL)noteOnly);
JSExportAs(searchFts3Text,
- (NSArray*)searchFts3Text:(NSString*)text titleOnly:(BOOL)titleOnly topicid:(NSString*)topicid limit:(NSInteger)limit noteOnly:(BOOL)noteOnly);
JSExportAs(searchURLs,
- (NSArray*)searchURLs:(NSArray<NSString*>*)urls topicid:(NSString*)topicid);

- (BOOL)hasTopicIndex:(NSString*)topicid;
- (BOOL)hasVectorIndex:(NSString*)topicid;
- (BOOL)hasBookIndex:(NSString*)md5;
- (void)resetBookIndex;

JSExportAs(searchPage,
- (NSArray*)searchPage:(NSString*)searchText beginsWith:(BOOL)beginsWith limit:(NSInteger)limit);
JSExportAs(snippetForFts3RowId,
- (NSString*)snippetForFts3RowId:(NSInteger)rowid);
JSExportAs(snippetForPageRowId,
- (NSDictionary*)snippetForPageRowId:(NSInteger)rowid);

JSExportAs(findSimilarNotes,
- (NSArray<NSDictionary *> *)findSimilarNotes:(NSData *)queryVector inTopic:(NSString *)topicId topK:(NSInteger)k);
JSExportAs(batchFindSimilarNotes,
- (NSArray<NSArray<NSDictionary *> *> *)batchFindSimilarNotes:(NSArray<NSData *> *)queryVectors inTopic:(NSString *)topicId topK:(NSInteger)k);
JSExportAs(findSimilarNotesHybrid,
- (NSArray<NSDictionary *> *)findSimilarNotesHybrid:(NSData *)queryVector queryText:(NSString *)queryText inTopic:(NSString *)topicId topK:(NSInteger)k semanticWeight:(float)semanticWeight bm25Weight:(float)bm25Weight);

- (NSDictionary<NSString *, NSData *> *)loadVectorCacheForTopic:(NSString *)topicId;
- (void)syncTopicVectors:(NSString *)topicId force:(BOOL)force completion:(JSValue*_Nullable)completion;
- (void)invalidateVectorCacheForTopics:(NSArray<NSString *> *)topicIds;

@property (nonatomic,readonly)  BOOL ftsIndexing;
@property (nonatomic,readonly)  BOOL propIndexing;
@property (nonatomic,readonly)  BOOL vectorIndexing;

#pragma clang diagnostic pop

@end
