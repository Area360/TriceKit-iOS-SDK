//
//  TriceBuilding.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import "MTLModel.h"
#import "MTLJSONAdapter.h"
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class TriceAddress;

/**
 *  TriceBuilding models a building that is used for mapping.
 */
@interface TriceBuilding : MTLModel <MTLJSONSerializing>

/// A unique identifier for this building.
@property (nonatomic, copy, readonly)   NSString *uid;

/// A human readable name for this building. This is the name that is specified in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSString *name;

/// A human readable description of this building. This is the description that is specied in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSString *buildingDescription;

/// Image URL of this building.
@property (nonatomic, copy, readonly)   NSString *imageUrl;

/// The address of this building.
@property (nonatomic, strong, readonly) TriceAddress *address;

/// The geo-coordinate of this building.
@property (nonatomic, assign, readonly) CLLocationCoordinate2D coordinate;

/// The floors that are in this building.
@property (nonatomic, copy, nullable)   NSArray *floors;
/**
 *  Gets all map markers that are in this building.
 *
 *  @return An array of TriceMarker objects.
 */
-(NSArray *)allMarkers;

@end

/**
 *  TriceAddress models a physical location in the world.
 */
@interface TriceAddress : MTLModel <MTLJSONSerializing>

@property (nonatomic, copy, readonly)   NSString *street;       ///< Street name.
@property (nonatomic, copy, readonly)   NSString *city;         ///< City name.
@property (nonatomic, copy, readonly)   NSString *state;        ///< State, if applicable.
@property (nonatomic, copy, readonly)   NSString *country;      ///< Country.
@property (nonatomic, copy, readonly)   NSString *postalCode;   ///< The postal code.

@end

NS_ASSUME_NONNULL_END
