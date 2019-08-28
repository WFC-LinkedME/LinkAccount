//
//  LMCustomModel.h
//  LinkAccount
//
//  Created by admin on 2019/6/11.
//  Copyright © 2019 bindx. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 版本注意事项:
 授权页面的各个控件的Y轴默认值都是以375*667屏幕为基准 系数 ： 当前屏幕高度/667
 1、当设置Y轴并有效时 偏移量OffsetY属于相对导航栏的绝对Y值
 2、（负数且超出当前屏幕无效）为保证各个屏幕适配,请自行设置好Y轴在屏幕上的比例（推荐:当前屏幕高度/667）
 */

@interface LMCustomModel : NSObject

// 自定义View
@property (nonatomic,copy) void(^authViewBlock)(UIView *customView);

// 状态栏
@property (nonatomic ,assign) UIBarStyle statusBarStyle;

// 导航栏
@property (nonatomic, strong) UIColor *navColor;
@property (nonatomic, copy) NSAttributedString *navTitle;

// logo图片
@property (nonatomic,assign) CGFloat logoOffsetY;
@property (nonatomic, strong) UIImage *logoImage;
@property (nonatomic, assign) BOOL logoIsHidden;

// slogon
@property (nonatomic, strong) UIColor *slogonColor;

// 号码
@property (nonatomic, strong) UIColor *numberColor;
@property (nonatomic, assign) CGFloat numberSize;

// 登录
/**
 登录按钮背景图片添加到数组(顺序如下)
 @[激活状态的图片,失效状态的图片,高亮状态的图片]
 */
@property (nonatomic,strong) NSArray *logBtnImgs;

//13、LOGO图片偏移量,距离顶部位置
@property (nonatomic, copy) NSString *loginBtnText;
@property (nonatomic, strong) UIColor *loginBtnTextColor;

// 协议
/**
 隐私协议数组u顺序如下
 @[@"xxxx隐私协议",@"https://www.xxx.com"]
 */
@property (nonatomic, copy) NSArray *privacyOne;
@property (nonatomic, copy) NSArray *privacyTwo;

//隐私条款Y偏移量(注:此属性为与屏幕底部的距离)
@property (nonatomic,assign) CGFloat privacyOffsetY;
@property (nonatomic,strong) NSArray *appPrivacyColor;


// 切换账号
@property (nonatomic, assign) BOOL changeBtnIsHidden;
@property (nonatomic, strong) UIColor *swithAccTextColor;

// 复选框未选中时图片
@property (nonatomic,strong) UIImage *uncheckedImg;
// 复选框选中时图片
@property (nonatomic,strong) UIImage *checkedImg;
// 导航返回图标
@property (nonatomic,strong) UIImage *navReturnImg;
// 授权页面背景
@property (nonatomic,strong) UIImage *authPageBackgroundImage;

@end

NS_ASSUME_NONNULL_END
