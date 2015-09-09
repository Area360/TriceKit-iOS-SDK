//
//  TriceZone.h
//  TriceKit
//
//  Created by Jake Bellamy on 28/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Mantle/MTLModel.h>
#import <Mantle/MTLJSONAdapter.h>
#import "TriceObjectDescriptor.h"
#import "TriceTrigger.h"
#import "TriceBeacon.h"
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLRegion.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/// The notification name which is posted when a zones state property changes. The object is the TriceZone object whose value changed, and the new value is reflected in the property at the time of the notification.
extern NSString * const TriceZoneStateDidChangeNotification;

/**
 *  The type of zone. This corresponds with the class that is instantiated.
 */
typedef NS_ENUM(NSInteger, TriceZoneType){
    TriceZoneTypeUnknown = 0,       ///< Unknown type. TriceZone class used.
    TriceZoneTypeGeoLocation,       ///< Geo location type. A subclass of TriceGeoZone used.
    TriceZoneTypeBeaconProximity,   ///< Beacon proximity type. TriceBeaconZone class used.
    TriceZoneTypeIndoorLocation     ///< Indoor location type. TriceIndoorZone class used.
};

/**
 *  The current state of a zone.
 */
typedef NS_ENUM(NSInteger, TriceZoneState){
    TriceZoneStateOutside = 0,      ///< The device is outside of a zone.
    TriceZoneStateExited,           ///< The device has just exited a zone.
    TriceZoneStateEntered,          ///< The device has just entered a zone.
    TriceZoneStateDwelling          ///< The device is currently dwelling inside of a zone.
};

NS_INLINE NSString * NSStringFromTriceZoneState(TriceZoneState state)
{
    switch (state) {
        case TriceZoneStateOutside:  return @"Outside";
        case TriceZoneStateEntered:  return @"Entered";
        case TriceZoneStateDwelling: return @"Dwelling";
        case TriceZoneStateExited:   return @"Exited";
        default:                     return @"Invalid";
    }
}

#pragma mark - TriceZone

/**
 *  TriceZone is an abstract base class which models a physical area that a person may be inside or outside of.
 *
 *  A zone has a list of associated triggers which are fired when certain conditions are met, for example on entering a zone, or dwelling inside a zone for 60 seconds.
 *
 *  You should not instantiate this class directly. Instead, instantiate one of the concrete subclasses that determines how the zone is implemented and updated in order to determine whether the user is inside or outside.
 */
@interface TriceZone : MTLModel <MTLJSONSerializing>

/// A unique identifier that is provided from the TriceKit CMS. Equality is based solely on this property, so calling isEqual: on this object with another TriceZone object with the same uid will return YES.
@property (nonatomic, copy, readonly)   NSString *uid;

/// The descriptive name for this zone. This matches the name that is provided in the TriceKit CMS.
@property (nonatomic, copy)             NSString *name;

/// The type of this zone. This corresponds to which class is used, eg. TriceZoneTypeBeaconProximity will be a TriceBeaconZone class.
@property (nonatomic, assign, readonly) TriceZoneType type;

/// A set of TriceTrigger objects.
@property (nonatomic, copy, readonly)   NSSet *triggers;

/// The current state that this zone is in. For example if the user has entered this zone then this value will be TriceZoneStateEntered, and on the next update TriceZoneStateDwelling.
@property (nonatomic, assign, readonly) TriceZoneState state;

/// The amount of time that the user has been dwelling inside the zone, or the amount of time that the state of this zone has been in TriceZoneStateDwelling.
@property (nonatomic, assign, readonly) NSTimeInterval currentDwellTime;

/// The distance in metres that the device is currently away from this zone. A negative value indicates the distance could not be calculated.
@property (nonatomic, assign, readonly) CLLocationDistance currentDistanceAway;

/**
 *  Adds a trigger to this zone.
 *
 *  @param trigger The trigger to add.
 */
-(void)addTrigger:(TriceTrigger *)trigger;

/**
 *  Gets a set of triggers that matches a given descriptor.
 *
 *  @param descriptor The descriptor to evaluate each zone to.
 *
 *  @return A set of TriceTrigger objects that the descriptor has evaluated YES to.
 */
