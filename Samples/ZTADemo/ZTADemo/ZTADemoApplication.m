// Copyright © 2016 Area360.
// All rights reserved.
//
// This file is released under the New BSD License (see NewBSDLicense.txt).

#import "ZTADemoApplication.h"
#import "TriceKit/TKTriceKitManager.h"
#import "TriceKit/TKTriceKitManagerDelegate.h"
#import "TriceKit/TKTrigger.h"
#import "TriceKit/TKZone.h"
#import "TriceKit/TKCallbackAction.h"

@class TKTriceKitManager;


@interface TriggerCallbackAction : NSObject<TKCallbackAction>

-(id)initWithMessage:(NSString *)message;
-(void)onActionTriggered;

@end


@implementation TriggerCallbackAction
{
    NSString *_triggerMessage;
}


-(id)initWithMessage:(NSString *)message
{
    self = [super init];
    if (self)
    {
        self->_triggerMessage = [message copy];
    }
    return self;
}


-(void)onActionTriggered
{
    NSLog(@"Trigger fired: %@", _triggerMessage);
}


@end


@interface ZTADemoApplication() <TKTriceKitManagerRemoteUpdateDelegate>

@end


@implementation ZTADemoApplication : UIApplication


-(id)init
{
    self = [super init];
    if (self)
    {
        self->_triceKitManager = [[TKTriceKitManager alloc] init];
        self->_triceKitManager.remoteUpdateDelegate = self;
    }
    return self;
}


+(ZTADemoApplication *)demoApplication
{
    return (ZTADemoApplication *)[UIApplication sharedApplication];
}


-(void)onTriggerAdded:(TKTrigger *)trigger toZone:(TKZone *)zone
{
    NSLog(@"Trigger %@ added to zone %@.", trigger.name, zone.name);
    NSString *actionMessage = [NSString stringWithFormat:@"zone %@, trigger %@", zone.name, trigger.name];
    TriggerCallbackAction *action = [[TriggerCallbackAction alloc] initWithMessage:actionMessage];
    [trigger attachAction:action];
}


@end
