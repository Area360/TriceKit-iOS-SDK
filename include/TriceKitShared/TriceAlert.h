//
//  TriceAlert.h
//  TriceKit
//
//  Created by Jake Bellamy on 26/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Action block that is executed on the result of an alert.
typedef void(^TriceAlertAction)(void);

/**
 *  TriceAlert provides a convenient interface for displaying an alert to the user. The alert displayed will either be a UIAlertView or UIAlertController depending on the OS version.
 */
@interface TriceAlert : NSObject

/**
 *  Displays an alert on the current view controller.
 *
 *  @param title       The string that appears in the alert's title bar.
 *  @param message     Descriptive text that provides more details than the title.
 *  @param cancelTitle The title of the cancel button or nil if there should be no cancel button.
 *  @param otherTitles An array of  NSString objects which are the titles of the other buttons.
 *  @param actions     An array of block objects that each take no parameters and return void. See the TriceAlertAction type definition. The index of the block in this array corresponds with the index of the otherTitles array. As such, the number of elements in this array must match the number of elements in the otherTitles array. Use [NSNull null] to signify no action for that particular button.
 */
+(void)displayAlertWithTitle:(nullable NSString *)title
                     message:(nullable NSString *)message
                 cancelTitle:(nullable NSString *)cancelTitle
                 otherTitles:(nullable NSArray *)otherTitles
                     actions:(nullable NSArray *)actions;

/**
 *  Displays an alert on the current view controller with two buttons, yes and no. Useful for confirmation alerts.
 *
 *  @param title     The string that appears in the alert's title bar.
 *  @param message   Descriptive text that provides more details than the title.
 *  @param yesAction The block that will be called if the yes button is pressed. May be nil.
 *  @param noAction  The block that will be called if the no button is pressed. May be nil.
 */
+(void)displayYesNoAlertWithTitle:(nullable NSString *)title
                          message:(nullable NSString *)message
                        yesAction:(nullable TriceAlertAction)yesAction
                         noAction:(nullable TriceAlertAction)noAction;

/**
 *  Displays an alert on the current view controller with one 'OK' button.
 *
 *  @param title    The string that appears in the alert's title bar.
 *  @param message  Descriptive text that provides more details than the title.
 *  @param okAction The block that will be called when the OK button is pressed. May be nil.
 */
+(void)displayOkAlertWithTitle:(nullable NSString *)title
                       message:(nullable NSString *)message
                      okAction:(nullable TriceAlertAction)okAction;

/**
 *  Displays an alert on the current view controller to inform the user that an error has occurred.
 *
 *  @param error    The error that occurred that the user should be informed about. The  [NSError localizedDescription] of the alert is used to fill the alert's message.
 *  @param okAction The block that will be called when the OK button is pressed. May be nil.
 */
+(void)displayErrorAlert:(nullable NSError *)error
                okAction:(nullable TriceAlertAction)okAction;

@end
