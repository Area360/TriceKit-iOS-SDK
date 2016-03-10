// Copyright © 2016 Area360.
// All rights reserved.
//
// This file is released under the New BSD License (see NewBSDLicense.txt).

#import "ViewController.h"
#import "ZTADemoApplication.h"
#import "TriceKit/TKTriceKitManager.h"


@interface ViewController ()

@end


@implementation ViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)onStartButtonClick:(id)sender
{
    ZTADemoApplication *demoApplication = [ZTADemoApplication demoApplication];
    [demoApplication.triceKitManager start];
}


@end
