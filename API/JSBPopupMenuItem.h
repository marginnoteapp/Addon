//
//  QBPopupMenuItem.h
//  QBPopupMenu
//
//  Created by Tanaka Katsuma on 2013/11/22.
//  Copyright (c) 2013年 Katsuma Tanaka. All rights reserved.
//

#import "MbAppDelegate.h"
#import "JSBUIView.h"
@import Foundation;
@import JavaScriptCore;

@protocol JSBPopupMenuItem <JSExport, NSObject>

@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) NSString *actionString;

@end
