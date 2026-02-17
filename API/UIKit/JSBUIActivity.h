#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBUIActivity <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

//+ (UIActivityCategory)activityCategory;

- (NSString *)activityType;
- (NSString *)activityTitle;
- (UIImage *)activityImage;
- (BOOL)canPerformWithActivityItems:(NSArray *)activityItems;
- (void)prepareWithActivityItems:(NSArray *)activityItems;
- (UIViewController *)activityViewController;
- (void)performActivity;
- (void)activityDidFinish:(BOOL)completed;

#pragma clang diagnostic pop

@end
