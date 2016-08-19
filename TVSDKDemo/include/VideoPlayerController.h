//
//  VideoPlayerController.h
//
//  Created by YangXP on 15-11-25.
//  Copyright (c) 2015年 StarsChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>

//播放器状态
typedef enum {
    E_PLAY_STATUS_NONE=0,
    E_PLAY_STATUS_CONTENT_LOADING,
    E_PLAY_STATUS_CONTENT_LOADED,
    E_PLAY_STATUS_OPENING,
    E_PLAY_STATUS_OPENED,
    E_PLAY_STATUS_OPEN_FAILED,
    E_PLAY_STATUS_PLAYING,
    E_PLAY_STATUS_PAUSED,
    E_PLAY_STATUS_END,
    E_PLAY_STATUS_CONTENT_UNLOADING,
    E_PLAY_STATUS_CONTENT_UNLOADED
}ePlayStatus;

//播放器类型
typedef enum {
    E_PLAYER_TYPE_NONE=0,
    E_PLAYER_TYPE_AD_VIDEO,
    E_PLAYER_TYPE_AD_IMAGE,
    E_PLAYER_TYPE_VOD,
    E_PLAYER_TYPE_LIVE,
    E_PLAYER_TYPE_BROADCAST
}ePlayerType;

//当播放器状态发生变化时,发送此通知
extern NSString *const PlayerStatusChangedNotification;

//播放进度发生变化时,发送此通知
extern NSString *const PlayerProgressNotification;

//播放器缓存状态发生改变时,发送
//param--status
extern NSString *const PlayerCachingNotification;

////////////////////////////////////////////////////////////////

@interface VideoPlayerController : UIViewController


//播放地址
@property(atomic, readonly, copy) NSString *url;

//播放器类型
@property(atomic, readonly) ePlayerType eCurType;

//当前状态
@property(atomic, readonly) ePlayStatus eCurStatus;

//***********************
//isCaching:
//无帧可播->YES
//YES && 缓存数据>=minBufferedDuation->NO

//minBufferedDuation:
//缓存开始后,数据超过该值后恢复播放.避免频繁卡顿

//maxBufferedDuation:
//解码缓存的上限,超过后则暂停解码
//该值设小可减少内存开销,但网络抖动时会出现卡顿

//minBufferedDuation与maxBufferedDuation有默认设置,一般不需要上层关心
//当收到MemoryWarning时,会改变二者的值

@property(atomic, readonly) BOOL isCaching;

@property(atomic, readwrite) CGFloat minBufferedDuation;

@property(atomic, readwrite) CGFloat maxBufferedDuation;
//***********************

//系统的音量大小
@property(atomic, readwrite) CGFloat fVolume;

//当前播放位置
@property(atomic, readwrite) CGFloat fCurrentPosition;

//总时长
@property(atomic, readonly) CGFloat fTotalDuration;

//静音
@property(atomic, readwrite) BOOL isMute;

//
@property(atomic, readwrite) UIViewContentMode contentMode;

//是否正在播放
-(BOOL)isPlaying;

//是否已经暂停
-(BOOL)isPaused;

//是否是直播
-(BOOL)isAlive;

//加载内容
-(void)loadContent:(NSString *)url andContentType:(ePlayerType)ePlayerType;

//卸载内容
-(void)unloadContent;

//重新加载
-(void)reload;

//播放
-(BOOL)play;

//暂停
-(BOOL)pause;

@end
