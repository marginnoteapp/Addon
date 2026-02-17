#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBUIDynamicBehavior;

@protocol JSBUISnapBehavior <JSExport, JSBUIDynamicBehavior>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic, assign) CGFloat damping;

- (instancetype)initWithItem:(id <UIDynamicItem>)item snapToPoint:(CGPoint)point;

#pragma clang diagnostic pop

@end
