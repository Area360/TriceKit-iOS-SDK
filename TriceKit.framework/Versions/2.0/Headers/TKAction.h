//  Copyright © 2016 Area360. All rights reserved.
#ifndef TK_ACTION_H_INCLUDED
#define TK_ACTION_H_INCLUDED

#import <Foundation/NSObject.h>

@class NSUUID;

@interface TKAction : NSObject

-(instancetype)init NS_UNAVAILABLE;

@property(atomic, readonly) NSUUID *uuid;

@end

#endif
