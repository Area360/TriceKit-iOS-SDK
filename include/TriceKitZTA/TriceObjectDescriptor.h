//
//  TriceObjectDescriptor.h
//  TriceKit
//
//  Created by Jake Bellamy on 10/03/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  An instance of TriceObjectDescriptor forms a basis for describing TriceKit model objects, specifically a TriceZone or TriceTrigger object. You construct an instance of this class to describe a model, and pass that to another class (such as TriceTriggerManager) to retrieve the desired instance.
 */
@interface TriceObjectDescriptor : NSObject

/**
 *  Constructs an object descriptor with the specified uid.
 *
 *  @param uid The unique identifier to match.
 *
 *  @return A initialized instance.
 */
+(instancetype)descriptorWithUid:(NSString *)uid;

/**
 *  Constructs and object descriptor that tests the value that is identified by a given key.
 *
 *  @param key  The property key to use when performing a comparison. In the comparison, the property is accessed using key-value coding (see [Key-Value Coding Programming Guide](https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/KeyValueCoding/Articles/KeyValueCoding.html)).
 *  @param test A block that tests the value identified by the key. The block has one parameter, obj, which is the value returned from accessing the property given by key. The block returns a BOOL to indicate whether the test passed, and the model being described should be included.
 *
 *  @return An initialized instance.
 */
+(instancetype)descriptorWithKey:(NSString *)key passingTest:(BOOL (^)(id obj))test;

/**
 *  Constructs an object descriptor that that always evaluates to a given value.
 *
 *  @param value The value to which the new predicate should evaluate.
 *
 *  @return A descriptor that always evaluates to value.
 */
+(instancetype)descriptorWithValue:(BOOL)value;

/**
 *  Returns a Boolean value that indicates whether a given object matches the conditions specified by the receiver.
 *
 *  @param object The object against which to evaluate the receiver.
 *
 *  @return YES if object matches the conditions specified by the receiver, otherwise NO.
 */
-(BOOL)evaluateWithObject:(id)object;

@end

NS_ASSUME_NONNULL_END
