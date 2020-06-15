# Tiny Hot Corners for Windows 10

### 简介

macOS上有一个很方便的功能：“触发角”。通过这个功能可以设置当鼠标移动到屏幕的四个角时的触发事件，例如触发启动屏幕保护程序等，显示桌面等功能。和我们习惯的热键相对应，macOS将其称之为“Hot Corners(热角)”。笔者接下来要介绍的软件**“[HotCorner](https://github.com/misterchaos/hotcorner/releases)"**就是用于让Windows系统拥有像macOS那样的触发角，实现下面动图展示的效果：

当鼠标移动到屏幕的左上角时，自动打开Windows的时间轴试图，实现快捷切换任务。

![](https://github.com/misterchaos/img/raw/master/image/hotcorner.gif)

这个程序来源于一个国外大神（[Google](http://www.google.com/)的信息安全工程师）[Tavis Ormandy](https://github.com/taviso) 的一个小项目 [hotcorner](https://github.com/taviso/hotcorner)，他创作这个项目是因为习惯于一款Linux操作系统桌面GNOME 3，这款桌面可以在鼠标移动到左上角时触发任务视图。他发现每当自己使用Windows 10时，总是会忘记Windows中并没有这个功能，四处寻找替代软件都无法令他满意，因此自己用C语言手撸了一个小程序来实现这个功能。但这个小程序只有一个功能：屏幕左上角触发Windows时间轴视图。并且软件的安装，卸载都需要通过命令行或者手动实现，十分不方便。

笔者在原先的项目基础上做出了如下改动：

1. 用屏幕的左下角来触发开始菜单
2. 将软件打包成安装引导程序（安装包）
3. 给软件添加图标
4. 安装时可选择软件开机启动
5. 编写中文文档

下面一张动图演示了笔者添加的左下角触发开始菜单的功能

![](https://github.com/misterchaos/img/raw/master/image/hotcorner2.gif)

### 软件功能

- 当鼠标移动至屏幕左上角时显示Windows 10时间轴视图
- 当鼠标移动至屏幕右下角时显示Windows 开始菜单

### 下载

Github地址：[下载地址](https://github.com/misterchaos/hotcorner/releases)

码云地址：[下载地址](https://gitee.com/misterchaos/hotcorner/releases/v1.5)

如果你不打算参与本软件开发，只需要下载`HotcornerInstaller.exe`这个安装程序即可<br>国内推荐使用码云地址进行下载，速度比较快，但如果你需要提交issue，请前往Github地址。

### 安装

从上述下载地址将`HotcornerInstaller.exe`下载下来之后，双击打开即可开始安装。

![image-20200615203603094](http://nextcloud.hellochaos.cn/index.php/s/T6iLYN2FiS5FoJ7/preview)

### 卸载

找到软件的安装位置（默认是C:\Program Files (x86)\HotCorner），双击该文件夹下的`unins000.exe`即可完成卸载。在卸载之前请先停止软件运行（同时按下Ctrl+Alt+C）。

### 使用

软件安装完成之后会自动添加到开始菜单的应用列表中，在其中找到HotCorner，单击之后软件即可后台运行。如果你使用了如图所示的屏幕缩放，并且缩放比例不是100%时，则需要进行下面的配置

![image-20200615204923679](http://nextcloud.hellochaos.cn/index.php/s/6fCqMDKWgPdixYZ/preview)

正常情况下，软件可以自动获取屏幕的高度，但是在系统使用屏幕缩放时，会导致软件获取到的不是屏幕的真实高度，因此你需要编辑软件安装路径（默认是C:\Program Files (x86)\HotCorner）下的`config.txt`文件，在这个文件中写入屏幕的真实高度，例如图中的屏幕真实高度为1080（无单位），然后重启软件。（`config.txt`中的默认值是0，表示自动获取屏幕高度。）

> **在软件运行过程中同时按下Ctrl+Alt+C可以关闭程序**

### License

代码使用GPL3协议进行开源，如需使用代码请遵循CPL3协议相关规定。

### 作者

* Tavis Ormandy [@taviso](https://github.com/taviso/) - Original Author
* Ahmed Samy [@asamy](https://github.com/asamy) - HotKey support
* Yuchao Huang [@misterchaos](https://github.com/misterchaos/) - Application Package

### FAQ

* Q: 屏幕左上角可以触发时间轴视图，但是屏幕右下角没有反应？
* A: 你可能使用了屏幕缩放，查看[配置说明](#使用)


* Q: 我想修改屏幕角触发的事件，怎么办？
* A: 目前只能自己下载源代码进行修改，然后重新编译运行。


* Q: 软件运行之后怎么关闭？
* A: 在软件运行过程中同时按下Ctrl+Alt+C可以关闭程序


* Q: 怎么让软件在开机时运行？
* A: 在安装过程中可以选择`开机启动`，如果安装时没有选择，可以手动实现（方法自己百度即可）

