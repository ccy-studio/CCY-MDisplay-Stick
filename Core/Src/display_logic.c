//
// Created by 83503 on 2023/5/8.
//
#include "display_logic.h"
#include "delay.h"
#include "aht20.h"
#include "tim.h"
#include "page_index.h"
#include "page_datesetting.h"
#include "EPD_Test.h"

//连续多次点击的间隔有效值
uint8_t doubleClickTimDiff = 100;

//显示标记
uint8_t displayFlag;


void logicInit(void) {
    aht20_init();
    displayFlag = DISPLAY_INDEX;
    EPD_test();
}


/**
 * 按键按下-Set功能 ▧
 */
void buttonPressSet() {
    switch (displayFlag) {
        case DISPLAY_INDEX:
            indexPageHandlerClick(KEY_SET);
            break;
        case DISPLAY_DATE_SETTING:
            break;
            dateSettingPageHandlerClick(KEY_SET);
        default:
            Error_Handler();
    }
}

/**
 * 按键按下-Up功能 ↑
 */
void buttonPressUp() {
    switch (displayFlag) {
        case DISPLAY_INDEX:
            indexPageHandlerClick(KEY_SET);
            break;
        case DISPLAY_DATE_SETTING:
            break;
            dateSettingPageHandlerClick(KEY_SET);
        default:
            Error_Handler();
    }
}

/**
 * 按键按下-Down功能 ↓
 */
void buttonPressDown() {
    switch (displayFlag) {
        case DISPLAY_INDEX:
            indexPageHandlerClick(KEY_SET);
            break;
        case DISPLAY_DATE_SETTING:
            break;
            dateSettingPageHandlerClick(KEY_SET);
        default:
            Error_Handler();
    }
}

/**
 * 按键长按-Set功能 ▧
 */
void buttonPressLongSet() {
    switch (displayFlag) {
        case DISPLAY_INDEX:
            indexPageHandlerClick(KEY_SET_LONG);
            break;
        case DISPLAY_DATE_SETTING:
            break;
            dateSettingPageHandlerClick(KEY_SET_LONG);
        default:
            Error_Handler();
    }
}

/**
 * 按键中断回调函数
 * @param GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin) == RESET) {
        //下降沿
        if (GPIO_Pin == KEY1_Pin) {
            //Set按键
            startTim6();
        }
    } else {
        //上升沿
        if (GPIO_Pin == KEY1_Pin) {
            //检测是否长按成立
            stopTim6();
            if (getTim6Counter() > doubleClickTimDiff) {
                //成立
                buttonPressLongSet();
            } else {
                buttonPressSet();
            }
        } else if (GPIO_Pin == KEY2_Pin) {
            buttonPressUp();
        } else if (GPIO_Pin == KEY3_Pin) {
            buttonPressDown();
        }
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    updateAdc(HAL_ADC_GetValue(hadc));
}

void logicRun(void) {
    delay_ms(1000);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

    if (displayFlag == DISPLAY_INDEX) {
        indexDisplayShow();
    } else if (displayFlag == DISPLAY_DATE_SETTING) {
        dateSettingDisplayShow();
    }
}