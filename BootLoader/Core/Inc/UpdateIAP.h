/*
 * @FileName:
 * @Description:
 * @Version:
 * @Author: xxx
 * @Date: 2020-08-26 18:52:46
 * @LastEditors: fwz
 * @LastEditTime: 2020-09-01 18:18:27
 */
#ifndef _UPDATE_IAP_H_
#define _UPDATE_IAP_H_
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <string.h>

// APP³ÌÐò×´Ì¬±êÖ¾
//当内部flash没有被升级过则数值应为0xffffffff
#define FLASH_APP_DEFAULT_VALUE 0xFFFFFFFF

typedef signed char      int8_t;
typedef signed short int int16_t;
typedef signed int       int32_t;

/* exact-width unsigned integer types */
typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;

typedef void (*iapfun)(void);          //定义一个函数类型的参数.
void iap_load_app(uint32_t appxaddr);  //执行flash里面的app程序

bool check_update_flag(void);
// bool check_app1_flag(void);
// bool check_app2_flag(void);
bool CheckApp1Existed(void);
bool FlashErase(uint32_t StartAddress, uint16_t ErasePageNum);
bool FlashWriteWord(uint32_t WriteAddr, uint32_t data);
void updateInterface_CopyCode_FromApp2ToApp1(void);
#endif
