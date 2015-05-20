//
//  TriceRequestManager+TriceMapping.h
//  TriceKit
//
//  Created by Jake Bellamy on 3/03/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import "TriceRequestManager.h"

@class TricePositioning;

NS_ASSUME_NONNULL_BEGIN

/**
 *  This category on TriceRequestManager adds mapping related requests to the TriceKit SDK.
 */
@interface TriceRequestManager (TriceMapping)

/**
 *  Retrieves the list of buildings that have been added in the TriceKit CMS.
 *
 *  @param success A success callback block that returns an array of TriceBuilding objects as its only parameter.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsBuildingListOnSuccess:(nullable void (^)(NSArray *buildings))success
                                                  failure:(nullable void (^)(NSError *error))failure;

/**
 *  Retrieves detailed information about a specified building, including its list of floors.
 *
 *  @param buildingUid The unique identifier for the building in which to retrieve information about.
 *  @param success     A success callback block that returns a TriceBuilding object with its floors property set.
 *  @param failure     If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsBuildingDetails:(NSString *)buildingUid
                                           success:(nullable void (^)(TriceBuilding *building))success
                                           failure:(nullable void (^)(NSError *error))failure;

/**
 *  Retrieves a list of floors for a given building.
 *
 *  @param building The building in which to retrieve floor information for.
 *  @param success  A success callback block that returns an array of TriceFloor objects as its only parameter.
 *  @param failure  If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsFloorsForBuilding:(TriceBuilding *)building
                                              success:(nullable void (^)(NSArray *floors))success
                                              failure:(nullable void (^)(NSError *error))failure;

/**
 *  Retrieves a list of markers for a given floor.
 *
 *  @param floor   The floor in which to retrieve marker information for.
 *  @param success A success callback block that returns an array of TriceMarker objects as its only parameter.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsFloorMarkers:(TriceFloor *)floor
                                         success:(nullable void (^)(NSArray *markers))success
                                         failure:(nullable void (^)(NSError *error))failure;

/**
 *  Retrieves a list of beacons for a given floor.
 *
 *  @param floor   The floor in which to retrieve beacon information for.
 *  @param success A success callback block that returns an array of TriceBeacon objects as its only parameter.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsFloorBeacons:(TriceFloor *)floor
                                         success:(nullable void (^)(NSArray *beacons))success
                                         failure:(nullable void (^)(NSError *error))failure;

/**
 *  Retrieves a list of training points for a given building.
 *
 *  @param building The building in which to retrieve training point information for.
 *  @param success  A success callback block that returns an array of TriceFloor objects which in turn have their trainingPoints property set.
 *  @param failure  If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsTrainingPointsForFloor:(TriceFloor *)floor
                                                   success:(nullable void (^)(TricePositioning *points))success
                                                   failure:(nullable void (^)(NSError *error))failure;

/**
 *  Requests map directions from a starting point to an ending point.
 *
 *  @param fromLocation    The location to get directions from.
 *  @param toLocation      The location to get directions to.
 *  @param accessibleRoute Whether or not to use an accessible route if needed, for example to avoid stairs for a wheelchair-bound person.
 *  @param success         A success callback block that returns a TriceDirection object as its only parameter.
 *  @param failure         If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestMapsDirectionsFrom:(TriceMarker *)fromLocation
                                                to:(TriceMarker *)toLocation
                                   accessibleRoute:(BOOL)accessibleRoute
                                           success:(nullable void (^)(TriceDirections *directions))success
                                           failure:(nullable void (^)(NSError *error))failure;

@end

NS_ASSUME_NONNULL_END
