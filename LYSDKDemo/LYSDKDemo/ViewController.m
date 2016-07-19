//
//  ViewController.m
//  LYSDKDemo
//
//  Created by QuinnQiu on 16/5/31.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import "ViewController.h"
#import "LYCloudWatchViewController.h"
#import "LYMobileLivingViewController.h"
#import "LYInternetCallingViewController.h"
#import "LYCalledInternetViewController.h"
#import "LYHistoryCameraViewController.h"
#import "AppDelegate.h"
#import "LYCloudService.h"


@interface ViewController ()<UITableViewDelegate, UITableViewDataSource>{//两个协议遵守
    BOOL num1Open;
    BOOL num2Open;
    AppDelegate *app;
    
    UITableView *mTableView;//定义tableView
    NSMutableArray *array;//第一次显示的数组
    NSMutableArray *array2;//第二次显示的数组
    BOOL isFirst;//第一次显示的标记
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    num1Open = NO;
    num2Open = NO;
    app = [UIApplication sharedApplication].delegate;
    
    //
    array = [[NSMutableArray alloc] initWithCapacity:1];
    for (int i = 0; i < 10; i++) {
        [array addObject:[NSString stringWithFormat:@"test%zd", i]];
    }
    
    array2 = [[NSMutableArray alloc] initWithCapacity:1];
    for (int i = 0; i < 10; i++) {
        [array2 addObject:[NSString stringWithFormat:@"change %zd", i]];
    }
    isFirst = YES;
    
    //初始化tableview
    mTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 60, 200, 200) style:UITableViewStylePlain];
    [self.view addSubview:mTableView];
    mTableView.delegate = self;
    mTableView.dataSource = self;
    mTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    
    mTableView.hidden = YES;
    
}

//总共有多少行
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    NSInteger nCount = 0;
    if (isFirst) {
        nCount = array.count;
    } else {
        nCount = array2.count;
    }
    return nCount;
}

//每一行的高度
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 20;
}

//设置每一行的显示内容
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellID = @"cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellID];
    }
    
    NSString *text;
    if (isFirst) {
        text = array[indexPath.row];
    } else {
        text = array2[indexPath.row];
    }

    cell.textLabel.text = text;
    
    return cell;
}

//点击每一行的时候调用这个方法，拿到对应的数据
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"select data:%@", array[indexPath.row]);
    if (isFirst) {
        isFirst = NO;
        [mTableView reloadData];
    } else {
        mTableView.hidden = YES;
    }
    
}

- (void) clickButton: (UIButton *)sender {
    mTableView.hidden = NO;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark 账号1
- (IBAction)openPlatform:(UIButton *)sender {
    
//    nIsRealtimeMode = 0；老配置，= 1新配置
    NSString *config = @"[Config]\r\nIsRealtimeMode=1\r\nIsDebug=1\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\nSendPacketBufferLength=1408\r\nRecvPacketBufferLength=1408\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n";
    
    NSString *token = @"2147550103_3356753920_1685865792_1e4794f3fd1c2e8f5b1e374a405a6b33";
    
    [[LYCloudService sharedLYCloudService] startCloudService:token config:config startBlock:^(LYstatusCode statusCode, NSString *errorString) {
        QLog(@"startCloudService startus = %zd", statusCode);
    } popMessageBlock:^(NSDictionary *dictionary) {
        QLog(@"startCloudService dictionary = %@", dictionary);
    }];
    
}

#pragma mark 账号2
- (IBAction)openPlatform2:(UIButton *)sender {
    
    NSString *config = @"[Config]\r\nIsRealtimeMode=1\r\nIsDebug=1\r\nIsCaptureDev=1\r\nIsPlayDev=1\r\nIsSendBroadcast=0\r\nUdpSendInterval=2\r\nSendPacketBufferLength=1408\r\nRecvPacketBufferLength=1408\r\n[Tracker]\r\nCount=3\r\nIP1=121.42.156.148\r\nPort1=80\r\nIP2=182.254.149.39\r\nPort2=80\r\nIP3=203.195.157.248\r\nPort3=80\r\n[LogServer]\r\nCount=1\r\nIP1=120.26.74.53\r\nPort1=80\r\n";
    
    NSString *token = @"2147550104_3356753920_1685865797_f3e97fe4eb47bf8836c9eceee4e375bb";
    
    [[LYCloudService sharedLYCloudService] startCloudService:token config:config startBlock:^(LYstatusCode statusCode, NSString *errorString) {
        QLog(@"startCloudService startus = %zd", statusCode);
    } popMessageBlock:^(NSDictionary *dictionary) {
        QLog(@"startCloudService dictionary = %@", dictionary);
    }];
   
}


#pragma mark 观看直播
- (IBAction)watch:(UIButton *)sender {
    UIStoryboard *vcSB = [UIStoryboard storyboardWithName:@"LYCloudWatchVC" bundle:nil];
    LYCloudWatchViewController *vc = [vcSB instantiateViewControllerWithIdentifier:@"LYCloudWatchVC_ID"];
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark 观看历史
- (IBAction)clickHistoryBtn:(UIButton *)sender {
    LYHistoryCameraViewController *vc = [[LYHistoryCameraViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}
#pragma mark 手机直播
- (IBAction)phoneLiving:(UIButton *)sender {
    UIStoryboard *vcSB = [UIStoryboard storyboardWithName:@"LYMobileLivingViewController" bundle:nil];
    LYMobileLivingViewController *vc = [vcSB instantiateViewControllerWithIdentifier:@"LYMobileLivingVC_ID"];
    [self.navigationController pushViewController:vc animated:YES];
}


#pragma mark 互联主叫
- (IBAction)clickCallingBtn:(UIButton *)sender {
    UIStoryboard *vcSB = [UIStoryboard storyboardWithName:@"LYInternetCallingViewController" bundle:nil];
    LYInternetCallingViewController *vc = [vcSB instantiateViewControllerWithIdentifier:@"LYInternetCallingVC_ID"];
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark 互联被叫
- (IBAction)clickCalledBtn:(UIButton *)sender {
    UIStoryboard *vcSB = [UIStoryboard storyboardWithName:@"LYCalledInternetViewController" bundle:nil];
    LYCalledInternetViewController *vc = [vcSB instantiateViewControllerWithIdentifier:@"LYCalledInternetVC_ID"];
    [self.navigationController pushViewController:vc animated:YES];
    
}
@end
