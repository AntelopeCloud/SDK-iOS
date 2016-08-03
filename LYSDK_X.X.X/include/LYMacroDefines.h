//
//  LYMacroDefines.h
//  LingyangAPI
//
//  Created by QuinnQiu on 16/4/21.
//  Copyright © 2016年 QuinnQiu. All rights reserved.
//

#ifndef LYMacroDefines_h
#define LYMacroDefines_h


/**
 *  Debug模式下面输出
 */
#define QDEBUG  1

#if QDEBUG == 1
#ifndef QLog
#define QLog(format, args...) \
NSLog(@"[%s %d]: " format "\n", strrchr(__FILE__, '/') + 1, __LINE__, ## args);
//          NSLog(@"%s %s, line %d: " format "\n",  strrchr(__FILE__, '/') + 1, __func__, __LINE__, ## args);
#endif
#else
#ifndef QLog
#define QLog(format, args...) do {} while(0)
#endif
#endif

#pragma mark - 平台

/**
 *平台消息回调block的字典Key
 */
#define kMESSAGENAME_KEY    @"messageName"  //消息名称-->用来区分当前消息是什么回调
#define kMESSAGEBODY_KEY    @"messageBody"  //消息体  -->透传消息的具体数据(互联时候用户自定义数据)//是一个字符串，具体字符串要转什么格式调用者自行转换
#define kMESSAGESRCID_KEY   @"messageSrcID" //srcID

/**
 *messageName字典的Key
 */
#define kMESSAGENAME_ONLINE_KEY                     @"Online"               //登录成功之后的推送消息-->告知平台在线
#define kMESSAGENAME_CONNECTION_ACCEPTTED_KEY       @"ConnectionAcceptted"  //代表互联连接方连接成功之后(被叫方)，等待连接方(主叫方)收到的消息-->表示连接成功
#define kMESSAGENAME_CONNECTION_CLOSED_KEY          @"ConnectionClosed"     //代表①私有直播时中途出现断开；②互联双方出现断开的消息
#define kMESSAGENAME_POP_MESSAGE_KEY                @"PopMessage"           //代表互联被叫方接收的推送消息-->比如接收到主叫的呼叫信息、主叫断开等消息
#pragma mark - 下面的消息类型不用处理，忽略掉！！！！！！！
#define kMESSAGENAME_POP_OFFLINE_MESSAGE_KEY        @"PopOffLineMessage"    //代表设备状态的推送消息
#define kMESSAGENAME_START_POP_DATA_KEY             @"StartPopData"         //开始取流
#define kMESSAGENAME_POP_CONFIG_KEY                 @"PopConfig"            //配置信息(私有设备状态更改，建立连接和断开的时候设备状态变动的消息)
#define kMESSAGENAME_POP_CONFIG_RESULT_KEY          @"PopConfigResult"      //自己添加获取配置栏
#define kMESSAGENAME_DEVICE_BIND_CONFIRM_KEY        @"DeviceBindConfirm"    //

/**
 * messageBody:自定义推送信息-->比如互联时候主叫需要推送给被叫的数据；
 *
 * 如果没有自定义消息：则默认字典返回，key-value如下宏↓
 */
//messageBody没自定义消息的Key;
#define kMESSAGEBODY_DEFAULT_KEY    @"messageBodyNoKey"
#define kMESSAGEBODY_DEFAULT_VALUE  @"messageBodyNoValue"

#pragma mark - 播放器

/**
 *播放器播放过程中状态回调
 */
#define kLY_PLAYER_MESSAGE_TYPE_KEY            @"messageType"   //1开始播放 2连接中断 3数据源错误 4关闭播放器
#define kLY_PLAYER_PARAM_1_KEY                 @"param1"
#define kLY_PLAYER_PARAM_2_KEY                 @"param2"

#pragma mark - other

//当前系统版本
#define kLY_SYSTEM_VERSION  [[[UIDevice currentDevice] systemVersion] floatValue]


#if defined(__IPHONE_8_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_8_0
    #define kLY_CAN_USE_HARD    1
#else
    #define kLY_CAN_USE_HARD    0
#endif

#endif /* LYMacroDefines_h */
