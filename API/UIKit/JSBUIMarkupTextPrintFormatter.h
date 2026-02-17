#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBUIPrintFormatter;

@protocol JSBUIMarkupTextPrintFormatter <JSExport, JSBUIPrintFormatter>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

- (id)initWithMarkupText:(NSString *)markupText;

#pragma clang diagnostic pop

@end