-(NSSet *)triggersMatchingDescriptor:(TriceObjectDescriptor *)descriptor;

/**
 *  Updates the receiver to have the same internal state is the passed in zone. This is so that the receiver will not potentially fire its triggers again due to updating. This also updates the receiver's trigger list. 
 *
 *  @note Both TriceZone objects are assumed to be equal, that is, isEqual: should return YES.
 *
 *  @param zone The zone which values will be copied.
 */
-(void)setInternalStateSameAs:(TriceZone *)zone;

/**
 *  Used by subclasses to update the state property and fires any triggers that have been activated.
 */
-(void)update;

@end

#pragma mark - TriceGeoZone

/**
 *  The abstract TriceGeoZone class defines a zone by using the user's GPS location.
 */
@interface TriceGeoZone : TriceZone

/// The user's current location. This should be updated before calling  -update on this zone to check if we are now inside or outside of this zone.
@property (nonatomic, strong) CLLocation *userLocation;

@end

#pragma mark - TriceGeoRadiusZone

/**
 *  The TriceGeoRadiusZone class defines a circular zone that uses a geographical center coordinate plus radius to determine its area.
 */
@interface TriceGeoRadiusZone : TriceGeoZone

/// The geographical center coordinate of this zone.
@property (nonatomic, assign, readonly) CLLocationCoordinate2D coordinate;

/// Radius value from the center coordinate in metres will determine whether we are inside or outside of this zone.
@property (nonatomic, assign, readonly) CLLocationDistance radius;

/**
 *  Constructs a new TriceGeoRadiusZone object. This constructor is used to create an internal testing zone so that you may easily test and experiment with zones.
 *
 *  @param coordinate The center coordinate.
 *  @param radius     The radius in metres.
 *
 *  @return An initialized instance.
 */
+(instancetype)geoRadiusZoneWithCoordinate:(CLLocationCoordinate2D)coordinate radius:(CLLocationDistance)radius;

@end

#pragma mark - TriceGeoPolygonZone

/**
 *  The TriceGeoPolygonZone class defines a zone using geographical coordinates that can be any polygon shape.
 */
@interface TriceGeoPolygonZone : TriceGeoZone

/// An array of coordinates that make up the polygon. Each object is a CLLocationCoordinate2D wrapped in a NSValue.
@property (nonatomic, copy, readonly)   NSArray *polygonCoordinates;

/**
 *  Constructs a new TriceGeoPolygonZone object. This constructor is used to create an internal testing zone so that you may easily test and experiment with zones.
 *
 *  @param coordinates An array of geographical coordinates that make up the polygon. This objects in this array should be a CLLocationCoordinate2D wrapped in a NSValue.
 *
 *  @return An initialized instance.
 */
+(instancetype)geoPolygonZoneWithCoordinates:(NSArray *)coordinates;

@end

#pragma mark - TriceBeaconZone

/**
 *  The TriceBeaconZone class defines a zone that uses the user's proximity to a Bluetooth iBeacon to determine its area.
 */
@interface TriceBeaconZone : TriceZone

/// The beacon proximity at which we will be inside this zone.
@property (nonatomic, assign, readonly) CLProximity proximity;

/// The beacon that we are ranging and monitoring for proximity. This should be updated before calling [TriceZone update] on this zone to check if we are now inside or outside of this zone.
@property (nonatomic, strong, readonly) TriceBeacon *beacon;

/// Whether the application should monitor this beacon zone while in the background.
@property (nonatomic, assign, readonly) BOOL backgroundPing;

/**
 *  Constructs a new TriceBeaconZone object. This constructor is used to create an internal testing zone so that you may easily test and experiment with zones.
 *
 *  @param beacon    The beacon which will be monitored to determine the state of the zone.
 *  @param proximity The proximity from the beacon which will determine the radius of the zone.
 *
 *  @return An initialized instance.
 */
+(instancetype)beaconZoneWithBeacon:(TriceBeacon *)beacon proximity:(CLProximity)proximity;

@end

#pragma mark - TriceIndoorZone

@interface TriceIndoorZone : TriceZone

@end

NS_ASSUME_NONNULL_END
