# LinkAccount iOS对接文档

当前版本：1.0.0

发版时间：2019年06月30日

文档最后更新时间：2019年06月30日

版本更新：所有版本通用方式——替换SDK静态库， 删除旧版本SDK所有相关的`.framework``.bundle`文件，清除缓存，再导入新版SDK中的所有`.framework``.bundle`文件（.bundle文件注意保留开发者自定义资源），详细说明请移步至「升级指南」

## 一.准备工作


### 前置条件


- LinkAccount SDK支持Xcode 9.4.1，iOS8.0+及以上版本。
- LinkAccount SDK支持中国移动、联通、电信4G的取号能力。
- LinkAccount SDK支持网络环境为
 a.纯数据网络
 b.数据网络与wifi网络双开

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
pod 'LinkedME_LinkAccount', '1.0.0'

保存并执行pod install,然后用后缀为.xcworkspace的文件打开工程。
```

注意:

命令行下执行pod search LinkedME_LinkAccount,如显版本不是最新的，则先执行pod repo update操作更新本地repo的内容

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



### 二.SDK使用说明


1.初始化


方法原型

```
#初始化方法
+(void)initWithKey:(NSString *)key  complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;
```

**参数描述**

| 参数 | 是否必填 | 类型  | 说明 |
| --- | --- | --: | --: |
| key | 是 | NSString   | LinkAccount Key |
| complete | 是 | Block | 初始化回调block，可以在此回调block中接收初始化情况，也可以不关心初始化结果 |


**接口作用**

初始化SDK :传入用户的appID、获取本机运营商,读取缓存,获取运营商配置,初始化SDK


**使用场景**

- 建议在app启动时调用
- 必须在一键登录前至少调用一次
- 只需调用一次，多次调用不会多次初始化，与一次调用效果一致

**OC**
1.导入LinkAccount SDK头文件 #import`<LinkAccount_Lib/LinkAccount.h>`
2.在AppDelegate中的 didFinishLaunchingWithOptions方法中添加初始化代码

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    //初始化SDK
     [LMAuthSDKManager initWithKey:@"your Key" complete:^(NSDictionary * _Nonnull resultDic) {
        NSLog(@"%@",resultDic);
    }];
    ...
}
```

**Swift**
创建混编桥接头文件并导入LinkAccount SDK头文件 
#import `<LinkAccount_Lib/LinkAccount.h>`

在AppDelegate中的 didFinishLaunchingWithOptions方法中添加初始化代码

```
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
...        
      LMAuthSDKManager.initWithKey("your appKey") { ([AnyHashable : Any]) in
            
        }
...
        return true
    }
```


###2.预取号


方法原型

```
 * 预取号（获取临时凭证）
 * 建议在判断当前用户属于未登录状态时使用，已登录状态用户请不要调用该方法

+(void)getMobileAuthWithTimeout:(NSTimeInterval)timeout  complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;

```


| 参数 | 类型 | 说明 |
| --- | --- | --- |
| timeout | NSTimeInterval | 超时时间(内部单个请求)，单位s，传大于0有效，传小于等于0使用默认，默认10s   |
|complete|Block|预取号结果回调


**接口作用**

电信、联通、移动预取号 :初始化成功后，如果当前为电信/联通/移动，将调用预取号，可以提前获知当前用户的手机网络环境是否符合一键登录的使用条件，成功后将得到用于一键登录使用的临时凭证，默认的凭证有效期60s(电信)/30min(联通)/60min(移动)。


**使用场景**

建议在执行一键登录的方法前，提前一段时间调用此方法，比如调一键登录的vc的viewdidload中，或者rootVC的viewdidload中，或者app启动后，此调用将有助于提高拉起授权页的速度和成功率
不建议调用后立即调用拉起授权页方法（此方法是异步）
此方法需要1~2s的时间取得临时凭证，因此也不建议和拉起授权页方法一起串行调用
不建议频繁的多次调用和在拉起授权页后调用
建议在判断当前用户属于未登录状态时使用，已登录状态用户请不要调用该方法


> 请求示例代码

OC:


```

#import <LinkAccount_Lib/LinkAccount.h>

//需要拉起授权页的ViewController页面

...
- (void)viewDidLoad {
    [super viewDidLoad];
    if (YourAppLoginStatus == NO) {
        //预取号
         [LMAuthSDKManager getMobileAuthWithTimeout:999 complete:^(NSDictionary * _Nonnull resultDic) {
        //回调结果
    }];
        ...
    }
}
...
//拉起授权页
- (void)authPageLogin{
    ...
}

```


**Swift**

```
class ViewController: UIViewController {

    //需要拉起授权页的ViewController页面

    override func viewDidLoad() {
        
        super.viewDidLoad()        
        //预登陆
        if (YourAppLoginStatus == false) {
            LMAuthSDKManager.getMobileAuth(withTimeout: 88) { (dict) in
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

###3.拉起授权页

```
- (void)getLoginTokenWithController:(UIViewController *_Nonnull)vc model:(LMCustomModel *_Nullable)model timeout:(NSTimeInterval )timeout complete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete otherLogin:(void(^)(void))otherBlock;
```

`在预取号成功后调用`，预取号失败不可调用。调用拉起授权页方法后将会调起运营商授权页面。该方法会拉起登录界面，`已登录状态请勿调用` 。


| 参数 | 类型 | 说明 |
| --- | --- | --- |
| controller | UIViewController | 拉起授权页的vc |
| model | LMCustomModel | 自定义授权页面 |
| timeOut | 超时时间 | 超时时间(内部单个请求)，单位s，传大于0有效，传小于等于0使用默认，默认10s   |
| complete | Block | 授权完成回调 |

使用场景

用户进行一键登录操作时，调用一键登录方法，如果初始化成功，SDK将会拉起授权页面，用户授权后，SDK将返回取号 token给到应用客户端。
可以在多处调用
需在调用预预取号方法方法之后调用


> 请求示例代码


导入LinkAccount SDK头文件 #import `<LinkAccount_Lib/LinkAccount.h>`
在需要使用一键登录的地方调用一键登录接口

**OC**

```
...

