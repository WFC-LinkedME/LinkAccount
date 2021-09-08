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
 建议在即将执行一键登录的地方之前调用此方法，比如调一键登录的vc的viewDidLoad中，此调用将有助于提高拉起授权页的速度和成功率
 不建议频繁的多次调用和在拉起授权页后调用
 @param timeout 超时时间 传值小于等于0则使用默认超时时间8秒
 @param complete 预取号结果
 */
+ (void)getMobileAuthWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 获取本机号码校验Code
 调用此接口之前需要先调用getMobileAuthWithTimeout接口
 @param timeout 超时时间 传值小于等于0则使用默认超时时间8秒
 @param complete 回调，向服务端传递accessCode + 需要验证的手机号， 服务端返回结果
 */
- (void)getAccessCodeWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

/**
 调起登录页面 ⚠️Block内请使用`weakSelf`防止循环引用⚠️
 调用此接口之前需要先调用getMobileAuthWithTimeout接口
 @param vc 当前vc容器，用于一键登录授权页面切换
 @param model 自定义授权页面选项，可为nil，采用默认的授权页面
 @param timeout 超时时间 传值小于等于0则使用默认超时时间8秒
 @param complete 字典形式
 */
- (void)getLoginTokenWithController:(UIViewController *_Nonnull)vc model:(LMCustomModel *_Nullable)model timeout:(NSTimeInterval )timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete clickLoginBtn:(void(^)(UIViewController *loginVc))clickLogin otherLogin:(void(^)(UIViewController *loginVc))otherBlock;

/**
 无界面取号 (## 中国移动10分钟内获取token且未使用的数量不能超过30个 ##)
 @param timeout 超时时间 传值小于等于0则使用默认超时时间8秒
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

#pragma mark - ⚠️用户请不要使用以下属性⚠️

@property (nonatomic, assign, readonly) NSTimeInterval accessTokenTimeout;

@property (copy ,nonatomic, readonly) NSString *key;

@end


NS_ASSUME_NONNULL_END
