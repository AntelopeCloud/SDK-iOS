//
//  LYLiveBroadcast.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/23.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"
#import "LYVideoStreamingConfiguration.h"
#import "LYAudioStreamingConfiguration.h"

@interface LYLiveBroadcast : NSObject

/**
 *  初始化方法
 *
 *  @param videoConfiguration 视频采集编码以及推流的配置信息
 *  @param audioConfiguration 音频采集编码以及推流的配置信息
 *
 *  @return LYLiveBroadcast 实例
 *
 *  初始化的时候回首先根据配置参数使用对应摄像头，如果没有设备不支持当前设置摄像头，则开启该设备默认支持的摄像头，如果都没有，则返回nil.
 */

- (instancetype) initWithVideoConfiguration: (LYVideoStreamingConfiguration *)videoConfiguration
                         audioConfiguration: (LYAudioStreamingConfiguration *)audioConfiguration;

/**
 *  重设音视频采集参数
 *
 *  @param videoConfig 视频流配置类
 *  @param audioConfig 音频流配置类
 */
- (void) resetVideoConfig: (LYVideoStreamingConfiguration *)videoConfig
              audioConfig: (LYAudioStreamingConfiguration *)audioConfig;


/**
 *  开始直播
 *
 *  @param dataSourceAddress        直播地址
 *  @param startBlock               连接状态回调
 *
 *  该方法需要提前调用：直播的资源准备过程需要时间，包括和平台的连接建立等操作。
 *  该方法不是应用的开始直播，是指开始直播的前期资源准备。
 */
- (void) startLiveBroadcast: (NSString *)dataSourceAddress
                 startBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))startBlock;

/*！
 *  停止直播：断开直播连接释放资源。
 *
 *  结束直播后还要处理其他逻辑的时候应立即调用，防止占用资源
 */
- (void) stopLiveBroadcast;

/**
 *  设置预览view
 *
 *  @param preview 预览的view
 *  @param frame   view.frame
 *
 *  如果在viewDidLoad就调用预览方法，则frame需要用：CGRectMake(0, 0, kScreenWidth, kScreenHeight);这样的格式，
 *                  示例代码：[living setPreview:self.preview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
 *  如果在viewDidLayoutSubviews之后调用，则可以直接传入self.preview.frame作为参数
 *                  示例代码：[living setPreview:self.preview frame:self.preview.frame]；
 *
 *  调用该方法则会主动开启摄像头采集，调用的时候无需调用startVideoCapture;
 */
- (void) setPreview: (UIView *)preview
              frame: (CGRect)frame;

/**
 *  切换摄像头
 *
 *  @param cameraMode  前后置摄像头
 *  @param switchBlock 切换成功与否回调
 */
- (void) switchCamera: (LYCaptureCameraMode)cameraMode
          switchBlock: (void (^)(LYstatusCode statusCode, NSString *errorString))switchBlock;

/**
 *  打开闪光灯
 *
 *  @param on        是否打开: YES:打开 NO:关闭
 *  @param turnBlock 打开闪光灯状态回调：当当前摄像头采集为前置的时候闪光灯打开失败
 */
- (void) turnTorchAndFlashOn: (BOOL)on
                      status: (void (^)(LYstatusCode statusCode, NSString *errorString))turnBlock;

#pragma mark - 单独控制音视频流是否推流的接口
/**
 *  开始推视频流
 */
- (void) startSendVideoData;

/**
 *  停止推视频流
 */
- (void) stopSendVideoData;

/**
 *  开始推音频流
 */
- (void) startSendAudioData;

/**
 *  停止推音频流
 */
- (void) stopSendAudioData;

/**
 *  获取当前的错误信息，如果为nil或者@“”表示当前无错误信息
 *
 *  @return 错误信息
 */
- (NSString *) getCurrentErrorInfo;

/**
 *  获取当前采集帧UIImage
 *
 *  @param success 获取UIImage的block
 */
- (void) getCurrentFrameImage: (void (^)(UIImage *image, char *imageBuffer, int bufferLength))success;

/**
 *  释放资源：
 *
 *  切忌不用直播类的时候一定要调用该方法释放内部资源，否则内存泄露。
 */
- (void) destroy;

@end
