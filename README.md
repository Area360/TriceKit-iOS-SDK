<p align="center" >
<img src="https://cloud.githubusercontent.com/assets/1875075/6406263/27f07508-be93-11e4-862c-33d9f8d19138.png" alt="TriceKit" title="TriceKit">
</p>

Overview of TriceKit goes here. Coming soon

## Installation

The easiest way to install the SDK is using [CocoaPods](http://cocoapods.org).

In your Podfile

```ruby
pod 'TriceKit'
```

In your AppDelegate.m set your API key and username that is provided from the TriceKit CMS.
```objective-c
[[TriceSettings sharedInstance] setApiKey:<#API_KEY#>];
[[TriceSettings sharedInstance] setUsername:<#USERNAME#>];
```

Additionally, you may add TriceDebug with a boolean value of YES to enable the SDK to log information to the console.

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