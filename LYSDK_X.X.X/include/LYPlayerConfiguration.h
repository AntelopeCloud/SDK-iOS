//
//  LYPlayerConfiguration.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/5/14.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

/**
 *  播放器配置类
 */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"


//当你想要获取到当前播放数据进行特效等处理的时候请记得设置该代理并实现之。(遵循LYPlayerVideoDataDelegate协议)
@protocol LYPlayerVideoDataDelegate;

@interface LYPlayerConfiguration : NSObject


/**
 *   播放器解码之后的视频数据代理
 *   设置之后获取到当前的解码数据进行处理(特效、美颜等)
 *   设置该代理的时候请阅读代理处的说明。
 */
@property (nonatomic, weak) id<LYPlayerVideoDataDelegate> playerVideoDataDelegate;

/**
 *  播放器view
 *  ！可以在播放开始之后切换view
 */
@property (weak, nonatomic) UIView *playView;

/**
 *  播放器frame
 *  ！可以在播放开始之后改变view.frame
 */
@property (nonatomic, assign) CGRect  playViewFrame;

/**
 *  解码方式：软/硬解(iOS 8.0+才支持硬遍)：default iOS 8.0+ ↑hard / iOS 8.0- ↓soft
 *  你也可以自由选择设置。但是视频通话的时候强力建议硬解
 *
 *  ！！！播放开始之后(暂时不支持)不可以切换解码方式。！！！
 */
@property (nonatomic, assign) LYPlayerDecodeMode decodeMode;

/**
 *  其他参数根据需求增加
 */


/**
 *  初始化播放参数类
 *
 *  @param playView   播放view
 *  @param playFrame  播放view.frame
 *  @param decodeMode 解码方式
 *
 *  @return LYPlayerConfiguration
 *  ！也可以直接[[LYPlayerConfiguration alloc] init];然后再单个设置成员变量的的值
 */
- (instancetype) initWithPlayView: (UIView *)playView
                            frame: (CGRect)playFrame
                       decodeMode: (LYPlayerDecodeMode) decodeMode;

@end


/**
 *  视频通话过程中播放器解码之后的数据代理，以方便上层开发的同学可以随时修改渲染的数据。
 *  如果需要使用该功能，请一定要熟知数据的处理
 */
@protocol LYPlayerVideoDataDelegate <NSObject>

@required

/**
 *  目前只提供视频通话类的播放视频数据代理出来，请熟知。
 *  接收到的视频数据。用来播放对方画面的数据。如果不进行处理请勿实现该代理，以免浪费应用性能
 *
 *  @param object       调用代理方法的类对象
 *  @param recvBuffer   接收到的数据:!!!请一定不要修改这个数据，否则导致接收数据缓存内存的数据乱序，请熟知!!!
 *                      解码之后的yuv数据格式是NV12，并且是按照64字节对齐的方式进行缓存的。请在数据处理和拷贝的时候一定要清楚数据格式之间的转换；
 *
 *  @param renderBuffer 经过处理后的数据，(开发的同学拿到recvBuffer的基地址拷贝出去经过处理再拷贝到对应的renderBuffer内存上)
 *                      修改后要渲染的数据格式是NV12，并且是按照1字节对齐的方式进行处理的。请在处理之后拷贝回到内存地址的数据格式正确：Y和UV的内存位置要正确。否则渲染不出来
 */
- (void)lyPlayerVideoDataDelegate: (id)object yuvDataWillDisplayForPlayView: (CVPixelBufferRef)recvBuffer renderBuffer: (CVPixelBufferRef)renderBuffer;

@end