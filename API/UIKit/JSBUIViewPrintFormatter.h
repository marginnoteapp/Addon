#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBUIPrintFormatter;

@protocol JSBUIViewPrintFormatter <JSExport, JSBUIPrintFormatter>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#pragma clang diagnostic pop

@end
