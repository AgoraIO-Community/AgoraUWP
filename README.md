# AgoraWinRT Development Manual

*English* ｜ [**中文**](README.zh.md)

**

**NOTE: This community SDK supports Hololens 1 only. There is no support for Hololens 2 yet but Agora is working on that right now.**

**  

In UWP, Agora C++ Native Development kit cannot get the camera and microphone permission because they should be explicitly applying, and there is no handle property in UWP on Windows, Agora C++ Native also cannot render video data by default function like setupLocalVideo and setupRemoteVideo. On the other hand, UWP development is more friendly to C# users.

Based on those reasons, this project encapsulates native c++ kit to WinRT kit, and based on the WinRT kit, it encapsulates the UWP kit to manage video and audio devices. If you are a C++ user, you can also directly use the WinRT kit for development.

## Architecture Description

The whole architecture is divided into two main parts: AgoraWinRT and AgoraUWP.

AgoraWinRT is encapsulated from Agora C++ Native.

AgoraUWP is based on AgoraWinRT, and add device management and video render on UWP.

### AgoraWinRT Description

The AgoraWinRT SDK is encapsulated with the Agora C++ API, it uses the same function names and type names as Agora C++ SDK except for the namespace. Users can directly refer to [Agora C++ API Reference for All Platforms](https://docs.agora.io/en/Audio%20Broadcast/API%20Reference/cpp/index.html) to find the corresponding type and function description.

#### AgoraWinRT Unencapsulated Parts

In AgoraWinRT, some Agora C++ API is not encapsulated, the following list is those function's name and reason.

| Name                                | Reason                                                       |
| ----------------------------------- | ------------------------------------------------------------ |
| Screen Capture                      | not implemented temporarily                                  |
| Face Detection                      | Android and iOS                                              |
| Audio Routing Control               | Android and iOS                                              |
| In-ear Monitoring                   | Android and iOS                                              |
| Camera Control                      | Android and iOS                                              |
| setAudioSessionOperationRestriction | iOS                                                          |
| queryInterface                      | useless in WinRT                                             |
| IVideoDeviceManager                 | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| initialize                          | integrate into constructor                                   |
| release                             | integrate into dispose                                       |
| setupLocalVideo                     | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| setupRemoteVideo                    | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| setLocalRenderMode                  | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| setRemoteRenderMode                 | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| startPreview                        | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| stopPreview                         | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| enableLocalVideo                    | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |
| onVideoDeviceStateChanged           | implemented in specific platform such as UWP platform. For more details, please refer to [AgoraUWP Description](#AgoraUWP description) |

#### AgoraWinRT Project Files Description

AgoraWinRT project is a Windows Runtime Component (C++ WinRT) project, and the interfaces are defined in several idl files.

| File Name                        | Description                                                  |
| -------------------------------- | ------------------------------------------------------------ |
| AgoraWinRT.idl                   | the main interface file, which is a WinRT redefinition of AgoraRtc in Agora C++ |
| AgoraWinRTInterfaces.idl         | the event interfaces definition file, includes  AgoraRtcEventHandler、MetadataObserver、AudioFrameObserver、VideoFrameObserver, PacketObserver. Users can implement interface and call registration method to subscribe events. |
| AgoraWinRTAudioDeviceManager.idl | include redefinition of Agora C++ IAudioDeviceManager |
| AgoraWinRTChannel.idl            | include redefinition of Agora C++ IChannel and IChannelEventHandler |
| AgoraWinRTTypes.idl              | include types redefiniton of Agora C++ SDK           |
| AgoraWinRTEnums.idl              | include enums redefinition of Agora C++ SDK         |

#### AgoraWinRT::AgoraRtc Event Registration Method Description

AgoraWinRT::AgoraRtc is the core class of AgoraWinRT, which encapsulate AgoraRtc in Agora C++, and provides event registration methods that users can use those methods to subscribe to events.

| Event Registration Method     | Event Interface                                              |
| ----------------------------- | ------------------------------------------------------------ |
| RegisterRtcEngineEventHandler | AgoraRtcEventHandler                                         |
| RegisterMediaMetadataObserver | MetadataObserver                                             |
| RegisterPacketObserver        | PacketObserver，based on the internal implementation of Agora, only registration will not make this interface work. User need to call enableEncryption and set enable as true, then PacketObserver's event can take effect. |
| RegisterAudioFrameObserver    | AudioFrameObserver                                           |
| RegisterVideoFrameObserver    | VideoFrameObserver                                           |

#### Special Feature of AgoraWinRT::AgoraRtc

AgoraWinRT::AgoraRtc removes initialize and release functions. Instead of that, it automatically initializes the RTC engine when AgoraWinRT::AgoraRtc class is created in the constructor and automatically call the engine's release function when AgoraWinRT::AgoraRtc instance be destructed.

At the same time, AgoraWinRT::AgoraRtc implements the IDispose interface, so users can use Using or directly call the dispose method to release resources.

**NOTE: user can not use AgoraWinRT::AgoraRtc instance again after calling Dispose method, instead of that, the user must recreate a new instance of AgoraWinRT::AgoraRtc.**

#### AgoraWinRT::AgoraRtc Functions and Event Interfaces Document

[As mentioned above](#AgoarWinRT description), the name of all functions, types, enums, and interfaces definitions in AgoraWinRT::AgoraRtc is consistent with those in Agora C++ Naive SDK. Developers can use [the official documents](https://docs.agora.io/en/Audio%20Broadcast/API%20Reference/cpp/index.html) to find specific information of functions, types, enums, and interfaces.

### AgoraUWP Description

AgoraUWP is based on AgoraWinRT , implemented by C#. It provides VideoDeviceManager, permission request, video capture, and rendering in the UWP platform. At the same time,  there are three interfaces, AgoraRtcEventHandler, VideoFrameObserver, AudioFrameObserver, implemented by default, and the functions among them are converted to C# style events from the callback function.

AgoraUWP uses the same function names and type names with Agora C++ like AgoraWinRT, except for the namespace.

#### AgoraUWP Project Files Description

AgoraUWP is a DLL(Universal Windows) project

| File Name                  | Description                                                  |
| -------------------------- | ------------------------------------------------------------ |
| AgoraUWP.cs                | The main file of AgoraUWP, which includes AgoraUWP.AgoraRtc class. This class implements three AgoraWinRT interfaces: AgoraWinRT::AgoraRtcEventHandler、AgoraWinRT::VideoFrameObserver、AgoraWinRT::AudioFrameObserver in privately, and transfer those intefaces to events. It also provide video capture and rendering capabilities on UWP platform, so the user can simply use this SDK to implements video and audio communication app like using Agora C++ SDK. |
| AgoraUWPDelegate.cs        | include redefinition of AgoraWinRT::AgoraRtcEventHandler、AgoraWinRT::VideoFrameObserver、AgoraWinRT::AudioFrameObserver |
| IVideoDeviceCollection.cs  | include redefinition of AgoraWinRT::IVideoDeviceCollection |
| VideoDeviceManager.cs      | include redefinition of AgoraWinRT::IVideoDevicemanger，and include a implementation of AgoraWinRT::IVideoDeviceCollection and AgoraWinRT::IVideoDeviceManager on UWP platform |
| VideoCanvas.cs             | because there is no window handle on UWP platform, therefore, the VideoCanvas abstract class is defined to unify the implementation interface of video rendering on UWP platform, for specific instruction, refer to [VideoCanas](#VideoCanvas) |
| ImageBrushVideoCanvas.cs   | a VideoCanvas implementation based on ImageBrush.            |
| IMediaCapturer.cs          | the media capture interface used by AgoraUWP.AgoraRtc        |
| GeneralMediaCapturer.cs    | a default implementation of AgoraWinRT::IMediaCapturer interface, it is also the default media capture used by AgoraUWP.AgoraRtc |
| MediaCaptureVideoSource.cs | a implementation of Agora C++ VideoSource based on GeneralMediaCapturer |

#### AgoraUWP.AgoraRtc

This class is the core class in AgoraUWP. It inherits from AgoraWinRT::AgoraRtc and implements AgoraWinRT::AgoraRtcEventHandler, AgoraWinRT::VideoFrameObserver, AgoraWinRT::AudioFrameObserver interfaces, and converts them into events.

This class provides video capture, video rendering and device management functions on UWP platform that were not implmented on AgoraWinRT, and implemented setupLocalVideo, setupRemoteVideo, setLocalRenderMode, setRemoteRenderMode, startPreview, stopPreview, enableLocalVideo functions.

These are serval differences between AgoraUWP.AgoraRtc and Agora C++ SDK:

1. Users need to apply for permission to use the camera and microphone on the UWP platform. After testing, in the progress of applying for permission, pop-up confirmation windows cannot show in synchronous function. Therefore, AgoraUWP adds RequestCameraAccess asynchronous static function, the user must call this function to apply for permission before create and using AgoraUWP.AgoraRtc instance.
2. the parameters of SetupLocalVideo and SetupRemoteVideo functions are modified to accept parameters of AgoraUWP.VideCanvas, because there is no window handle on the UWP platform.  Users can use AgoraUWP.ImageBrushVideoCanvas to implement video rendering on ImageBrush, and the user can inherit VideoCanvas to implement video rendering on their own.

#### AgoraUWP.IMediaCapturer and AgoraUWP.GeneralMediaCapturer

IMediaCapturer defines an audio and video frame capturer on UWP, and GeneralMediaCapturer is the default implementation.

GeneralMediaCapturer is not only used by AgoraUWP.AgoraRtc as an internal video frame capture, but also can be used independently as an audio and video frame capture for audio and video self-capturing.

The definition of IMediaCapturer is as follows:

1. VideoDevice

   Get the video device used by the current capture, which can be null

2. AudioDevice

   Get the audio device used by the current capture, which can be null

3. AudioFormat

   The currently used audio format data, such as sampling rate, number of channels, etc., can be found in MSDN about [MediaFrameFormat](https://docs.microsoft.com/en-us/uwp/api/Windows.Media.Capture. Frames.MediaFrameFormat?redirectedfrom=MSDN&view=winrt-19041) part

4. VideoFormat

   Video format data currently in use

5. VideoBufferType

   The format of the currently given video data buffer, the default is VIDEO_BUFFER_RAW_DATA

6. OnVideoFrameArrived

   Trigger when video frame data is collected

7. EnableVideo

   Whether to enable video frame capture, the default is true, if set to false, OnVideoFrameArrived will not be triggered

8. OnAudioFrameArrived

   Trigger when the audio frame data is collected

9. EnableAudio

   Whether to enable the capture of audio frames, the default is true, if set to false, OnAudioFrameArrived will not be triggered

#### VideoCanvas and ImageBrushVideoCanvas

VideoCanvas defines the methods and properties that can be accepted by SetupLocalVideo and SetupRemoteVideo functions in AgoraUWP.AgoraRtc.

ImageBrushVideoCanvas is a VideoCanvas implementation class based on ImageBrush.

The definition of VideoCanvas is as follows:

1. Target

   Objects that need to be rendered on, such as ImageBrush objects in ImageBrushVideoCanvas

2. RenderMode

   How to fill the video in the video rendering window

3. Channel

   The channel of the source video

4. User

   User id corresponding to the video

5. MirrorMode

   Video mirror display

6. Render(MediaFrameReference)

   The rendering method used in the local video preview

7. Render(VideoFrame)

   Methods to call when AgoraUWP.AgoraRtc performs local and remote video rendering

The VideoCanvas class is an abstract class, in which two Render functions are implemented as virtual methods, which is convenient for users to selectively implement the two methods according to their needs. For example, VideoCanvas in the StartDeviceTest of VideoDeviceManager can only implement Render(MediaFrameReference), because of this function VideoCanvas is only used in local video testing.

#### MediaCaptureVideoSource

Agora C++ provides a setVideoSource method, which allows users to provide their own VideoSource, but in Agora's example, the custom video capture is performed in two methods: setExternalVideoSource and pushVideoFrame.

So this class only provides an example of a custom VideoSource based on GeneralMeidaCapturer. Users can refer to it to implement their own VideoSource.

## About AgoraUWPDemo

AgoraUWPDemo is an example of using AgoraUWP.

Three modes are demonstrated in the example:

1. Use SDK internal-collection mode

    Use the internal audio and video collection inside the AgoraUWP SDK, users don't need to care about the collection part.

2. Use audio self-collection

    It demonstrates how to use GeneralMediaCapturer for audio self-collection. As an example, users can refer to and implement their own audio self-collection method.

3. Use audio self-rendering

    Demonstrates how to use [AudioGraph](https://docs.microsoft.com/en-us/uwp/api/windows.media.audio.audiograph?view=winrt-19041) combined with [PullAudioFrame](https://docs .agora.io/en/Video/API%20Reference/cpp/classagora_1_1media_1_1_i_media_engine.html#aaf43fc265eb4707bb59f1bf0cbe01940) to render external audio.

At the same time, the example also demonstrates how to adjust the video resolution, frame rate, bit rate, etc.

### Use SDK Internal-collection Mode

This process corresponds to the section [How to quickly start](https://docs.agora.io/en/Video/start_call_windows?platform=Windows)

```mermaid
sequenceDiagram
participant UWP as UWP App
participant SDK as Agora UWP SDK
participant Agora as SD-RTN
Note left of UWP: Apply for camera and microphone permissions
UWP->>SDK: AgoraUWP.AgoraRtc.RequestCameraAccess
Note left of UWP: Initialization
UWP->>SDK: new AgoraUWP.AgoraRtc
Note left of UWP: Set local view
UWP->>SDK: SetupLocalVideo(new ImageBrushVideoCanvas)
UWP->>SDK: EnableVideo
UWP->>SDK: StartPreview optional
Note left Of UWP: Join the channel
UWP->>SDK: JoinChannel
SDK->>Agora: Request to join the channel
SDK-->>UWP: OnJoinChannelSuccess
Note left of UWP: Set remote view
Note right of Agora: Remote user join
Agora-->>UWP: OnFirstRemoteVideoDecoded or OnUserJoined
UWP->>SDK: SetupRemoteVideo(new ImageBrushVideoCanvas)
Note left of UWP: Leave the channel
UWP->>SDK: LeaveChannel
SDK->>Agora: Request to leave the channel
Note left of UWP: Release
UWP->>SDK: Dispose
```

![image-20201105165511709](images/image-20201105165511709.png)

Please note that due to UWP platform restrictions, you must apply for camera and microphone permissions before you can use it. Therefore, at the very beginning of the program, the user must call AgoraUWP.AgoraRtc.RequestCameraAccess asynchronous method to apply for permission, otherwise, it will cause AgoraUWP.AgoraRtc to fail to obtain device permissions.

### Use Audio Self-collection

This process corresponds to the first half of the section [Custom Audio Capture and Rendering](https://docs.agora.io/en/Video/custom_audio_windows?platform=Windows), the Custom Audio Capture.

```mermaid
sequenceDiagram
participant UWP as UWP App
participant SDK as Agora UWP SDK
participant Agora as SD-RTN
Note left of UWP: Apply for camera and microphone permissions
UWP->>SDK: AgoraUWP.AgoraRtc.RequestCameraAccess
Note left of UWP: Initialization
UWP->>SDK: new AgoraUWP.AgoraRtc
Note left of UWP: Set to use an external audio source
UWP->>SDK: SetExternalAudioSource
Note left of UWP: Join the channel
UWP->>SDK: JoinChannel
SDK->>Agora: Request to join the channel
SDK-->>UWP: OnJoinChannelSuccess
Note left of UWP: Send the processed audio data to the SDK
UWP->>SDK: PushAudioFrame
Note left of UWP: Leave the channel
UWP->>SDK: LeaveChannel
SDK->>Agora: Request to leave the channel
Note left of UWP: Release
UWP->>SDK: Dispose
```

![image-20201105165949740](images/image-20201105165949740.png)

Start function is

```c#
private void StartEngineAndSelfAudioProcess()
{
    InitEngine();
    InitAudioCapture();
    this.engine.SetExternalAudioSource(true, m_audioCapture.AudioFormat.AudioEncodingProperties.SampleRate, (byte)m_audioCapture.AudioFormat.AudioEncodingProperties.ChannelCount);
}
```

In this function, in addition to initializing the engine, an audio capture based on GeneralMediaCapturer is also be created.

```c#
private void InitAudioCapture()
{
    var sourceGroup = MediaFrameSourceGroup.FindAllAsync().AsTask().GetAwaiter().GetResult();
    if (sourceGroup.Count == 0) return;
    m_audioCapture = new GeneralMediaCapturer(sourceGroup[0], StreamingCaptureMode.Audio);
    m_audioCapture.OnAudioFrameArrived += AudioFrameArrivedEvent;
}
```

In this audio collector, when audio data is collected, AudioFrameArrivedEvent is triggered. After the collected PCM32 audio data is converted into PCM16 audio data that Agora C++ SDK can process, it is sent to PushAudioFrame function.

```c#
private void AudioFrameArrivedEvent(AudioMediaFrame frame)
{
    using (Windows.Media.AudioFrame rawAudioFrame = frame.GetAudioFrame())
        using (AudioBuffer audioBuffer = rawAudioFrame.LockBuffer(AudioBufferAccessMode.Read))
        using (AgoraWinRT.AudioFrame audioFrame = new AgoraWinRT.AudioFrame())
    {
        var buffer = Windows.Storage.Streams.Buffer.CreateCopyFromMemoryBuffer(audioBuffer);
        buffer.Length = audioBuffer.Length;
        using (var dataReader = DataReader.FromBuffer(buffer))
        {
            dataReader.ByteOrder = ByteOrder.LittleEndian;
            byte[] tmp = new byte[buffer.Length / 2];
            int pos = 0;
            while (dataReader.UnconsumedBufferLength > 0)
            {
                var int16Data = (Int16)(dataReader.ReadSingle() * Int16.MaxValue);
                byte[] chunck = BitConverter.GetBytes(int16Data);
                tmp[pos++] = chunck[0];
                tmp[pos++] = chunck[1];
            }
            var format = frame.AudioEncodingProperties;
            audioFrame.bytesPerSample = 2;
            audioFrame.channels = (byte)format.ChannelCount;
            audioFrame.samplesPerSec = format.SampleRate;
            audioFrame.samples = (uint)(tmp.Length / 4);
            audioFrame.type = AUDIO_FRAME_TYPE.FRAME_TYPE_PCM16;
            audioFrame.buffer = tmp;
            engine.PushAudioFrame(audioFrame);
        }
    }
}
```

This example is different from [the official example](https://docs.agora.io/en/Video/custom_audio_windows?platform=Windows). [The official example](https://docs.agora.io/en/Video/custom_audio_windows?platform=Windows) uses a queue to ensure that the sound data won't be lost due to processing time issues, this example does not deal with this aspect.

### Use Audio Self-rendering

This process corresponds to the second half of the section [Custom Audio Capture and Rendering](https://docs.agora.io/en/Video/custom_audio_windows?platform=Windows), the Custom Audio Rendering.

```mermaid
sequenceDiagram
participant UWP as UWP App
participant SDK as Agora UWP SDK
participant Agora as SD-RTN
Note left of UWP: Apply for camera and microphone permissions
UWP->>SDK: AgoraUWP.AgoraRtc.RequestCameraAccess
Note left of UWP: Initialization
UWP->>SDK: new AgoraUWP.AgoraRtc
Note left of UWP: Set to use external audio rendering
UWP->>SDK: SetExternalAudioSink
Note left of UWP: Join the channel
UWP->>SDK: JoinChannel
SDK->>Agora: Request to join the channel
SDK-->>UWP: OnJoinChannelSuccess
Note left of UWP: Pull remote audio data, process it, and play it
UWP->>SDK: PullAudioFrame
Note left of UWP: Leave the channel
UWP->>SDK: LeaveChannel
SDK->>Agora: Request to leave the channel
Note left of UWP: Release
UWP->>SDK: Dispose
```

![image-20201105171003324](images/image-20201105171003324.png)

Start function is

```c#
private void StartEngineAndPullAudioProcess()
{
    InitEngine();
    InitAudioGraph();
    log("Set External Audio Sink", this.engine.SetExternalAudioSink(true, DEFAULT_SAMPLE_RATE, (byte)DEFAULT_CHANNEL_COUNT));
}
```

In this function, in addition to initializing the engine, it also creates an [AudioGraph](https://docs.microsoft.com/en-us/uwp/api/windows.media.audio.audiograph?view=winrt-19041) as an audio player.

```c#
private void InitAudioGraph()
{
    var settings = new AudioGraphSettings(AudioRenderCategory.Media);
    var createGraphResult = AudioGraph.CreateAsync(settings).AsTask().GetAwaiter().GetResult();
    m_audioGraph = createGraphResult.Graph;
    var outputResult = m_audioGraph.CreateDeviceOutputNodeAsync().AsTask().GetAwaiter().GetResult();

    m_audioInput = m_audioGraph.CreateFrameInputNode(
        new AudioEncodingProperties
        {
            BitsPerSample = DEFAULT_BITS_PER_SAMPLE,
            ChannelCount = DEFAULT_CHANNEL_COUNT,
            SampleRate = DEFAULT_SAMPLE_RATE,
            Subtype = MediaEncodingSubtypes.Pcm,
        });
    m_audioInput.QuantumStarted += QuantumStartedEvent;
    m_audioInput.AddOutgoingConnection(outputResult.DeviceOutputNode);
    m_audioInput.Stop();
}
```

The m_audioInput is used as the input of PCM data and is linked to the default system audio outputs, such as speakers or headphones. Whenever m_audioInput is ready to process new audio data, it will trigger the QuantumStarted event. In this event, you can call Agora's PullAudioFrame to get the audio data and play it.

```c#
private void QuantumStartedEvent(AudioFrameInputNode sender, FrameInputNodeQuantumStartedEventArgs args)
{
    using (var frame = new AgoraWinRT.AudioFrame())
    {
        frame.bytesPerSample = 2;
        frame.channels = (byte)DEFAULT_CHANNEL_COUNT;
        frame.samplesPerSec = DEFAULT_SAMPLE_RATE;
        frame.type = AUDIO_FRAME_TYPE.FRAME_TYPE_PCM16;
        frame.renderTimeMs = 0;
        frame.samples = DEFAULT_SAMPLE_RATE / 100;
        var result = engine.PullAudioFrame(frame);
        if (result == 0) PlayAudioFrame(frame);
    }
}

 private unsafe void PlayAudioFrame(AgoraWinRT.AudioFrame frame)
 {
     using (var audioFrame = new Windows.Media.AudioFrame((uint)frame.buffer.Length))
     {
         using (var buffer = audioFrame.LockBuffer(AudioBufferAccessMode.Write))
             using (var reference = buffer.CreateReference())
         {
             byte* data;
             uint size;
             ((IMemoryBufferByteAccess)reference).GetBuffer(out data, out size);
             fixed (byte* raw = frame.buffer)
             {
                 System.Buffer.MemoryCopy(raw, data, size, size);
             }
         }
         m_audioInput?.AddFrame(audioFrame);
     }
 }
```

## How To Use In Your UWP Project

If you want to use AgoraUWP and AgoraWinRT in a new or existing UWP project, you only need to take the following steps, here is a new UWP project as an example

### Generate library files

After compiling the AgoraWinRT and AgoraUWP projects, generate the debug or release directory under bin/x86 or bin/x64 of the AgoraUWP project. The specific depend on the settings during compilation.

![image-20201114120001641](images/image-20201114120001641.png)

the required files is

1. AgoraUWP.dll
2. AgoraWinRT.dll
3. AgoraWinRT.winmd

### Create New UWP Project

Create a new UWP solution through Visual Studio

![image-20201114124043704](images/image-20201114124043704.png)

### Add Agora C++ RTC Library File

Add Existing Item

![image-20201114124137499](images/image-20201114124137499.png)

Download Agora RTC SDK from Agora Official website, and select agora_rtc_sdk.dll among them. Pay attention, you must select the corresponding x86 or x64 version.

![image-20201114124418606](images/image-20201114124418606.png)

Modify "Copy to Output Directory" in agora_rtc_sdk.dll properties to "Copy always"

![image-20201114124617071](images/image-20201114124617071.png)

### Add AgoraWinRT and AgoraUWP Reference

Add References in project

![image-20201114124748758](images/image-20201114124748758.png)

Select browse

![image-20201114124834054](images/image-20201114124834054.png)

Click "Browse...", find AgoraUWP.dll and AgoraWinRT.winmd in AgoraUWP and AgoraWinRT bin directory.

![image-20201114121437673](images/image-20201114121437673.png)

Click "Add"

![image-20201114125125239](images/image-20201114125125239.png)

Click "OK", add AgoraUWP and AgoraWnRT to project's references

![image-20201114125217706](images/image-20201114125217706.png)

### Finally

For subsequent use, you can refer to the AgoraUWPDemo project in the AgoraWinRT project. Note that the project needs to add microphone and webcam capabilities.

![image-20201114125344615](images/image-20201114125344615.png)
