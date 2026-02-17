#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBUINavigationController;

@protocol JSBUIVideoEditorController <JSExport, JSBUINavigationController>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic) NSTimeInterval videoMaximumDuration;
@property (nonatomic, copy) NSString *videoPath;

+ (BOOL)canEditVideoAtPath:(NSString *)videoPath;

#pragma clang diagnostic pop

@end
