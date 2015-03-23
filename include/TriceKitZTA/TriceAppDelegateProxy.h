//
//  TriceAppDelegateProxy.h
//  TriceKit
//
//  Created by Jake Bellamy on 26/02/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIApplication.h>

/**
 *  TriceAppDelegateProxy is a proxy object which enables TriceKit to handle receiving UILocalNotification objects.
 */
@interface TriceAppDelegateProxy : NSProxy <UIApplicationDelegate>

/**
 *  Allows TriceKit to handle receiving local notifications that have been presented from within the TriceKit SDK. Notifications that have not come from the TriceKit SDK are ignored.
 *
 *  Specifically, this method sets the singleton UIApplication's delegate property to be an instance of this class. All delegate messages will automatically be forwarded on to the original application delegate, including application:didReceiveLocalNotification: if it is implemented. This method will also register for notifications if needed.
 *
 *  It is recommended that you call this method within application:willFinishLaunchingWithOptions: or application:didFinishLaunchingWithOptions: of your applications delegate.
 */
+(void)handleTriceKitLocalNotifications;

@end
