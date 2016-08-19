//
//  LYFaceTime.h
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
#import "LYPlayerConfiguration.h"


@interface LYFaceTime : NSObject


/**
 *  初始化方法
 *
 *  @param videoConfiguration 视频采集编码以及推流的配置信息
 *  @param audioConfiguration 音频采集编码以及推流的配置信息
 *
 *  @return LYFaceTime 实例
 *
 *  初始化的时候回首先根据配置参数使用对应摄像头，如果没有设备不支持当前设置摄像头，则开启该设备默认支持的摄像头，如果都没有，则返回nil.
 */

- (instancetype) initWithVideoConfiguration: (LYVideoStreamingConfiguration *)videoConfiguration
                         audioConfiguration: (LYAudioStreamingConfiguration *)audioConfiguration;

/**
 *  重设音视频采集参数
 *
 *  @param videoConfig 视频流配置类
 *  @param audioConfig 音频流配置类:该版本不支持重置采集和推流参数，未来版本支持会在文档更新说明
 */
- (void) resetVideoConfig: (LYVideoStreamingConfiguration *)videoConfig
              audioConfig: (LYAudioStreamingConfiguration *)audioConfig;

#pragma mark - 本地采集和推流控制
/**
 *  设置预览view
 *
 *  @param preview 预览的view
 *  @param frame   view.frame
 *
 *  如果在viewDidLoad就调用预览方法，则frame需要用：CGRectMake(0, 0, kScreenWidth, kScreenHeight);这样的格式，
 *                  示例代码：[facetime setPreview:self.preview frame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
 *  如果在viewDidLayoutSubviews之后调用，则可以直接传入self.preview.frame作为参数
 *                  示例代码：[facetime setPreview:self.preview frame:self.preview.frame]；
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

/*！
 *  设置传输码率：切换发送码率：普通、标清、高清
 *
 *  disc: 改接口设置的码率是推流码率。要改变对方的码率请消息通知对方调用该接口让对方传输码率改变。
 *  @param qualityLevel 码率等级
 */
- (void) setVideoEncodeBitrateLevel: (LYVideoStreamingQualityLevel)qualityLevel;

#pragma mark 单独控制音视频流是否推流的接口
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

#pragma mark - 观看对方的操作

/**
 *  设置播放器配置参数
 *
 *  @param dataSourceAddress   播放地址
 *  @param playerConfiguration 播放器配置类：播放器view、view.frame、解码方式等；
 */
- (void) setPlayView: (NSString *)dataSourceAddress
 playerConfiguration: (LYPlayerConfiguration *)playerConfiguration;

/**
 *  更改播放器frame---->开始播放之后动态修改播放器的frame调用
 *
 *  @param dataSourceAddreess 播放地址
 *  @param frame frame
 */
- (void)setPlayViewFrame: (NSString *)dataSourceAddreess frame: (CGRect)frame;

//调用open之后要调用close释放相应的资源：拿到连接地址的一方调用。
/**
 *  打开播放器：播放地址(由第三方后台返回)
 *
 *  @param dataSourceAddreess 播放源：播放地址
 *  @param openBlock          打开状态回调
 *  @param playerBlock        播放状态回调
 */
- (void)open: (NSString *)dataSourceAddreess
  openStatus: (void (^)(LYstatusCode statusCode, NSString *errorString))openBlock
playerStatus: (playerCallBackBlock)playerBlock;

/**
 *  关闭播放器:会关闭播放器以及断开播放连接-----注意openPlayerWithPlayerAddress成功之后一定要调用closePlayer释放底层资源，否则内存泄露
 *  @param dataSourceAddreess 播放地址
 */
- (void)close: (NSString *)dataSourceAddreess;


/**
 *  打开声音
 *  @param dataSourceAddreess 播放地址
 */
- (NSInteger)unmute: (NSString *)dataSourceAddreess;

/**
 *  关闭声音
 *  @param dataSourceAddreess 播放地址
 */
- (void)mute: (NSString *)dataSourceAddreess;


/**
 *  获取播放(流媒体参数)信息数据
 *
 *  @param dataSourceAddreess 播放地址
 *  @param stremMediaParam 想要获取信息的对应序号
 *
 *  @return 当前信息数据
 */
- (NSString *)getMediaParam: (NSString *)dataSourceAddreess mediaParam: (LYStreamMediaParam)stremMediaParam;

/**
 *  创建视频截图
 *
 *  @param dataSourceAddreess 播放地址
 *  @param path          路径：包括文件名-->后缀jpg格式
 *  @param snapshotBlcok 截图成功与否回调 SNAPSHOT_TYPE(enum)
 */
- (void)snapshot: (NSString *)dataSourceAddreess path: (NSString *)path
          status:(void (^)(LYstatusCode statusCode, NSString *errorString))snapshotBlock;

/**
 *  开始录像
 *
 *  @param dataSourceAddreess 播放地址
 *  @param path 路径：包括文件名-->后缀mp4格式
 */
- (void)startLocalRecord: (NSString *)dataSourceAddreess path: (NSString *)path
                  status: (void (^)(LYstatusCode statusCode, NSString *errorString))startRecordBlock;

/**
 *  结束录像
 *
 *  @param dataSourceAddreess 播放地址
 *  @param stopLocalRecordBlock 回调录像 size:录制大小，单位:KB  time:录制时长，单位：s
 */

- (void)stopLocalRecord: (NSString *)dataSourceAddreess patj: (void (^)(NSInteger size, NSInteger time))stopLocalRecordBlock;


#pragma mark - 销毁
/**
 *  释放资源：
 *
 *  切忌不用互联类的时候一定要调用该方法释放内部资源，否则内存泄露。
 */
- (void) destroy;

@end


