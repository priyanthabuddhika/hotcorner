# Tiny Hot Corners for Windows 10

### Documents

[English](https://github.com/misterchaos/hotcorner/blob/Yuchao-Huang/README_En.md)|[中文](https://github.com/misterchaos/hotcorner/blob/Yuchao-Huang/README.md)

### Introduction

One handy feature on macOS is the *trigger Angle*. Through this function, you can set the trigger event when the mouse moves to the four corners of the screen, such as triggering to start the activities view, display desktop or other functions.MacOS calls them *Hot Corners*, in contrast to our usual hotkeys. This *HotCorner App* is used to make Windows have like macOS trigger Angle, the GIF below shows how it works:

When the mouse moves to the upper left corner of the screen, it can automatically opens the Windows timeline (activities view) so that we can switch task quickly.

![](https://raw.githubusercontent.com/misterchaos/img/master/image/hotcorner%20(4).gif)

You can view the original version here:

 [@Tavis Ormandy](https://github.com/taviso)-[hotcorner:Tiny Hot Corners for Windows 10](https://github.com/taviso/hotcorner)



Based on the original project, I made the following changes:

1. Add a trigger angle in the lower left corner to trigger the start menu
2. Program Installer added
3. Program icon added
4. Enable run on startup

5. Chinese documents provided



To trigger the start menu in the lower left corner like this:

![](https://img2020.cnblogs.com/blog/1654007/202006/1654007-20200615225727735-1550089543.gif)


### Functions

- Trigger the activities view with mouse in the upper left corner
- Trigger the start menu with mouse in the lower left corner

### Download

- [Download from github](https://github.com/misterchaos/hotcorner/releases)

- [Download from gitee](https://gitee.com/misterchaos/hotcorner/releases/v1.5)

If you do not want to participate in the development, just download `hotcornerinstaller.exe` <br>

If you are in China, I suggest you [Download from gitee](https://gitee.com/misterchaos/hotcorner/releases/v1.5)

### Installing

After downloading `Hotcornerinstaller.exe` from the above download address, double-click on it to start the installation.![image-20200615203603094](http://nextcloud.hellochaos.cn/index.php/s/T6iLYN2FiS5FoJ7/preview)

### Uninstalling

Find the installation location of the software (default is C:\Program Files (x86)\HotCorner) and double-click 'unins000.exe' under the folder to complete the uninstallation.Stop the software before uninstalling (press Ctrl+Alt+C)

### Configuration

After the software installation is completed, it will be automatically added to the application list in the Start menu, where you can find HotCorner and click it to run the software in the background.If you are using screen zooming as shown in the figure, and the scale is not 100%, you need to do the following configuration

![image-20200615204923679](http://nextcloud.hellochaos.cn/index.php/s/6fCqMDKWgPdixYZ/preview)

Under normal circumstances, the software can automatically obtain the height of the screen, but when the system uses a scaling of screen, can cause the software to get is not the real height of the screen, so you need to edit ` config. TXT ` file in the software installation path (the default is C: \ Program Files \ HotCorner (x86)) , write the actual height of the screen in this file and then restart the app.(The default value in 'config.txt' is 0, indicating that screen height is automatically obtained.)

> **Press Ctrl+Alt+C to close the program during the software running**

### License

The code is open source using GPL3 protocol. If you need to use the code, please follow the relevant provisions of CPL3 protocol.

### Authors

* Tavis Ormandy [@taviso](https://github.com/taviso/) - Original Author
* Ahmed Samy [@asamy](https://github.com/asamy) - HotKey support
* Yuchao Huang [@misterchaos](https://github.com/misterchaos/) - Application Package

### FAQ

* Q: The top left corner of the screen triggers the timeline view, but the bottom right corner doesn't respond ?
* A: You may have used screen zooming, check out the [configuration instructions](#Configuration)


* Q: What should I do if I want to change the event triggered by the screen corner?
* A:  you can download the source code to make changes, and then recompile.


* Q: How can I close the software after it runs?
* A: Press Ctrl+Alt+C to close the program during the software running


* Q: How do I enable *run on startup*？
* A: In the installation process, you can choose 'run on startup'. You can also manually make it (You can do it with Google).

