//
//  LYCloudWatchViewController.m
//  LingyangAPI
//
//  Created by QuinnQiu on 16/3/15.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

//屏幕宽高
#define kScreenWidth [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height

#define TESTCLUST_HASH_CID     @"B5990A006298A196"

#define TESTCLUST_CID     @"10000025"

#import "LYCloudWatchViewController.h"
#import "LYPlayer.h"

#import <objc/runtime.h>

@interface LYCloudWatchViewController (){
    LYPlayer *player;
    LYPlayerConfiguration *playerConfig;
    
}

@property (weak, nonatomic) IBOutlet UIView *playerview;

@end

@implementation LYCloudWatchViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.navigationItem.title = @"观看直播";
    
    
    self.view.transform = CGAffineTransformMakeRotation(M_PI_2);//观看摄像头时候旋转
    player = [[LYPlayer alloc] init];
    
    UIScrollView *sView1 = [[UIScrollView alloc] initWithFrame:CGRectMake(40, 0, kScreenHeight, kScreenWidth)];//摄像头
    sView1.backgroundColor = [UIColor redColor];
    sView1.contentSize = CGSizeMake(2000, 0);
    [self.view addSubview:sView1];
    
    playerConfig = [[LYPlayerConfiguration alloc] initWithPlayView:sView1 frame:CGRectMake(40, 0, kScreenHeight, kScreenWidth) decodeMode:LYPlayerDecodeModeSoft];
    [player setViewWithConfiguration:playerConfig];
    
    //纯私有
//    [player open:@"topvdn://203.195.157.248:80?protocolType=1&connectType=2&token=10000025_3356491776_1464660470_9c3b8ffc37bd21032d14d00a6eb9f389" openStatus:^(LYstatusCode statusCode, NSString *errorString) {
//        NSLog(@"errorString = %@, statusCode = %zd", errorString, statusCode);
//    } playerStatus:^(NSDictionary *playerMessageDic) {
//        NSLog(@"dictionary = %@", playerMessageDic);
//    }];
    
    //私有带录像 10000025_3356491776_1464438005_7fb7fadbf8bdc58beb8e31d2d88fa9a1
    
//    [player open:@"topvdn://183.57.151.177:1935?protocolType=2&connectType=2&token=10000025_3356491776_1464660684_9812af5d6a2ace484beae309c900745e" openStatus:^(LYstatusCode statusCode, NSString *errorString) {
//        
//        QLog(@"thread = %@", [NSThread currentThread]);
//        NSLog(@"errorString = %@, statusCode = %zd", errorString, statusCode);
//    } playerStatus:^(NSDictionary *playerMessageDic) {
//
//        NSLog(@"dictionary = %@", playerMessageDic);
//    }];
    
    
    //rtmp
    [player open:@"rtmp://rtmp2.public.topvdn.cn/live/10000412_3356491776_1464659762_467355d0e0f14f6613e9426f2f797781" openStatus:^(LYstatusCode statusCode, NSString *errorString) {
        NSLog(@"errorString = %@, statusCode = %zd", errorString, statusCode);
    } playerStatus:^(NSDictionary *playerMessageDic) {
        NSLog(@"dictionary = %@", playerMessageDic);
    }];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [player close];
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
