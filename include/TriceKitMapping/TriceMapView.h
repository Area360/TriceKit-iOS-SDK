//
//  TriceMapView.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "TriceBuilding.h"
#import "TriceFloor.h"
#import "TriceMarker.h"
#import "TriceBeacon.h"
#import "TriceDirections.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The name of a notification that is posted by a TriceFloor object when that floor's floorplan image has completed loading and will be displayed imminently. This is a good time to hide any loading views that may be present.
 */
extern NSString * const TriceMapViewFloorplanImageDidLoadNotification;

@protocol TriceMapViewDelegate;

/**
 *  TriceMapView provides an embeddable map interface for displaying indoor mapping in your application. You may use this class as-is to display markers and other points of interest as well as interact with them.
 *
 *  This class is used by TriceMapViewController as part of its interface to provide an entire indoor mapping experience. It is recommended that you use the view controller to display mapping in your application, although you may use this class directly to create your own custom mapping experience if you wish.
 *
 */
@interface TriceMapView : GLKView

/**
 *  Routing directions that are used by the map to display turn-by-turn directions to the user.
 *
 *  Assigning a non-nil value to this property automatically sets up the map to display the directions. That is, it draws a line for each step from starting to end points, hides all markers that are not the start and end markers and sets the camera frame by calling setCameraFrameToRouteOverview.
 *
 *  Assigning a nil value to this property will reshow all markers and remove the guide line.
 */
@property (nonatomic, strong, nullable) TriceDirections *routeDirections;

/**
 *  The building that this map is displaying. 
 *
 *  Setting this will request the building's floors if necessary. Once the floors are loaded, markers for currentFloorIndex will be loaded, requesting them if necessary. If the value of currentFloorIndex is beyond the number of loaded floors for this building, a NSRangeException will be raised.
 */
@property (nonatomic, strong, nullable) TriceBuilding *building;

/**
 *  The currently viewed floor on the map.
 *
 *  This is a transient property that simply calls building.floors[currentFloorIndex].
 */
@property (nonatomic, strong, readonly) TriceFloor *currentFloor;

/**
 *  The currently viewed floor on the map.
 *
 *  Setting this will cause the map to load that specified floor along with that floors markers. It is invalid to set this to any negative value or greater than the number of floors the building has (ie. building.floors.count-1), and will raise a NSRangeException if attempted.
 *
 *  It is safe to set this value before the building's floors have been loaded yet. You may set this property and the building property in any order, however, you must ensure that it is not beyond the number of floors that are returned from the server when they are eventually loaded, otherwise a NSRangeException is raised.
 */
@property (nonatomic, assign) NSInteger currentFloorIndex;

/**
 *  The delegate object you wish to receive update events to.
 */
@property (nonatomic, weak, nullable) id <TriceMapViewDelegate> mapDelegate;

/**
 *  The camera frame that this map view is used to display its content.
 *
 *  Setting this value will animate the change to the new frame.
 */
@property (nonatomic, assign) CGRect cameraFrame;

/**
 *  Whether or not the camera frame is currently tracking the user's location.
 *
 *  Setting this to YES will animate the camera frame to to the user's current location.
 */
@property (nonatomic, assign, getter=isLockedOnUserLocation) BOOL lockedOnUserLocation;

/**
 *  Sets the camera frame to show the entire route on screen. Does nothing if the property routeDirections is not set.
 */
-(void)setCameraFrameToRouteOverview;

/**
 *  Sets the camera frame to show the specified routing step. Does nothing if the property routeDirections is not set.
 *
 *  @param index The index of the routing step to zoom to.
 */
-(void)setCameraFrameToRouteStepIndex:(NSInteger)index;

/**
 *  Cancels all pending or currently executing map server requests. Typically you would call this method when you are done with the mapView and do not want to wait for the requests to finish before deallocating.
 */
-(void)cancelAllMapRequests;

@end

/**
 *  The TriceMapViewDelegate protocol defines a set of optional methods that you can use to receive map-related update messages.
 */
@protocol TriceMapViewDelegate <NSObject>
@optional

/**
 *  This method is called whenever the the map view has started updating the user's location.
 *
 *  @param mapView The map view that has updated.
 */
-(void)triceMapViewDidStartUpdatingUserLocation:(TriceMapView *)mapView;

/**
 *  This method is called whenever the map is tapped, but not when a marker on the map is tapped.
 *
 *  @param mapView The map view that was tapped.
 */
-(void)triceMapViewWasTapped:(TriceMapView *)mapView;

/**
 *  This method is called whenever a marker has been selected.
 *
 *  @param mapView The map view containing the marker.
 *  @param marker  The marker that was selected.
 */
-(void)triceMapView:(TriceMapView *)mapView didSelectMarker:(TriceMarker *)marker;

/**
 *  This method is called whenever the currently displayed map region is about to change.
 *
 *  @param mapView  The map view whose visible region is about to change.
 *  @param animated If YES, the change to the new region will be animated. If NO, the change will be made immediately.
 */
-(void)triceMapView:(TriceMapView *)mapView regionWillChangeAnimated:(BOOL)animated;

/**
 *  This method is called whenever the currently displayed map region has just changed.
 *
 *  @param mapView  The map view whose visible region changed.
 *  @param animated If YES, the change to the new region was animated.
 */
-(void)triceMapView:(TriceMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
