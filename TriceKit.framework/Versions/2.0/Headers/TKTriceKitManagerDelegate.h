#ifndef TK_TRICEKIT_MANAGER_DELEGATE_H_INCLUDED
#define TK_TRICEKIT_MANAGER_DELEGATE_H_INCLUDED

#include <Foundation/NSObject.h>

@class TKZone;
@class TKTrigger;

@protocol TKTriceKitManagerRemoteUpdateDelegate<NSObject>

@optional
-(void)onTriggerAdded:(TKTrigger *)trigger toZone:(TKZone *)zone;

@end

#endif
