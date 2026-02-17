#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBUIScreen <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic, readonly) CGRect bounds;
@property (nonatomic, readonly) CGRect applicationFrame;
@property (nonatomic, readonly, copy) NSArray *availableModes;
#if !TARGET_OS_XR
@property (nonatomic, retain) UIScreenMode *currentMode;
#endif
//@property (nonatomic, readonly, retain) UIScreenMode *preferredMode;
@property (nonatomic) CGFloat brightness;
//@property (nonatomic) BOOL wantsSoftwareDimming;
//@property (nonatomic) UIScreenOverscanCompensation overscanCompensation;
//@property (nonatomic, readonly, retain) UIScreen *mirroredScreen;
@property (nonatomic, readonly) CGFloat scale;

+ (NSArray *)screens;
#if !TARGET_OS_XR
+ (UIScreen *)mainScreen;
#endif

//- (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel;
- (UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates;

#pragma clang diagnostic pop

@end
