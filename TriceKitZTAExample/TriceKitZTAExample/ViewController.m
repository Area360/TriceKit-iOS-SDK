//
//  ViewController.m
//  TriceKitZTAExample
//
//  Created by Jake Bellamy on 5/10/15.
//  Copyright © 2015 STQRY. All rights reserved.
//

#import "ViewController.h"
#import <TriceKit/TriceTriggerManager.h>

@interface ViewController ()
@property (nonatomic, strong) TriceTriggerManager *triggerManager;
@property (nonatomic, weak) IBOutlet UILabel *mainLabel;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.triggerManager = [TriceTriggerManager new];
    [self.triggerManager startMonitoringZones];
    
    [self setupEnterBeaconZone];
    [self setupExitBeaconZone];
    [self setupCMSAction];
}

- (void)setupEnterBeaconZone
{
    CLBeaconMajorValue major = 0x4277;
    CLBeaconMinorValue minor = 0x6efa;
    NSUUID *proximityUUID = [[NSUUID alloc] initWithUUIDString:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
    
    TriceBeacon *beacon = [TriceBeacon beaconWithMajor:major minor:minor proximityUuid:proximityUUID];
    TriceZone *zone = [TriceBeaconZone beaconZoneWithBeacon:beacon proximity:CLProximityImmediate];
    TriceTrigger *trigger = [TriceTrigger triggerWithEvent:TriceTriggerEventEnter frequency:10 limit:0];
    
    [trigger addAction:[TriceAction pushNotificationAction:^(UILocalNotification *notification) {
        self.mainLabel.text = @"Entered!";
        notification.alertBody = @"Entered!";
    }]];
    
    [zone addTrigger:trigger];
    [self.triggerManager addZone:zone];
}

- (void)setupExitBeaconZone
{
    CLBeaconMajorValue major = 0x4277;
    CLBeaconMinorValue minor = 0x6efa;
    NSUUID *proximityUUID = [[NSUUID alloc] initWithUUIDString:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
    
    TriceBeacon *beacon = [TriceBeacon beaconWithMajor:major minor:minor proximityUuid:proximityUUID];
    TriceZone *zone = [TriceBeaconZone beaconZoneWithBeacon:beacon proximity:CLProximityImmediate];
    TriceTrigger *trigger = [TriceTrigger triggerWithEvent:TriceTriggerEventExit frequency:10 limit:0];
    
    [trigger addAction:[TriceAction pushNotificationAction:^(UILocalNotification *notification) {
        self.mainLabel.text = @"Exited!";
        notification.alertBody = @"Exited!";
    }]];
    
    [zone addTrigger:trigger];
    [self.triggerManager addZone:zone];
}

- (void)setupCMSAction
{
    NSString *zoneUid = @"";
    NSString *triggerUid = @"";
    
    // Using the unique identifier ensures we are adding this action to only one specific trigger.
    TriceObjectDescriptor *zoneDescriptor = [TriceObjectDescriptor descriptorWithUid:zoneUid];
    TriceObjectDescriptor *triggerDescriptor = [TriceObjectDescriptor descriptorWithUid:triggerUid];
    
    TriceAction *customAction = [TriceAction action:^{
        // This block gets executed when the trigger matching the description fires.
        NSLog(@"Wooooo!");
        self.mainLabel.text = [NSString stringWithFormat:@"CMS Trigger %@ fired!", triggerUid];
    }];
    
    [self.triggerManager addAction:customAction toTrigger:triggerDescriptor zone:zoneDescriptor];
}

@end
