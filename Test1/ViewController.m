//
//  ViewController.m
//  Test1
//
//  Created by admin on 2019/6/11.
//  Copyright © 2019 admin. All rights reserved.
//

#import "ViewController.h"
//#import <EAccountHYSDK/EAccountOpenPageSDK.h>
//#import <EAccountHYSDK/EAccountOpenPageConfig.h>
#import "LMAuthSDKManager.h"
#import "LMCustomModel.h"

@interface ViewController ()

@property (nonatomic ,copy) NSString *token;
    
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeSystem];
    btn.frame = CGRectMake(10, 200, 300, 30);
    [btn setTitle:@"登录" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(login:) forControlEvents:UIControlEventTouchDown];
    [self.view addSubview:btn];
    
//    __weak typeof(self) weakSelf = self;
    
    [LMAuthSDKManager initWithLinkMessageKey:@"" complete:^(NSDictionary * _Nonnull resultDic) {
        
    }];

//    [EAccountOpenPageSDK requestPreLogin:@"8148613161" appSecret:@"2vFtoe8ZOFTxEEbqtj1MqClMaMfTFps9" completion:^(NSDictionary * _Nonnull resultDic) {
//
//    } failure:^(NSError * _Nonnull error) {
//
//    }];
    
    // Do any additional setup after loading the view.
}

- (IBAction)login:(id)sender {
    LMCustomModel * conf = [[LMCustomModel alloc]init];
    conf.logoImage = [UIImage imageNamed:@"logoo"];
    
    
//    EAccountOpenPageConfig * config = [EAccountOpenPageConfig new];
//    config.logoImg = [UIImage imageNamed:@"logoo"];
//    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        [EAccountOpenPageSDK openAtuhVC:config viewController:self completion:^(NSDictionary * _Nonnull resultDic) {
//            
//        } failure:^(NSError * _Nonnull error) {
//            
//        }];
//       
//    });
}
                   
@end
