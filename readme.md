本项目意为制作一个智能手表，其中包含的功能有时间年月日时分秒的显示和修改、秒表计时、手电筒、手表姿态检测、小游戏、动态表情包展示、电池电量显示、开关机，参考了https://www.bilibili.com/video/BV1CoGuzEEeN/?spm_id_from=333.1387.favlist.content.click。
使用裸机开发,使用的模块有stm32f103c8t6最小系统板、OLED、mpu6050、按键、LED
效果视频（视频中显示不清晰、闪屏或错位的情况是拍摄导致的并不是代码问题）：https://www.bilibili.com/video/BV1TEJw6qEXQ/?vd_source=7d0d7a57140f407a6a251ec7df2b29df#reply116747864637735

![初始界面效果1](images/watch1.jpg)
![初始界面效果2](images/watch2.jpg)

log：
2026
    4.13
        创建初始界面
        优化：使用时钟定时中断，每20ms识别一次按键，达到按键消抖的效果
    4.14
        创建时间设置界面
    4.15
        创建循环滑动菜单
    4.16
        1.完成计时功能
          完成led控制功能
        2.修复计时功能bug：重复退出计时功能会触发计时
    4.17
        1.完成MPU6050姿态解算功能
          利用死区过滤，让Yaw的值不在静止时自减
        2.制作一个小游戏：小恐龙
          修改oled驱动文件中的OLED_SetCursor函数，取消显存偏移，修复oled显示白边bug
    4.18
        1.完善动态表情包功能和水平仪功能
        2.更改key和led的引脚，方便ad引脚使用排线
        3.添加电量显示功能（使用ADC；用电位器模拟电量变化）和长按两秒确认键（key3）关机功能
    5.25
        完善led模拟开关机功能，将开机改为长按2秒key3，关机为长按4秒

若需打印pcb板制作完整的手表可参考下面的硬件原理图：
    ![硬件原理图](images/HardwareSchematic.png.png)
