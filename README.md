# Video-to-ASCII

A Video to ASCII real-time converter for terminal using C++ and OpenCV.

![video-to-ascii](https://github.com/ale3d62/Video-to-ASCII/blob/main/readmegif.gif)

## Functionalities

- Play local videos
- Play youtube videos
- Load webcam preview
- Video is played with audio

### Extra features

- Dynamic size: Video dimensions will adjust dynamically when changing the terminal window size.
- Video and audio synchronization: If the video slows down, it will speed back up when it can until it synchronizes with the audio.
- High performance: Play videos of up to 200x113 character resolution at 60fps.

## Requisites

- Windows only.
- The terminal used must support escape characters.
- [FFmpeg](https://www.ffmpeg.org/) is needed for audio playing.
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) (which is included in the download) is needed for playing videos from Youtube.


## How to run

The `video_to_ascii.exe` must be run with one of the following parameters:
- `webcam` for loading the webcam preview.
- `video` for playing a local video. 
- `link` for playing a Youtube video.

Dependencies (like FFmpeg, yt-dlp, or a local video you want to play) should be in the same directory as `video_to_ascii.exe` if not installed by yourself and accessible from anywhere on your computer.

When playing Youtube videos, yt-dlp is not very flexible with the links, make sure that the link you enter is the one from the actual video. Links to videos played from a playlist or similar may not work.

## How to build

The project was built in `VSCode` using `CMake` with `MSVC 17.8.5 x64`.

Download [OpenCV](https://opencv.org/releases/) (the version used was `4.9.0`), create a new system variable called `OpenCV_DIR` which points to `opencv\build`, and create a new item in `path` which points to `opencv\build\x64\vc16\bin`. From there, you can compile using the `CMakeLists.txt` provided. 

The built file should be in `build\Debug`.
