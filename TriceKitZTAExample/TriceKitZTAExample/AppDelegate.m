//
//  AppDelegate.m
//  TriceKitZTAExample
//
//  Created by Jake Bellamy on 5/10/15.
//  Copyright © 2015 STQRY. All rights reserved.
//

#import "AppDelegate.h"
#import <TriceKit/TriceKitShared.h>
#import <TriceKit/TriceKitZTA.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TriceSettings sharedInstance].apiKey = <#API_KEY#>;
    [TriceSettings sharedInstance].username = <#USERNAME#>;
    [TriceSettings sharedInstance].debugEnabled = YES;
    [TriceSettings sharedInstance].useProductionServer = YES;
    
    [TriceAppDelegateProxy handleTriceKitLocalNotifications];
    
    return YES;
}

@end
