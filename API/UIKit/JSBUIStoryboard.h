#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBUIStoryboard <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

+ (UIStoryboard *)storyboardWithName:(NSString *)name bundle:(NSBundle *)storyboardBundleOrNil;

- (id)instantiateInitialViewController;
- (id)instantiateViewControllerWithIdentifier:(NSString *)identifier;

#pragma clang diagnostic pop

@end
