//
//  QBPopupMenu.h
//  QBPopupMenu
//
//  Created by Tanaka Katsuma on 2013/11/22.
//  Copyright (c) 2013年 Katsuma Tanaka. All rights reserved.
//

#import "MbAppDelegate.h"
#import "JSBUIView.h"
@import Foundation;
@import JavaScriptCore;

#import "JSBPopupMenuItem.h"

@class QBPopupMenu;
@class QBPopupMenuItemView;
@class QBPopupMenuPagenatorView;


@protocol JSBPopupMenu <JSExport, JSBUIView>


@property (nonatomic, assign, getter = isVisible, readonly) BOOL visible;
@property (nonatomic, copy) NSArray *items;
@property (nonatomic, readonly) NSUInteger arrowDirection;

@property (nonatomic, readonly) CGRect targetWinRect;

+ (instancetype)currentMenu;
+ (instancetype)popupMenuWithItems:(NSArray *)items;

- (void)dismissAnimated:(BOOL)animated;
- (void)updateWithTargetRect:(CGRect)targetRect;
- (void)showInView:(UIView *)view targetRect:(CGRect)targetRect animated:(BOOL)animated;

@end
