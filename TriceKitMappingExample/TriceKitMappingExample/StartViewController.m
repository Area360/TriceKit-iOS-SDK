//
//  StartViewController.m
//  TriceKitMappingExample
//
//  Created by Jake Bellamy on 29/02/16.
//  Copyright © 2016 STQRY. All rights reserved.
//

#import "StartViewController.h"
#import "MarkerDetailViewController.h"
#import <TriceKit/TriceKitMapping.h>

@implementation StartViewController

- (IBAction)startMappingButtonPressed:(UIButton *)sender
{
    TriceMapViewController *mapViewController = [TriceMapViewController mapViewControllerForBuilding:^BOOL(TriceBuilding * _Nonnull building) {
        return YES;
    }];
    
    UINavigationController *navigationController = self.navigationController;
    UIStoryboard *storyboard = self.storyboard;
    
    mapViewController.markerSelectedAction = ^(TriceMarker *marker) {
        MarkerDetailViewController *detailViewController = [storyboard instantiateViewControllerWithIdentifier:NSStringFromClass(MarkerDetailViewController.class)];
        detailViewController.marker = marker;
        [navigationController pushViewController:detailViewController animated:YES];
    };
    
    [navigationController pushViewController:mapViewController animated:YES];
}

@end
