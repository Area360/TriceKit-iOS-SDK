//  Copyright © 2016 Area360. All rights reserved.
#ifndef TK_TRIGGER_H_INCLUDED
#define TK_TRIGGER_H_INCLUDED

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

@class NSUUID;
@class TKAction;

@protocol TKCallbackAction;

@interface TKTrigger : NSObject

-(instancetype)init NS_UNAVAILABLE;

@property(atomic, readonly) NSString *name;
@property(atomic, readonly) NSUUID *uuid;

-(NSArray<TKAction *> *)allActions;
-(TKAction *)attachAction:(id<TKCallbackAction>)action;

@end

#endif
