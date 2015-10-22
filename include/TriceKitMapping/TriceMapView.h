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

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, TriceMapCameraUpdateType) {
    TriceMapCameraUpdateTypeNone   = 0,
    TriceMapCameraUpdateTypeMove   = 1 << 0,
    TriceMapCameraUpdateTypeRotate = 1 << 1,
    TriceMapCameraUpdateTypeZoom   = 1 << 2
};

typedef NS_ENUM(NSInteger, TriceMapViewState) {
    TriceMapViewStateNormal,
    TriceMapViewStateWayfindingOverview
};

@protocol TriceMapViewDelegate;

/**
 *  TriceMapView provides an embeddable map interface for displaying indoor mapping in your application. You may use this class as-is to display markers and other points of interest as well as interact with them.
 *
 *  This class is used by TriceMapViewController as part of its interface to provide an entire indoor mapping experience. It is recommended that you use the view controller to display mapping in your application, although you may use this class directly to create your own custom mapping experience if you wish.
 *
 */
@interface TriceMapView : GLKView

/**
 *  The building that this map is displaying. 
 *
 *  Setting this will request the building's floors if necessary. Once the floors are loaded, markers for currentFloorIndex will be loaded, requesting them if necessary. If the value of currentFloorIndex is beyond the number of loaded floors for this building, a NSRangeException will be raised.
 */
@property (nonatomic, strong, nullable) TriceBuilding *building;

/**
 *  The currently viewed floor on the map.
 *
 *  This is a transient property that simply wraps around currentFloorIndex by calling building.floors[currentFloorIndex] or setCurrentFloorIndex:.
 */
@property (nonatomic, strong) TriceFloor *currentFloor;

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
 *  Whether or not the camera frame is currently tracking the user's location.
 *
 *  Setting this to YES will animate the camera frame to to the user's current location.
 */
@property (nonatomic, assign, getter=isLockedOnUserLocation) BOOL lockedOnUserLocation;

/**
 *  Cancels all pending or currently executing map server requests. Typically you would call this method when you are done with the mapView and do not want to wait for the requests to finish before deallocating.
 */
-(void)cancelAllMapRequests;

/**
 *  Updates the map camera. The change will be animated.
 *
 *  @param updateType      The type of update to perform. Valid updates are a combination of move, zoom and rotate.
 *  @param centerPoint     If the updateType includes move, then this value will be used to calculate the new center of the map.
 *  @param rotationDegrees If the updateType includes rotate, then this value will be used to calculate the new camera rotation.
 *  @param zoomScale       If the updateType includes zoom, then this value will be used to calculate the new zoom scale for the camera.
 */
-(void)updateMapCamera:(TriceMapCameraUpdateType)updateType centerPoint:(CGPoint)centerPoint rotation:(CGFloat)rotationDegrees zoom:(CGFloat)zoomScale;

- (BOOL)hasLoadedWayfindingInfoForFloor:(TriceFloor *)floor;

@property (nonatomic, assign, readonly) TriceMapViewState state;

- (void)startWayfindingFromLocation:(TriceMarker *)fromLocation toLocation:(TriceMarker *)toLocation;
- (void)endWayfinding;

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

/**
 *  This method is called whenever the floorplan image finishes loading, and will be displayed imminently. This is a good time to hide any loading views that may be active if the floor is the current floor.
 *
 *  @param mapView The map view whose floorplan image loaded.
 *  @param floor   The floor which floorplan has loaded. This may or may not be the current floor.
 */
-(void)triceMapView:(TriceMapView *)mapView floorplanImageDidLoad:(TriceFloor *)floor;

/**
 *  This method is called whenever the mapView fails loading required assets from a network request. Note this is not called for every failure, only those above a certain significance. Examples of significant errors include when the map fails retrieving its list of floors, or list of markers for the current floor. Not significant errors include failing to download a single marker's image.
 *
 *  @param mapView The map view which failed loading.
 *  @param error   The error object describing the problem.
 */
-(void)triceMapView:(TriceMapView *)mapView didFailLoadingWithError:(NSError *)error;


- (void)triceMapView:(TriceMapView *)mapView didLoadWayfindingInfoForFloor:(TriceFloor *)floor;

@end

NS_ASSUME_NONNULL_END
