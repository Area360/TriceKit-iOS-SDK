//  Copyright © 2016 Area360. All rights reserved.
#ifndef TK_CALLBACK_ACTION_TYPE_H_INCLUDED
#define TK_CALLBACK_ACTION_TYPE_H_INCLUDED

@class NSString;
@class NSDictionary;

@protocol TKCallbackActionType

-(void)onActionTypeTriggered:(NSString *)actionType metadata:(NSDictionary *)metadata;

@end

#ifdef __cplusplus
extern "C" {
#endif

extern NSString * const kTKLocalNotificationActionType;

#ifdef __cplusplus
}
#endif

#endif
