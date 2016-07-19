//
//  LYPlayer.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/21.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"
#import "LYPlayerConfiguration.h"

@interface LYPlayer : NSObject


/**
*  设置播放器配置
*
*  @param playerConfiguration 播放器配置信息类对象
*/
- (void) setViewWithConfiguration: (LYPlayerConfiguration *)playerConfiguration;

/**
 *  更改播放器frame---->开始播放之后动态修改播放器的frame调用
 *
 *  @param frame frame
 */
- (void)setViewFrame: (CGRect)frame;

//调用之后要调用stop释放相应的资源
/**
 *  打开播放器：播放地址(由第三方后台返回)
 *
 *  @param dataSourceAddreess  播放源：播放地址
 *  @param openBlock          与播放源建立连接的回调：errorString表示建立过程中错误串信息，statusCode:建立连接成功与否标识
 *  @param playerBlock        播放状态回调
 */
- (void)open: (NSString *)dataSourceAddreess
  openStatus: (void (^)(LYstatusCode statusCode, NSString *errorString))openBlock
playerStatus: (playerCallBackBlock)playerBlock;

/**
 *  暂停播放//暂未实现
 */
- (void)pause;

/**
 *  恢复播放//暂未实现
 */
- (void)resume;

/**
 *  关闭播放器:会关闭播放器以及断开播放连接-----注意openPlayerWithPlayerAddress成功之后一定要调用closePlayer释放底层资源，否则内存泄露
 */
- (void)close;


/**
 *  打开声音
 */
- (NSInteger)unmute;

/**
 *  关闭声音
 */
- (void)mute;

/**
 *  开启对讲
 *
 *  @param sampleRate 采样率：默认11025
 *  @param channel    通道号：默认1
 */
- (void)startTalkWithSampleRate: (NSInteger)sampleRate channel: (NSInteger)channel;

/**
 *  停止对讲
 */
- (void)stopTalk;

/**
 *  获取播放(流媒体参数)信息数据
 *
 *  @param stremMediaParam 想要获取信息的对应序号
 *
 *  @return 当前信息数据
 */
- (NSString *)getMediaParam:(LYStreamMediaParam)streamMediaParam;

/**
 *  创建视频截图
 *
 *  @param path          路径：包括文件名-->后缀jpg格式
 *  @param snapshotBlcok 截图成功与否回调 SNAPSHOT_TYPE(enum)
 */
- (void)snapshot: (NSString *)path
          status:(void (^)(LYstatusCode statusCode, NSString *errorString))snapshotBlock;

/**
 *  开始录像
 *
 *  @param path 路径：包括文件名-->后缀mp4格式
 */
- (void)startLocalRecord: (NSString *)path
                  status: (void (^)(LYstatusCode statusCode, NSString *errorString))startRecordBlock;

/**
 *  结束录像
 *
 */

- (void)stopLocalRecord;


#pragma mark 历史相关使用
/**
 *  点播播放定位
 *
 *  @param seekTimestamp 定位时间点(相对时间)-->时间戳
 *  @param seekBlock     block
 */
- (void)seek: (NSInteger)timestamp
      status: (void (^)(LYstatusCode statusCode))seekBlock;

/**
 *  获取点播播放位置
 *
 *  @return 当前播放时间戳
 */
- (NSInteger)getCurrentPlayTime;


@end
