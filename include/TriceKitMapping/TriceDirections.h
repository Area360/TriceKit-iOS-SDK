//
//  TriceDirections.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import "MTLModel.h"
#import "MTLJSONAdapter.h"
#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class TriceMarker;

/**
 *  TriceDirections models routing instructions in order to do turn-by-turn directions.
 */
@interface TriceDirections : MTLModel <MTLJSONSerializing>

/// Total distance of this route.
@property (nonatomic, assign, readonly) CGFloat distance;

/// Total distance of this route in metres.
@property (nonatomic, assign, readonly) CLLocationDistance distanceMetres;

/// The estimated time to complete all steps in seconds.
@property (nonatomic, assign, readonly) NSInteger durationSeconds;

/// A localized string describing the number of minutes and seconds to complete all steps.
@property (nonatomic, copy, readonly)   NSString *duration;

/// An array of TriceDirectionStep objects.
@property (nonatomic, copy, readonly)   NSArray *steps;

/// The starting point of these directions.
@property (nonatomic, strong) TriceMarker *fromLocation;

/// The ending point of these directions.
@property (nonatomic, strong) TriceMarker *toLocation;

/// Whether or not these directions are wheelchair accessable.
@property (nonatomic, assign, getter=isAccessibleRoute) BOOL accessibleRoute;

/// The index of the current step that is being viewed.
@property (nonatomic, assign) NSInteger currentStepIndex;

@end

/**
 *  TriceDirectionsStep models an individual step used in TriceDirections.
 */
@interface TriceDirectionStep : MTLModel <MTLJSONSerializing>

/// A unique identifier for this step.
@property (nonatomic, copy, readonly)   NSString *uid;

/// The location of the ending point of this step.
@property (nonatomic, assign, readonly) CGPoint location;

/// The distance between the start of this point and end.
@property (nonatomic, assign, readonly) CGFloat distanceToNextPoint;

/// The distance between the start of this point and end, in metres.
@property (nonatomic, assign, readonly) CLLocationDistance distanceToNextPointMetres;

/// The angle offset from north to the next point.
@property (nonatomic, assign, readonly) CGFloat headingToNextPoint;

/// The estimated time to complete this step, in seconds.
@property (nonatomic, assign, readonly) NSInteger durationToNextPointSeconds;

/// A localized string describing the path to take to get to the next step.
@property (nonatomic, copy, readonly)   NSString *directionsToNextPoint;

/// A localized string describing the time it will take to get to the next step.
@property (nonatomic, copy, readonly)   NSString *durationToNextPoint;

/// An image URL for the helpful arrow icons.
@property (nonatomic, copy, readonly)   NSURL *iconUrl;

@end

NS_ASSUME_NONNULL_END
