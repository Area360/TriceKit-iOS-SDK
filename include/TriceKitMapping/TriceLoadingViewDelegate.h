//
//  TriceLoadingViewDelegate.h
//  TriceKit
//
//  Created by Jake Bellamy on 21/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Protocol used for a loading view to display and hide a itself when required, such as when a network request starts and when that request completes.
 */
@protocol TriceLoadingViewDelegate <NSObject>

/**
 *  The view that the loading view will be added as a subview to on a call to startLoadingAnimated:.
 */
@property (nonatomic, strong, nullable) UIView *targetView;

/**
 *  Starts the loading view. You are responsible for adding the loading view as a subview to targetView and also setting up any needed constraints before displaying it.
 *
 *  @param animated Whether displaying the loading view should be animated.
 */
-(void)startLoadingAnimated:(BOOL)animated;

/**
 *  Stops the loading view. You are responsible for removing the loading view from targetView and stopping any animations.
 *
 *  @param animated Whether hiding the loading view should be animated.
 */
-(void)stopLoadingAnimated:(BOOL)animated;

@end

NS_ASSUME_NONNULL_END
