//
//  MarkerDetailViewController.m
//  TriceKitMappingExample
//
//  Created by Jake Bellamy on 29/02/16.
//  Copyright © 2016 STQRY. All rights reserved.
//

#import "MarkerDetailViewController.h"
#import <TriceKit/TriceKitMapping.h>

@interface MarkerDetailViewController ()

@property (nonatomic, weak) IBOutlet UILabel *detailLabel;

@end

@implementation MarkerDetailViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self updateMarkerLabelText];
}

- (void)updateMarkerLabelText
{
    self.detailLabel.text = [NSString stringWithFormat:NSLocalizedString(@"Selected marker: %@", @""), self.marker.name];
}

- (void)setMarker:(TriceMarker *)marker
{
    _marker = marker;
    
    if (self.isViewLoaded) {
        [self updateMarkerLabelText];
    }
}

@end
