//
//  AppDelegate.m
//  TriceKitMappingExample
//
//  Created by Jake Bellamy on 29/02/16.
//  Copyright © 2016 STQRY. All rights reserved.
//

#import "AppDelegate.h"
#import <TriceKit/TriceSettings.h>

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TriceSettings sharedInstance].username = <#API Username#>;
    [TriceSettings sharedInstance].apiKey = <#API Key#>;
    return YES;
}

@end
