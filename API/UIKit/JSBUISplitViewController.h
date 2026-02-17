#import <UIKit/UIKit.h>

#import <UIKit/UIKit.h>
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBUISplitViewController <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

@property (nonatomic, readonly, retain) UISplitViewController *splitViewController;

#if !TARGET_OS_XR
- (void)splitViewController:(UISplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController:(UIPopoverController *)pc;
- (void)splitViewController:(UISplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem;
- (void)splitViewController:(UISplitViewController *)svc popoverController:(UIPopoverController *)pc willPresentViewController:(UIViewController *)aViewController;
- (BOOL)splitViewController:(UISplitViewController *)svc shouldHideViewController:(UIViewController *)vc inOrientation:(UIInterfaceOrientation)orientation;
#endif
- (NSUInteger)splitViewControllerSupportedInterfaceOrientations:(UISplitViewController *)splitViewController;
- (UIInterfaceOrientation)splitViewControllerPreferredInterfaceOrientationForPresentation:(UISplitViewController *)splitViewController;

#pragma clang diagnostic pop

@end
