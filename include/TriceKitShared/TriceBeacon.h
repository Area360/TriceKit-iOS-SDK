//
//  TriceBeacon.h
//  TriceKit
//
//  Created by Jake Bellamy on 8/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import "MTLModel.h"
#import "MTLJSONAdapter.h"
#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  The manufacturer of a particular iBeacon.
 */
typedef NS_ENUM(NSInteger, TriceBeaconManufacturer) {
    TriceBeaconManufacturerUnknown = 0,
    TriceBeaconManufacturerEstimote,        ///< Estimote.
    TriceBeaconManufacturerKontakt,         ///< Kontact.
    TriceBeaconManufacturerSensoro          ///< Sensoro.
};

NS_INLINE NSString * NSStringFromCLProximity(CLProximity proximity)
{
    switch (proximity) {
        case CLProximityImmediate: return @"Immediate";
        case CLProximityNear:      return @"Near";
        case CLProximityFar:       return @"Far";
        case CLProximityUnknown:
        default:                   return @"Unknown";
    }
}

/**
 *  TriceBeacon represents a Bluetooth iBeacon.
 */
@interface TriceBeacon : MTLModel <MTLJSONSerializing>

/// The proximity ID of the beacon.
@property (nonatomic, strong, readonly) NSUUID *proximityUUID;

/// The most significant value in the beacon.
@property (nonatomic, strong, readonly) NSNumber *major;

/// The least significant value in the beacon.
@property (nonatomic, strong, readonly) NSNumber *minor;

/// The relative distance to the beacon.
@property (nonatomic, assign, readonly) CLProximity proximity;

/// The relative distance to the beacon, calculated using the beacon's current RSSI value.
@property (nonatomic, assign, readonly) CLProximity rssiProximity;

/// The relative distance to the beacon, calculated using the beacon's current accuracy value.
@property (nonatomic, assign, readonly) CLProximity distanceProximity;

/// The accuracy of the proximity value, measured in meters from the beacon.
@property (nonatomic, assign, readonly) CLLocationAccuracy accuracy;

/// The received signal strength of the beacon, measured in decibels.
@property (nonatomic, assign, readonly) NSInteger rssi;

/// An identifier constructed from the major and minor properties. Useful for using as a key to store this beacon in a dictionary. This identifier matches the property CLBeacon -identifier defined in the category CLBeacon (TriceIdentifier).
@property (nonatomic, copy, readonly)   NSString *identifier;

/// The identifier used by the TriceKit server for this beacon.
@property (nonatomic, copy, readonly)   NSString *serverId;

/// The MAC address of the beacon.
@property (nonatomic, copy, readonly)   NSString *macAddress;

/// The transmitting power level that this beacon is set to.
@property (nonatomic, assign, readonly) NSInteger power;

/// The manufacturer of the beacon.
@property (nonatomic, assign, readonly) TriceBeaconManufacturer manufacturer;

/// Whether or not this beacon is pending an update.
@property (nonatomic, assign, readonly, getter=isPendingUpdate) BOOL pendingUpdate;

/// Whether or not this beacon should be connected to when ranged by TriceBeaconManager, either to read or to update the beacon's values.
@property (nonatomic, assign, readonly) BOOL shouldConnectOnPing;

/// The current connection status to the beacon. Updated by TriceBeaconManager when connecting.
@property (nonatomic, assign)           CBPeripheralState connectionState;

/// Whether this beacon is currently physically moving.
@property (nonatomic, assign, getter=isMoving) BOOL moving;

/// The current battery percentage that the beacon is reporting.
@property (nonatomic, assign, readonly) NSInteger batteryPercentage;

/// The time interval that the beacon broadcasts its signal, in milliseconds.
@property (nonatomic, assign, readonly) NSInteger interval;

/// The hardware version of the beacon.
@property (nonatomic, copy, readonly)   NSString *hardwareVersion;

/// The firmware version of the beacon.
@property (nonatomic, copy, readonly)   NSString *firmwareVersion;

/**
 *  Programmatially creates a new TriceBeacon that may be monitored and ranged.
 *
 *  @param major         The most significant value in the beacon.
 *  @param minor         The least significant value in the beacon.
 *  @param proximityUuid The proximity ID of the beacon.
 *
 *  @return An initialized instance.
 */
+(instancetype)beaconWithMajor:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor proximityUuid:(NSUUID *)proximityUuid;

/**
 *  Creates a new TriceBeacon with the same values as that from a CLBeacon.
 *
 *  @param beacon The beacon that was ranged.
 *
 *  @return An initialized instance.
 */
+(instancetype)beaconWithBeacon:(CLBeacon *)beacon;

/**
 *  Updates this beacons proximity, accuracy and rssi values match that of the beacon passed in. 
 *
 *  @note The beacon passed in should be equivalent to the receiver, that is, isEqualToBeacon: should return YES.
 *
 *  @param beacon The beacon that matches this one.
 */
-(void)updateBeacon:(CLBeacon *)beacon;

/**
 *  Determines if the receiver is equivalent to a CLBeacon.
 *
 *  @param beacon The beacon to test for equivalence.
 *
 *  @return YES if the beacon is equal to the reciever, otherwise NO.
 */
-(BOOL)isEqualToBeacon:(CLBeacon *)beacon;

/**
 *  Determines if the receiver is equivalent to a CBPeripheral.
 *
 *  @param peripheral The peripheral to test for equivalence.
 *
 *  @return YES if the peripheral is equal to the receiver, otherwise NO.
 */
-(BOOL)isEqualToPeripheral:(CBPeripheral *)peripheral;

@end

#pragma mark - CLBeacon Extension

/**
 *  This category extends CLBeacon to include a useful identifier which may be used as a key in a dictionary.
 */
@interface CLBeacon (TriceIdentifier)

/**
 *  An identifier constructed from the major and minor properties. The format used matches that of TriceBeacon, making it useful as a key for checking beacons that have been ranged if they exist in a dictionary.
 *
 *  @return This beacon's identifier value.
 */
-(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
