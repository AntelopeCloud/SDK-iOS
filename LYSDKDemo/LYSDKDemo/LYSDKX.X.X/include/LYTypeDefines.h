//
//  LYTypeDefines.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/21.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#ifndef LYTypeDefines_h
#define LYTypeDefines_h


#pragma mark - status code

/**
 *  羚羊云SDK状态码
 *
 *  每个模块对应的错误状态码，调用对应功能失败时候请log当前API的状态码！
 */
typedef NS_ENUM(NSInteger, LYstatusCode) {
    LYstatusCodeSuccess                          = 0,  //成功
    
    //统一的错误码
    LYstatusCodeUnityErrorParamInvalid           = -2000,//传入的参数为nil或者null(主要用于检测token等连接参数)
    LYstatusCodeUnityErrorOperaterNil            = -2004,//调用对应操作的对象为nil
    LYstatusCodeUnityErrorIsStarting             = -2005,//调用的某个操作正在进行中(还未执行完成)ServiceOutline
    LYstatusCodeUnityErrorIsSuccess              = -2006,//调用的某个操作已经成功，再次调用的时候需要调用其对应的停止和关闭接口(已经成功返回再调用状态)
    LYstatusCodeUnityErrorServiceOutline         = -2007,//调用的接口需要云服务时，云服务离线或者未启动云服务
    
    //启动云服务错误码
    LYstatusCodeStartCloudServiceError           = -3000,//启动云服务失败
    LYstatusCodeStartCloudServiceIsBusy          = -3001,//服务繁忙中(正在启动云服务中，还未返回)
    LYstatusCodeStartCloudServiceIsSuccess       = -3002,//云服务已经启动成功,要重新调用启动云服务则需要先调用stop云服务
    
    //播放器(LYPlayer)错误码
    LYstatusCodePlayerErrorScheme                = -4000,//播放地址格式不对(只判断头信息uri:scheme)
    LYstatusCodePlayerErrorType                  = -4001,//播放类型不正确(type)
    LYstatusCodePlayerErrorOpenProtocol          = -4002,//打开播放协议失败
    LYstatusCodePlayerErrorOpenPlayer            = -4003,//打开播放器失败
    LYstatusCodePlayerErrorRecordFromToInvalid   = -4004,//观看录像的from || to 为0
    LYstatusCodePlayerErrorRequestRecordInfo     = -4005,//获取录像信息错误
    LYstatusCodePlayerErrorSeekTimestamp         = -4006,//seek失败
    LYstatusCodePlayerErrorSavePathInvalid       = -4007,//截图或者本地录像路径为空
    LYstatusCodePlayerErrorSnapshot              = -4008,//截图失败
    LYstatusCodePlayerErrorStartLocalRecord      = -4009,//本地录像失败
    LYstatusCodePlayerErrorNoSetPlayerConfig     = -4010,//没设置播放器配置
    LYstatusCodePlayerErrorLocalRecording        = -4011,//正在进行本地录像，需要先停止录制才可以开启
    LYstatusCodePlayerErrorSavePathSuffix        = -4012,//地址后缀是.mp4
    //视频通话本地录像错误码
    LYstatusCodePlayerErrorNOFacetime            = -4013,//没有进行视频通话
    
    //视频采集错误码
    LYstatusCodeVideoCaptureErrorNoDevice        = -5000,//获取摄像头设备列表失败(系统默认采集摄像头也获取不到)
    LYstatusCodeVideoCaptureErrorInput           = -5001,//对应采集设备获取输入流失败(deviceInputWithDevice)
    LYstatusCodeVideoCaptureCameraStarting       = -5002,//摄像头正在开启中，
    LYstatusCodeVideoCaptureStartFaild           = -5003,//摄像头开启失败
    LYstatusCodeVideoCaptureCameraIsFront        = -5004,//打开闪光灯失败，前置摄像头无法开启闪关灯，
    LYstatusCodeVideoCaptureErrorCameraTorch     = -5005,//当前设备不支持闪光灯或者闪光灯打开失败。
    
    //直播错误码
    LYstatusCodeLiveBroadcastErrorGetRelayInfo    = -6000,//获取relay info error
    LYstatusCodeLiveBroadcastErrorOpenProtocol    = -6001,//打开协议失败
    LYstatusCodeLiveBroadcastErrorInitEncoder     = -6002,//初始化编码器失败
    
    LYstatusCodeLiveBroadcastErrorSwitchCamera    = -6020,//切换摄像头失败(1.摄像头获取失败；2.切换的和当前工作的是同一设备)
};



#pragma mark - 平台服务

/**
 *  启动云服务的状态回调
 *
 *  @param statusCode  启动的状态
 *  @param errorString 失败时候的错误信息
 */
typedef void(^startCloudServiceBlock)(LYstatusCode statusCode, NSString *errorString);

/**
 *  平台透传消息回调
 *
 *  @param dictionary 消息字典
 *
 *  dictionary：key-value具体说明见Macro defines文件(LYMacroDefines.h)
 */
typedef void(^cloudServicePopMessageBlock)(NSDictionary *dictionary);

#pragma mark - 播放器

/**
 *  播放器状态回调，字典形式回调返回信息
 *
 *  @param playerMessageDic 播放状态信息
 */
typedef void(^playerCallBackBlock)(NSDictionary *playerMessageDic);

