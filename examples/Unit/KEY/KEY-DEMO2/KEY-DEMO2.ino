/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*
 * @Hardwares: M5Core + Unit Key
 * @Platform Version: Arduino M5Stack Board Manager v2.1.3
 * @Dependent Library:
 * M5Stack@^0.4.6: https://github.com/m5stack/M5Stack
 * FastLED@^3.9.10: https://github.com/FastLED/FastLED
 */

#include <FastLED.h>
#include <M5Stack.h>

uint8_t ledColor = 0;

#define KEY_PIN  (22)  // Define Key Pin.  定义Key引脚
#define DATA_PIN (21)  // Define LED pin.  定义LED引脚.
CRGB leds[1];          // Define the array of leds.  定义LED阵列.

void LED(void *parameter);
void changeLedColor();

void setup()
{
    M5.begin();  // Init M5Stack  初始化M5Stack
    M5.Lcd.setTextSize(3);
    M5.Lcd.print(("\n UNIT-KEY Example\n\n    Key State:"));

    pinMode(KEY_PIN, INPUT_PULLUP);  // Init Key pin.  初始化Key引脚.

    FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds,
                                           1);  // Init FastLED.  初始化FastLED.

    xTaskCreate(LED, "led", 1000, NULL, 0, NULL);  // Create a thread for breathing LED. 创建一个线程用于LED呼吸灯.
}

void loop()
{
    if (!digitalRead(KEY_PIN)) {  // If Key was pressed.  如果按键按下.
        M5.Lcd.setCursor(75, 130);
        M5.Lcd.print(("Pressed "));
        changeLedColor();              // Change LED color.  更换LED呼吸灯颜色.
        while (!digitalRead(KEY_PIN))  // Hold until the key released.  在松开按键前保持状态.
            ;
    } else {
        M5.Lcd.setCursor(75, 130);
        M5.Lcd.println(("Released"));
    }
    delay(100);
}

void LED(void *parameter)
{
    leds[0] = CRGB::Red;
    for (;;) {
        for (int i = 0; i < 255; i++) {  // Set LED brightness from 0 to 255.  设置LED亮度从0到255.
            FastLED.setBrightness(i);
            FastLED.show();
            delay(5);
        }
        for (int i = 255; i > 0; i--) {  // Set LED brightness from 255 to 0.  设置LED亮度从255到0.
            FastLED.setBrightness(i);
            FastLED.show();
            delay(5);
        }
    }
    vTaskDelete(NULL);
}

void changeLedColor()
{
    ledColor++;
    if (ledColor > 2) ledColor = 0;
    switch (ledColor) {  // Change LED colors between R,G,B.  在红绿蓝中切换LED颜色.
        case 0:
            leds[0] = CRGB::Red;
            break;
        case 1:
            leds[0] = CRGB::Green;
            break;
        case 2:
            leds[0] = CRGB::Blue;
            break;
        default:
            break;
    }
}
