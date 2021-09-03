//
//  LMCustomModel.h
//  LinkAccount
//
//  Created by admin on 2019/6/11.
//  Copyright © 2019 bindx. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 版本注意事项:
 授权页面的各个控件的Y轴默认值都是以375*667屏幕为基准 系数 ：当前屏幕高度/667
 1、当设置Y轴并有效时 偏移量OffsetY属于相对导航栏的绝对Y值
 2、（负数且超出当前屏幕无效）为保证各个屏幕适配,请自行设置好Y轴在屏幕上的比例（推荐:当前屏幕高度/667）
 */

@interface LMCustomModel : NSObject

#pragma mark 自定义控件
/// 1.授权界面自定义控件View的Block
@property (nonatomic, copy) void(^authViewBlock)(UIView * customView ,CGRect logoFrame, CGRect  numberFrame, CGRect sloganFrame ,CGRect loginBtnFrame, CGRect privacyFrame ,CGRect swithAccFrame);

/// 2.授权界面背景图片
@property (nonatomic, strong) UIImage *authPageBackgroundImage;

#pragma mark 导航栏
/// 1.导航栏颜色
@property (nonatomic, strong) UIColor *navColor;
/// 2.状态栏着色样式
@property (nonatomic, assign) UIBarStyle barStyle;
/// 3.导航栏标题
@property (nonatomic,   copy) NSAttributedString *navText;
/// 4.导航返回图标
@property (nonatomic, strong) UIImage *navReturnImg;
/// 5.导航栏自定义（适配全屏图片）
@property (nonatomic, assign) BOOL navCustom;
/// 6.导航栏右侧自定义控件（导航栏传 UIBarButtonItem对象 自定义传非UIBarButtonItem ）
@property (nonatomic, strong) id navControl;
/// 7.返回按钮隐藏
@property (nonatomic, assign) BOOL backBtnHidden;

#pragma mark LOGO图片设置
/// 1.LOGO图片
@property (nonatomic, strong) UIImage *logoImg;
/// 2.LOGO图片宽度
@property (nonatomic, assign) CGFloat logoWidth;
/// 3.LOGO图片高度
@property (nonatomic, assign) CGFloat logoHeight;
/// 4.LOGO图片轴y偏移（距离顶部位置）
@property (nonatomic, assign) CGFloat logoOffsetY;
/// 5.LOGO图片轴x偏移
@property (nonatomic, assign) CGFloat logoOffsetX;
/// 6.LOGO图片隐藏
@property (nonatomic, assign) BOOL logoHidden;

#pragma mark 号码框设置
/// 1.号码颜色
@property (nonatomic, strong) UIColor *numberColor;
/// 2.号码大小
@property (nonatomic, assign) CGFloat numberSize;
/// 3.号码栏Y偏移量（相对Logo位置）
@property (nonatomic, assign) CGFloat numberOffsetY;
/// 4.号码栏X偏移量
@property (nonatomic, assign) CGFloat numberOffsetX;
/// 5.号码栏高h 注意：必须大于80
@property (nonatomic, assign) CGFloat numberHeight;

#pragma mark slogon
/// 1.文字颜色(默认为[UIColor grayColor])
@property (nonatomic, strong) UIColor *slogonTextColor;
/// 2.slogen Y轴偏移（相对号码框位置）
@property (nonatomic, assign) CGFloat slogonTextOffSetY;
/// 3.slogen X轴偏移
@property (nonatomic, assign) CGFloat slogonTextOffSetX;
/// 4.slogen字体大小(弹窗模式下默认为10, 否则默认为12, 如果设置了该值, 默认值将失效)
@property (nonatomic, assign) CGFloat slogonFontSize;

#pragma mark 登录按钮
/// 1.登录按钮文本
@property (nonatomic, copy) NSString *loginBtnText;
/// 2.登录按钮字体大小
@property (nonatomic, strong) UIFont *loginBtnFont;
/// 3.登录按钮背景图片(顺序如下)@[激活状态的图片,失效状态的图片,高亮状态的图片]
@property (nonatomic, strong) NSArray *loginBtnImgs;
/// 4.登录按钮文字颜色
@property (nonatomic, strong) UIColor *loginBtnTextColor;
/// 5.登录按钮Y偏移量（相对slogon位置）
@property (nonatomic, assign) CGFloat loginBtnOffsetY;
/// 6.登录按钮的左右边距 注意:按钮呈现的宽必须大于屏幕的一半
@property (nonatomic, assign) CGFloat loginBtnOriginX;
/// 7.登录按钮高h 注意：必须大于40
@property (nonatomic, assign) CGFloat loginBtnHeight;
/// 8.登录按钮高h 注意：必须大于40
@property (nonatomic, assign) CGFloat loginBtnWidth;
/// 9.登录按钮圆角大小(默认为0无圆角)
@property (nonatomic, assign) CGFloat loginBtnCornerRadius;
/// 10.隐私协议未确认时登录按钮是否设置为unable状态, unable状态下点击登录按钮不会收到回调
@property (nonatomic, assign) BOOL loginBtnUnableWhenPrivacyNotChecked;

