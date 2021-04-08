//
//  ViewController.m
//  NetChina
//
//  Created by bindx on 2019/4/29.
//  Copyright © 2019 bindx. All rights reserved.
//

#import "ViewController.h"
#import <LinkAccount_Lib/LinkAccount.h>
#import <LinkAccount_Lib/LMAuthSDKManager.h>


@interface ViewController()

@property (weak, nonatomic) IBOutlet UITextView *textView;
@property (copy, nonatomic) NSMutableString *logStr;
@property (copy,nonatomic) NSString *token;
@property (strong, nonatomic) LMCustomModel *model;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    _logStr = [[NSMutableString alloc] init];
    self.textView.editable = NO;
    
    [self addLog:[NSString stringWithFormat:@"当前SDK版本: %@", [LMAuthSDKManager getVersion]]];
}

// 预取号,登陆前60s调用此方法
- (IBAction)getphoneNumber:(id)sender {
    __weak typeof(self) weakSelf = self;
    [self addLog:@"取号中...（请勿重复点击）"];
    [LMAuthSDKManager getMobileAuthWithTimeout:10 complete:^(NSDictionary * _Nonnull resultDic) {
        [weakSelf addLog:[self convertToJsonData:resultDic]];
    }];
}

// 调起登录页面
- (IBAction)showLogin:(id)sender {
    
#pragma mark 自定义授权页面
    
    __weak typeof(self) weakSelf = self;
    //自定义Model
    _model = [[LMCustomModel alloc]init];
    //LOGO
    //    _model.logoImg = [UIImage imageNamed:@"logo"];
    //是否隐藏其他方式登陆按钮
    //    _model.swithAccHidden = NO;
    //登录按钮文字
    //    _model.logBtnText = @"一键登录";
    //自定义隐私条款1
    _model.appPrivacyOne   = @[@"用户服务条款1",@"https://www.linkedme.cc"];
    //自定义隐私条款2
    _model.appPrivacyTwo   = @[@"用户服务条款2",@"https://www.baidu.com"];
    //隐私条款复选框非选中状态
    //    _model.uncheckedImg = [UIImage imageNamed:@"checkBox_unSelected"];
    //隐私条款复选框选中状态
    //    _model.checkedImg   = [UIImage imageNamed:@"checkBox_selected"];
    //登陆按钮
    //    _model.logBtnImgs   = [NSArray arrayWithObjects:[UIImage imageNamed:@"loginBtn_Nor"],[UIImage imageNamed:@"loginBtn_Dis"] ,[UIImage imageNamed:@"loginBtn_Pre"],nil];
    // 登录按钮Y轴偏移量
    _model.loginBtnOffsetY = 5;
    //返回按钮
    _model.navReturnImg = [UIImage imageNamed:@"goback_nor"];
    //背景图片
    //    _model.authPageBackgroundImage = [self createImageWithColor:[UIColor groupTableViewBackgroundColor]];
    //标题
//    _model.navText = [[NSAttributedString alloc]initWithString:@"一键登录" attributes:@{NSForegroundColorAttributeName:[UIColor whiteColor]}];
    _model.navCustom = YES;
    //状态栏颜色
    _model.barStyle = UIBarStyleBlackOpaque;
    //导航栏颜色
    _model.navColor = [UIColor whiteColor];
    //logo距离屏幕顶部位置
    //    _model.logoOffsetY = 100;
    // ⚠️隐私协议复选框Y轴偏移 - 默认底部与文字基线对齐, 可以设置该属性让复选框向下移动一点达到与文字居中的效果
    _model.checkedImgOriginY = 2;
    //隐私协议距离屏幕底部位置
    //    _model.privacyOffsetY = 20;
    //隐私协议标题颜色，默认颜色和高亮颜色
    _model.privacyTitleColor = [UIColor redColor];
    //隐私协议颜色，默认颜色和高亮颜色
    //    _model.appPrivacyColor = @[[UIColor blueColor],[UIColor redColor]];
    //是否隐藏切换按钮
    //    _model.swithAccHidden = YES;
    //使用弹窗模式
    //    _model.useWindow = YES;
    //弹出窗口圆角
    //    _model.authWindowCornerRadius = 20;
    //默认勾选用户隐私协议
    //    _model.privacyState = YES;
    //    _model.margin = 20;
    //    _model.privacyFontSize = 13;
    //不需要隐私协议复选框登录即表示同意服务协议
    //    _model.noChecked = YES;
    //    _model.checkedImgOriginY = 2;
    //    _model.checkedImgOriginX = 14;
    //开启后隐藏确认复选框，默认登录即同意使用本机号码
    //    _model.noChecked = YES;
    
#pragma mark 自定义View（添加其它方式登录）
    [_model setAuthViewBlock:^(UIView * _Nonnull customView, CGRect logoFrame, CGRect numberFrame, CGRect sloganFrame, CGRect loginBtnFrame, CGRect privacyFrame ,CGRect swithAccFrame) {
        
        UIView * view = [[UIView alloc]init];
        view.frame = CGRectMake(loginBtnFrame.origin.x, swithAccFrame.origin.y + 45, loginBtnFrame.size.width, 30);
        [customView addSubview:view];
        
        NSArray *btnTitles = @[@"wechat_account", @"qq_account", @"weibo_account"];
        
        for (int i = 0; i<3; i++) {
            UIButton *btn = [[UIButton alloc]initWithFrame:CGRectMake((view.frame.size.width -15) /4 + (view.frame.size.width -15) /3 *i, swithAccFrame.origin.y + 65, 30, 30)];
            [btn setImage:[UIImage imageNamed:btnTitles[i]] forState:UIControlStateNormal];
            [btn setTag:i + 1];
            [btn addTarget:weakSelf action:@selector(customBtn:) forControlEvents:UIControlEventTouchUpInside];
            [btn setTintColor:[UIColor blackColor]];
            [customView addSubview:btn];
        }
    }];
    
#pragma mark 一键登陆
    
    [[LMAuthSDKManager sharedSDKManager] getLoginTokenWithController:self model:_model timeout:10 complete:^(NSDictionary * _Nonnull resultDic) {
        //关闭授权登录页
        [[LMAuthSDKManager sharedSDKManager] closeAuthView];
        
        if ([resultDic[@"resultCode"] isEqualToString:SDKStatusCodeSuccess]) {
            [weakSelf addLog:@"🤪登录成功🤪"];
            NSLog(@"%@",resultDic);
        } else {
            [weakSelf addLog:@"😫登录失败😫"];
            NSLog(@"%@",resultDic);
        }
        [weakSelf addLog:[weakSelf convertToJsonData:resultDic]];
        
    } clickLoginBtn:^(UIViewController * _Nonnull loginVc) {
        NSLog(@"%@",@"用户点击了登录按钮");
        BOOL isPrivacyChecked = [LMAuthSDKManager sharedSDKManager].isPrivacyChecked;
        if (!isPrivacyChecked) {
            [weakSelf showAlertOnVc:loginVc title:@"请先同意协议"];
        }
    } otherLogin:^(UIViewController * _Nonnull loginVc) {
        [weakSelf addLog:@"😄用户选择使用其他方式登录"];
    }];
}

