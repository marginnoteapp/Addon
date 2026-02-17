#import <Foundation/NSObject.h>

@import Foundation;
@import JavaScriptCore;

@protocol JSBNSObject;

@protocol JSBNSJSONSerialization <JSExport, JSBNSObject>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

+ (BOOL)isValidJSONObject:(id)obj;
+ (NSData *)dataWithJSONObject:(id)obj options:(NSJSONWritingOptions)opt;
+ (id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt;

#pragma clang diagnostic pop

@end
