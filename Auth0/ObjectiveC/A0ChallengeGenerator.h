// A0ChallengeGenerator.h
//
// Copyright (c) 2016 Auth0 (http://auth0.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

#if WEB_AUTH_PLATFORM

NS_ASSUME_NONNULL_BEGIN
@interface A0SHA256ChallengeGenerator : NSObject
@property (readonly, strong, nonatomic) NSString *verifier;
@property (readonly, strong, nonatomic) NSString *challenge;
@property (readonly, strong, nonatomic) NSString *method;

- (instancetype)init;
- (instancetype)initWithVerifier:(NSData *)verifier;

@end
NS_ASSUME_NONNULL_END
#endif

  
  
  
  
  
  
  
  

#if __has_include("LocalAuthentication/LocalAuthentication.h")

#import <LocalAuthentication/LocalAuthentication.h>

#endif

///---------------------------------------------------
/// @name Keychain Items Accessibility Values
///---------------------------------------------------

/**
 *  Enum with Kechain items accessibility types. It's a mirror of `kSecAttrAccessible` values.
 */
typedef NS_ENUM(NSInteger, A0SimpleKeychainItemAccessible) {
    /**
     *  @see kSecAttrAccessibleWhenUnlocked
     */
    A0SimpleKeychainItemAccessibleWhenUnlocked = 0,
    /**
     *  @see kSecAttrAccessibleAfterFirstUnlock
     */
    A0SimpleKeychainItemAccessibleAfterFirstUnlock,
    /**
     *  @see kSecAttrAccessibleAlways
     */
    A0SimpleKeychainItemAccessibleAlways,
    /**
     *  @see kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly
     */
    A0SimpleKeychainItemAccessibleWhenPasscodeSetThisDeviceOnly,
    /**
     *  @see kSecAttrAccessibleWhenUnlockedThisDeviceOnly
     */
    A0SimpleKeychainItemAccessibleWhenUnlockedThisDeviceOnly,
    /**
     *  kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly
     */
    A0SimpleKeychainItemAccessibleAfterFirstUnlockThisDeviceOnly,
    /**
     *  @see kSecAttrAccessibleAlwaysThisDeviceOnly
     */
    A0SimpleKeychainItemAccessibleAlwaysThisDeviceOnly
};

#define A0ErrorDomain @"com.auth0.simplekeychain"

#define A0LocalAuthenticationCapable (TARGET_OS_IOS && __IPHONE_OS_VERSION_MIN_REQUIRED >= 80000) || (TARGET_OS_OSX && __MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2)


/**
 * Enum with keychain error codes. It's a mirror of the keychain error codes. 
 */
typedef NS_ENUM(NSInteger, A0SimpleKeychainError) {
    /**
     * @see errSecSuccess
     */
    A0SimpleKeychainErrorNoError = 0,
    /**
     * @see errSecUnimplemented
     */
    A0SimpleKeychainErrorUnimplemented = -4,
    /**
     * @see errSecParam
     */
    A0SimpleKeychainErrorWrongParameter = -50,
    /**
     * @see errSecAllocate
     */
    A0SimpleKeychainErrorAllocation = -108,
    /**
     * @see errSecNotAvailable
     */
    A0SimpleKeychainErrorNotAvailable = -25291,
    /**
     * @see errSecAuthFailed
     */
    A0SimpleKeychainErrorAuthFailed = -25293,
    /**
     * @see errSecDuplicateItem
     */
    A0SimpleKeychainErrorDuplicateItem = -25299,
    /**
     * @see errSecItemNotFound
     */
    A0SimpleKeychainErrorItemNotFound = -25300,
    /**
     * @see errSecInteractionNotAllowed
     */
    A0SimpleKeychainErrorInteractionNotAllowed = -25308,
    /**
     * @see errSecDecode
     */
    A0SimpleKeychainErrorDecode = -26275
};

NS_ASSUME_NONNULL_BEGIN

/**
 *  A simple helper class to deal with storing and retrieving values from iOS Keychain.
 *  It has support for sharing keychain items using Access Group and also for iOS 8 fine grained accesibility over a specific Kyechain Item (Using Access Control).
 *  The support is only available for iOS 8+, otherwise it will default using the coarse grained accesibility field.
 *  When a `NSString` or `NSData` is stored using Access Control and the accesibility flag `A0SimpleKeychainItemAccessibleWhenPasscodeSetThisDeviceOnly`, iOS will prompt the user for it's passcode or pass a TouchID challenge (if available).
 */
@interface A0SimpleKeychain : NSObject

/**
 *  Service name under all items are saved. Default value is Bundle Identifier.
 */
@property (readonly, nonatomic) NSString *service;

/**
 *  Access Group for Keychain item sharing. If it's nil no keychain sharing is possible. Default value is nil.
 */
@property (readonly, nullable, nonatomic) NSString *accessGroup;

