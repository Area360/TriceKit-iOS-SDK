This is the TriceKit iOS SDK that delivers delightful experiences in conjunction
with the [TriceKit management system](http://tricekit.com).

# Table of Contents
 - [Usage (iOS)](#usage-iOS)
  - [Installation](#installation)
  - [Configuration](#configuration)
  - [Starting TriceKit](#starting-triceKit)
  - [Adding actions to triggers](#adding-actions-to-triggers)
  - [Setting and fetching user data](#setting-and-fetching-user-data)
 - [Features](#features)
  - [User data](#user-data)
   - [What is user data?](#what-is-user-data)
   - [How does it work?](#how-does-it-work)
   - [How can you use it?](#how-can-you-use-it)
    - [URL callback](#url-callback)
    - [Trigger segmentation (coming soon)](#trigger-segmentation-coming-soon)
   - [Use case example](#use-case-example)

# Usage (iOS)

## Installation

Using TriceKit in an existing project simply requires adding TriceKit.framework
to the project.  You may then need to make some additional changes to the
project configuration:

* The following frameworks are required as dependencies of your app:
 * `CoreBluetooth.framework`: Needed to obtain beacon battery levels.
 * `CoreLocation.framework`: Needed to detect locations and beacons.
 * `CoreTelephony.framework`: Needed to detect changes in network connectivity.
 * `libstdc++.tbd`: The core of TriceKit is written in C++.
 * `SystemConfiguration.framework`: Needed to detect proximity to Wi-Fi
   networks.
 * `TriceKit.framework`: TriceKit itself.
* Bitcode must be disabled:
 * This is configured through the target Build Settings; set "Enable Bitcode" to
   "No".
* You may have to update the framework search paths to include the location
  where `TriceKit.framework` is stored:
 * This is configured through the target Build Settings; add the path to the
   "Framework Search Paths" list.

Additionally, TriceKit needs to perform background location monitoring to avoid
using battery power scanning for beacons when there are no beacons expected to
be nearby.  This is enabled through the `Info.plist` file for the app:

* `NSLocationAlwaysUsageDescription` and `NSLocationWhenInUseUsageDescription`:
  These contain messages shown to the user when TriceKit (or the app) uses
  location services in the background and foreground respectively.
* `UIBackgroundModes` (shown as "Required background modes" in Xcode): This
  needs to have the following two values added:
 * bluetooth-central: Needed to obtain beacon battery levels while the app is in
   the background.
 * location: Needed to determine what beacons are likely to be nearby (and thus
   whether to register for beacon notifications) when the app is in the
   background.

## Configuration

TriceKit configuration is done through the `TriceKitConfig.plist` file.  This
contains two properties: trice_api_key, and trice_username.  These values are
obtained through the TriceKit CMS.

## Starting TriceKit

Typically, the application object will hold the reference to TriceKit, with the
TriceKit object being constructed during application initialization.
```objective-c
-(id)init
{
    self = [super init];
    if (self)
    {
        self->_triceKitManager = [[TKTriceKitManager alloc] init];
    }
    return self;
}
```

Typically, TriceKit will not be started right away.  For example, a permissions
screen may be shown explaining the required permissions if the app detects that
some permissions are missing.  Once it has been determined that TriceKit should
start, simply call `start` on the `TKTriceKitManager` instance:
```objective-c
[[ZTADemoApplication demoApplication].triceKitManager start];
```

This is an asynchronous function call.  The progress of TriceKit starting can be
watched via KVO on the `triceKitState` property of the `TKTriceKitManager`
instance.

## Adding actions to triggers

This is best done by detecting when triggers are added in response to data
obtained from the server.  To do this, implement the `TKTriceKitManagerRemoteUpdateDelegate`
protocol, and set the remoteUpdateDelegate on the `TKTriceKitManager` instance:
```objective-c
[ZTADemoApplication demoApplication].triceKitManager.remoteUpdateDelegate = self;
```

When a trigger gets added, the `onTriggerAdded` method will be called.  Inside
this function, you can add a callback action to the triger:
```objective-c
-(void)onTriggerAdded:(TKTrigger *)trigger toZone:(TKZone *)zone
{
    [trigger attachAction:[[TriggerCallbackAction alloc] init]];
}
```

When the trigger fires, the `onActionTriggered` method of the action will be
called.

## Setting and fetching user data

Details of the user (such as a frequent flyer ID) can be set on the
`TKTriceKitManager` instance through the `userData` property.  This expects an
NSDictionary that can be converted to JSON via `NSJSONSerialization`.  When
this property is set, the user data is uploaded to the server.  The response
from the server (containing information uploaded via the user data REST API) is
made available through the KVO-compliant `sessionUserData` property on the
`TKTriceKitManager` instance.

# Features

## User data

### What is user data?

User data is meta data associated with users. user data can contain any data as
long as it follows the standard JSON format. Key/value pairs, objects and arrays
are supported.

### How does it work?

When the TriceKit SDK starts, it will initiate a session. Along with that
session you can provide user data.

> This could for example come from you login system.  When a user logs in, you
could initiate the TriceKit session with email, age and gender.

In order to associate ZTA pings to a user, each TriceKit organization specifies
a user primary key. By default the primary key is the device id. This means that if a
user changes their device, they will look like a new user to TriceKit. To solve
this, you are able to change the primary key [see user data REST API
documentation](http://tricekit.com/api/api_doc.html#user-data) to any of the
user data fields you provide. This can be for example your own `user id` from
your customer database. As soon as the primary key has been changed, TriceKit
will associate any subsequent sessions coming with that primary key to the same
user.

By using our [user data REST
API](http://tricekit.com/api/api_doc.html#user-data-single-user-data-post), you
will also be able to update user data for your users as well. User data does not
necessarily need to come from your app!

### How can you use it?

As soon as you start sending user data, you will be able to use that data to
personalize your user's experience!

#### URL callback

By setting up a URL Callback Action on TriceKit CMS (POST only), you will
receive along that POST any information regarding the Venue, Zone and Trigger
that trigger that action as well as all the user data. This allows you to
identify who is in the zone and triggered the action. This is highly valuable to
you as you will be able to personalize your customer experience.

#### Trigger segmentation (coming soon)

Once user data are available, you will be able to apply segmentation rules to
your Trigger. You can decide if a trigger fires for a particular user based on
user data. Segmentation rules will be available while creating/editing a trigger
on TriceKit CMS.

### Use case example

Primary key has been previously set to `user_id` ([see user data REST API documentation](https://tricekit.com/api/api_doc.html#user data-user data-primary-key-put)).

Example of information you get once the user logged into the app and that you
pass to TriceKit:

```
"name": "Anakin",
"age": "32",
"status": "Gold"
"user_id": "UIEWQ781AHX23"
```

If you want to know where your users spend their time in your venue based on
their age, it is now possible. The only thing you have to do is setup a URL
Callback Action with your own end point that you will have previously developed.

Here is an example of the JSON data that you will get along that POST event.

```
{
    "user_data": {
        "name": "Anakin",
        "age": "32",
        "status": "Gold",
        "user_id": "UIEWQ781AHX23"
    },
    "trigger": {
        "id": 439,
        "zones_uid": "321",
        "name": "Cafe trigger",
        "frequency": 420,
        "event": "enter"
    },
    "zone": {
      "id": 312,
      "name": "Cafe"
    },
    "venue_uid": "UWIEOQ32AHDBJ"
}
```

Now let's use segmentation to personalize the experience of your `GOLD` members.
In order to achieve that, you have to create a Trigger with segmentation rule.

Setting up a segmentation rule `status == "GOLD"` will restrict the trigger
from firing unless the user data field `status` exists and has the value
`GOLD`.
