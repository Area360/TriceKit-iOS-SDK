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
 *  TriceSettings is used as a singleton object that holds configuration values for the TriceKit SDK.
 */
@interface TriceSettings : NSObject

/**
 *  Gets the shared instance used for TriceKit settings.
 *
 *  @return The shared instance.
 */
+(instancetype)sharedInstance;

/**
 *  Required. The username value that is provided on the TriceKit CMS.
 */
@property (nonatomic, copy) NSString *username;

/**
 *  Required. The API Key value that is provided on the TriceKit CMS.
 */
@property (nonatomic, copy) NSString *apiKey;

/**
 *  Whether or not the TriceKit SDK should log output to console. Default is NO.
 */
@property (nonatomic, assign) BOOL debugEnabled;

/**
 *  YES to use the TriceKit production server, otherwise NO to use the testing server. Default is YES. This property will only be read once, so is required to be set during application launch in order to use the testing server.
 */
@property (nonatomic, assign) BOOL useProductionServer;

/**
 *  An optional notification configuration block that will be applied to all local notifications that are constructed through the TriceKit CMS. Default is nil.
 */
@property (nonatomic, copy) void (^localNotificationConfigurationBlock)(UILocalNotification *notification);

@end
