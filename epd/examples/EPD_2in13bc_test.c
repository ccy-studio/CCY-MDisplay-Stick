/*****************************************************************************
* | File      	:   EPD_2in13bc_test.c
* | Author      :   Waveshare team
* | Function    :   2.13inch B&C e-paper test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-13
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_2IN13BC.h"

int EPD_test(void) {
    printf("EPD_2IN13BC_test Demo\r\n");
    DEV_Module_Init();

    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN13BC_Init();
    EPD_2IN13BC_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache named IMAGE_BW and fill it with white
    UBYTE *BlackImage;
    UWORD Imagesize =
            ((EPD_2IN13BC_WIDTH % 8 == 0) ? (EPD_2IN13BC_WIDTH / 8) : (EPD_2IN13BC_WIDTH / 8 + 1)) * 100;
    if ((BlackImage = (UBYTE *) malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("NewImage:BlackImage and RYImage\r\n");
    Paint_NewImage(BlackImage, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, 270, WHITE);

    //Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);


#if 1   // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    printf("Draw black image\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 70, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 80, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 50, 100, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(50, 70, 20, 100, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(60, 70, 90, 100, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(125, 85, 15, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawString_CN(5, 15, "abc", &Font12CN, WHITE, BLACK);


    printf("EPD_Display\r\n");
    EPD_2IN13BC_Display(BlackImage, NULL);
    DEV_Delay_ms(2000);
#endif

    printf("Clear...\r\n");
    EPD_2IN13BC_Clear();

    printf("Goto Sleep...\r\n");
    EPD_2IN13BC_Sleep();
    free(BlackImage);
    BlackImage = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return 0;
}

