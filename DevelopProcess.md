# AgoraWinRT
The realization of AgoraWinRT and the packaging class on UWP

## UPWDemo implementation part

-[x] Set video resolution, frame rate, bit rate
-[x] When you exit the channel, the preview will not be restored automatically
-[x] On｜Off video
-[x] Mute｜Unmute
-[x] Join and leave the channel

## Implement the API part

-[x] Audio self rendering
-[x] Audio self-collection
-[x] Video self-rendering
-[x] Video self-capture
-[x] Video management
-[x] Audio management
-[x] Channel Management

-[x] Device management
-[x] Raw audio data
-[x] Original video data
-[x] Media ancillary information
-[x] Audio recording
-[x] Live input online media stream
-[x] Multi-channel management
-[x] Encryption
-[x] Streaming message
-[x] Network test before call
-[x] Video stream back
-[x] Video dual stream mode
-[x] Cross-channel media stream forwarding
-[x] Volume reminder
-[x] CDN push
-[x] Identify position by listening
-[x] Voice change and reverb
-[x] Music file playback and mixing
-[x] Sound effect file playback management
-[x] Primary post-processing before video
-[x] Statistics

## Program structure description

### AgoraWinRT

The AgoraWinRT part is the WinRT package of the Agora C++ part. Its name is the same as the Agora C++ API and is implemented in the AgoraWinRT namespace.

#### Part not implemented
-setVideoProfile: Obsolete after 2.3
-Screen sharing: technical reasons
-Face detection: Android and iOS
-Audio playback routing: Android and iOS
-Ear back control: Android and iOS
-Custom video module: use video self-capture instead
-Camera control: Android and iOS
-SetAudioSessionOperationRestriction in other audio control: iOS
-queryInterface: internal use

#### Part implemented in UWP
-[x] onVideoDeviceStatsChanged
-[x] onFirstLocalVideoFrame

-[x] enableLocalVideo
-[x] setRemoteRenderModel
-[x] setLocalRenderModel
-[x] setupRemoteVideo
-[x] setupLocalVideo
-[x] startPreview
-[x] stopPreview

-[x] GetVideoDeviceManager

### AgoraUWP

The encapsulation of AgoraWinRT in UWP provides some special functions that WinRT inconveniently provide natively under UWP, mainly focusing on video capture and video device management

#### Main functions implemented
-Provide local video capture and rendering by default
-Rendering of remote video
-Provide management functions for video capture equipment

#### File description
-AgoraUWP.cs provides inheritance and encapsulation of AgoraWinRT, and integrates the following classes to provide a complete simulation implementation of Agora C++ API on UWP
-AgoraUWPDelegate.cs converts Agora C++ events to delegates
-GeneralMediaCapturer.cs provides default video capture function
-ImageBrushVideoCanvas.cs provides video rendering function based on ImageBrush
-ImageVideoCanvas.cs provides Image-based video rendering function, which is inferior to ImageBrushVideoCanvas
-MediaList.cs provides examples of getting devices under Windows
-VideoDeviceManager.cs is the UWP implementation of VideoDeviceManager in Agora C++

### AgoraUWPDemo

Provide UWP usage examples
