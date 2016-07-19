//
//  LYCloudService.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/20.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LYTypeDefines.h"
#import "LYMacroDefines.h"

@interface LYCloudService : NSObject

/**
 *  单例LYCloudService
 *
 *  @return LYCloudService 实例
 */

+ (LYCloudService *) sharedLYCloudService;

/**
 * 启动云服务。
 * 调用了此api之后,平台相关凭证及资源开始准备，并且在回调接口通知云服务是否启动成功！
 * 建议在客户端登录验证逻辑通过之后即刻调用。服务启动之后，相关的平台接口才能正常使用。
 * 注册修改平台用户信息等功能将以web接口的形式提供，请知悉
 *
 *  @param token         用户token
 *  @param config        用户配置串
 *  @param startStatus   云平台打开是否成功状态block;
 *                       token格式：2147556615_3221225472_1458280395_5e78e66c2104fa6466449a0367d7145e
 *
 *  @param popMessage    接收平台推送消息block(返回字典包装后的数据:具体看block定义)
 */
- (void) startCloudService: (NSString *)token
                    config: (NSString *)config
                startBlock: (startCloudServiceBlock)startBlock
           popMessageBlock: (cloudServicePopMessageBlock)popMessageBlock;

/**
 * 获取当前SDK版本
 *
 * @return
 */
- (NSString *) getSDKVersion;

/**
 *  当前用户是否平台在线
 *
 *  @return YES:在线  or NO:离线
 */
- (BOOL) isOnline;

/**
 *  停止云服务
 *
 *  退出的时候一定要调用该方法断开与平台直接的连接
 */
- (void) stopCloudService;

@end
