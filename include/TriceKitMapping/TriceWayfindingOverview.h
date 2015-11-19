//
//  TriceWayfindingOverview.h
//  Pods
//
//  Created by Jake Bellamy on 17/11/15.
//
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>

typedef NS_ENUM(NSInteger, TriceLengthType) {
    TriceLengthTypeMetric,
    TriceLengthTypeImperial
};

@interface TriceWayfindingOverview : NSObject

@property (nonatomic, assign, readonly) CLLocationDistance distance;
@property (nonatomic, assign, readonly) NSTimeInterval     time;
@property (nonatomic, assign, readonly) TriceLengthType    lengthType;

- (instancetype)initWithDistance:(CLLocationDistance)distance
                            time:(NSTimeInterval)time
                      lengthType:(TriceLengthType)lengthType;

@end
