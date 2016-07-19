//
//  LYMobileLivingViewController.m
//  LYMobileLivingDemo
//
//  Created by QuinnQiu on 16/1/12.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import "LYMobileLivingViewController.h"
#import "AppDelegate.h"
#import "LYLiveBroadcast.h"

#import "LYPlayer.h"

#define TICK   NSDate *startTime = [NSDate date]


#define TOCK   NSLog(@"live Time: %f", -[startTime timeIntervalSinceNow])
/*
 *手机视频采集步骤：( https://github.com/QiuQuinn/QQVideoCapture.git )
 *1、初始化QQVideoSessionManager类指针；
 *2、设置预览view：- (void) setPreview: (UIView *)preview withFrame: (CGRect)frame;
 *3、开启采集：- (void) startVideoCapture；
 
 */

#define kRetFaild   -1//失败
#define kRetDefault 0//默认
#define kRetSuccess 1//成功
#define kRetOpening 2//调用打开中



#define kScreenWidth [UIScreen mainScreen].bounds.size.width
#define kScreenHeight [UIScreen mainScreen].bounds.size.height


@interface LYMobileLivingViewController ()<UIGestureRecognizerDelegate>{
    LYLiveBroadcast *living;
    
    NSInteger retOpenCloud;
    NSString *rtmpStr;
    UIView *playView;
    LYPlayer *player;
    LYVideoStreamingConfiguration *videoConfig;
    LYAudioStreamingConfiguration *audioConfig;
    UIView *preview;
}
@property (weak, nonatomic) IBOutlet UIView *preview;

@end

@implementation LYMobileLivingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initSubviews];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [living destroy];
    //    [connect closePlayerVideoConnectAddress:nil status:nil];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void) test{
//    
//    //该方法生成一个默认的视频采集配置、videoSize = (640, 480); frameRate = 30fps, bitrate = 512kbps;
//    LYVideoStreamingConfiguration *mVideoConfig = [LYVideoStreamingConfiguration defaultConfiguration];
//    
//    //该方法生成一个默认的音频采集配置。sampleRate = 44100, channle = 1, birrate = 128kpbs,
//    LYAudioStreamingConfiguration *mAudioConfig = [LYAudioStreamingConfiguration defaultConfiguration];
//    
//    //初始化直播类:如果不采集音频，则audioConfiguration传nil即可，不采集视频相同
//    LYLiveBroadcast *mLiving = [[LYLiveBroadcast alloc] initWithVideoConfiguration:mVideoConfig audioConfiguration:mAudioConfig];
//    
//    //设置采集视频预览view
//    [mLiving setPreview:self.preview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
//    
//    NSString *mToken;
//    
//    //直播资源的准备，返回 statusCode == LYstatusCodeSuccess 才可以推流
//    [mLiving startLiveBroadcastWithMode:LYLiveBroadcastModeLiving token:mToken startBlock:^(LYstatusCode statusCode, NSString *errorString) {
//        
//        if (LYstatusCodeSuccess == statusCode) {
//           //直播资源准备完成，可以开始推流；
//        }
//        
//    }];
//    
//    //开始推流
//    [mLiving startSendData];
//    
//    //也可以调用单独的视频和音频推流接口
//    [mLiving startSendVideoData];
//    [mLiving startSendAudioData];
}

- (void) initSubviews {
    self.navigationItem.title = @"开启手机直播";
    videoConfig = [LYVideoStreamingConfiguration defaultConfiguration];
    
    audioConfig = [LYAudioStreamingConfiguration defaultConfiguration];
    
    living = [[LYLiveBroadcast alloc] initWithVideoConfiguration:videoConfig audioConfiguration:audioConfig];

    [living setPreview:self.preview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
    
        [self setLivingParam];
//    });
    preview = nil;
}

#pragma mark 连接开始直播
- (void) setLivingParam{
    
    NSString *token = @"topvdn://0.0.0.0:0?token=2147550103_3356753920_1685865792_1e4794f3fd1c2e8f5b1e374a405a6b33&protocolType=2&connectType=1&mode=2";
    __block LYMobileLivingViewController *weakSelf = self;
    [living startLiveBroadcast:token startBlock:^(LYstatusCode statusCode, NSString *errorString) {
        
        NSLog(@"startLiveBroadcastWithMode errorString = %@, statusCode = %zd", errorString, statusCode);
        if (LYstatusCodeSuccess == statusCode) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                
                [weakSelf startSendData];
            });
        }
        
    }];
}

- (void) startSendData{
    NSLog(@"startSendData");
    [living startSendVideoData];
    [living startSendAudioData];
}

