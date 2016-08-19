//
//  TVEngine.h
//  
//
//  Created by Zy on 15/12/5.
//  Copyright © 2015年 StarsChina. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "VideoPlayerController.h"
@protocol ClearADProtocol <NSObject>
@optional
- (void)clearADAction;
@end
typedef void (^CreatSuccessBlock)(BOOL creatSuccess,NSError* error);
typedef void (^ListBlock)(NSArray *list, NSError *error);
typedef void (^EPGBlock)(NSArray *epgList, NSError *error);
typedef void (^CurrentBlock)(NSArray *curentList, NSError *error);
typedef void (^GetStartUpLogoBlock)(BOOL success,NSDictionary *startUpLogo);
typedef void (^GetStartViewControllerBlock)(BOOL end);

@interface TVEngine : NSObject
/**
 *  注册
 */
+ (void) creatWithSDKAppKey:(NSString*)appKey  success:(CreatSuccessBlock)successBlock;
/**
 *  是否已经注册
 */
+ (BOOL)isRegistered;
/**
 *  销毁
 */
+ (void) destroy;

/**
 *  根据视频ID来播放视频
 *
 *  @param videoID 视频ID
 *  @param by      自定义的播放器
 *  @param type    视频的类型 @"1"直播 @"0"点播
 */
+ (void)loadVideoWithID:(NSString*)videoID By:(VideoPlayerController *)by andType:(NSString *)type baseViewController:(UIViewController*)base;
/**
 *  根据视频url来播放视频
 *
 *  @param url url
 */
+ (void)loadVideoWithUrl:(NSString*)url By:(VideoPlayerController *)by baseViewController:(UIViewController*)base;
/**
 *  结束播放
 */
+ (void)unLoadVideo;
/**
 *  获取频道列表
 *
 *  @param listBlock 频道列表的block
     @"videoId":                    频道id
     @"videoName":                  频道名称
     @"icon":                       频道图标
     @"currentImage":               频道截图
     @"area":                       频道地区
 */
+ (void)getChannellist:(ListBlock)listBlock;


/**
 *  取得相应频道的节目单信息（节目单会随着电视台的调整而与已获取到的节目单信息造成差异）
 *
 *  @param channleid 频道ID
 *  @param epgBlock  节目单
        @"title":                   节目名称
        @"timeInterval":            节目开始时间（时间戳since1970）
        @"endTimeInterval":         节目结束时间（时间戳since1970）
 */
+ (void)getEPGListWith:(NSString*)channleid block:(EPGBlock)epgBlock;


/**
 *  获取传入的频道数组正在播放以及下一个播放的节目的数组
 *
 *  @param channleid 频道id
 *  @param block     返回参数block
 
    @"current":         当前正在播放的节目字典
    @"next":            下一个要播放的节目字典
 
    节目字典属性:
        @"name":                    节目名
        @"timeInterval":            节目开始时间（时间戳since1970）
        @"endTimeInterval":         节目结束时间（时间戳since1970）
 */
+ (void)getCurrentPlayingChannleWith:(NSArray*)channleid block:(CurrentBlock)block;
/**
 *  设置语言
 *
 *  @param languge 语言种类：zh-Hans,zh-Hant,en
 */
+ (void)setLanguge:(NSString*)languge;
/**
 *  获取开机图片
 *
 *  @param block 
 */
+ (void)getStartUpLogo:(GetStartUpLogoBlock)block;
/**
 *  开机图控制器
 *
 *  @param block 结束回调的block
 *
 *  @return 开机图控制器
 */
+ (UIViewController*)getStartViewControllerAndBlock:(GetStartViewControllerBlock)block;
@end
