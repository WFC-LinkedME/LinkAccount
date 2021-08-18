# LinkAccount iOS对接文档



当前最新版本：2.3.8
* 修复无SIM卡或蜂窝网络未开启时预取号发生多次失败回调的问题。

当前版本：2.3.6

* 修复电信号码登录获取的accessToken可能失效的问题。

当前版本：2.3.5
* 修复移动预取号不能返回脱敏手机号的问题

当前版本：2.2.9

* 更新电信运营商SDK
* 号码校验接口返回结果中增加 `operatorType` 字段，用于标识运营商类型
* 电信号码登录成功返回结果中增加 `accessToken` 字段



当前版本： 2.2.8

* 完善接口超时时间的设置
* 修复中国移动返回 `operatorType` 不正确的问题
* 修复中国移动取号失败的情况下UI被遮挡无法交互的问题



当前版本： 2.2.7

* 用户协议默认不勾选，可通过 `LMCustomModel `的 `privacyState`属性设置
* 去掉用户未勾选隐私协议的提示，可通过`[LMAuthSDKManager sharedManager].isPrivacyChecked`  获取选中状态自行进行处理。（未勾选隐私协议点击登录按钮不会执行登录操作）
* 隐私协议复选框可以隐藏，隐藏后默认同意隐私协议（ `noChecked = YES` 隐藏 ）



当前版本：2.1.8

* 修改用户未勾选隐私协议提示样式
* 隐私协议复选框大小可自己调整
* 用户隐私协议支持打开自定义页面
* 用户点击一键登录按钮返回回调结果


* 修复初始化可能失败的潜在问题



当前版本：2.1.5

* 修复初始化可能失败的潜在问题



当前版本：2.1.1

* 未安装SIM卡时候错误提示优化



当前版本：2.0.1

发版时间：2019年10月24日

* 支持弹窗模式打开授权登录页
* 提供无界面版本（需添加白名单）



最近更新：2.0.0

* 支持授权页面添加自定义控件
* 授权页面控件Frame设置
* 隐私协议自定义
* 隐私协议页面title，设置为用户自定义title

* 修复弱网环境下或双卡手机切换网络时，预取号回调失败存在不返回的情况



文档最后更新时间：2019年10月24日

版本更新：所有版本通用方式——替换SDK静态库， 删除旧版本SDK所有相关的`.framework``.bundle`文件，清除缓存，再导入新版SDK中的所有`.framework``.bundle`文件（.bundle文件注意保留开发者自定义资源），详细说明请移步至「升级指南」

## 一. 准备工作


### 前置条件


- LinkAccount SDK支持Xcode 9.4.1，iOS8.0+及以上版本。
- LinkAccount SDK支持中国移动、联通、电信4G的取号能力。
- LinkAccount SDK支持网络环境为
 a. 纯数据网络
  b. 数据网络与WIFI网络双开

- 对于双卡手机，取当前流量卡号


