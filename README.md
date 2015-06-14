<p align="center"><img src="https://cloud.githubusercontent.com/assets/6678136/8150781/4a39f442-134b-11e5-8414-d2f4a583f5f7.png" alt="TriceKit logo" /></p>

This is the TriceKit iOS SDK that delivers delightful experiences in conjunction with the [TriceKit management system](http://tricekit.com).

## Installation

The easiest way to install the SDK is using [CocoaPods](http://cocoapods.org).

In your Podfile

```ruby
pod 'TriceKit'
```

In your AppDelegate.m during application launch set your API key and username that is provided from the TriceKit CMS:

```objective-c
[[TriceSettings sharedInstance] setApiKey:<#API_KEY#>];
[[TriceSettings sharedInstance] setUsername:<#USERNAME#>];
```

Additionally, you may configure the TriceKit SDK further by changing the settings provided in TriceSettings:

```objective-c
[[TriceSettings sharedInstance] setDebugEnabled:YES]; // Log messages out to console.
[[TriceSettings sharedInstance] setUseProductionServer:NO]; // Use the testing server.
```

## Zones, Triggers, Actions

```objective-c
@property (nonatomic, strong) TriceTriggerManager *triggerManager;

self.triggerManager = [TriceTriggerManager new];
[self.triggerManager startMonitoringZones];
```

To allow TriceKit to handle local notifications that are generated from it, add to your AppDelegate.m:

```objective-c
[TriceAppDelegateProxy handleTriceKitLocalNotifications];
```

### Example Tasks

###### Creating a new beacon zone, trigger and action programmatically:

This will fire a local notification on entering the zone every 10 seconds. If TriceKit is handling its own local notifications then an alert will display upon receiving the notification.

```objective-c
TriceBeacon *beacon = [TriceBeacon beaconWithMajor:<#(CLBeaconMajorValue)#> minor:<#(CLBeaconMinorValue)#> proximityUuid:<#(NSUUID *)#>];
TriceZone *zone = [TriceBeaconZone beaconZoneWithBeacon:beacon proximity:CLProximityImmediate];
TriceTrigger *trigger = [TriceTrigger triggerWithEvent:TriceTriggerEventEnter frequency:10 limit:0];

[trigger addAction:[TriceAction pushNotificationAction:^(UILocalNotification *notification) {
    notification.alertBody = @"Entered!";
}]];

[zone addTrigger:trigger];
[self.triggerManager addZone:zone];
```

###### Creating a new geo coordinate zone programmatically:

Creating triggers, actions and attaching are ommitted. See creating beacon zone for this sample.

```objective-c
NSArray *coordinates = @[
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.290923539344, 174.77681817021)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.291038412930, 174.77658750024)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.291215761226, 174.77654726710)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.291294358613, 174.77689058986)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.291294358613, 174.77718295064)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.291104918598, 174.77717490401)],
    [NSValue valueWithMKCoordinate:CLLocationCoordinate2DMake(-41.290988029803, 174.77703811135)]
];
TriceZone *geoPolygonZone = [TriceGeoPolygonZone geoPolygonZoneWithCoordinates:coordinates];
```

###### Creating a new geo radius zone programmatically:

Creating triggers, actions and attaching are ommitted. See creating beacon zone for this sample.

```objective-c
CLLocationCoordinate2D coordinate = CLLocationCoordinate2DMake(-41.290384160865536, 174.77760503743434);
TriceZone *geoRadiusZone = [TriceGeoRadiusZone geoRadiusZoneWithCoordinate:coordinate radius:20];
```

###### Adding a custom action to a zone+trigger created in CMS:

This is assuming you have set up both a zone and trigger in the CMS.

```objective-c
// Using the unique identifier ensures we are adding this action to only one specific trigger.
TriceObjectDescriptor *zoneDescriptor = [TriceObjectDescriptor descriptorWithUid:<#(NSString *)#>];
TriceObjectDescriptor *triggerDescriptor = [TriceObjectDescriptor descriptorWithUid:<#(NSString *)#>];

TriceAction *customAction = [TriceAction action:^{
    // This block gets executed when the trigger matching the description fires.
    NSLog(@"Wooooo!");
}];

[self.triggerManager addAction:customAction toTrigger:triggerDescriptor zone:zoneDescriptor];
```

###### Adding a custom action to many zones and triggers

In this example we are displaying an alert whenever someone enters any one of the meeting rooms, and a different alert when they leave. It is assumed that in the CMS the names of the zones are "Meeting room 1", "Meeting room 2", "Meeting room 3", ...

```objective-c
// Describe all zones in the meeting rooms.
TriceObjectDescriptor *meetingRoomZones = [TriceObjectDescriptor descriptorWithKey:@"name" passingTest:^BOOL(NSString *name) {
    return [name hasPrefix:@"Meeting room"];
}];
// All enter triggers.
TriceObjectDescriptor *enterTriggerDescriptor = [TriceObjectDescriptor descriptorWithKey:@"event" passingTest:^BOOL(NSNumber *eventValue) {
    TriceTriggerEvent event = (TriceTriggerEvent)[eventValue integerValue];
    return (event == TriceTriggerEventEnter);
}];
// All exit triggers.
TriceObjectDescriptor *exitTriggerDescriptor = [TriceObjectDescriptor descriptorWithKey:@"event" passingTest:^BOOL(NSNumber *eventValue) {
    TriceTriggerEvent event = (TriceTriggerEvent)[eventValue integerValue];
    return (event == TriceTriggerEventExit);
}];

TriceAction *showEnterAlert = [TriceAction action:^{
    [TriceAlert displayOkAlertWithTitle:@"Welcome to the meeting!" message:nil okAction:nil];
}];

TriceAction *showExitAlert = [TriceAction action:^{
    [TriceAlert displayYesNoAlertWithTitle:@"Was this meeting productive for you?" message:nil yesAction:^{
        [TriceAlert displayOkAlertWithTitle:@"Good, we hope to see you next time!" message:nil okAction:nil];
    } noAction:^{
        [TriceAlert displayOkAlertWithTitle:@"Lets work on improving that." message:@"We will collect this response to improve your experience." okAction:^{
            // Do further actions to collect response, send request to server, perhaps display a new view controller...
        }];
    }];
}];

[self.triggerManager addAction:showEnterAlert toTrigger:enterTriggerDescriptor zone:meetingRoomZones];
[self.triggerManager addAction:showExitAlert toTrigger:exitTriggerDescriptor zone:meetingRoomZones];
```

###### Observing events:

There are several NSNotification objects posted from TriceKit which are free to observe and react to.

TriceZone objects post a TriceZoneStateDidChangeNotification whenever their state property changes.

TriceTrigger objects post both a TriceTriggerWillFireNotification and TriceTriggerDidFireNotification when they are about to, and have just executed their actions. During the WillFire notification you are able to cancel the triggers firing sequence.

```objective-c
- (void)addNotificationObservers
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(zoneDidChangeState:) name:TriceZoneStateDidChangeNotification object:nil];
    [center addObserver:self selector:@selector(triggerWillFire:) name:TriceTriggerWillFireNotification object:nil];
    [center addObserver:self selector:@selector(triggerDidFire:) name:TriceTriggerDidFireNotification object:nil];
}

- (void)zoneDidChangeState:(NSNotification *)notification
{
    // Zone was entered or exited, relevant triggers may fire.
    
    TriceZone *zone = notification.object;
    
    if (zone.state == TriceZoneStateEntered || zone.state == TriceZoneStateDwelling) { // We are now inside!
        self.view.backgroundColor = [UIColor greenColor];
    } else { // We are now outside!
        self.view.backgroundColor = [UIColor redColor];
    }
}

- (void)triggerWillFire:(NSNotification *)notification
{
    TriceTrigger *trigger = notification.object;
    if (/* we don't actually want this trigger to fire yet */ YES) {
        [trigger cancelFiring];
    }
}

- (void)triggerDidFire:(NSNotification *)notification
{
    TriceTrigger *trigger = notification.object;
    NSLog(@"A trigger fired! %@", trigger);
}
```

###### Pausing or stopping notifications:

You can temporarily pause notifications by displaying by registering for the TriceTriggerWillFireNotification notification and cancelling all triggers from firing. See example above about how to do this.

To stop for a more extended period, then it is recommended that you stop TriceTriggerManager from monitoring by calling:

```objective-c
[self.triggerManager stopMonitoringZones];
```

###### Offline support:

The latest set of zones that are nearby can be preserved between application launches without needing to be online.

```objective-c
self.triggerManager.allowEncodingZonesToDisk = YES;
```

