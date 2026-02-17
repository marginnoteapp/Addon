#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>
@import JavaScriptCore;
#if !TARGET_OS_IPHONE
#import "PSTCollectionView.h"
#import "PSTCollectionViewLayout.h"
#endif

@protocol JSBUICollectionViewLayout;

@protocol JSBUICollectionViewFlowLayout <JSExport, JSBUICollectionViewLayout>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic) UIEdgeInsets sectionInset;
@property (nonatomic) CGSize headerReferenceSize;
@property (nonatomic) CGFloat minimumLineSpacing;
//@property (nonatomic) UICollectionViewScrollDirection scrollDirection;
@property (nonatomic) BOOL invalidateFlowLayoutAttributes;
@property (nonatomic) BOOL invalidateFlowLayoutDelegateMetrics;
@property (nonatomic) CGSize footerReferenceSize;
@property (nonatomic) CGSize itemSize;
@property (nonatomic) CGFloat minimumInteritemSpacing;

#pragma clang diagnostic pop

@end
