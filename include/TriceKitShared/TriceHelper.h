//
//  TriceHelper.h
//  TriceKit
//
//  Created by Jake Bellamy on 8/12/14.
//  Copyright (c) 2014 STQRY. All rights reserved.
//

#import <CoreLocation/CLLocationManager.h>
#import <CoreGraphics/CoreGraphics.h>

#define TriceLog(str, ...) if (TriceDEBUG) { NSLog(@"TriceKit: " str, ##__VA_ARGS__); }

#define TriceNilPtrErrorLog(description)      TriceLog(@"No error pointer passed to %s! ERROR: %@", __PRETTY_FUNCTION__, description)
#define TriceNilBlockErrorLog(description)    TriceLog(@"No error block assigned to %@! ERROR: %@", NSStringFromClass([self class]), description)
#define TriceNoDelegatesErrorLog(description) TriceLog(@"No registered delegates assigned to %@! ERROR: %@", NSStringFromClass([self class]), description)

#ifdef __cplusplus
extern "C" {
#endif

typedef NSString TriceDeviceKey;
typedef NSString TriceAPIKey;
typedef NSString TriceAPIValue;

extern TriceDeviceKey * const TriceKeyDeviceUuid;
extern TriceDeviceKey * const TriceKeyDeviceModel;
extern TriceDeviceKey * const TriceKeyDeviceOS;
extern TriceDeviceKey * const TriceKeyDeviceOSVersion;
extern TriceDeviceKey * const TriceKeyDeviceCarrier;
extern TriceDeviceKey * const TriceKeyDeviceScreenResolution;
extern TriceDeviceKey * const TriceKeyDeviceNetworkSSID;
extern TriceDeviceKey * const TriceKeyDeviceGPSLongitude;
extern TriceDeviceKey * const TriceKeyDeviceGPSLatitude;
extern TriceDeviceKey * const TriceKeyDeviceGPSAltitude;
extern TriceDeviceKey * const TriceKeyDeviceGPSAccuracy;
extern TriceDeviceKey * const TriceKeyDeviceCompassHeading;
extern TriceDeviceKey * const TriceKeyDeviceTravellingSpeed;
extern TriceDeviceKey * const TriceKeyDeviceInMotion;

extern TriceAPIKey    * const TriceKeyUsername;
extern TriceAPIKey    * const TriceKeyAPIKey;
extern TriceAPIKey    * const TriceKeySDKVersion;
extern TriceAPIKey    * const TriceKeyDeviceInformation;

extern TriceAPIValue  * const TriceErrorDomain;
extern TriceAPIValue  * const TriceBaseUrl;
extern TriceAPIValue  * const TriceValueSDKVersion;
extern TriceAPIValue  *       TriceValueUsername;
extern TriceAPIValue  *       TriceValueAPIKey;

extern BOOL                   TriceDEBUG;

/**
 *  Trice error codes that are used in the TriceKit SDK.
 */
typedef NS_ENUM(NSInteger, TriceErrorCode) {
    TriceConfigUsernameValueNotPresent = 1001,  ///< Username not found in the Trice configuration property list.
    TriceConfigAPIKeyValueNotPresent,           ///< API Key not found in the Trice configuration property list.
    TriceLocationServicesDisabled,              ///< Location services are disabled in phone settings.
    TriceBluetoothUnsupported,                  ///< Core Bluetooth is not supported on this device.
    TriceBluetoothUnauthorized,                 ///< Access to Core Bluetooth has been denied.
    TriceBluetoothPoweredOff,                   ///< Bluetooth is turned off.
    TriceRequestManagerNilUrl,                  ///< URL provided to a network request was nil.
    TriceRequestManagerResponse,                ///< Error in a network request.
    TriceModelValidationError                   ///< An object model attempted to be serialized but failed validation.
};

@class UIViewController;

/**
 *  Gets the cached folder directory used by TriceKit, creating it if it does not already exist.
 *
 *  @return The absolute path to the cache directory.
 */
NSString * cacheDirectoryPath();

/**
 *  Gets the local cached file path that is used for a given url.
 *
 *  @note This file may or may not exist. It is your responsibility to check before attempting to use this file.
 *
 *  @param url The url that is used to identify the file.
 *
 *  @return The absolute path to the cached file.
 */
NSString * cachedFilePathForUrl(NSString *url);

/**
 *  Tests a geographical coordinate for whether it is inside or outside of a polygon of coordinates.
 *
 *  @param testCoordinate The coordinate point to test.
 *  @param coordinates    An array of coordinates that makes up the polygon area.
 *  @param count          The number of elements in the coordinates array.
 *
 *  @return YES if the coordinate is inside the polygon, otherwise NO if it is outside.
 */
BOOL CLLocationCoordinate2DIsInsidePolygon(CLLocationCoordinate2D testCoordinate, CLLocationCoordinate2D coordinates[], NSUInteger count);

/**
 *  Gets the currently displayed full screen view controller. This ignores any child view controllers.
 *
 *  @return The currently displayed view controller.
 */
UIViewController * topViewController();

/**
 *  Tests any object presented to it for it's emptiness. For example an NSArray with zero elements is considered empty.
 *
 *  @param thing The object to test.
 *
 *  @return YES if the object is empty, otherwise NO.
 */
NS_INLINE BOOL isEmpty(id thing) {
    return !thing
    || [thing isKindOfClass:[NSNull class]]
    || ([thing respondsToSelector:@selector(length)] && [((id)thing) length] == 0)
    || ([thing respondsToSelector:@selector(count)]  && [((id)thing) count]  == 0);
}

/**
 *  Returns the negated value of isEmpty(thing). Is defined for readability purposes.
 *
 *  @param thing The object to test.
 *
 *  @return NO if the object is empty, otherwise YES.
 */
NS_INLINE BOOL isNotEmpty(id thing) {
    return !isEmpty(thing);
}

/**
 *  Tests a given integer to see if it is a power of two.
 *
 *  @param a The integer to test.
 *
 *  @return YES if the integer is a power of two, otherwise NO.
 */
NS_INLINE BOOL isPowerOfTwo(unsigned int a) {
    return ((a != 0) && ((a & (~a + 1)) == a));
}

/**
 *  Calculates the next valid power of two for the integer specified. If the integer is already a power of two, then returns that same integer value. For example, calling this with a value of 2 will return 2, not 4.
 *
 *  @param a The integer to check.
 *
 *  @return An integer equalling (a) if (a) is already a power of two, otherwise the next largest integer that is a power of two.
 */
NS_INLINE int nextPowerOfTwo(int a) {
    int b = 1;
    for (; b < a; b <<= 1);
    return b;
}
    
/**
 *  Reverses an array of characters. This does not create and return new array, instead it directly modifies the array that is passed in.
 *
 *  @param b A C array of char to swap.
 *  @param c The number of elements in the byte array.
 */
NS_INLINE void reverseChars(unsigned char * b, size_t c) {
    for (unsigned char *i = b, *j = b + c - 1; i < b + c / 2; i++, j--) {
        *i ^= *j; *j ^= *i; *i ^= *j;
    }
}

/**
 *  A convenience wrapper function around NSFileManager for checking whether a file exists.
 *
 *  @param path The absolute file path to check.
 *
 *  @return YES if a file exists at the given path, otherwise NO.
 */
NS_INLINE BOOL fileExists(NSString *path) {
    return [[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:nil];
}

/**
 *  A convenience function for checking whether a cached file exists for a given url identifier.
 *
 *  @param url The url that is used to identify the file.
 *
 *  @return YES if the file exists, otherwise NO.
 */
NS_INLINE BOOL cachedFileExistsForUrl(NSString *url) {
    return fileExists(cachedFilePathForUrl(url));
}

/**
 *  Returns the relative difference between two floating-point values. Useful for checking whether two floating-point values are approximately equal to each other when the result is compared against a very small value. In this example using a standard equality check (==) would fail:
 *
 *  @code
 const CGFloat EPSILON = 0.0000001;
 CGFloat a1 = 0.1f + 0.2f;
 CGFloat a2 = 0.3f;
 
 if (relDiff(a1, a2) <= EPSILON) {
    // These are approx. equal
 }
 *  @endcode
 *
 *  @param a First value.
 *  @param b Second value.
 *
 *  @return The difference between the first and second value.
 */
NS_INLINE CGFloat relDiff(CGFloat a, CGFloat b) {
    CGFloat c = ABS(a), d = ABS(b); d = MAX(c, d);
    return d == 0.0 ? 0.0 : ABS(a - b) / d;
}

/**
 *  Compares two CGSize values to see if they are approximately equal to each other.
 *
 *  @param size1 The first size.
 *  @param size2 The second size.
 *  @param delta The maximum difference the width and height may differ by.
 *
 *  @return YES if the two sizes are approximately equal as given by delta, otherwise NO.
 */
NS_INLINE BOOL CGSizeApproxEqualToSize(CGSize size1, CGSize size2, CGFloat delta) {
    return (relDiff(size1.width,  size2.width ) <= delta &&
            relDiff(size1.height, size2.height) <= delta);
}

/**
 *  This class provides helper methods and constants that are used throughout TriceKit.
 */
@interface TriceHelper : NSObject

/**
 *  Retrieves information about the device.
 *
 *  @return A dictionary containing device information stored in the predefined keys.
 */
+(NSDictionary *)deviceInformation;

/**
 *  Gets the SSID of the WiFi network the device is currently connected to.
 *
 *  @return The SSID of the current WiFi network, or nil if it is not currently connected to any networks.
 */
+(NSString *)networkSSID;

/**
 *  Gets the stored unique identifier for the device, creating one if it does not already exist.
 *
 *  @return The device UUID.
 */
+(NSString *)uuid;

/**
 *  Retrieves information about the geo-location position and speed of the device.
 *
 *  @param locationManager The location manager used to retrieve values from.
 *
 *  @return A dictionary containing geo-location information stored in the predefined keys.
 */
+(NSDictionary *)geoPositionInformation:(CLLocationManager *)locationManager;

/**
 *  Retrieves the Trice configuration out of a given dictionary and returns them if successful.
 *
 *  @param dictionary The dictionary to load the configuration values from.
 *  @param error      If an error occurs, upon return contains an NSError object that describes the problem.
 *
 *  @return A new NSDictionary containing values in the configuration file, or nil if an error occured during loading or verification.
 */
+(NSDictionary *)triceAPIValuesFromDictionary:(NSDictionary *)dictionary error:(NSError **)error;

@end
    
#ifdef __cplusplus
}
#endif
