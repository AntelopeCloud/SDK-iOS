//
//  LYVideoStreamingConfiguration.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/21.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"


/**
 *  LYVideoStreamingConfiguration 是直播和互联采集和推流前的摄像头配置参数以及视频编码时的具体参数
 *  
 *  当你不明白每个具体参数代表什么意思或者你不确定怎么设置参数的时候，你可以使用defaultConfiguration 或者指定分辨率和推流质量来生成一个cofig.
 *  设定参数之时一定要知其所以然，并且知道设置该参数可能导致的结果，不合理的设置可能导致编码器设置失败。
 *
 */


//当你想要获取到当前采集数据进行特效等处理的时候请记得设置该代理并实现之。(遵循LYVideoStreamingSampleDataDelegate协议)
//遵循该协议的时候请设置视频编码的数据是经过你处理之后的还是之前的数据。
@protocol LYVideoStreamingSampleDataDelegate;


@interface LYVideoStreamingConfiguration : NSObject

/**
 *   摄像头采集数据的代理
 *   设置之后获取到当前的采集数据进行处理(特效、美颜等)
 *   设置该代理的时候请一定要设置编码并推流的数据(是处理前的还是处理后的)
 *   设置该代理的时候请阅读代理处的说明。
 *  !:注意:设置代理拿到视频采集数据进行处理的时候务必清楚您所要进行的操作的耗时问题，SDK内部会同步等待你执行完代理方法才进行下一帧数据的处理.
 */
@property (nonatomic, weak) id<LYVideoStreamingSampleDataDelegate> sampleVideoDataDelegate;

/**
 *   如果设置了摄像头采集数据代理并且编码、推流的数据使用处理过后的数据才需要设置，
 *   默认是编码发送摄像头采集之后的数据。
 */
@property (nonatomic, assign) LYVideoDataEncodeType  videoDataEncodeType;

/**
 *   视频的分辨率，宽高务必设定为 2 的倍数，否则解码播放时可能出现绿边:default 640*480
 */
@property (nonatomic, assign) CGSize  videoSize;


/**
 *   视频的帧率，即 fps:default 30fps 视频通话的时候是15fps
 */
@property (nonatomic, assign) NSUInteger videoFrameRate;

/**
 *  视频的码率，单位是 bps :default 512
 */
@property (nonatomic, assign) NSUInteger videoBitRate;

/**
 *  编码方式：软编/硬编(iOS 8.0+才支持硬遍)：default iOS 8.0+ hard / iOS 8.0- soft
 */
@property (nonatomic, assign) LYCaptureDataEncodeMode encodeMode;

/**
 *  摄像头类型：前/后置 default front
 */
@property (nonatomic, assign) LYCaptureCameraMode cameraMode;

/**
 *  生成配置时错误信息描述：如果该属性为nil或者为@“”表示参数正确
 */
@property (weak, nonatomic) NSString *error;

/**
 *  生成默认的配置
 *  ！！！该方法不是单例方法，每次调用都会生成一个新的配置，默认情况下对应的参数分辨率为（640，480）,推流质量为标清配置.
 *
 *  @return self（config）
 */
+ (instancetype) defaultConfiguration;

/**
 *  根据自定义分辨率和推流质量生成一个配置
 *
 *  @param videoSize 分辨率
 *  @param quality   推流质量
 *
 *  @return LYVideoStreamingConfiguration 实例
 *
 *  ！！！该方法不是单例方法，每次调用都会根据自定义的分辨率和推流质量生成一个新的配置，
 */
+ (instancetype) configurationWithVideoSize: (CGSize)videoSize videoQuality: (LYVideoStreamingQualityMode)quality;

/**
 *  根据全部自定义参数初始化获取一个新的配置
 *
 *  @param videoSize    分辨率
 *  @param frameRate    帧率
 *  @param videoBitrate 码率
 *  @param encodeMode   编码方式
 *  @param cameraMode   摄像头类型
 *
 *  @return LYVideoStreamingConfiguration 实例
 *
 *  ！！！务必清楚每一个参数的含义，清楚各个参数的意义和影响才调用该方法进行初始化生成新的配置，内部会判断参数的有效性
 *  如果参数无效会
 */
- (instancetype) initWithVideoSize: (CGSize)videoSize
                    videoFrameRate: (NSUInteger)frameRate
                      videoBitrate: (NSUInteger)videoBitrate
                        encodeMode: (LYCaptureDataEncodeMode)encodeMode
                        cameraMode: (LYCaptureCameraMode)cameraMode;

/**
 *  验证参数的有效性:当更改参数的时候，调用该方法验证参数是否正确，有错则返回错误信息
 *
 *  @return 错误信息：正确则返回nil
 */
- (NSString *)validate;

@end


@protocol LYVideoStreamingSampleDataDelegate <NSObject>


@required
/**
 *  摄像头采集进行预览的数据，如果不处理采集数据请勿执行该代理，以避免浪费不必要的性能
 *
 *  @param object       调用代理方法的类对象
 *  @param sampleBuffer 摄像头采集得到的数据（NV12格式的数据）
 *                      采集得到的yuv数据格式是NV12，并且是按照64字节对齐的方式缓存。请一定要在处理数据的时候熟知数据格式转换。否则处理后的数据不能正常预览。
 */
- (void)lyVideoStreaming: (id)object yuvDataWillDisplayForPreview: (CVPixelBufferRef)sampleBuffer;

@end

