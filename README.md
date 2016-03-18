This is the TriceKit iOS SDK that delivers delightful experiences in conjunction
with the [TriceKit management system](http://tricekit.com).

# Table of Contents
- [Usage (iOS)](#ios-usage)
    - [Installation](#ios-installation)
    - [Configuration](#ios-configuration)
    - [Starting TriceKit](#ios-starting)
    - [Adding actions to triggers](#ios-add-action)
        - [Adding a local action](#ios-local-action)
        - [Handling server actions](#ios-server-action)
    - [Setting and fetching user data](#ios-user-data)
- [Usage (Android)](#android-usage)
    - [Installation](#android-installation)
    - [Configuration](#android-configuration)
    - [System requirements](#android-requirements)
    - [Starting TriceKit](#android-starting)
    - [Adding actions to triggers](#android-add-action)
        - [Adding a local action](#android-local-action)
        - [Handling server actions](#android-server-action)
    - [Setting and fetching user data](#android-user-data)
- [Features](#features)
    - [User data](#feature-user-data)
        - [What is user data?](#feature-user-data-what-is-it)
        - [How does it work?](#feature-user-data-how-does-it-work)
        - [How can you use it?](#feature-user-data-how-can-you-use-it)
            - [URL callback](#feature-user-data-url-callback)
            - [Trigger segmentation (coming soon)](#feature-user-data-trigger-segmentation)
        - [Use case example](#feature-user-data-examples)

# <a name="ios-usage"></a>Usage (iOS)

## <a name="ios-installation"></a>Installation

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

## <a name="ios-configuration"></a>Configuration

TriceKit configuration is done through the `TriceKitConfig.plist` file.  This
contains two properties: trice_api_key, and trice_username.  These values are
obtained through the TriceKit CMS.

## <a name="ios-starting"></a>Starting TriceKit

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

## <a name="ios-add-action"></a>Adding actions to triggers

There are two ways of handling actions in TriceKit.

### <a name="ios-local-action"></a>Adding a local action

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

### <a name="ios-server-action"></a>Handling server actions

If you have set up a notification action on our TriceKit CMS, you will be able
to handle that server action by registering for notifications when triggers of a
particular type fire.  For example, if a local notification should be shown to
the user, a handler object can be defined:

```objective-c
@interface LocalNotifier : NSObject<TKCallbackActionType>
@end

@implementation LocalNotifier

-(void)onActionTypeTriggered:(NSString *)actionType metadata:(NSDictionary *)metadata
{
    // Handle your notification action the way you want here.  For
    // example, a local notification can be shown to the user.
    NSObject *messageObj = [metadata objectForKey:@"message"];
    if (messageObj && [messageObj isKindOfClass:[NSString class]])
    {
        UILocalNotification *notification = [[UILocalNotification alloc] init];
        notification.alertBody = (NSString *)messageObj;

        [[ZTADemoApplication demoApplication] presentLocalNotificationNow:notification];
    }
}

@end
```

To get notifications for when the action is fired, register this object against
the TriceKitManager:

```objective-c
[[ZTADemoApplication demoApplication].triceKitManager registerCallback:[[LocalNotifier alloc] init]
                                                         forActionType:kTKLocalNotificationActionType];
```

Example of the Notification Action metadata:

```json
{
    "message": "my notification"
}
```

You will soon be able to create your own action type on our CMS.

## <a name="ios-user-data"></a>Setting and fetching user data

Details of the user (such as a frequent flyer ID) can be set on the
`TKTriceKitManager` instance through the `userData` property.  This expects an
NSDictionary that can be converted to JSON via `NSJSONSerialization`.  When
this property is set, the user data is uploaded to the server.  The response
from the server (containing information uploaded via the user data REST API) is
made available through the KVO-compliant `sessionUserData` property on the
`TKTriceKitManager` instance.

# <a name="android-usage"></a>Usage (Android)

## <a name="android-installation"></a>Installation

Using TriceKit in you Android Studio project required both tricekit-android-sdk.aar
and tricekit-shared-android-sdk.aar. Copy these two libraries in your libs folder.
You will then need to modify you app build.gradle:

```
android {
  ...

  repositories {
      flatDir {
          dirs 'libs'
      }
  }
}

dependencies {

    ...

    // Location Services
    compile 'com.google.android.gms:play-services-location:8.4.0'

    // Gson
    compile 'com.google.code.gson:gson:2.4'

    // OkHttp: http://square.github.io/okhttp/
    compile 'com.squareup.okhttp:okhttp:2.5.0'
    compile 'com.squareup.okhttp:okhttp-urlconnection:2.5.0'

    // EventBus
    compile 'de.greenrobot:eventbus:2.4.0'

    // Dagger
    compile 'com.google.dagger:dagger:2.0.1'

    // TriceKit
    compile (name:'tricekit-zta-android-sdk', ext:'aar')
    compile (name:'tricekit-shared-android-sdk', ext:'aar')
}

```

## <a name="android-configuration"></a>Configuration

In your `AndroidManifest.xml`

```
<application ... >

  ...

  <meta-data android:name="tricekit_api_key" android:value="YOUR_API_KEY" />
  <meta-data android:name="tricekit_username" android:value="YOUR_USER_NAME" />

</application>
```

## <a name="android-requirements"></a>System requirements

TriceKit needs Location permissions to run on Marshmallow and above, but also needs Bluetooth to be enable for Beacon scan.
`SystemRequirementsHelper` provides tools to help you identify what features need to be enabled or turned on. (Location permission for Android Marshmallow and above, Location Services or Bluetooth)
`checkRequirements` will tells you what is not currently enabled. If you wish to personalize the experience,
you can then prompt the user using your own dialogs.
`defaultCheckRequirements` provides default Android dialog to ask user to turn on any requirements.

```java
if (SystemRequirementsHelper.checkRequirements(this).isEmpty()) {
    mTriceKitManager.start(false);
} else {
    SystemRequirementsHelper.defaultCheckRequirements(this);
}

@Override
protected void onActivityResult (int requestCode, int resultCode, Intent data) {
    super.onActivityResult(requestCode, resultCode, data);

   switch (requestCode) {
        case SystemRequirementsHelper.TRICEKIT_REQUIREMENTS_REQUEST_CODE:
            if (resultCode == Activity.RESULT_OK) {
                Toast.makeText(this, "All requirements granted!", Toast.LENGTH_SHORT).show();

                mTriceKitManager.start(false);
            }
            else {
                List<Requirement> requirements = SystemRequirementsHelper.checkRequirements(this);

                if (requirements.size() == 1 && requirements.contains(Requirement.BLUETOOTH_DISABLED)) {
                    mTriceKitManager.start(false);

                    Toast.makeText(this, "Bluetooth has been denied, location is granted, let's start!", Toast.LENGTH_SHORT).show();
                }
                else
                    Toast.makeText(this, "Failed to meet requirements", Toast.LENGTH_SHORT).show();
            }
            break;
    }
}
```

## <a name="android-starting"></a>Starting TriceKit


You need first need to initialize TriceKit, we recommend using the Application class.

```java
public class MainApp extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        TriceKitZTA.init(this);
    }
}
```

In order to use this Application class you will need to modify your `AndroidManifest.xml`

```
 <application
        android:name=".MainApp"
        ...
 </application>
```

Now you are ready to start TriceKitManager:

```java
TriceKitManager triceManager = new TriceKitManager(this);
triceManager.start(boolean restoreTriceKitState);
```
Note that you
This is an asynchronous call, you will need to  monitor TriceKit state by using `TriceKitEventListener`:

```java
tricekitManager.egisterTriceKitEventListener(new TriceKitManager.TriceKitEventListener() {
  @Override
  public void onEvent(@NonNull TriceKitEvent event) {
    switch (event) {
        case STATUS:
        // see TriceKitStatus for all possible status.
    }
  }
});
```

Note that usually all TriceKit call need to happen during `STARTING` or `STARTED` state.

To stop TriceKit you simply need to call `stop` method:

```java
triceManager.stop();
```

## <a name="android-add-action"></a>Adding actions to triggers

There are two ways of handling actions in TriceKit.

### <a name="android-local-action"></a>Adding a local action

This is best done by detecting when triggers are added in response to data
obtained from the server. To do this, you will need to register `OnRemoteUpdateListener`:

```java
tricekitManager.registerOnRemoteUpdateListener(new TriceKitManager.OnRemoteUpdateListener() {
    @Override
    public void onTriggerAdded(@NonNull TriceKitZone zone, @NonNull TriceKitTrigger trigger) {
        // add you action here.
        trigger.attachAction(new MyAction());
    }
});
```

In order to attach action to particular trigger, you can use the name or the UUID of the trigger.
Important: Note that if you are using v1 trigger id, you will need to convert is to v2 UUID by using our `V1Helper` utility class:

```java
tricekitManager.registerOnRemoteUpdateListener(new TriceKitManager.OnRemoteUpdateListener() {
    @Override
    public void onTriggerAdded(@NonNull TriceKitZone zone, @NonNull TriceKitTrigger trigger) {
        UUID v1Zone = V1Helper.toZoneUUID(1748);
        UUID v1Trigger = V1Helper.toTriggerUUID(1264);

        if (V1Helper.isV1Zone(zone.getUUID()) && V1Helper.isV1Trigger(trigger.getUUID())) {
            if (v1Zone.equals(zone.getUUID()) && v1Trigger.equals(trigger.getUUID()))
                trigger.attachAction(new MyAction());
        }
    }
});
```

### <a name="android-server-action"></a>Handling server actions

If you have set up a notification action on our TriceKit CMS, you will be able
to handle that server action by registering for notifications when triggers of a
particular type fire:

```java
tricekitManager.registerTriceKitEventListener(new TriceKitManager.TriceKitEventListener() {
    @Override
    public void onEvent(@NonNull TriceKitEvent status) {
        switch (status) {
            case STATUS:
                if (mTriceManager.getStatus() == TriceKitStatus.STARTING) {
                    mTriceManager.registerActionTypeCallback(TriceKitActionType.LOCAL_NOTIFICATION_TYPE, new TriceKitActionTypeCallback() {
                        @Override
                        public void onActionTypeTriggered(@NonNull String type, @NonNull JSONObject metadata) {
                         // Handle your notification action the way you want here.
                        }
                    });
                }
            default:
                break;
        }
    }
});
```

Example of the Notification Action metadata:

```json
{
    "message": "my notification"
}
```

You will soon be able to create your own action type on our CMS.

## <a name="android-user-data"></a>Setting and fetching user data

Details of the user (such as a frequent flyer ID) can be set by calling `setUserData` on the `STARTED` event:

```java
case STATUS:
  if (mTriceManager.getStatus() == TriceKitStatus.STARTED) {
      try {
          mTriceManager.setUserData(new JSONObject("{\"ff_id\": \"136HDF89\"}"));
      } catch (JSONException e) {
          e.printStackTrace();
      }
  }
  break;
```

When this method is called, the user data is uploaded to the server.  The response
from the server (containing information uploaded via the user data REST API) is
made available by listening the `USERDATA` event:

```java
case USERDATA:
    JSONObject userData = mTriceManager.getUserData();
  break;
```

# <a name="features"></a>Features

## <a name="feature-user-data"></a>User data

### <a name="feature-user-data-what-is-it"></a>What is user data?

User data is meta data associated with users. user data can contain any data as
long as it follows the standard JSON format. Key/value pairs, objects and arrays
are supported.

### <a name="feature-user-data-how-does-it-work"></a>How does it work?

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

### <a name="feature-user-data-how-can-you-use-it"></a>How can you use it?

As soon as you start sending user data, you will be able to use that data to
personalize your user's experience!

#### <a name="feature-user-data-url-callback"></a>URL callback

By setting up a URL Callback Action on TriceKit CMS (POST only), you will
receive along that POST any information regarding the Venue, Zone and Trigger
that trigger that action as well as all the user data. This allows you to
identify who is in the zone and triggered the action. This is highly valuable to
you as you will be able to personalize your customer experience.

#### <a name="feature-user-data-trigger-segmentation"></a>Trigger segmentation (coming soon)

Once user data are available, you will be able to apply segmentation rules to
your Trigger. You can decide if a trigger fires for a particular user based on
user data. Segmentation rules will be available while creating/editing a trigger
on TriceKit CMS.

### <a name="feature-user-data-examples"></a>Use case example

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
