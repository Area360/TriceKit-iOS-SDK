//
//  TriceCoordinate.h
//  TriceKit
//
//  Created by Jake Bellamy on 9/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import "MTLModel.h"
#import "MTLJSONAdapter.h"
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface TriceCoordinate : MTLModel <MTLJSONSerializing>

@property (nonatomic, assign, readonly) CGFloat x;
@property (nonatomic, assign, readonly) CGFloat y;

+(instancetype)coordinateWithPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
