//
//  TriceAction.h
//  TriceKit
//
//  Created by Jake Bellamy on 30/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UILocalNotification.h>

NS_ASSUME_NONNULL_BEGIN

@class TriceTrigger;

/// A key used in the UILocalNotification userInfo dictionary, whose value is the trigger identifier that caused this action to fire.
extern NSString * const TriceLocalNotificationTriggerUidKey;

/**
 *  The HTTP method type used for a URL callback action.
 */
typedef NS_ENUM(NSInteger, TriceURLCallbackType){
    TriceURLCallbackTypeGET = 1,    ///< GET callback action.
    TriceURLCallbackTypePOST        ///< POST callback action.
};

/**
 *  The TriceAction class encapsulates an action that is executed upon firing of a TriceTrigger.
 */
@interface TriceAction : NSObject <NSCopying>

/// The trigger that this action has been attached to, or nil if it has not been attached yet.
@property (nonatomic, weak) TriceTrigger *trigger;

/**
 *  Creates a new TriceAction object.
 *
 *  @param action A void returning block with no parameters that will be executed upon firing of this action.
 *
 *  @return An initialized instance.
 */
+(instancetype)action:(void (^)())action;

/**
 *  Creates a new TriceAction object which posts a UILocalNotification.
 *
 *  @param notificationConfigurationBlock A void returning block that takes a single UILocalNotification object. Use this block to configure the notification that is presented. You are expected to set the alertBody and/or alertAction properties on the notification yourself here.
 *
 *  @return An initialized instance.
 */
+(instancetype)pushNotificationAction:(void (^)(UILocalNotification *notification))notificationConfigurationBlock;

/**
 *  Creates a new TriceAction object which sends a request to a url.
 *
 *  @param type       The HTTP method type to use. See TriceURLCallbackType
 *  @param url        The URL to send the request to.
 *  @param parameters Optional parameters that may be sent along with the request.
 *
 *  @return An initialized instance.
 */
+(instancetype)urlCallbackAction:(TriceURLCallbackType)type url:(NSString *)url parameters:(nullable NSDictionary *)parameters;

/**
 *  Executes this action.
 */
-(void)fire;

@end

NS_ASSUME_NONNULL_END
