//
//  TriceRequestManager.h
//  TriceKit
//
//  Created by Jake Bellamy on 8/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import <AFHTTPSessionManager.h>
#import <CoreLocation/CLLocationManager.h>

NS_ASSUME_NONNULL_BEGIN

@class TriceBeacon;

/**
 *  TriceRequestManager is the networking manager used throughout TriceKit to make HTTP requests to the TriceKit server.
 */
@interface TriceRequestManager : AFHTTPSessionManager

/**
 *  The location manager used for requests that need the user's current location, such as getting a list of nearby zones.
 */
@property (nonatomic, strong, readonly) CLLocationManager *locationManager;

/**
 *  Gets a currently scheduled or executing download task. Useful for checking whether an image request is currently downloading.
 *
 *  @note This synchronous method will stall the thread it is called on, as NSURLSessionTask tasks are executed on a background thread.
 *
 *  @param url The URL of the scheduled or executing task to check.
 *
 *  @return The scheduled or executing task if it exists, otherwise  nil.
 */
+(nullable NSURLSessionDownloadTask *)requestTaskForUrl:(NSURL *)url;

/**
 *  Helpful wrapper around the standard request failure blocks.
 *
 *  @param failure The failure block passed into TriceRequestManager.
 */
+(void (^)(NSURLSessionDataTask *, NSError *))failureBlock:(nullable void (^)(NSError *error))failure;

#pragma mark - Beacons

/**
 *  Requests a list of beacons to be uploaded to the TriceKit server.
 *
 *  @param beacons An array of TriceBeacon objects.
 *  @param success A callback block that indicates the upload was successful.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestBeaconsUpload:(NSArray *)beacons
                                      success:(nullable void (^)())success
                                      failure:(nullable void (^)(NSError *error))failure;

/**
 *  Request sent to the TriceKit server to confirm that a beacon has been successfully updated.
 *
 *  @param beacon  The beacon that was connected to and values updated.
 *  @param success A callback block to indicate the request was successful.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestBeaconUpdateConfirmation:(TriceBeacon *)beacon
                                                 success:(nullable void (^)())success
                                                 failure:(nullable void (^)(NSError *error))failure;

/**
 *  Requests the list of beacons that are close to the device. For this to succeed a  CLLocationManager must have successfully updated the user's location at least once.
 *
 *  @param success A success callback block that returns an array of TriceBeacon objects as its only parameter.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestBeaconsNearbyOnSuccess:(nullable void (^)(NSArray *beacons))success
                                               failure:(nullable void (^)(NSError *error))failure;

/**
 *  Sends a request to the TriceKit server to indicate that the device has come in range of a beacon that has been previously fetched.
 *
 *  @param beacon  The beacon that the device has ranged.
 *  @param success A callback block to indicate the request was successful.
 *  @param failure If something went wrong during the upload, that is described in the NSError object that is passed back through this failure callback block.
 *
 *  @return The task that was created for this request.
 */
+(NSURLSessionDataTask *)requestBeaconPing:(TriceBeacon *)beacon
                                   success:(nullable void (^)())success
                                   failure:(nullable void (^)(NSError *error))failure;

@end

NS_ASSUME_NONNULL_END