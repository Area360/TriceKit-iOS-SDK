//
//  TriceMarker.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import "MTLModel.h"
#import "MTLJSONAdapter.h"
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  The type of marker that a TriceMarker may be.
 */
typedef NS_ENUM(NSInteger, TriceMarkerType){
    TriceMarkerTypeUnknown, ///< Unknown marker type.
    TriceMarkerTypePortal,  ///< A portal type. This means this marker may get to other rooms and/or floors.
    TriceMarkerTypePOI,     ///< A point of interest type specific to the purpose of the organization. For example a piece of art inside of an art gallery.
    TriceMarkerTypeFeature  ///< A common feature type. For example, a toilet, ATM, medical area, or public phone.
};

@class TriceFloor;

/**
 *  TriceMarker represents a marker or point of interest used in indoor mapping. TriceFloor holds a list of markers which are displayed using  TriceMapView.
 */
@interface TriceMarker : MTLModel <MTLJSONSerializing>

/// A unique identifier for this marker.
@property (nonatomic, copy, readonly)   NSString *uid;

/// The unique identifier of the room that this marker exists in.
@property (nonatomic, copy, readonly)   NSString *roomUid;

/// The type of marker this is.
@property (nonatomic, assign, readonly) TriceMarkerType type;

/// The subtype of marker this is.
@property (nonatomic, copy, readonly)   NSString *subtype;

/// A human readable name for this marker. This is the name that is specified in the TriceKit CMS.
@property (nonatomic, copy, readonly)   NSString *name;

/// The location on the map that this marker is.
@property (nonatomic, assign, readonly) CGPoint coordinate;

/// The image URL to the icon for displaying this marker.
@property (nonatomic, copy, readonly)   NSURL *iconUrl;

/// The image URL to the story image, if applicable.
@property (nonatomic, copy, readonly)   NSURL *storyImageUrl;

/// The unique identifier of the story this links to, if applicable.
@property (nonatomic, copy, readonly)   NSString *storyUid;

/// The floor that this marker is on.
@property (nonatomic, weak)             TriceFloor *floor;

@end

NS_ASSUME_NONNULL_END
