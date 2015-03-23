//
//  TriceSettings.h
//  TriceKit
//
//  Created by Jake Bellamy on 11/03/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UILocalNotification.h>

/**
 *  TriceSettings is a single abstract class that declares preference methods for configuring the TriceKit SDK. You should subclass this class and override all of the declared public methods, without calling the superclass implementation as every abstract method simply invokes doesNotRecogniseSelector:. TriceKit will automatically find and use your subclass if it is defined. If you subclass this class more than once, the class that will be used is undefined.
 */
@interface TriceSettings : NSObject

/**
 *  The username value that is provided on the TriceKit CMS.
 *
 *  @return The username API value.
 */
+(NSString *)username;

/**
 *  The API Key value that is provided on the TriceKit CMS.
 *
 *  @return The API Key value.
 */
+(NSString *)apiKey;

/**
 *  Whether or not the TriceKit SDK should log output to console.
 *
 *  @return YES if debugging is enabled, otherwise NO.
 */
+(BOOL)debugEnabled;

/**
 *  A notification configuration block that will be applied to all local notifications that are constructed through the TriceKit CMS.
 *
 *  @return A block that configures the local notification. Returning nil indicates no configuration.
 */
+(void (^)(UILocalNotification *))localNotificationConfigurationBlock;

@end
