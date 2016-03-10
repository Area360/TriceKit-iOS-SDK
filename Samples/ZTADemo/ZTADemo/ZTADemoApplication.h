// Copyright © 2016 Area360.
// All rights reserved.
//
// This file is released under the New BSD License (see NewBSDLicense.txt).

#import "UIKit/UIApplication.h"

@class TKTriceKitManager;


@interface ZTADemoApplication : UIApplication

@property(strong, atomic, readonly) TKTriceKitManager *triceKitManager;

+(ZTADemoApplication *)demoApplication;

@end
