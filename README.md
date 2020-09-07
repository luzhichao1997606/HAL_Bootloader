<!--
 * @FileName: 
 * @Description: 
 * @Version: 
 * @Author: lzc
 * @Date: 2020-09-07 15:11:22
 * @LastEditors: lzc
 * @LastEditTime: 2020-09-07 15:27:43
-->
# HAL_Bootloader
采用STM32F103C8T6进行升级，其中Boot规划10K，参数2K APP规划52K
* 其中APP1 26KB,APP2 26KB
```
[15:27:05.738]收←◆IAP
[15:27:06.742]收←◆jump
hello world!
[15:27:07.743]收←◆hello world!
[15:27:08.745]收←◆hello world!
[15:27:09.747]收←◆hello world!
[15:27:10.750]收←◆hello world!
[15:27:11.751]收←◆hello world!
```
结果如上