- (IBAction)authPageLogin:(id)sender {
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
    //一键登陆
    [[LMAuthSDKManager sharedSDKManager] getLoginTokenWithController:self model:model timeout:888 complete:^(NSDictionary * _Nonnull resultDic) {
        if ([resultDic[@"resultCode"] isEqualToString:SDKStatusCodeSuccess]) {
            NSLog(@"登陆成功");
            
            [[LMAuthSDKManager sharedSDKManager] closeAuthView];
        }else{
            NSLog(@"%@",resultDic);
        }
    } otherLogin:^{
        NSLog(@"用户选择使用其他方式登录");
    }];
}
```



**Swift**

```****
    //拉起授权页
    @IBAction func authPageLogin(_ sender: Any) {
        //自定义Model
        let model = LMCustomModel.init()
        //logo
        model.logoImage = UIImage.init(named: "logo")!
        //是否隐藏其他方式登陆按钮
        model.changeBtnIsHidden = false
        //自定义隐私条款1
        model.privacyOne = ["用户服务条款1","https://www.linkedme.cc"]
        //自定义隐私条款2
        model.privacyTwo = ["用户服务条款2","https://www.linkedme.cc"]
        //隐私条款复选框非选中状态
        model.uncheckedImg = UIImage.init(named: "checkBox_unSelected")!
        //隐私条款复选框选中状态
        model.checkedImg = UIImage.init(named: "checkBox_selected")!
        //登陆按钮
        model.logBtnImgs = [UIImage.init(named: "loginBtn_Nor")!,
                            UIImage.init(named: "loginBtn_Dis")!,
                            UIImage.init(named: "loginBtn_Pre")!]
        //返回按钮
        model.navReturnImg = UIImage.init(named: "goback_nor")!
        
            //一键登陆
            LMAuthSDKManager.shared().getLoginToken(with: self, model: model, timeout: 888, complete: { (dict) in
                //SDKStatusCodeSuccess
                if let resultCode = dict["resultCode"] as? String{
                    if (resultCode == SDKStatusCodeSuccess){
                        print("登陆成功")
                    }
                }
            }) {
                
        }
    }
```

> 成功回调

```
{
	{
	"resultCode": "6666",
	"telecom": "CU",
	"accessToken": "nm4434942e5a874835b78952959e9fbb65",
	"os": "0",
	"gwAuth" : "8787"
	}
}
```
**参数描述**

| 字段 | 类型 | 说明 |
| --- | --- | --- |
| resultCode | NSString | 状态码 |
| telecom | NSString |  <div>当前数据流量卡的运营商类型</div> <div> CM 移动</div> <div>CT 电信</div> <div>CU 联通</div>|
| accessToken | NSString | token，置换令牌，用来和后台置换手机号。一次有效，有效期3min |
| gwAuth | NSString | 仅电信运营商返回此字段，配合accessToken置换手机号 |
| os | NSString | 手机系统 |


开发者需将此data字典作为参数，以form-data格式完整地发送到开发者后台配置的`查询手机号API`

异常处理

用户取消登录(授权页点击返回) 【处理建议：若无特殊需求可不做处理】
用户选择其他方式登录(点击授权页自带的其他方式登录): 【处理建议：可根据实际情况跳转其他登录方式 】
其他错误 【处理建议：可根据实际情况跳转其他登录方式 】


### 4.本机号码验证
```
- (void)getAccessCodeWithcomplete:(void (^_Nullable)(NSDictionary * _Nonnull resultDic))complete;
```

调用后返回accessCode用于本机号码验证。该方法不会拉起登录界面，用于校验用户输入的手机号码是否为本机号码。


| 字段 | 类型 | 说明 |
| --- | --- | --- |
| complete | Block | 回调  |

**OC**

```
...
- (IBAction)phoneNumValidation:(id)sender {
    [[LMAuthSDKManager sharedSDKManager]getAccessCodeWithcomplete:^(NSDictionary * _Nonnull resultDic) {
        NSLog(@"%@",resultDic);
    }];
}
...
```

**Swift**

```
...
@IBAction func authLogin(_ sender: Any) {
    LMAuthSDKManager.getMobileAuth(withTimeout: 666) { ([AnyHashable : Any]) in
        
    }
}
...
```


###5.手动关闭授权页
当开发者设置点击一键登录或者自定义控件不自动销毁授权页时，将需要自行调用此方法主动销毁授权页，建议在置换手机号成功后销毁。如在得到回调后未销毁授权页而，使用拉起授权页方法再次拉起授权页，此页面将无法响应任何按键（除了导航栏的返回按钮）。

> 关闭授权页时机

- a.SDK拉起授权页方法 直接回调失败时
- b.置换手机号有返回结果时

```
    [[LMAuthSDKManager sharedSDKManager] closeAuthView];
```

##三.授权界面修改

![](https://pagedoc.lkme.cc/.gitbook/assets/sdk-shou-quan-ye-she-ji-gui-fan.jpg)
可以调整属性

```
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
```


### 四.返回码对照


| 状态码 |   描述 |
| --- | --- | 
| 6666 | 成功  |
| 5555 | 用户取消登陆 |  
| 4444 | 数据解析异常   |  
| 1111 | 无网络   |  
| 2222 | 请求超时   |  
| 2233 | 其他错误   |  
| 3344 | 蜂窝数据未开启或不稳定   |  

### 五.已知问题
1.ATS开关(Http与Https)

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


