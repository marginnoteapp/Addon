#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBNSStringDrawingContext <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic) CGFloat minimumScaleFactor;
@property (nonatomic, readonly) CGFloat actualScaleFactor;
@property (nonatomic) CGFloat minimumTrackingAdjustment;
@property (nonatomic, readonly) CGFloat actualTrackingAdjustment;
@property (nonatomic, readonly) CGRect totalBounds;

#pragma clang diagnostic pop

@end
