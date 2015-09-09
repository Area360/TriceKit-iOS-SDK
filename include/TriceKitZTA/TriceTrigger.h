//
//  TriceTriggerModel.h
//  TriceKit
//
//  Created by Jake Bellamy on 28/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Mantle/MTLModel.h>
#import <Mantle/MTLJSONAdapter.h>
#import "TriceAction.h"

NS_ASSUME_NONNULL_BEGIN

/// The notification name which is posted when a trigger has activated and is about to perform its associated actions. The object is the TriceTrigger object that is about to fire.
extern NSString * const TriceTriggerWillFireNotification;

/// The notification name which is posted when a trigger has activated and has just performed its associated actions. The object is the TriceTrigger object that has just fired.
extern NSString * const TriceTriggerDidFireNotification;

/**
 *  The types of events that can cause a trigger to fire.
 */
typedef NS_ENUM(NSInteger, TriceTriggerEvent){
    TriceTriggerEventUnknown = 0,       ///< Unknown trigger event or was not set.
    TriceTriggerEventEnter,             ///< Entering a zone will cause the trigger to fire.
    TriceTriggerEventExit,              ///< Exiting a zone will cause the trigger to fire.
    TriceTriggerEventDwell,             ///< Dwelling in a zone for a certain time period.
    TriceTriggerEventAccelerometer      ///< Trigger will fire when the beacon is in motion.
};

NS_INLINE NSString * NSStringFromTriceTriggerEvent(TriceTriggerEvent event)
{
    switch (event) {
        case TriceTriggerEventEnter:         return @"Enter";
        case TriceTriggerEventExit:          return @"Exit";
        case TriceTriggerEventDwell:         return @"Dwell";
        case TriceTriggerEventAccelerometer: return @"Accelerometer";
        case TriceTriggerEventUnknown:
        default:                             return @"Unknown";
    }
}

@class TriceZone;

/**
 *  A TriceTrigger models an event that fires when the state of a TriceZone changes. Each trigger has a list of TriceAction objects that are executed when the conditions of this trigger are met. For example, a trigger may have conditions to fire when its parent zone is entered.
 *
 *   TriceTrigger objects are typically constructed from Triggers in the TriceKit CMS. However, you may instantiate an object of this class yourself using the constructor triggerWithEvent:dwellTime:frequency:.
 */
@interface TriceTrigger : MTLModel <MTLJSONSerializing>

/// A unique identifier that is provided from the TriceKit CMS. Equality is based solely on this property, so calling  isEqual: on this object with another  TriceTrigger object with the same uid will return YES.
@property (nonatomic, copy, readonly)   NSString *uid;

/// The descriptive name for this trigger. This matches the name that is provided in the TriceKit CMS.
@property (nonatomic, copy)             NSString *name;

/// The minimum time in seconds that should pass before this trigger should be able to fire again.
@property (nonatomic, assign, readonly) NSTimeInterval frequency;

/// The maximum number of times this trigger may fire. Zero indicates there is no limit.
@property (nonatomic, assign, readonly) NSUInteger limit;

/// The number of times this trigger has fired.
@property (nonatomic, assign, readonly) NSUInteger fireCount;

/// The event that should occur for this trigger to fire.
@property (nonatomic, assign, readonly) TriceTriggerEvent event;

/// The amount of time in seconds that the user should be inside the parent zone. This value is only valid if the  event property is TriceTriggerEventDwell.
@property (nonatomic, assign, readonly) NSTimeInterval dwellTime;

/// A list of TriceAction objects.
@property (nonatomic, copy, readonly)   NSArray *actions;

/// Custom point of interest data that is linked to this trigger.
@property (nonatomic, copy, readonly)   NSDictionary *linkedPointOfInterest;

/// The parent zone which contains this trigger.
@property (nonatomic, weak) TriceZone *zone;

/**
 *  Constructs a new TriceTrigger object for entering and exiting a zone. This constructor is used to create internal testing triggers for use in TriceZone objects so that you may easily test and experiment with triggers.
 *
 *  This trigger will not have any actions added to it by default. You should call addAction: to add actions that will be executed with this trigger fires before adding this trigger to a zone.
 *
 *  @note There will not be any analytics for any constructed triggers using this method, to support analyics you must create the trigger through the TriceKit CMS.
 *
 *  @param event     The event that will cause this trigger to fire.
 *  @param frequency The amount of time in seconds which should pass before being able to fire this trigger again.
 *  @param limit     The maximum number of times this trigger may fire. Use 0 to indicate no limit.
 *
 *  @return An initialized instance.
 */
+(instancetype)triggerWithEvent:(TriceTriggerEvent)event frequency:(NSTimeInterval)frequency limit:(NSUInteger)limit;

/**
 *  Constructs a new TriceTrigger object for dwelling in a zone. This constructor is used to create internal testing triggers for use in TriceZone objects so that you may easily test and experiment with triggers.
 *
 *  This trigger will not have any actions added to it by default. You should call addAction: to add actions that will be executed with this trigger fires before adding this trigger to a zone.
 *
 *  @note There will not be any analytics for any constructed triggers using this method, to support analyics you must create the trigger through the TriceKit CMS.
 *
 *  @param dwellTime The time in seconds to dwell in the zone to cause the trigger to fire.
 *  @param frequency The amount of time in seconds which should pass before being able to fire this trigger again.
 *  @param limit     The maximum number of times this trigger may fire. Use 0 to indicate no limit.
 *
 *  @return An initialized instance.
 */
+(instancetype)triggerWithDwellTime:(NSTimeInterval)dwellTime frequency:(NSTimeInterval)frequency limit:(NSUInteger)limit;

/**
 *  Updates the receiver to have the same internal state as the passed in trigger. This is so that the receiver will not fire again immediately. 
 * 
 *  @note Both TriceTrigger objects are assumed to be equal, that is, isEqual: should return YES.
 *
 *  @param trigger The trigger which values will be copied.
 */
-(void)setInternalStateToSameAs:(TriceTrigger *)trigger;

/**
 *  Adds a custom action to this trigger which will be executed when this trigger fires.
 *
 *  @param action The action that is fired when this trigger activates.
 */
-(void)addAction:(TriceAction *)action;

/**
 *  Whether or not this trigger should fire given its parent zone's current state.
 *
 *  @return Whether or not this trigger should fire.
 */
-(BOOL)shouldFire;

/**
 *  Fires this trigger and executes all added TriceAction objects associated with it.
 */
-(void)fire;

/**
 *  Stops this trigger from firing. This will only have an effect when called from the TriceTriggerWillFireNotification notification callback.
 */
-(void)cancelFiring;

@end

NS_ASSUME_NONNULL_END
