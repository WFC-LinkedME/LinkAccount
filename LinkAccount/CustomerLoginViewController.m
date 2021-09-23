//
//  CustomerLoginViewController.m
//  LinkAccountLib-Demo
//
//  Created by YeZhongxiang on 2021/9/23.
//  Copyright © 2021 admin. All rights reserved.
//

#import "CustomerLoginViewController.h"
#import <LinkAccount_Lib/LinkAccount.h>

@interface CustomerLoginViewController ()

@property (weak, nonatomic) IBOutlet UIImageView *logoImgView;
@property (weak, nonatomic) IBOutlet UILabel *phoneLabel;
@property (weak, nonatomic) IBOutlet UILabel *noteLabel;
@property (weak, nonatomic) IBOutlet UILabel *privacyLabel;
@property (weak, nonatomic) IBOutlet UIButton *loginBtn;

@end

@implementation CustomerLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.title = @"一键登录";
    self.navigationController.navigationBar.hidden = YES;
    
    self.phoneLabel.text = [[self.preLoginDict valueForKey:@"desc"] valueForKey:@"mobile"];
    
    NSString *carrierId = [[self.preLoginDict valueForKey:@"desc"] valueForKey:@"operatorType"];
    NSString *carrier;
    if ([carrierId isEqualToString:@"CU"]) {
        carrier = @"中国联通";
    } else if ([carrierId isEqualToString:@"CM"]) {
        carrier = @"中国移动";
    } else if ([carrierId isEqualToString:@"CT"]) {
        carrier = @"中国电信";
    }
    self.noteLabel.text = [NSString stringWithFormat:@"%@提供认证服务", carrier];
}

- (IBAction)close:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)loginBtnAction:(id)sender {
    [[LMAuthSDKManager sharedSDKManager] getAccessTokenWithTimeout:0 controller:self complete:^(NSDictionary * _Nonnull resultDic) {
        NSLog(@"🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥");
        NSLog(@"\n%@", resultDic);
        NSLog(@"🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥");
        [self close:nil];
    }];
}

- (void)dealloc {
    NSLog(@"自定义登录页面销毁了!!");
}

@end