/**
 *播放器解码类型，
 */
typedef NS_ENUM(NSInteger, LYPlayerDecodeMode) {
    LYPlayerDecodeModeHard = 1, //硬解
    LYPlayerDecodeModeSoft = 2  //软解
};

/*
 * 流媒体参数获取枚举
 */
typedef NS_ENUM(NSInteger, LYStreamMediaParam) {
    LYStreamMediaParamVideoDownloadSpeed        = 1,//当前视频下载速度
    LYStreamMediaParamAudioDownloadSpeed        = 2,//当前音频下载速度
    LYStreamMediaParamVideoRate                 = 3,//当前视频帧率
    LYStreamMediaParamAudioRate                 = 4,//当前音频帧率
    LYStreamMediaParamVideoAverageDownloadSpeed = 5,//平均视频下载速度
    LYStreamMediaParamAudioAverageDownloadSpeed = 6,//平均音频下载速度
    LYStreamMediaParamRTMPAddress               = 7,//RTMP地址
    LYStreamMediaParamDeviceUploadFrame         = 8,//上行帧率
    LYStreamMediaParamDeviceUploadSpeed         = 9,//上行速度
    LYStreamMediaParamBufferTime                = 10,//缓冲时长（毫秒）
    LYStreamMediaParamBufferFrame               = 11,//缓冲区帧数
    LYStreamMediaParamFrameDelay                = 12,//当前帧延时（毫秒）
    LYStreamMediaParamBufferDelay               = 13,//缓冲区延时（毫秒）
    LYStreamMediaParamRatioWidth                = 14,//分辨率宽
    LYStreamMediaParamRatioHeight               = 15,//分辨率高
    LYStreamMediaParamRTMPSendPercent           = 16,//发送时间比：rtmp上传网络状态 （255 未知   0-10 极好   10-30 好  30-60 一般 60-100 差  100以上 极差）
    LYStreamMediaParamOnlineNumber              = 17 //在线人数
};


#pragma mark - 采集&推流

/**
 *  摄像头类型(前后置)
 */
typedef NS_ENUM(NSInteger, LYCaptureCameraMode) {
    LYCaptureCameraModeFront = 1,  //前置摄像头
    LYCaptureCameraModeBack  = 2,  //后置摄像头
};

/**
 *  编码方式
 */
typedef NS_ENUM(NSInteger, LYCaptureDataEncodeMode) {
    LYCaptureDataEncodeModeSoft = 1,    //软编码
    LYCaptureDataEncodeModeHard = 2,    //硬编码
};

#pragma mark - 目前仅支持这三个等级
/**
 *  视频流质量
 */
typedef NS_ENUM(NSInteger, LYVideoStreamingQualityLevel) {
    LYVideoStreamingQualityModeLevelLow         = 1,  //普通
    LYVideoStreamingQualityModeLevelMedium      = 2,  //标清
    LYVideoStreamingQualityModeLevelHigh        = 3,  //高清
};



/*！后期扩展多码率支持使用
 *  视频流质量
 */
typedef NS_ENUM(NSInteger, LYVideoStreamingQualityMode) {
    LYVideoStreamingQualityModeLow1     = 1,  //低1：fps:12 video bitrate:150kbps
    LYVideoStreamingQualityModeLow2     = 2,  //低2：fps:15 video bitrate:256kbps
    LYVideoStreamingQualityModeLow3     = 3,  //低3：fps:15 video bitrate:350kbps
    LYVideoStreamingQualityModeMedium1  = 4,  //中1：fps:30 video bitrate:512kbps
    LYVideoStreamingQualityModeMedium2  = 5,  //中2：fps:30 video bitrate:800kbps
    LYVideoStreamingQualityModeMedium3  = 6,  //中3：fps:30 video bitrate:1000kbps
    LYVideoStreamingQualityModeHigh1    = 7,  //高1：fps:30 video bitrate:1200kbps
    LYVideoStreamingQualityModeHigh2    = 8,  //高2：fps:30 video bitrate:1500kbps
    LYVideoStreamingQualityModeHigh3    = 9,  //高3：fps:30 video bitrate:2000kbps
};

/**
 *  音频流质量
 */
typedef NS_ENUM(NSInteger, LYAudioStreamingQualityMode) {
    LYAudioStreamingQualityModeHigh1     = 1,  //高1：sample rate:44MHz audio bitrate:96kbps
    LYAudioStreamingQualityModeHigh2     = 2,  //高2：sample rate:44MHz audio bitrate:128kbps
};

/**
 *  音频码率
 */
typedef NS_ENUM(NSInteger, LYAudioStreamingBitRate) {
    
    LYAudioStreamingBitRate_64Kbps     = 64000,  //64Kbps 音频码率
    LYAudioStreamingBitRate_96Kbps     = 96000,  //96Kbps 音频码率
    LYAudioStreamingBitRate_128Kbps    = 128000, //128Kbps 音频码率
    
    LYAudioStreamingBitRate_Default    = LYAudioStreamingBitRate_64Kbps
};

#pragma mark - 直播
/**
 *  直播类型
 */
typedef NS_ENUM(NSInteger, LYLiveBroadcastMode) {
    LYLiveBroadcastModeLiving = 2,  //不带录像的直播
    LYLiveBroadcastModeRecord = 4   //带录像的直播
};

#endif /* LYTypeDefines_h */
