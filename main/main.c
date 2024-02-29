/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_B = 14;
const int BTN_G = 15;
const int BTN_R = 14;
const int BTN_Y = 15;

const int BUZZER = 16;

const int LED_B = 14;
const int LED_G = 15;
const int LED_R = 14;
const int LED_Y = 15;

volatile bool PRESSED_B = false;
volatile bool PRESSED_G = false;

void buz(int freq, int tempo, int buzzer){ 
    int i;
    int tempo_total = 1000000 / (freq * 2);
    int n = tempo * freq / 1000;
    for (i = 0; i < n; i++) {
        printf("buzz");
        gpio_put(buzzer, 1);
        sleep_us(tempo_total);
        gpio_put(buzzer, 0);
        sleep_us(tempo_total);
    }
}

int main() {

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    gpio_init(BTN_G);
    gpio_set_dir(BTN_G, GPIO_IN);
    gpio_pull_up(BTN_G);

    gpio_init(BTN_R);
    gpio_set_dir(BTN_R, GPIO_IN);
    gpio_pull_up(BTN_R);

    gpio_init(BTN_Y);
    gpio_set_dir(BTN_Y, GPIO_IN);
    gpio_pull_up(BTN_Y);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_IN);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_IN);

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_IN);

    gpio_init(LED_Y);
    gpio_set_dir(LED_Y, GPIO_IN);

    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
