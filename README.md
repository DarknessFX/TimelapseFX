     .----------------.  .----------------.  .----------------. 
    | .--------------. || .--------------. || .--------------. |
    | |  ________    | || |  _________   | || |  ____  ____  | |
    | | |_   ___ `.  | || | |_   ___  |  | || | |_  _||_  _| | |
    | |   | |   `. \ | || |   | |_  \_|  | || |   \ \  / /   | |
    | |   | |    | | | || |   |  _|      | || |    > `' <    | |
    | |  _| |___.' / | || |  _| |_       | || |  _/ /'`\ \_  | |
    | | |________.'  | || | |_____|      | || | |____||____| | |
    | |              | || |              | || |              | |
    | '--------------' || '--------------' || '--------------' |
     '----------------'  '----------------'  '----------------' 

           DarknessFX @ https://dfx.lv | Twitter: @DrkFX

# TimelapseFX

Windows tool that create timelapse screenshots and export to video (MP4,AVI,GIF) with caption. Support multi-monitor and application-only screenshot.

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/img_app.png" width="48" height="48" />
<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_Intro720p.gif" width="854" height="480" />

## About

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_Systray.png" /><br/>

TimelapseFX runs at Windows systray as a background process. Left-click capture a screenshot, Right-click open the context menu.<br/><br/>

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_Menu.png" /><br/>

The context menu offer some shotcuts to Open the screenshots folder and to Reorder filenames, this is useful to delete unwanted screenshots and organize the timelapse sequence before export to video.<br />TimelapseFX will stop create screenshots while the Windows screensaver is activated or the display is in sleep mode, if necessary you can use the Pause menu to stop the timer and resume later.<br/><br/>

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_Settings.png" /><br/>

Settings allows to adjust options with tooltips explaining each setting.<br/><br/>

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_CaptureMode.png" />
<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_CaptureMode_Application.png" /><br/>

Capture Mode allows to select between capture All Displays, Single display or Application. In application mode, TimelapseFX can screenshot the application even behind other windows, but it cannot screenshot if the application is minimized.<br/><br/>

<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_Export.png" />
<img src="https://raw.githubusercontent.com/DarknessFX/TimelapseFX/main/.git_img/TimelapseFX_ExpFormats.png" /><br/>

Export Timelapse have options to choose between video resolutions and video formats. It can also Create Caption (TimelapseFX_caption.srt) in sync with your timelapse screenshots to easily add captions and descriptions.<br/><br/>

Project info/blog at <a href="https://dfx.lv/TimelapseFX" target="_blank">https://dfx.lv/TimelapseFX</a> .<br/><br/>

## To Do

- Capture Mode by Screen Region, like Windows Snip & Sketch (Win+Shift+S).<br/>
- Capture Mode by Application Region, to capture just part of the application (like: viewport).<br/><br/>

## Changelog
1.2
- Overall improvements and fixes.
- Better GIF conversion.
 
1.1
- New DirectX capture helper to improve screenshot compatibility with custom renders (like DirectX, Qt, WinUI).
- New Camera icon to display the capture is in progress.
- Better and faster Applications list.
- Overall bug fixes and improvements.<br/><br/>
 
## Credits

Microsoft FluentUI System Icons - https://github.com/microsoft/fluentui-system-icons <br/>
FFMpeg - https://ffmpeg.org <br/>
MajorGeeks FFMpeg Build - https://m.majorgeeks.com/files/details/ffmpeg.html <br/>
IsAltTabWindow() from Microsoft - https://github.com/microsoft/Windows.UI.Composition-Win32-Samples/blob/master/cpp/ScreenCaptureforHWND/ScreenCaptureforHWND/Win32WindowEnumeration.h<br/>
Gil123 at StackOverflow, for the Windowless ScreenCaptureforHWND code - https://stackoverflow.com/questions/11283015/screen-capture-specific-window<br/>
High quality GIF with FFmpeg by ubitux - http://blog.pkh.me/p/21-high-quality-gif-with-ffmpeg.html<br/><br/>

## License

@Copyleft - All wrongs reserved. <br/><br/>
DarknessFX @ <a href="https://dfx.lv" target="_blank">https://dfx.lv</a> | Twitter: <a href="https://twitter.com/DrkFX" target="_blank">@DrkFX</a> <br/>https://github.com/DarknessFX/TimelapseFX

