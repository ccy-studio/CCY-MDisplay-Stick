//
// Created by 83503 on 2023/5/8.
//
#include "page_index.h"
#include "aht20.h"
#include "ds1302.h"

#define PAGE_FRAGMENT_STYLE1 0x01
#define PAGE_FRAGMENT_STYLE2 0x02

uint8_t fragment_list_len = 2;
uint8_t fragment_list[2] = {PAGE_FRAGMENT_STYLE1, PAGE_FRAGMENT_STYLE2};
uint8_t currentFragmentIdx = 0;
//温湿度
float humidity = 0, temp = 0;
//当前时间
DS_TimeDef currentTime;

extern ADC_HandleTypeDef hadc;
extern uint8_t displayFlag;

void indexPageHandlerClick(uint8_t buttonType) {
    switch (buttonType) {
        case KEY_DOWN:
            printf("Press Down\n");
            currentFragmentIdx = (currentFragmentIdx + 1) % fragment_list_len;
            break;
        case KEY_UP:
            printf("Press UP\n");
            currentFragmentIdx = (currentFragmentIdx - 1) % fragment_list_len;
            if (currentFragmentIdx < 0) {
                currentFragmentIdx *= -1;
            }
            break;
        case KEY_SET:
            printf("Press Set\n");
            break;
        case KEY_SET_LONG:
            printf("Press LongSet\n");
            //进入设置页面
            displayFlag = DISPLAY_DATE_SETTING;
            break;
    }
}


void readAht20() {
    aht20_read(&humidity, &temp);
    printf("温度:%d,湿度:%d\n---\n", (int) temp, (int) humidity);
}

void readDateTime() {
    currentTime = DS1302_Read_Time();
    //DEBUG 打印输出日期时间
    printf("%d-%d-%d %d:%d:%d\n", currentTime.year, currentTime.month, currentTime.day, currentTime.hour,
           currentTime.minute, currentTime.second);
}

/**
 * ADC转换开始
 */
void startReadAdc() {
    HAL_ADC_Start_IT(&hadc);
}

/**
 * 获得ADC的转换结果
 * @param adcValue
 */
void updateAdc(uint32_t adcValue) {
    printf("ADC VALUE: %ld\n", adcValue);
}

void indexDisplayShow() {
    uint8_t currentFragment = fragment_list[currentFragmentIdx];
    if (currentFragment == PAGE_FRAGMENT_STYLE1) {

    } else if (currentFragment == PAGE_FRAGMENT_STYLE2) {

    } else {
        Error_Handler();
    }

    //测试
    readAht20();
    startReadAdc();
    readDateTime();
}