#pragma mark 点击关闭
- (IBAction)clickCancleBtn:(UIButton *)sender {
    
//    [self.navigationController popViewControllerAnimated:YES];
    sender.selected = !sender.selected;
    LYCaptureCameraMode mode = LYCaptureCameraModeFront;
    if (sender.selected) {
        mode = LYCaptureCameraModeBack;
    }
    [living switchCamera:mode switchBlock:^(LYstatusCode statusCode, NSString *errorString) {
        NSLog(@"statuscode = %ld, errorstring = %@", (long)statusCode, errorString);
    }];
}

#pragma mark 切换前后摄像头
- (IBAction)clickCameraFrontOrBackBtn:(UIButton *)sender {
//    if (preview != nil) {
//        [preview removeFromSuperview];
//        preview = nil;
//    }
    if (preview == nil) {
        
        preview = [[UIView alloc] initWithFrame:CGRectMake(20, 20, 150, 200)];
        preview.backgroundColor = [UIColor greenColor];
        [self.view addSubview:preview];
        [living setPreview:preview frame:CGRectMake(0, 0, 150, 200)];
        // 移动手势
        [self addGestureRecognizerToView:preview];
    }
//    int x = arc4random() % 100;
//    int y = arc4random() % 500;
//    preview = [[UIView alloc] initWithFrame:CGRectMake(x, y, 150, 200)];
//    preview.backgroundColor = [UIColor greenColor];
//    [self.view addSubview:preview];
//    [living changePreview:preview frame:CGRectMake(0, 0, 150, 200)];
//    [living setPreview:preview frame:CGRectMake(0, 0, 150, 200)];
//    sender.selected = !sender.selected;
//    LYCaptureCameraMode mode = LYCaptureCameraModeFront;
//    if (sender.selected) {
//        mode = LYCaptureCameraModeBack;
//    }
//    [living switchCamera:mode switchBlock:^(LYstatusCode statusCode, NSString *errorString) {
//        NSLog(@"statuscode = %ld, errorstring = %@", (long)statusCode, errorString);
//    }];
}

#pragma mark 头像添加的手势
// 添加所有的手势
- (void) addGestureRecognizerToView:(UIView *)view
{
    UIPinchGestureRecognizer *pinchGestureRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinchView:)];
    [view addGestureRecognizer:pinchGestureRecognizer];
    
    // 移动手势
    UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(panView:)];
    [view addGestureRecognizer:panGestureRecognizer];
}


// 处理缩放手势
- (void) pinchView:(UIPinchGestureRecognizer *)pinchGestureRecognizer
{
    UIView *view = pinchGestureRecognizer.view;
    if (pinchGestureRecognizer.state == UIGestureRecognizerStateBegan
        || pinchGestureRecognizer.state == UIGestureRecognizerStateChanged) {
        view.transform = CGAffineTransformScale(view.transform, pinchGestureRecognizer.scale, pinchGestureRecognizer.scale);
        pinchGestureRecognizer.scale = 1;
    }
}

// 处理拖拉手势
- (void) panView:(UIPanGestureRecognizer *)panGestureRecognizer
{
    UIView *view = panGestureRecognizer.view;
    if (   panGestureRecognizer.state == UIGestureRecognizerStateBegan
        || panGestureRecognizer.state == UIGestureRecognizerStateChanged) {
        CGPoint translation = [panGestureRecognizer translationInView:view.superview];
        [view setCenter:(CGPoint){view.center.x + translation.x, view.center.y + translation.y}];
        [panGestureRecognizer setTranslation:CGPointZero inView:view.superview];
    }
}

#pragma mark 打开闪光灯
- (IBAction)clickLightBtn:(UIButton *)sender {
    
    sender.selected = !sender.selected;
    [self turnTorchOn:sender.selected];
}
#pragma mark 开关闪光灯
- (void)turnTorchOn:(bool)on {
    
    Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
    if (captureDeviceClass != nil) {
        AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        
        if ([device hasTorch] && [device hasFlash]){
            
            [device lockForConfiguration:nil];
            if (on) {
                [device setTorchMode:AVCaptureTorchModeOn];
                [device setFlashMode:AVCaptureFlashModeOn];
            } else {
                [device setTorchMode:AVCaptureTorchModeOff];
                [device setFlashMode:AVCaptureFlashModeOff];
            }
            [device unlockForConfiguration];
            [self clickCameraFrontOrBackBtn:nil];
        }
    }
}

- (void) start{
    
}



- (void) dealloc {
   
}

@end
