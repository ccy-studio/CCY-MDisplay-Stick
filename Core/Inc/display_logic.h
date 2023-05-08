//
// Created by 83503 on 2023/5/8.
//

#ifndef CCY_MDISPLAY_STICK_DISPLAY_LOGIC_H
#define CCY_MDISPLAY_STICK_DISPLAY_LOGIC_H

#include "main.h"
#include "delay.h"

#define KEY_SET 0x01
#define KEY_SET_LONG 0x11
#define KEY_UP 0x02
#define KEY_DOWN 0x03

#define DISPLAY_INDEX 0x10 //首页
#define DISPLAY_DATE_SETTING 0x11 //时间设置页


void logicInit(void);

void logicRun(void);

#endif //CCY_MDISPLAY_STICK_DISPLAY_LOGIC_H
