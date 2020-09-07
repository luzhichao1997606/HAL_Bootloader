/*
 * @FileName:
 * @Description:
 * @Version:
 * @Author: fwz
 * @Date: 2020-08-26 18:11:55
 * @LastEditors: lzc
 * @LastEditTime: 2020-09-07 11:16:49
 */
#ifndef __Mcu_Config_h
#define __Mcu_Config_h

/************************** IAP 数据相关参数 **************************/

// 系统默认的起始ROM和RAM地址
#define BASE_OF_ROM (0x08000000)
#define BASE_OF_RAM (0x20000000)

//每个FLash页大小1024 byte
#define MCU_FLASH_PAGE_SIZE 0x400
//总共页数：64

/************************************************
 *应用程序由Bootloader引导再启动
 *------------------------------------------------
 *内部Flash分区:
 * | 62kB boot | 50kB param | 200kB app1 | 200kB app2
 * 目前Bootloader程序rom用了8.47kB，剩余53.53kb
 *------------------------------------------------
 *RAM分区:
 * | 6K boot  |  58K app1
 * 目前Bootloader程序ram用了1.48kB，剩余1.02kB
 ************************************************/

// Bootloader代码区域
#define BLOCK_BOOTLOADER_START (BASE_OF_ROM) // 0x08000000
#define BLOCK_BOOTLOADER_NUM (10)            // 10K
#define BLOCK_BOOTLOADER_SPACE (MCU_FLASH_PAGE_SIZE * BLOCK_BOOTLOADER_NUM)

// 系统参数区域
#define BLCOK_SYS_PARAM_START (BLOCK_BOOTLOADER_START + BLOCK_BOOTLOADER_SPACE) ////0x08000A00
#define BLCOK_SYS_PARAM_NUM (2)                                                 // 2页   2K
#define BLCOK_SYS_PARAM_SPACE (MCU_FLASH_PAGE_SIZE * BLCOK_SYS_PARAM_NUM)

// APP1代码区域
#define BLOCK_APP1_START (BLCOK_SYS_PARAM_START + BLCOK_SYS_PARAM_SPACE) // 0x08000B00
#define BLOCK_APP1_NUM (26)                                              // 26k
#define BLCOK_APP1_SPACE (MCU_FLASH_PAGE_SIZE * BLOCK_APP1_NUM)

// APP2代码区域
#define BLOCK_APP2_START (BLOCK_APP1_START + BLCOK_APP1_SPACE) // 0x08004580
#define BLOCK_APP2_NUM (26)                                    // 26k
#define BLCOK_APP2_SPACE (MCU_FLASH_PAGE_SIZE * BLOCK_APP2_NUM)
/*********************************************************************/

///* Bootloader程序版本号 */
////主版本编号
//#define Bootloader_Software_Version_Major (3u)
////子版本编号
//#define Bootloader_Software_Version_Child (1u)

//程序更新标志位地址，更新之后变成0x55555555，目前只设置1个标志位
#define UPDATE_FLASH_FLAG BLCOK_SYS_PARAM_START // 4 byte
// // APP1标志位地址 更新之后变成0x66666666
// #define APP1_FLASH_FLAG UPDATE_FLASH_FLAG + 4  // 4 byte
// // APP2标志位地址 更新之后变成0x77777777
// #define APP2_FLASH_FLAG APP1_FLASH_FLAGT + 4  // 4 byte

#endif