// 直接获取AccessToken（bundle id需要添加白名单）
- (IBAction)getAccessToken:(id)sender {
    __weak typeof(self) weakSelf = self;
    [[LMAuthSDKManager sharedSDKManager] getAccessTokenWithTimeout:10 controller:self complete:^(NSDictionary * _Nonnull resultDic) {
        [weakSelf addLog:[weakSelf convertToJsonData:resultDic]];
    }];
}

// 获取本机号码校验
- (IBAction)phoneNumValidation:(id)sender {
    __weak typeof(self) weakSelf = self;
    [[LMAuthSDKManager sharedSDKManager] getAccessCodeWithTimeout:10 complete:^(NSDictionary * _Nonnull resultDic) {
        weakSelf.token = resultDic[@"accessCode"];
        [weakSelf addLog:[weakSelf convertToJsonData:resultDic]];
    }];
}

// 自定义View点击方法(QQ WeChat WeiBo)
- (void)customBtn:(UIButton *)btn {
    NSString *str = [NSString stringWithFormat:@"第%ld个按钮被点击了",(long)btn.tag];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        UIViewController *vc = [UIApplication sharedApplication].keyWindow.rootViewController;
        [self showAlertOnVc:vc title:str];
    });
    
    NSInteger tag = btn.tag;
    switch (tag) {
        case 1:
            [self addLog:@"🙂自定义登录方式: 微信"];
            break;
        case 2:
            [self addLog:@"🙂自定义登录方式: QQ"];
            break;
        case 3:
            [self addLog:@"🙂自定义登录方式: 微博"];
            break;
        default:
            break;
    }
    
    // 关闭登录页面(根据业务需要决定是否关闭)
    [[LMAuthSDKManager sharedSDKManager] closeAuthView];
}

// 弹窗
- (void)showAlertOnVc:(UIViewController *)vc title:(NSString *)title {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:nil preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancel];
    [vc presentViewController:alert animated:YES completion:nil];
}

- (void)addLog:(NSString *)str {
    [self.logStr appendFormat:@"%@:%@\n\n", [self getCurrentTimes], str];
    self.textView.text = self.logStr;
    [self.textView scrollRangeToVisible:NSMakeRange(self.textView.text.length, 1)];
}

- (NSString *)convertToJsonData:(NSDictionary *)dict {
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:&error];
    NSString *jsonString;
    
    if (!jsonData) {
        NSLog(@"%@",error);
    } else {
        jsonString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    
    NSMutableString *mutStr = [NSMutableString stringWithString:jsonString];
    //去掉字符串中的换行符
    NSRange range2 = {0, mutStr.length};
    [mutStr replaceOccurrencesOfString:@"\n" withString:@"" options:NSLiteralSearch range:range2];
    //去掉字符串中的空格
    NSRange range3 = {0, mutStr.length};
    [mutStr replaceOccurrencesOfString:@" " withString:@"" options:NSLiteralSearch range:range3];
    return mutStr;
}

- (NSDictionary *)convertToDictionary:(NSString *)jsonStr {
    NSData *data = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *tempDic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    return tempDic;
}

- (NSString *)getCurrentTimes {
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"YYYY-MM-dd HH:mm:ss"];
    NSDate *datenow = [NSDate date];
    NSString *currentTimeString = [formatter stringFromDate:datenow];
    return currentTimeString;
}

- (UIImage *)createImageWithColor:(UIColor *)color {
    CGRect rect=CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

@end
