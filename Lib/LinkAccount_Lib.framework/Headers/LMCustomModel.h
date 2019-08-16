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

@interface LMCustomModel : NSObject

// 导航栏
@property (nonatomic, strong) UIColor *navColor;
@property (nonatomic, copy) NSAttributedString *navTitle;

// logo图片
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
@property (nonatomic, copy) NSString *loginBtnText;
@property (nonatomic, strong) UIColor *loginBtnTextColor;

// 协议
/**
 隐私协议数组u顺序如下
 @[@"xxxx隐私协议",@"https://www.xxx.com"]
 */
@property (nonatomic, copy) NSArray *privacyOne;
@property (nonatomic, copy) NSArray *privacyTwo;
@property (nonatomic, strong) UIColor *privacyColor;

// 切换账号
@property (nonatomic, assign) BOOL changeBtnIsHidden;
@property (nonatomic, strong) UIColor *changeBtnColor;

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
