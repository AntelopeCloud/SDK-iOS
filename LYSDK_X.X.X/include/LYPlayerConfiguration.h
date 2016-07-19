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

@interface LYPlayerConfiguration : NSObject

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

/*！
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
