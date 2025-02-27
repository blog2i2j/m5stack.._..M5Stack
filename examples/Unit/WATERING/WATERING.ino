/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*
 * @Hardwares: M5Core + Unit Watering
 * @Platform Version: Arduino M5Stack Board Manager v2.1.3
 * @Dependent Library:
 * M5Stack@^0.4.6: https://github.com/m5stack/M5Stack
 */

#include <M5Stack.h>

#define INPUT_PIN 36
#define PUMP_PIN  26

bool flag = true;
int rawADC;

void setup()
{
    M5.begin();
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString("Watering TEST", 160, 20, 1);
    M5.Lcd.drawString("ON/OFF PUMP", 160, 200, 1);
    pinMode(INPUT_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(25, OUTPUT);
    digitalWrite(25, 0);
}

char info[30];

void loop()
{
    rawADC = analogRead(INPUT_PIN);
    M5.lcd.fillRect(80, 100, 240, 50, BLACK);
    M5.Lcd.setCursor(80, 100);
    M5.Lcd.print("ADC: " + String(rawADC));
    Serial.print("Watering ADC value: ");
    Serial.println(rawADC);
    if (M5.BtnB.wasPressed()) {
        digitalWrite(PUMP_PIN, flag);
        flag = !flag;
    }
    M5.update();
    delay(100);
}