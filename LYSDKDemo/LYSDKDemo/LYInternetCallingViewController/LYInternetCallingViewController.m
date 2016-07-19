//
//  LYInternetCallingViewController.m
//  LYCloudDemo
//
//  Created by QuinnQiu on 16/1/13.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import "LYInternetCallingViewController.h"
#import "AppDelegate.h"
#import "LYFaceTime.h"



#define kScreenWidth [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height

@interface LYInternetCallingViewController (){
    LYFaceTime *faceTime;
    NSString *connString;
    
    LYVideoStreamingConfiguration *videoConfig;
    LYAudioStreamingConfiguration *audioConfig;
    LYPlayerConfiguration *playerConfig;
}

@property (weak, nonatomic) IBOutlet UIView *preview;
@property (weak, nonatomic) IBOutlet UIView *playview;

@end

@implementation LYInternetCallingViewController

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
    self.navigationItem.title = @"互联主叫";
    videoConfig = [LYVideoStreamingConfiguration defaultConfiguration];
    
    audioConfig = [LYAudioStreamingConfiguration defaultConfiguration];
    
    NSLog(@"start");
    faceTime = [[LYFaceTime alloc] initWithVideoConfiguration:videoConfig audioConfiguration:audioConfig];
  
    [faceTime setPreview:self.preview frame:CGRectMake(0, 0, 150, 200)];
    
    playerConfig = [[LYPlayerConfiguration alloc] initWithPlayView:self.playview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight) decodeMode:LYPlayerDecodeModeHard];
    [faceTime setPlayView:nil playerConfiguration:playerConfig];

}

#pragma mark 本地
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

#pragma mark 远程
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

- (IBAction)swapCamera:(UIButton *)sender {
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
