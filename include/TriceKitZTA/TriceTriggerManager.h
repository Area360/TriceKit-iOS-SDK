//
//  TriceTriggerManager.h
//  TriceKit
//
//  Created by Jake Bellamy on 28/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TriceObjectDescriptor.h"
#import "TriceZone.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The TriceTriggerManager class manages the Zones, Triggers and Actions aspect of the TriceKit SDK.
 */
@interface TriceTriggerManager : NSObject

/// A set of TriceZone objects, which the device will be monitoring on a call to startMonitoringZones. Once the location of the device has been updated this is populated with the list of zones in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSSet *zones;

/// A set of TriceZone objects which the device is currently inside of. That is, each zone's state property is TriceZoneStateDwelling.
@property (nonatomic, copy, readonly)   NSSet *zonesInside;

/// If set, this block will be executed whenever an error occurs, such as a failed URL request, or when monitoring beacons is denied. If this property is nil (which it is by default), the error is logged to the console and an alert is displayed to the user.
@property (nonatomic, copy, nullable)   void (^handleErrorBlock)(NSError *error);

/// If this property is YES, TriceTriggerManager will cache its most recent list of zones by encoding to disk so that they may be reloaded when offline.
@property (nonatomic, assign)           BOOL allowEncodingZonesToDisk;

/**
 *  Starts monitoring for all nearby zones.
 */
-(void)startMonitoringZones;

/**
 *  Starts monitoring for only beacon zones.
 */
-(void)startMonitoringBeaconZones;

/**
 *  Starts monitoring for only GPS-based zones.
 */
-(void)startMonitoringGPSZones;

/**
 *  Stops monitoring all zones.
 */
-(void)stopMonitoringZones;

/**
 *  Adds a programmatically created zone to the list of zones that are monitored.
 *
 *  @param zone The zone to add.
 */
-(void)addZone:(TriceZone *)zone;

/**
 *  Programatically adds an action to a trigger inside of a zone. This is useful for testing actions and triggers without needing to use the TriceKit CMS, which would make the action live for everybody using your application with the TriceKit SDK installed.
 *
 *  This method allows you to add programmatically created triggers and actions to zones that exist in the TriceKit CMS. Simply specify the identifiers provided in the CMS and when the trigger fires the action will be executed as well.
 *
 *  The action may attach to multiple triggers if multiple test evaluations return YES. The zones to attach the action to will be evaluated. Then, each TriceZone that passes evaluation will test the list of triggers to be evaluated. The list of TriceTriggers that pass this evaluation will have this action attached to.
 *
 *  @param action            The action to attach.
 *  @param triggerDescriptor A descriptor which identifies the trigger to attach this action to. The action will attach to all triggers that pass evaluation.
 *  @param zoneDescriptor    A descriptor which identifies the zone to attach this action to. The triggerDescriptor will be evaluated against all zones that pass zoneDescriptor evaluation.
 */
-(void)addAction:(TriceAction *)action toTrigger:(TriceObjectDescriptor *)triggerDescriptor zone:(TriceObjectDescriptor *)zoneDescriptor;

/**
 *  Gets a set of zones that matches a given descriptor.
 *
 *  @param descriptor The descriptor to evaluate each zone to.
 *
 *  @return A set of TriceZone objects that the descriptor has evaluated YES to.
 */
-(NSSet *)zonesMatchingDescriptor:(TriceObjectDescriptor *)descriptor;

@end

NS_ASSUME_NONNULL_END
