#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBUIAccelerometer <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#if !TARGET_OS_XR
@property (nonatomic, readonly) UIAccelerationValue y;
@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly) UIAccelerationValue z;
@property (nonatomic, readonly) UIAccelerationValue x;
#endif
@property (nonatomic) NSTimeInterval updateInterval;
@property (nonatomic, assign) id delegate;

#if !TARGET_OS_XR
+ (UIAccelerometer *)sharedAccelerometer;
#endif

#pragma clang diagnostic pop

@end
