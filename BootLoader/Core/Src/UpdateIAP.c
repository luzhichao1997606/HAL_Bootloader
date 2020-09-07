/*
 * @FileName:
 * @Description:
 * @Version:
 * @Author: fwz
 * @Date: 2020-08-26 17:37:26
 * @LastEditors: lzc
 * @LastEditTime: 2020-09-07 13:29:47
 */
/* 升级头文件 */
#include "UpdateIAP.h"

/* 系统头文件 */
#include "MCU_Config.h"

iapfun jump2app;
void MSR_MSP(unsigned int addr); //设置堆栈地址

//设置栈顶地址
// addr:栈顶地址
__asm void MSR_MSP(unsigned int addr)
{
    MSR MSP, r0 // set Main Stack value
                 BX r14
}

//跳转到应用程序段
// appxaddr:用户代码起始地址.
void iap_load_app(uint32_t appxaddr)
{
    if (((*(__IO uint32_t *)appxaddr) & 0x2FFE0000) == 0x20000000) //检查栈顶地址是否合法.
    {
        jump2app = (iapfun) * (__IO uint32_t *)(appxaddr + 4); //用户代码区第二个字为程序开始地址(复位地址)
        MSR_MSP(*(__IO uint32_t *)appxaddr);                   //初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
        jump2app();                                            //跳转到APP.
    }
}

/**
 * @name: uint32_t FlashReadWord(uint32_t addr)
 * @brief: 读取指定地址的字(32位数据)
 * @author: fwz
 * @param {：uint32_t} addr	,	写入的地址
 * @return {uint32_t} 返回读到的32位数据
 * @note: 修改记录：初次创建
 */
uint32_t FlashReadWord(uint32_t addr)
{
    return *(uint32_t *)addr;
}

/**
 * @name:bool FlashWriteWord(uint32_t WriteAddr, uint32_t data)
 * @brief:不做检查的写入数据（32位）
 * @author: fwz
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
bool FlashWriteWord(uint32_t WriteAddr, uint32_t data)
{
    HAL_FLASH_Unlock();

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddr, data) != HAL_OK)
    {
        HAL_FLASH_Lock();
        return false;
    }
    HAL_FLASH_Lock();
    return true;
}

/**
 * @name:bool FlashErase(uint32_t StartAddress, uint16_t ErasePageNum)
 * @brief:
 * @author: fwz
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
bool FlashErase(uint32_t StartAddress, uint16_t ErasePageNum)
{
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;

    HAL_FLASH_Unlock();

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; //
    EraseInitStruct.PageAddress = StartAddress;        //
    EraseInitStruct.NbPages = ErasePageNum;            //
                                                       //页大小FLASH_PAGE_SIZE=1024byte
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
        HAL_FLASH_Lock();
        return false;
    }
    else
    {
        HAL_FLASH_Lock();
        return true;
    }
}

/**
 * @name: bool check_update_flag(void)
 * @brief: 检查更新标志位
 * @author: fwz
 * @param {type} None
 * @return {bool} false：表示无更新标志；true:表示有更新标志位
 * @note: 修改记录：初次创建
 */
bool check_update_flag(void)
{
    bool status = false;
    if (FlashReadWord(UPDATE_FLASH_FLAG) == 0x55555555)
    {
        status = true;
    }
    return status;
}

// /**
//  * @name: bool check_app1_flag(void)
//  * @brief: 检查app1标志位
//  * @author: fwz
//  * @param {type} None
//  * @return {bool} false：表示无更新标志；true:表示有更新标志位
//  * @note: 修改记录：初次创建
//  */
// bool check_app1_flag(void)
// {
//     bool status = false;
//     if (FlashReadWord(UPDATE_FLASH_FLAG) == 0x66666666)
//     {
//         status = true;
//     }
//     return status;
// }

// /**
//  * @name: bool check_app2_flag(void)
//  * @brief: 检查app2标志位
//  * @author: fwz
//  * @param {type} None
//  * @return {bool} false：表示无更新标志；true:表示有更新标志位
//  * @note: 修改记录：初次创建
//  */
// bool check_app2_flag(void)
// {
//     bool status = false;
//     if (FlashReadWord(UPDATE_FLASH_FLAG) == 0x77777777)
//     {
//         status = true;
//     }
//     return status;
// }
/**
 * @name: bool CheckAppExisted(void)
 * @brief:检查APP是否存在
 * @author: xxx
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
bool CheckApp1Existed(void)
{
    uint8_t i = 0;
    //检测APP1地址是都是0XFF
    for (i = 0; i < 8; i++)
    {
        // 从第5K开始
        if (FlashReadWord(BLOCK_APP1_START + MCU_FLASH_PAGE_SIZE * 5 + i * 4) != FLASH_APP_DEFAULT_VALUE)
        {
            return false; //
        }
    }
    return true; //
}
/**
 * @name:void updateInterface_CopyCode_FromApp2ToApp1(void)
 * @brief:将APP2代码复制到APP1中
 * @author: fwz
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
void updateInterface_CopyCode_FromApp2ToApp1(void)
{
    uint32_t i = 0;

    for (i = 0; i < BLCOK_APP2_SPACE; i += 4)
    {
        FlashWriteWord(BLOCK_APP1_START + i, *(uint32_t *)(BLOCK_APP2_START + i));
    }
}