### 创建应用
应用的创建流程及APPID/APPKEY的获取，请查看[「产品指南」](https://pagedoc.lkme.cc/linkaccount/product-guide)文档

### 开发环境搭建
LinkAccount SDK目前仅提供两种集成方式，手动集成，cocoaPods集成。

- 通过CocoaPods自动集成
在工程的Podfile里面添加以下代码：

```
#以下两种版本选择方式示例

#集成最新版SDK:
pod 'LinkedME_LinkAccount'

#集成指定版本SDK:
pod 'LinkedME_LinkAccount', '2.2.9'
```

##### 保存并执行pod install，然后用后缀为.xcworkspace的文件打开工程。



注意:

命令行下执行pod search LinkedME_LinkAccount，如显示版本不是最新的，则需先执行pod repo update，更新本地repo的内容。

关于CocoaPods的更多信息请查看 [CocoaPods官方网站](https://cocoapods.org/)。



- 手动集成

1.导入framework和bundle资源文件：将LinkAccount SDK压缩包中framework文件夹下所有资源添加到工程中（注意勾选Copy items if needed）
![屏幕快照 2019-06-25 下午3.55.03](https://pagedoc.lkme.cc/.gitbook/assets/ping-mu-kuai-zhao-20190625-xia-wu-3.55.03%20%284%29.png)

2.Xcode配置：

2.1 OtherLinkerFlags中 添加**-ObjC**：xcode->BuildSetting->Other Linker Flags 添加 **-ObjC**
![屏幕快照 2019-06-25 下午3.57.39](https://pagedoc.lkme.cc/.gitbook/assets/ping-mu-kuai-zhao-20190625-xia-wu-3.57.39.png)

2.2 **Swift**工程需要额外添加-force_load：
在xcode->BuildSetting->Other Linker Flags 添加-force_load
![swift](https://pagedoc.lkme.cc/.gitbook/assets/swift.png)


2.3
添加libc++.1.tbd: 在xcode->General->Linked Frameworks and Libraries中点击 **+** ，搜索并选择添加 **libc++.1.tbd**
![Build Phases](https://pagedoc.lkme.cc/.gitbook/assets/build-phases.png)

2.4（SDK 2.3.1以后版本）如需支持iOS11及以下系统，需要添加依赖库，在项目设置target -> 选项卡Build Phase -> Linked Binary with Libraries添加如下依赖库: `Network.framework` 。

### 二. SDK使用说明

###  1.初始化

**方法原型**

```
// 初始化方法
+(void)initWithKey:(NSString *)key  complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;
```

**参数描述**

| 参数 | 是否必填 | 类型  | 说明 |
| --- | --- | --: | --: |
| key | 是 | NSString   | LinkAccount Key |
| complete | 是 | Block | 初始化回调block，可以在此回调block中接收初始化情况，也可以不关心初始化结果 |

**接口作用**

初始化SDK：传入用户的appID、获取本机运营商，读取缓存，获取运营商配置，初始化SDK。

**使用场景**

- 建议在app启动时调用
- 必须在一键登录前至少调用一次
- 只需调用一次，多次调用不会多次初始化，与一次调用效果一致

**OC**
1. 导入LinkAccount SDK头文件  `#import <LinkAccount_Lib/LinkAccount.h>` 
2. 在AppDelegate中的 `didFinishLaunchingWithOptions` 方法中添加初始化代码

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    //初始化SDK
    [LMAuthSDKManager initWithKey:@"your Key" complete:^(NSDictionary * _Nonnull resultDic) {
        NSLog(@"%@",resultDic);
    }];
    NSLog(@"版本号：%@", [LMAuthSDKManager getVersion]);
    ...
}
```

**Swift**
创建混编桥接头文件并导入LinkAccount SDK头文件 
`#import <LinkAccount_Lib/LinkAccount.h>` 

在AppDelegate中的 `didFinishLaunchingWithOptions` 方法中添加初始化代码

```
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
...        
      LMAuthSDKManager.initWithKey("your appKey") { ([AnyHashable : Any]) in
            
      }
...
        return true
    }
```

### 2.预取号

**方法原型**

```
// 预取号（获取临时凭证）
// 建议在判断当前用户属于未登录状态时使用，已登录状态用户请不要调用该方法
+ (void)getMobileAuthWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;
```


| 参数 | 类型 | 说明 |
| --- | --- | --- |
| timeout | NSTimeInterval | 超时时间(内部单个请求)，单位s，传大于0有效，传小于等于0使用默认，默认8s   |
| complete | Block | 预取号结果回调 |


**接口作用**

电信、联通、移动预取号：初始化成功后，如果当前为电信/联通/移动，将调用预取号，可以提前获知当前用户的手机网络环境是否符合一键登录的使用条件，成功后将得到用于一键登录使用的临时凭证，默认的凭证有效期60s(电信)/30min(联通)/60min(移动)。

**使用场景**

建议在执行一键登录的方法前，提前一段时间调用此方法，比如调一键登录的vc的viewdidload中，或者rootVC的viewdidload中，或者app启动后，此调用将有助于提高拉起授权页的速度和成功率。
不建议调用后立即调用拉起授权页方法（此方法是异步）
此方法需要1~2s的时间取得临时凭证，因此也不建议和拉起授权页方法一起串行调用
不建议频繁的多次调用和在拉起授权页后调用
建议在判断当前用户属于未登录状态时使用，已登录状态用户请不要调用该方法


> 请求示例代码

**OC**


```

#import <LinkAccount_Lib/LinkAccount.h>

// 需要拉起授权页的ViewController页面

...
- (void)viewDidLoad {
    [super viewDidLoad];
    if (YourAppLoginStatus == NO) {
        // 预取号
         [LMAuthSDKManager getMobileAuthWithTimeout:10 complete:^(NSDictionary * _Nonnull resultDic) {
        // 回调结果
    }];
        ...
    }
}
...
// 拉起授权页
- (void)authPageLogin{
    ...
}

```

**Swift**

```
class ViewController: UIViewController {

    // 需要拉起授权页的ViewController页面
    override func viewDidLoad() {
        super.viewDidLoad()        
        // 预登录
        if (YourAppLoginStatus == false) {
            LMAuthSDKManager.getMobileAuth(withTimeout: 10) { (dict) in
                print(dict)
            }
        }
    }

    //拉起授权页
    @IBAction func authPageLogin(_ sender: Any) {
        ...
    }
}

```

### 3.拉起授权页

```
- (void)getLoginTokenWithController:(UIViewController *_Nonnull)vc model:(LMCustomModel *_Nullable)model timeout:(NSTimeInterval )timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete clickLoginBtn:(void(^)(UIViewController *loginVc))clickLogin otherLogin:(void(^)(UIViewController *loginVc))otherBlock;
```

***在预取号成功后调用***，预取号失败不可调用。调用拉起授权页方法后将会调起运营商授权页面。该方法会拉起登录界面，***已登录状态请勿调用*** 。


| 参数 | 类型 | 说明 |
| --- | --- | --- |
| controller | UIViewController | 拉起授权页的vc |
| model | LMCustomModel | 自定义授权页面 |
| timeout | NSTimeInterval | 超时时间(内部单个请求)，单位秒，传小于等于0的值时默认为8s |
| complete | Block | 授权完成回调 |

**使用场景**

用户进行一键登录操作时，调用一键登录方法，如果初始化成功，SDK将会拉起授权页面，用户授权后，SDK将返回取号 token给到应用客户端。
可以在多处调用
需在调用预预取号方法方法之后调用


> 请求示例代码

导入LinkAccount SDK头文件 ` #import <LinkAccount_Lib/LinkAccount.h>` 
在需要使用一键登录的地方调用一键登录接口

**OC**

```
...

- (IBAction)authPageLogin:(id)sender {
		__weak typeof(self) weakSelf = self;
    //自定义Model
    LMCustomModel *model = [LMCustomModel new];
    //LOGO
    model.logoImage = [UIImage imageNamed:@"logo"];
    //是否隐藏其他方式登陆按钮
    model.changeBtnIsHidden = NO;
    //自定义隐私条款1
    model.privacyOne = @[@"用户服务条款1",@"https://www.linkedme.cc"];
    //自定义隐私条款2
    model.privacyTwo = @[@"用户服务条款2",@"https://www.linkedme.cc"];
    //隐私条款复选框非选中状态
    model.uncheckedImg = [UIImage imageNamed:@"checkBox_unSelected"];
    //隐私条款复选框选中状态
    model.checkedImg = [UIImage imageNamed:@"checkBox_selected"];
    //登陆按钮
    model.logBtnImgs = [NSArray arrayWithObjects:[UIImage imageNamed:@"loginBtn_Nor"],[UIImage imageNamed:@"loginBtn_Dis"] ,[UIImage imageNamed:@"loginBtn_Pre"],nil];
    //返回按钮
    model.navReturnImg = [UIImage imageNamed:@"goback_nor"];
    //一键登录
    [[LMAuthSDKManager sharedSDKManager] getLoginTokenWithController:self model:_model timeout:0 complete:^(NSDictionary * _Nonnull resultDic) {        
        //关闭授权登录页
        [[LMAuthSDKManager sharedSDKManager] closeAuthView];
        if ([resultDic[@"resultCode"] isEqualToString:SDKStatusCodeSuccess]) {
            NSLog(@"登录成功");
            NSLog(@"%@",resultDic);
        } else {
            NSLog(@"%@",resultDic);
        }
    } clickLoginBtn:^(UIViewController * _Nonnull loginVc) {
        NSLog(@"用户点击了登录按钮!!");
        BOOL isPrivacyChecked = [LMAuthSDKManager sharedSDKManager].isPrivacyChecked;
        if (!isPrivacyChecked) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"请先同意隐私协议" message:nil preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleCancel handler:nil];
            [alert addAction:cancel];
            [loginVc presentViewController:alert animated:YES completion:nil];
        }
    } otherLogin:^(UIViewController * _Nonnull loginVc) {
//        [loginVc dismissViewControllerAnimated:YES completion:nil];
        UIViewController *phoneLoginVc = [[UIViewController alloc] init];
        phoneLoginVc.view.backgroundColor = [UIColor whiteColor];
        [loginVc.navigationController pushViewController:phoneLoginVc animated:YES];
        NSLog(@"用户选择使用其他方式登录");
    }];
}
```



**Swift**

```****
    //拉起授权页
    @IBAction func authPageLogin(_ sender: Any) {
        // 自定义Model
        let model = LMCustomModel.init()
        // LOGO
        model.logoImage = UIImage.init(named: "logo")!
        // 是否隐藏其他方式登录按钮
        model.changeBtnIsHidden = false
        // 自定义隐私条款1
        model.privacyOne = ["用户服务条款1","https://www.linkedme.cc"]
        // 自定义隐私条款2
        model.privacyTwo = ["用户服务条款2","https://www.linkedme.cc"]
        // 隐私条款复选框非选中状态
        model.uncheckedImg = UIImage.init(named: "checkBox_unSelected")!
        // 隐私条款复选框选中状态
        model.checkedImg = UIImage.init(named: "checkBox_selected")!
        // 登录按钮背景图
        model.logBtnImgs = [UIImage.init(named: "loginBtn_Nor")!,
                            UIImage.init(named: "loginBtn_Dis")!,
                            UIImage.init(named: "loginBtn_Pre")!]
        // 返回按钮
        model.navReturnImg = UIImage.init(named: "goback_nor")!
        
            // 一键登录
            LMAuthSDKManager.shared().getLoginToken(with: self, model: model, timeout: 888, complete: { (dict) in
                //SDKStatusCodeSuccess
                if let resultCode = dict["resultCode"] as? String{
                    if (resultCode == SDKStatusCodeSuccess){
                        print("登录成功")
                    }
                }
            }) {
                
        }
    }
```

> 成功回调示例

```
// 移动
{
  "resultCode":"6666",
  "operatorType":"CM",
  "accessToken":"STsid00000015783159423136R9MZRTTB05bIDw0uVGuPZuNYPxkXK3r",
  "operatorCode":"103000",
  "os":"0"
}

// 联通
{
  "resultCode":"6666",
  "operatorType":"CU",
  "accessToken":"527d507cf00a475883bcc593638b2258",
  "operatorCode":"0",
  "os":"0"
}
// 电信
{
  "result":0,
  "gwAuth":"7473",
  "number":"189****0547",
  "expiredTime":3600,
  "operatorType":"CT",
  "msg":"success",
  "accessCode":"nmb5209acbc83944dbb24738801c806991",
  "accessToken":"nmb5209acbc83944dbb24738801c806991",
  "reqId":"42670674cGwhZVqXbWYHdEGazBCoksak",
  "resultCode":"6666"
}
```
**参数描述**

| 字段 | 类型 | 说明 |
| --- | --- | --- |
| resultCode | NSString | 状态码 |
| operatorType | NSString | 当前数据流量卡的运营商类型：CM-移动 CT-电信 CU-联通 |
| accessToken | NSString | token，置换令牌，用来和后台置换手机号。一次有效，有效期3min |
| gwAuth | NSString | 仅电信运营商返回此字段，配合accessToken置换手机号 |
| os | NSString | 手机系统 “0”为iOS |


开发者需将此data字典作为参数，以form-data格式完整地发送到开发者后台配置的`查询手机号API`

异常处理

用户取消登录(授权页点击返回) 【处理建议：若无特殊需求可不做处理】
用户选择其他方式登录(点击授权页自带的其他方式登录): 【处理建议：可根据实际情况跳转其他登录方式 】
其他错误 【处理建议：可根据实际情况跳转其他登录方式 】


### 4.本机号码验证
```
- (void)getAccessCodeWithTimeout:(NSTimeInterval)timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;
```

调用后返回accessCode用于本机号码验证。该方法不会拉起登录界面，用于校验用户输入的手机号码是否为本机号码。


| 字段 | 类型 | 说明 |
| --- | --- | --- |
| complete | Block | 回调  |
| timeout | NSTimeInterval | 超时时间 |

**OC**

```
...
- (IBAction)phoneNumValidation:(id)sender {
    [[LMAuthSDKManager sharedSDKManager]getAccessCodeWithTimeout:10 complete:^(NSDictionary * _Nonnull resultDic) {
        NSLog(@"%@",resultDic);
    }];
}
...
```

**Swift**

```
...
@IBAction func authLogin(_ sender: Any) {
    LMAuthSDKManager.getAccessCode(withTimeout: 10) { ([AnyHashable : Any]) in
        
    }
}
...
```

### 5.手动关闭授权页
当开发者设置点击一键登录或者自定义控件不自动销毁授权页时，将需要自行调用此方法主动销毁授权页，建议在置换手机号成功后销毁。如在得到回调后未销毁授权页而，使用拉起授权页方法再次拉起授权页，此页面将无法响应任何按键（除了导航栏的返回按钮）。

> 关闭授权页时机

- a. SDK拉起授权页方法直接回调失败时
- b. 置换手机号有返回结果时

```
[[LMAuthSDKManager sharedSDKManager] closeAuthView];
```

### 三. 授权界面修改

![](https://pagedoc.lkme.cc/.gitbook/assets/sdk-shou-quan-ye-she-ji-gui-fan.jpg)
可以调整属性

```
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
/// 2.slogen 轴y偏移（相对号码框位置）
@property (nonatomic, assign) CGFloat slogonTextOffSetY;
/// 3.slogen 轴x偏移
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
/// 3.复选框图片大小
@property (nonatomic, assign) CGFloat checkedImgSize;
/// 4.不需要确认复选框(默认为NO, 设为YES后会隐藏复选框且5/6/9会失效, 隐私协议永远为同意状态, privacyState设置将失效且为YES)
@property (nonatomic, assign) BOOL noChecked;
/// 5.复选框x坐标距离左边框距离
@property (nonatomic, assign) float checkedImgOriginX;
/// 6.复选框y坐标偏移量
@property (nonatomic, assign) float checkedImgOriginY;
/// 7.用户自定义协议1(@[@"xxx协议1",@"https://www.xxx1.com"])
@property (nonatomic, copy) NSArray *appPrivacyOne;
/// 8.用户自定义协议2(@[@"xxx协议2",@"https://www.xxx2.com"])
@property (nonatomic, copy) NSArray *appPrivacyTwo;
/// 9.复选框默认勾选状态
@property (nonatomic, assign) BOOL privacyState;
/// 10.隐私协议详情页标题颜色
@property (nonatomic, strong) UIColor *privacyTitleColor;
/// 11.隐私条款Y偏移量(注:此属性为与屏幕底部的距离)
@property (nonatomic, assign) CGFloat privacyOffsetY;
/// 12.隐私协议颜色，@[默认文字颜色，协议名称颜色]
@property (nonatomic, strong) NSArray *appPrivacyColor;
/// 13.隐私协议对齐状态
@property (nonatomic, assign) NSTextAlignment privacyTextAlignment;
/// 14.隐私协距离屏幕边框位置
@property (nonatomic, assign) float privacyMargin;
/// 15.隐私协议高度
@property (nonatomic, assign) float privacyHeight;
/// 16.隐私协议字体大小
@property (nonatomic, assign) float privacyFontSize;
/// 17.自定义隐私协议的点击方法(设置后需在block内自行处理跳转逻辑)
@property (nonatomic, copy) void(^privateClickInfo)(NSString *privacyTitle, NSURL *url);
 
#pragma mark 窗口模式

/// 是否使用弹窗模式
@property (nonatomic, assign) BOOL useWindow;
/// 窗口圆角（非窗口模式下设置该值无效）
@property (nonatomic, assign) CGFloat authWindowCornerRadius;
/// 页面打开动画
@property (nonatomic, assign) UIModalPresentationStyle presentationStyle;

```


### 四. 返回码对照


| 状态码 |   描述 |
| --- | --- |
| 6666 | 成功  |
| 5555 | 用户取消登陆 |
| 4444 | 数据解析异常   |
| 1111 | 无网络   |
| 2222 | 请求超时   |
| 2233 | 其他错误   |
| 3344 | 蜂窝数据未开启或不稳定   |

### 五. 已知问题
1. ATS开关(Http与Https)

目前运营商个别接口为http请求，解决办法如下
1.开启ATS开关

```
Info.plist -> App Transport Security Settings -> Allow Arbitrary Loads -> YES
```

2.全局禁用Http的项目，需要设置Http白名单。以下为运营商http接口host名单：

*.cmpassport.com、id6.me、123.125.99.8:9001、ms.zzx9.cn、mdn.open.wo.cn、10.99.255.231，*为通配符，建议按以下方式配置Info.plist

```
<key>NSAppTransportSecurity</key>
	<dict>
		<key>NSExceptionDomains</key>
		<dict>
			<key>zzx9.cn</key>
			<dict>
				<key>NSIncludesSubdomains</key>
				<true/>
				<key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
				<true/>
			</dict>
			<key>cmpassport.com</key>
			<dict>
				<key>NSIncludesSubdomains</key>
				<true/>
				<key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
				<true/>
			</dict>
			<key>id6.me</key>
			<dict>
				<key>NSIncludesSubdomains</key>
				<true/>
				<key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
				<true/>
			</dict>
			<key>wostore.cn</key>
			<dict>
				<key>NSIncludesSubdomains</key>
				<true/>
				<key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
				<true/>
			</dict>
			<key>mdn.open.wo.cn</key>
			<dict>
				<key>NSIncludesSubdomains</key>
				<true/>
				<key>NSTemporaryExceptionAllowsInsecureHTTPLoads</key>
				<true/>
			</dict>
		</dict>
	</dict>
```
=======
参见：[LinkAccount iOS对接文档](https://pagedoc.lkme.cc/linkaccount/linkaccount-integrated-document/ios-sdk.html)

