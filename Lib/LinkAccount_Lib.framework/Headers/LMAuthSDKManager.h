//
//  LMAuthSDKManager.h
//  LinkAccount
//
//  Created by bindx on 2019/6/6.
//  Copyright © 2019 bindx. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LMCustomModel.h"


NS_ASSUME_NONNULL_BEGIN

@interface LMAuthSDKManager : NSObject
    
/**
获取SDK Manager单例对象
参数：无
返回：单例
*/
+ (LMAuthSDKManager *)sharedSDKManager;

/**
获取SDK版本号
参数：无
返回：字符串，sdk版本号
*/
+ (NSString *_Nonnull)getVersion;

/**
初始化SDK
@param key LinkAccount Key
@param complete 初始化结果
 */
+ (void)initWithKey:(NSString *)key complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 预取号
 初始化方法内部会自动执行一次预取号，一般情况下外部可无需调用
 建议在即将执行一键登录的地方的前60s调用此方法，比如调一键登录的vc的viewdidload中，当初始化的预取号失败的情况下，此调用将有助于提高拉起授权页的速度和成功率
 不建议频繁的多次调用和在拉起授权页后调用
 @param timeout 超时时间 传值小于等于0则使用默认超时时间5秒(联通小于5秒默认为5秒, 电信小于3秒默认为3秒)
 @param complete 预取号结果
 */
+ (void)getMobileAuthWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 获取SDK预初始化完成情况（成功/失败），用户可以在将要调用一键登录方法处，通过此方法获取SDK预初始化情况，对于预初始化失败的，仍可以直接调一键登录接口，由用户自行决定
 @return status
 */

/**
 获取本机号码校验Code
 调用此接口之前需要先调用getMobileAuthWithTimeout接口
 @param timeout 超时时间 传值小于等于0则使用默认超时时间5秒(联通小于5秒默认为5秒, 电信小于3秒默认为3秒)
 @param complete 回调，向服务端i传递accessCode + 本机号码服务端返回结果
 */
- (void)getAccessCodeWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 调起登录页面 ⚠️Block内请使用`weakSelf`防止循环引用⚠️
 调用此接口之前需要先调用getMobileAuthWithTimeout接口
 @param vc 当前vc容器，用于一键登录授权页面切换
 @param model 自定义授权页面选项，可为nil，采用默认的授权页面
 @param timeout 超时时间 传值小于等于0则使用默认超时时间5秒(联通小于5秒默认为5秒, 电信小于3秒默认为3秒)
 @param complete 字典形式
 */
- (void)getLoginTokenWithController:(UIViewController *_Nonnull)vc model:(LMCustomModel *_Nullable)model timeout:(NSTimeInterval )timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete clickLoginBtn:(void(^)(UIViewController *loginVc))clickLogin otherLogin:(void(^)(UIViewController *loginVc))otherBlock;

/**
 无界面取号
 @param timeout 超时时间 传值小于等于0则使用默认超时时间5秒(联通小于5秒默认为5秒, 电信小于3秒默认为3秒)
 @param vc 传当前调用该方法的控制器
 @param complete 字典形式
 */
- (void)getAccessTokenWithTimeout:(NSTimeInterval)timeout controller:(UIViewController *_Nonnull)vc complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 关闭授权页面
 */
- (void)closeAuthView;

/**
 获取隐私协议复选框是否选中
 */
@property (nonatomic, assign, getter=isPrivacyChecked) BOOL privacyChecked;

#pragma mark - ⚠️⚠️

/**
 用户请不要使用此属性
 */
@property (nonatomic, assign, readonly) NSTimeInterval accessTokenTimeout;

@end


NS_ASSUME_NONNULL_END
