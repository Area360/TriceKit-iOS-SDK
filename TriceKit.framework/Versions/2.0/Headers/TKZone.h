//  Copyright © 2016 Area360. All rights reserved.
#ifndef TK_ZONE_H_INCLUDED
#define TK_ZONE_H_INCLUDED

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

@class NSUUID;
@class TKTrigger;

@interface TKZone: NSObject

-(instancetype)init NS_UNAVAILABLE;

@property(atomic,readonly) NSString *name;
@property(atomic,readonly) NSUUID *uuid;

-(NSArray<TKTrigger *> *)allTriggers;

@end

#endif
