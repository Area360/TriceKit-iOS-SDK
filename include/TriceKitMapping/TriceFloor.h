//
//  TriceFloor.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import <Mantle/MTLModel.h>
#import <Mantle/MTLJSONAdapter.h>
#import <UIKit/UIImage.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class TriceBuilding;

/**
 *  TriceFloor models a single floor inside of a TriceBuilding.
 */
@interface TriceFloor : MTLModel <MTLJSONSerializing>

/// A unique identifier for this floor.
@property (nonatomic, copy, readonly)   NSString *uid;

/// A human readable name for this floor. This is the name that is specified in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSString *name;

/// The level that this floor is on inside the building.
@property (nonatomic, assign, readonly) NSInteger level;

/// An image URL for the floorplan of this floor.
@property (nonatomic, copy, readonly)   NSURL *imageUrl;

/// The offset from north that this floor is.
@property (nonatomic, assign, readonly) CLLocationDegrees offset;

/// The size of the floorplan image. This is set before the image has been downloaded.
@property (nonatomic, assign, readonly) CGSize imageSize;

/// An array of TriceRoom objects.
@property (nonatomic, copy, readonly)   NSArray *rooms;

/// An array of TriceMarker objects.
@property (nonatomic, copy, nullable)   NSArray *markers;

/// An array of TriceBeacon objects.
@property (nonatomic, copy, nullable)   NSArray *beacons;

/// An array of TriceTrainingPoint objects.
@property (nonatomic, copy, nullable)   NSArray *trainingPoints;

/// The building that this floor is contained in.
@property (nonatomic, weak)             TriceBuilding *building;

@end

/**
 *  TriceRoom models a room that is part of a floor.
 */
@interface TriceRoom : MTLModel <MTLJSONSerializing>

/// A unique identifier for this room.
@property (nonatomic, copy, readonly)   NSString *uid;

/// A human readable name for this room. This is the name that is specified in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSString *name;

/// The floor that this room is on.
@property (nonatomic, weak)             TriceFloor *floor;

@end

NS_ASSUME_NONNULL_END
