//
//  LYCalledInternetViewController.m
//  LYCloudDemo
//
//  Created by QuinnQiu on 16/1/13.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import "LYCalledInternetViewController.h"

#import "AFNetworking.h"
//#import "LYCloudInterConnect.h"
#import "AppDelegate.h"

//#import "LYCloudVideoCaptue.h"

//#import "LYTestModel.h"
#import "LYFaceTime.h"



#define kScreenWidth [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height

@interface LYCalledInternetViewController () <UIAlertViewDelegate> {
//    LYCloudInterConnect *connect;
    NSString *connectPhoneNumber;
    NSString *connString;
    LYFaceTime *faceTime;
    LYVideoStreamingConfiguration *videoConfig;
    LYAudioStreamingConfiguration *audioConfig;
    LYPlayerConfiguration *playerConfig;

}

@property (nonatomic, strong) dispatch_source_t timer;

@property (weak, nonatomic) IBOutlet UIView *preview;
@property (weak, nonatomic) IBOutlet UIView *playview;

@end

@implementation LYCalledInternetViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initSubViews];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (void) viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [faceTime destroy];
    faceTime = nil;
    self.timer = nil;
    
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
- (void) initSubViews {
    self.navigationItem.title = @"互联被叫";
    
    videoConfig = [LYVideoStreamingConfiguration defaultConfiguration];
    
    audioConfig = [LYAudioStreamingConfiguration defaultConfiguration];
    
    NSLog(@"start");
    faceTime = [[LYFaceTime alloc] initWithVideoConfiguration:videoConfig audioConfiguration:audioConfig];
    
    [faceTime setPreview:self.preview frame:CGRectMake(0, 0, 150, 200)];
    
    playerConfig = [[LYPlayerConfiguration alloc] initWithPlayView:self.playview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight) decodeMode:LYPlayerDecodeModeHard];
    [faceTime setPlayView:nil playerConfiguration:playerConfig];
    connString = @"topvdn://203.195.157.248:80?protocolType=1&token=2147550103_3356753920_1685865792_1e4794f3fd1c2e8f5b1e374a405a6b33";
    
    [self connect];
}

- (void) connect{

    [faceTime open:connString openStatus:^(LYstatusCode statusCode, NSString *errorString) {
        NSLog(@"open statusCode = %d, errorString = %@", statusCode, errorString);
    } playerStatus:^(NSDictionary *playerMessageDic) {
        NSLog(@"playerMessageDic = %@", playerMessageDic);
    }];
}


- (void) start{
    [faceTime startSendVideoData];
    [faceTime startSendAudioData];
}


- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    
    if (buttonIndex == 1) {
        [self connect];
    } else {
        //拒绝消息发送
//        [self callBackToMineFriendsWitmessage:KEY_CONNECT_REFUSE_iOS];
    }
}

- (IBAction)location:(UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        [faceTime startSendAudioData];
        [sender setTitle:@"关闭本地音频" forState:UIControlStateNormal];
    } else{
        [faceTime stopSendAudioData];
        [sender setTitle:@"开启本地音频" forState:UIControlStateNormal];
    }
}

- (IBAction)open:(UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        [faceTime unmute:nil];
        [sender setTitle:@"关闭播放" forState:UIControlStateNormal];
    } else {
        [faceTime mute:nil];
        [sender setTitle:@"开启播放" forState:UIControlStateNormal];
    }
}

- (IBAction)change:(UIButton *)sender {
    [faceTime stopSendVideoData];
    sender.selected = !sender.selected;
    //修改码率：普通、标清、高清
    if (!sender.selected) {
        
    } else{
        
    }
}

- (IBAction)swapCamer:(UIButton *)sender {
    sender.selected = !sender.selected;
    LYCaptureCameraMode mode = LYCaptureCameraModeFront;
    if (sender.selected) {
        mode = LYCaptureCameraModeBack;
    }
    [faceTime switchCamera:mode switchBlock:^(LYstatusCode statusCode, NSString *errorString) {
        NSLog(@"statuscode = %ld, errorstring = %@", (long)statusCode, errorString);
    }];
}

@end
