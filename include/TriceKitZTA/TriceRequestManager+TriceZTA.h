//
//  TriceRequestManager+TriceZTA.h
//  TriceKit
//
//  Created by Jake Bellamy on 3/03/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import "TriceRequestManager.h"

@class TriceZone;

NS_ASSUME_NONNULL_BEGIN

/**
 *  This category on TriceRequestManager adds zones, triggers and actions related requests to the TriceKit SDK.
 */
@interface TriceRequestManager (TriceZTA)

/**
 *  Retrieves the list of nearby zones to the device in order to monitor proximity.
 *
 *  @param distance The maximum distance in kilometers in which to get zones for.
 *  @param success  A success callback block that returns an array of TriceZone objects as its only parameter.
 *  @param failure  If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestZonesNearbyWithDistanceFilter:(CGFloat)distance
                                                      success:(nullable void (^)(NSArray *zones))success
                                                      failure:(nullable void (^)(NSError *error))failure;

/**
 *  Notifies the TriceKit server that a zone has been either entered or exited by the device.
 *
 *  @param zone    The zone that was either entered or exited, which is determined by the current value of its state property.
 *  @param success A callback block to indicate the request was successful.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestZonePing:(TriceZone *)zone
                                 success:(nullable void (^)())success
                                 failure:(nullable void (^)(NSError *error))failure;

@end

NS_ASSUME_NONNULL_END
