# AgoraWinRT
AgoraWinRT的实现及UWP上的包装类

## UPWDemo实现部分

- [x] 设置视频分辨率、帧率、码率
- [x] 退出频道的时候，预览不会自动恢复
- [x] 开启｜关闭视频
- [x] 静音｜取消静音
- [x] 加入离开频道
             
## 实现API部分

- [x] 音频自渲染
- [x] 音频自采集
- [x] 视频自渲染
- [x] 视频自采集
- [x] 视频管理
- [x] 音频管理
- [x] 频道管理

- [x] 设备管理
- [x] 原始音频数据
- [x] 原始视频数据
- [x] 媒体附属信息
- [x] 音频录制
- [x] 直播输入在线媒体流
- [x] 多频道管理
- [x] 加密
- [x] 流消息
- [x] 通话前网络测试
- [x] 视频流回退
- [x] 视频双流模式
- [x] 跨频道媒体流转发
- [x] 音量提示
- [x] CDN推流
- [x] 听声辨位
- [x] 变声与混响
- [x] 音乐文件播放及混音
- [x] 音效文件播放管理
- [x] 视频前初级后处理
- [x] 数据统计

## 程序结构说明

### AgoraWinRT

AgoraWinRT部分为Agora C++部分的WinRT封装，其命名与Agora C++ API相同，实现在AgoraWinRT名字空间内部。

#### 不实现的部分
- setVideoProfile: 2.3后废弃
- 屏幕共享: 技术原因
- 人脸检测: Android和iOS
- 音频播放路由: Android和iOS
- 耳返控制: Android和iOS
- 自定义视频模块: 使用视频自采集代替
- 摄像头控制: Android和iOS
- 其他音频控制中的 setAudioSessionOperationRestriction: iOS
- queryInterface: 内部使用

#### 在UWP中实现的部分
- [x] onVideoDeviceStatsChanged
- [x] onFirstLocalVideoFrame

- [x] enableLocalVideo
- [x] setRemoteRenderModel
- [x] setLocalRenderModel
- [x] setupRemoteVideo 
- [x] setupLocalVideo
- [x] startPreview 
- [x] stopPreview 

- [x] GetVideoDeviceManager

### AgoraUWP

AgoraWinRT在UWP中的封装，提供一些UWP下特殊的WinRT不方便原生提供的功能，主要集中在视频采集与视频设备管理

#### 实现的主要功能
- 提供缺省情况下本地视频的采集与渲染
- 远程视频的渲染
- 提供对视频采集设备的管理功能

#### 文件说明
- AgoraUWP.cs 提供对AgoraWinRT的继承与封装，并整合以下几个类提供完整的Agora C++ API在UWP上的模拟实现
- AgoraUWPDelegate.cs 将Agora C++事件转换为delegate
- GeneralMediaCapturer.cs 提供缺省的视频采集功能
- ImageBrushVideoCanvas.cs 提供基于ImageBrush的视频渲染功能
- ImageVideoCanvas.cs 提供基于Image的视屏渲染功能，此类的功能较ImageBrushVideoCanvas差
- MediaList.cs 提供得到Windows下设备的示例
- VideoDeviceManager.cs 为Agora C++中VideoDeviceManager的UWP实现

### AgoraUWPDemo

提供UWP使用示例
