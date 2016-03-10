// Copyright © 2016 Area360.
// All rights reserved.
//
// This file is released under the New BSD License (see NewBSDLicense.txt).

#import "TriceKitStatusViewController.h"
#import "ZTADemoApplication.h"
#import "TriceKit/TKTriceKitManager.h"


@interface TriceKitStatusViewController ()

@property (weak, nonatomic) IBOutlet UIButton *btnStopTriceKit;
@property (weak, nonatomic) IBOutlet UILabel *lblTriceKitStatus;

@end


@implementation TriceKitStatusViewController


-(void)dealloc
{
    [[ZTADemoApplication demoApplication].triceKitManager removeObserver:self forKeyPath:@"triceKitState"];
}


-(void)triceKitStateUpdated
{
    TKTriceKitState newState = [ZTADemoApplication demoApplication].triceKitManager.triceKitState;
    self.btnStopTriceKit.enabled = (newState == TKSStarting) || (newState == TKSStarted);
    switch (newState)
    {
        case TKSStopped:
            self.lblTriceKitStatus.text = @"Status: Stopped";
            [self.navigationController popViewControllerAnimated:YES];
            break;
        case TKSStarting: self.lblTriceKitStatus.text = @"Status: Starting"; break;
        case TKSStarted:  self.lblTriceKitStatus.text = @"Status: Started"; break;
        case TKSStopping: self.lblTriceKitStatus.text = @"Status: Stopping"; break;
        default:          self.lblTriceKitStatus.text = @"Status: Invalid"; break;
    }
}


-(void)viewDidLoad
{
    NSLog(@"TriceKitStatus view did load.");

    [super viewDidLoad];

    [self triceKitStateUpdated];

    [[ZTADemoApplication demoApplication].triceKitManager addObserver:self
                                                           forKeyPath:@"triceKitState"
                                                              options:0
                                                              context:NULL];
    NSLog(@"TriceKitStatus view did load complete.");
}


-(IBAction)onStopButtonClick:(id)sender
{
    [[ZTADemoApplication demoApplication].triceKitManager stop];
}


-(void)observeValueForKeyPath:(NSString *)keyPath
                     ofObject:(id)object
                       change:(NSDictionary<NSString *, id> *)change
                      context:(void *)context
{
    if ([keyPath isEqualToString:@"triceKitState"])
    {
        NSLog(@"Got triceKitState change event.");
        [self triceKitStateUpdated];
    }
}


-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
