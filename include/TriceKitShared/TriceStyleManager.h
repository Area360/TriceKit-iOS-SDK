//
//  TriceStyleManager.h
//  TriceKit
//
//  Created by Jake Bellamy on 5/01/15.
//  Copyright (c) 2015 STQRY. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NSString TriceColourKey;
typedef NSString TriceFontKey;

extern TriceColourKey * const TriceColourKeyPrimary;
extern TriceColourKey * const TriceColourKeySecondary;
extern TriceColourKey * const TriceColourKeyElements;

extern TriceFontKey   * const TriceFontKeyPrimary;
extern TriceFontKey   * const TriceFontKeySecondary;

/**
 *  TriceStyleManager is a configuration class that holds styling values for any views that are used in the TriceKit SDK. By setting any of the values through this class you may style elements to suit your application.
 */
@interface TriceStyleManager : NSObject

/**
 *  Sets a new font scale for any labels that are displayed. This value is multiplied with the size of all fonts. The default is 1.0.
 *
 *  @param fontScale The new font scale to be used.
 */
+(void)setFontScale:(CGFloat)fontScale;

/**
 *  Adds entries from a dictionary of fonts to use. The keys for each font is defined by the type definition TriceFontKey.
 *
 *  @param fonts A new dictionary of fonts to use.
 */
+(void)setFonts:(NSDictionary *)fonts;

/**
 *  Adds entries from a dictionary of colours to use. The keys for each colour is defined by the type definition TriceColourKey.
 *
 *  @param colours A new dictionary of colours to use.
 */
+(void)setColours:(NSDictionary *)colours;

/**
 *  Gets a colour for a given key.
 *
 *  @param key The colour key.
 *
 *  @return The colour for the given key, or nil if it does not exist.
 */
+(UIColor *)colourForKey:(TriceColourKey *)key;

/**
 *  Gets a font for a given key.
 *
 *  @param key The font key.
 *
 *  @return The font for the given key, or nil if it does not exist.
 */
+(UIFont *)fontForKey:(TriceFontKey *)key;

/**
 *  Gets a font for a given key with a specified point size.
 *
 *  @param key  The font key.
 *  @param size The point size of the font. This value will be multiplied against the fontScale value.
 *
 *  @return The font for the given key with the specified size, or nil if it does not exist.
 */
+(UIFont *)fontForKey:(TriceFontKey *)key size:(CGFloat)size;

@end