/**
 *  What type of accessibility the items stored will have. All values are translated to `kSecAttrAccessible` constants.
 *  Default value is A0SimpleKeychainItemAccessibleAfterFirstUnlock.
 *  @see kSecAttrAccessible
 */
@property (assign, nonatomic) A0SimpleKeychainItemAccessible defaultAccessiblity;

/**
 *  Tells A0SimpleKeychain to use `kSecAttrAccessControl` instead of `kSecAttrAccessible`. It will work only in iOS 8+, defaulting to `kSecAttrAccessible` on lower version.
 *  Default value is NO.
 */
@property (assign, nonatomic) BOOL useAccessControl;


/**
*  LocalAuthenticationContext used to access items. Default value is a new LAContext object
*/
#if A0LocalAuthenticationCapable
@property (readonly, nullable, nonatomic) LAContext *localAuthenticationContext;
#endif

///---------------------------------------------------
/// @name Initialization
///---------------------------------------------------

/**
 *  Initialise a `A0SimpleKeychain` with default values.
 *
 *  @return an initialised instance
 */
- (instancetype)init;

/**
 *  Initialise a `A0SimpleKeychain` with a given service.
 *
 *  @param service name of the service to use to save items.
 *
 *  @return an initialised instance.
 */
- (instancetype)initWithService:(NSString *)service;

/**
 *  Initialise a `A0SimpleKeychain` with a given service and access group.
 *
 *  @param service name of the service to use to save items.
 *  @param accessGroup name of the access group to share items.
 *
 *  @return an initialised instance.
 */
- (instancetype)initWithService:(NSString *)service accessGroup:(nullable NSString *)accessGroup;

/**
 *  The duration for which Touch ID authentication reuse is allowable.
 *  Maximun value is LATouchIDAuthenticationMaximumAllowableReuseDuration
 */
#if A0LocalAuthenticationCapable
- (void)setTouchIDAuthenticationAllowableReuseDuration:(NSTimeInterval) duration API_AVAILABLE(ios(8), macosx(10.12)) API_UNAVAILABLE(watchos, tvos);
#endif

///---------------------------------------------------
/// @name Store values
///---------------------------------------------------

/**
 *  Saves the NSString with the type `kSecClassGenericPassword` in the keychain.
 *
 *  @param string value to save in the keychain
 *  @param key    key for the keychain entry.
 *
 *  @return if the value was saved it will return YES. Otherwise it'll return NO.
 */
- (BOOL)setString:(NSString *)string forKey:(NSString *)key;

/**
 *  Saves the NSData with the type `kSecClassGenericPassword` in the keychain.
 *
 *  @param data value to save in the keychain
 *  @param key    key for the keychain entry.
 *
 *  @return if the value was saved it will return YES. Otherwise it'll return NO.
 */
- (BOOL)setData:(NSData *)data forKey:(NSString *)key;

/**
 *  Saves the NSString with the type `kSecClassGenericPassword` in the keychain.
 *
 *  @param string   value to save in the keychain
 *  @param key      key for the keychain entry.
 *  @param message  prompt message to display for TouchID/passcode prompt if neccesary
 *
 *  @return if the value was saved it will return YES. Otherwise it'll return NO.
 */
- (BOOL)setString:(NSString *)string forKey:(NSString *)key promptMessage:(nullable NSString *)message;

/**
 *  Saves the NSData with the type `kSecClassGenericPassword` in the keychain.
 *
 *  @param data   value to save in the keychain
 *  @param key      key for the keychain entry.
 *  @param message  prompt message to display for TouchID/passcode prompt if neccesary
 *
 *  @return if the value was saved it will return YES. Otherwise it'll return NO.
 */
- (BOOL)setData:(NSData *)data forKey:(NSString *)key promptMessage:(nullable NSString *)message;

///---------------------------------------------------
/// @name Remove values
///---------------------------------------------------

/**
 *  Removes an entry from the Keychain using its key
 *
 *  @param key the key of the entry to delete.
 *
 *  @return If the entry was removed it will return YES. Otherwise it will return NO.
 */
- (BOOL)deleteEntryForKey:(NSString *)key;

/**
 *  Remove all entries from the kechain with the service and access group values.
 */
- (void)clearAll;

///---------------------------------------------------
/// @name Obtain values
///---------------------------------------------------

/**
 *  Fetches a NSString from the keychain
 *
 *  @param key the key of the value to fetch
 *
 *  @return the value or nil if an error occurs.
 */
- (nullable NSString *)stringForKey:(NSString *)key;

/**
 *  Fetches a NSData from the keychain
 *
 *  @param key the key of the value to fetch
 *
 *  @return the value or nil if an error occurs.
 */
- (nullable NSData *)dataForKey:(NSString *)key;