#pragma mark  切换账号
/// 1.隐藏按钮
@property (nonatomic, assign) BOOL swithAccHidden;
/// 2.设置y偏移（相对登录按钮位置）
@property (nonatomic, assign) float swithAccOffsetY;
/// 3.登录按钮的左右边距 注意:按钮呈现的宽必须大于屏幕的一半
@property (nonatomic, assign) float swithAccOriginX;
/// 4.字体颜色
@property (nonatomic, strong) UIColor *swithAccTextColor;
/// 5.字体大小(默认为12)
@property (nonatomic, assign) CGFloat swithAccFontSize;
/// 6.标题内容 (6 / 7 二选一)
@property (nonatomic,   copy) NSString *swithAccTitle;
/// 7.标题内容（AttributedString, 优先级高）
@property (nonatomic, copy) NSAttributedString *attributedSwithAccTitle;

#pragma mark 隐私协议

/// 1.复选框未选中时图片(uncheckedImg和checkedImg必须同时设置, 否则将使用默认图片)
@property (nonatomic, strong) UIImage *uncheckedImg;
/// 2.复选框选中时图片
@property (nonatomic, strong) UIImage *checkedImg;
/// 3.复选框图片大小(默认为一个文字的大小)
@property (nonatomic, assign) CGFloat checkedImgSize;
/// 4.不需要确认复选框(默认为NO, 设为YES后会隐藏复选框且5/6/9会失效, 隐私协议永远为同意状态, privacyState设置将失效且为YES)
@property (nonatomic, assign) BOOL noChecked;
/// 5.复选框X坐标距离左边框距离(在14.privacyMargin的基础上偏移)
@property (nonatomic, assign) CGFloat checkedImgOriginX;
/// 6.复选框Y坐标偏移量
@property (nonatomic, assign) CGFloat checkedImgOriginY;
/// 7.用户自定义协议1(@[@"xxx协议1",@"https://www.abc.com"])
@property (nonatomic, copy) NSArray *appPrivacyOne;
/// 8.用户自定义协议2(@[@"xxx协议2",@"https://www.def.com"])
@property (nonatomic, copy) NSArray *appPrivacyTwo;
/// 9.复选框默认勾选状态
@property (nonatomic, assign) BOOL privacyState;
/// 10.隐私协议首行文字距离复选框右边的距离(根据实际情况微调, +-值均可)
@property (nonatomic, assign) CGFloat privacyFirstLineIndent;
/// 11.隐私协议文字行间距(默认为0)
@property (nonatomic, assign) CGFloat privacyLineSpacing;
/// 12.隐私协议换行模式
@property (nonatomic, assign) NSLineBreakMode privacyLineBreakMode;
/// 13.隐私协议详情页标题颜色
@property (nonatomic, strong) UIColor *privacyTitleColor;
/// 14.隐私条款Y偏移量(注:此属性为与屏幕底部的距离)
@property (nonatomic, assign) CGFloat privacyOffsetY;
/// 15.隐私协议颜色，@[默认文字颜色，协议名称颜色]
@property (nonatomic, strong) NSArray *appPrivacyColor;
/// 16.隐私协议对齐状态(建议左对齐, 默认为左对齐)
@property (nonatomic, assign) NSTextAlignment privacyTextAlignment;
/// 17.隐私协距离屏幕边框位置
@property (nonatomic, assign) CGFloat privacyMargin;
/// 18.隐私协议高度
@property (nonatomic, assign) CGFloat privacyHeight;
/// 19.隐私协议字体大小 默认为14
@property (nonatomic, assign) CGFloat privacyFontSize;
/// 20.自定义隐私协议的点击方法(设置后需在block内自行处理跳转逻辑)
@property (nonatomic, copy) void(^privateClickInfo)(NSString *privacyTitle, NSURL *url);

/*
🙂隐私协议是否同意请使用 [LMAuthSDKManager sharedSDKManager].isPrivacyChecked 获取其状态, 然后自行处理
 
/// 18.用户未同意隐私协议提示
@property (nonatomic, copy) NSString *appPrivacyWarningStr;
/// 19.用户未同意隐私协议提示Y偏移量(注:此属性为与屏幕顶部的距离)
@property (nonatomic, assign) CGFloat appPrivacyWarningStrOffsetY;
/// 20.提示框距离边距文字距离
@property (nonatomic, assign) CGFloat margin;
/// 21.未勾选隐私协议提示框 圆角
@property (nonatomic, assign) CGFloat cornerRadius;
/// 22.未勾选隐私协议提示框 透明度
@property (nonatomic, assign) CGFloat appPrivacyAlpah;
/// 23.未勾选隐私协议提示框 字体颜色
@property (nonatomic, strong) UIColor *appPrivacyTextColor;
/// 24.未勾选隐私协议提示框 字体大小
@property (nonatomic, assign) CGFloat appPrivacyFontSize;
/// 25.未勾选隐私协议提示框 背景颜色
@property (nonatomic, assign) UIColor *appPrivacyBackgroundColor;
/// 26.未勾选隐私协议提示框 等待时间
@property (nonatomic, assign) CGFloat appPrivacyWaitTime;
*/
 
#pragma mark 窗口模式

/// 是否使用弹窗模式
@property (nonatomic, assign) BOOL useWindow;
/// 窗口圆角（非窗口模式下设置该值无效）
@property (nonatomic, assign) CGFloat authWindowCornerRadius;
/// 页面打开动画
@property (nonatomic, assign) UIModalPresentationStyle presentationStyle;

@end

NS_ASSUME_NONNULL_END
