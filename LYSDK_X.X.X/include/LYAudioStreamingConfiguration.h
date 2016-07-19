//
//  LYAudioStreamingConfiguration.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/21.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"

//LYAudioStreamingQualityMode
@interface LYAudioStreamingConfiguration : NSObject

/**
 *  音频流的质量
 */
@property (nonatomic, assign) LYAudioStreamingQualityMode audioQuality;

/**
 *  音频流码率
 */
@property (nonatomic, assign, readonly) LYAudioStreamingBitRate audioBitRate;


@property (nonatomic, assign) NSUInteger audioSampleRate; // 4800 for iPhone 6s family devices, 44100 for others


@property (nonatomic, assign) UInt32 numberOfChannels;   // default as 1


/**
 *  生成一个默认的配置
 *
 *  注意：！！！该方法不是单例方法，每次调用都会生成一个新的配置，
 *
 *  @return LYAudioStreamingConfiguration 实例
 */
// LYAudioStreamingQualityModeHigh2 as default
+ (instancetype)defaultConfiguration;

/**
 * 指定可选码率和采样率生成一个配置
 *  @return LYAudioStreamingConfiguration 实例
 */
+ (instancetype)configurationWithAudioQuality:(LYAudioStreamingQualityMode)quality;

@end
