//
//  TriceMapViewController.h
//  TriceKit
//
//  Created by Jake Bellamy on 10/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "TriceMapView.h"
#import "TriceLoadingViewDelegate.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, TriceMapViewControllerDisplayOptions) {
    TriceMapViewControllerDisplayOptionsNone                 = 0,
    TriceMapViewControllerDisplayOptionsRoundImageCorners    = 1 << 0,
    TriceMapViewControllerDisplayOptionsDisableWayfinding    = 1 << 1,
    TriceMapViewControllerDisplayOptionsDisableFloorSelector = 1 << 2
};

/**
 *  TriceMapViewController manages a TriceMapView to render an entire indoor mapping experience. You should use this class as-is and not subclass it when using this view controller.
 *
 *  To set up mapping in your application using this class you must first have a building that has been set up in the TriceKit CMS. You may then fetch the list of buildings from the TriceKit server, alloc-init a new instance of this class and set its mapView's building, or you may use the convenience constructor mapViewControllerForBuilding: which will do the request for you and allow you to pick the building to use.
 *
 *  When presenting this view controller, it should be inside of a UINavigationController. This is so that it may push on other view controllers in order to do marker searching and routing directions.
 */
@interface TriceMapViewController : GLKViewController <TriceMapViewDelegate>

/**
 *  The loading view that this view controller will use when making network requests.
 *
 *  This property is lazy-loaded. If you do not set this value yourself then a default loading view will be initialized and set to this property when needed.
 */
@property (nonatomic, strong) UIView <TriceLoadingViewDelegate> *loadingView;

/**
 *  The map view that this view controller uses to render indoor mapping.
 */
@property (nonatomic, strong, readonly) TriceMapView *mapView;

/**
 *  A callback block that indicates that the popup info view for a marker was selected.
 */
@property (nonatomic, copy, nullable) void (^markerSelectedAction)(TriceMarker *marker);

@property (nonatomic, assign) TriceMapViewControllerDisplayOptions displayOptions;

/**
 *  Creates a new TriceMapViewController for a given building.
 *
 *  This constructor will request the list of buildings from the TriceKit server if neccessary, caching it in memory for 15 minutes, after which time the cache will be removed and any subsequent calls will send another request.
 *
 *  @param buildingSelectionBlock A BOOL returning block with a single TriceBuilding parameter that allows you to select the building to be loaded for mapping. This block will be invoked for every building that exists in the TriceKit CMS until the first YES is returned from the block.
 *
 *  @return An initialized instance.
 */
+(instancetype)mapViewControllerForBuilding:(BOOL (^)(TriceBuilding *building))buildingSelectionBlock;

@end

NS_ASSUME_NONNULL_END
