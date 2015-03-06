//
//  TriceTriggerManager.h
//  TriceKit
//
//  Created by Jake Bellamy on 28/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TriceZone.h"

@class TriceAction;

/**
 *  The TriceTriggerManager class manages the Zones, Triggers and Actions aspect of the TriceKit SDK.
 */
@interface TriceTriggerManager : NSObject

/**
 *  A set of TriceZone objects, which the device will be monitoring on a call to startMonitoringZones. Once the location of the device has been updated this is populated with the list of zones in the TriceKit CMS.
 */
@property (nonatomic, strong, readonly) NSSet *zones;

/**
 *  Starts monitoring for the zones given in the  zones property.
 */
-(void)startMonitoringZones;

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
 *  @param action     The action to attach.
 *  @param triggerUid The unique identifier of the trigger to attach the action to. This is provided in the TriceKit CMS, or the identifier specified for a TriceTrigger created programatically.
 *  @param zoneUid    The unique identifier of the zone to attach the action to. This is provided in the TriceKit CMS, or the identidier specified for a TriceZone created programatatically.
 */
-(void)addAction:(TriceAction *)action toTrigger:(NSString *)triggerUid zone:(NSString *)zoneUid;

@end