/**
 *  Fetches a NSString from the keychain
 *
 *  @param key     the key of the value to fetch
 *  @param message prompt message to display for TouchID/passcode prompt if neccesary
 *
 *  @return the value or nil if an error occurs.
 */
- (nullable NSString *)stringForKey:(NSString *)key promptMessage:(nullable NSString *)message;

/**
 *  Fetches a NSData from the keychain
 *
 *  @param key     the key of the value to fetch
 *  @param message prompt message to display for TouchID/passcode prompt if neccesary
 *
 *  @return the value or nil if an error occurs.
 */
- (nullable NSData *)dataForKey:(NSString *)key promptMessage:(nullable NSString *)message;

/**
 *  Fetches a NSData from the keychain
 *
 *  @param key     the key of the value to fetch
 *  @param message prompt message to display for TouchID/passcode prompt if neccesary
 *  @param err     Returns an error, if the item cannot be retrieved. F.e. item not found 
 *                 or user authentication failed in TouchId case.
 *
 *  @return the value or nil if an error occurs.
 */
- (nullable NSData *)dataForKey:(NSString *)key promptMessage:(nullable NSString *)message error:(NSError **)err;

/**
 *  Checks if a key has a value in the Keychain
 *
 *  @param key the key to check if it has a value
 *
 *  @return if the key has an associated value in the Keychain or not.
 */
- (BOOL)hasValueForKey:(NSString *)key;

///---------------------------------------------------
/// @name Create helper methods
///---------------------------------------------------

/**
 *  Creates a new instance of `A0SimpleKeychain`
 *
 *  @return a new instance
 */
+ (A0SimpleKeychain *)keychain;

/**
 *  Creates a new instance of `A0SimpleKeychain` with a service name.
 *
 *  @param service name of the service under all items will be stored.
 *
 *  @return a new instance
 */
+ (A0SimpleKeychain *)keychainWithService:(NSString *)service;

/**
 *  Creates a new instance of `A0SimpleKeychain` with a service name and access group
 *
 *  @param service     name of the service under all items will be stored.
 *  @param accessGroup name of the access group to share keychain items.
 *
 *  @return a new instance
 */
+ (A0SimpleKeychain *)keychainWithService:(NSString *)service accessGroup:(NSString *)accessGroup;

@end

NS_ASSUME_NONNULL_END

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
typedef NS_ENUM(NSUInteger, A0SimpleKeychainRSAKeySize) {
    A0SimpleKeychainRSAKeySize512Bits = 512,
    A0SimpleKeychainRSAKeySize1024Bits = 1024,
    A0SimpleKeychainRSAKeySize2048Bits = 2048
};

NS_ASSUME_NONNULL_BEGIN

/**
 *  Category of `A0SimpleKeychain` to handle RSA pairs keys in the Keychain
 */
@interface A0SimpleKeychain (KeyPair)

/**
 *  Generates a RSA key pair with a specific length and tags. 
 *  Each key is marked as permanent in the Keychain
 *
 *  @param keyLength     number of bits of the keys.
 *  @param publicKeyTag  tag of the public key
 *  @param privateKeyTag tag of the private key
 *
 *  @return if the key par is created it will return YES, otherwise NO.
 */
- (BOOL)generateRSAKeyPairWithLength:(A0SimpleKeychainRSAKeySize)keyLength
                        publicKeyTag:(NSString *)publicKeyTag
                       privateKeyTag:(NSString *)privateKeyTag;

/**
 *  Returns a RSA key as NSData.
 *
 *  @param keyTag tag of the key
 *
 *  @return the key as NSData or nil if not found
 */
- (nullable NSData *)dataForRSAKeyWithTag:(NSString *)keyTag;

/**
 *  Removes a key using its tag.
 *
 *  @param keyTag tag of the key to remove
 *
 *  @return if the key was removed successfuly.
 */
- (BOOL)deleteRSAKeyWithTag:(NSString *)keyTag;

/**
 *  Returns a RSA key as `SecKeyRef`. You must release it when you're done with it
 *
 *  @param keyTag tag of the RSA Key
 *
 *  @return SecKeyRef of RSA Key
 */
- (nullable SecKeyRef)keyRefOfRSAKeyWithTag:(NSString *)keyTag;

/**
 *  Checks if a RSA key exists with a given tag.
 *
 *  @param keyTag tag of RSA Key
 *
 *  @return if the key exists or not.
 */
- (BOOL)hasRSAKeyWithTag:(NSString *)keyTag;

@end

@interface A0SimpleKeychain (Deprecated)

/**
 *  Returns the public key as NSData.
 *
 *  @param keyTag tag of the public key
 *
 *  @return the public key as NSData or nil if not found
 *  
 *  @deprecated 0.2.0
 */
- (nullable NSData *)publicRSAKeyDataForTag:(NSString *)keyTag __attribute__((deprecated));

@end

NS_ASSUME_NONNULL_END
