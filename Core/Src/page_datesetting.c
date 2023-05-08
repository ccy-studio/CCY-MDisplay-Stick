//
// Created by 83503 on 2023/5/8.
//
#include "page_datesetting.h"

extern uint8_t displayFlag;

void dateSettingPageHandlerClick(uint8_t buttonType) {
    switch (buttonType) {
        case KEY_DOWN:
            break;
        case KEY_UP:
            break;
        case KEY_SET:
            break;
        case KEY_SET_LONG:
            displayFlag = DISPLAY_INDEX;
            break;
    }
}

void dateSettingDisplayShow() {

}