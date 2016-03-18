//  Copyright © 2016 Area360. All rights reserved.
#ifndef TK_APIV1_UUID_UTIL_H_INCLUDED
#define TK_APIV1_UUID_UTIL_H_INCLUDED

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

@class NSUUID;

NSUUID *apiv1ZoneIDToUUID(unsigned int zoneID);
NSUUID *apiv1TriggerIDToUUID(unsigned int triggerID);

#endif
