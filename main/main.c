/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// const int RED_LED = 19;
// const int GREEN_LED = 20;
// const int BLUE_LED = 21;
const int MOTOR_PIN_O = 10;
const int MOTOR_PIN_Y = 11;
const int MOTOR_PIN_P = 12;
const int MOTOR_PIN_B = 13;
const int LED_PIN_R = 18;
const int LED_PIN_B = 19;
const int LED_PIN_Y = 20;
const int LED_PIN_G = 21;
const int BTN_PIN_Y = 2;
const int BTN_PIN_R = 3;
const int BTN_PIN_B = 4;
const int BTN_PIN_G = 5;
const int BUZZER_PIN = 6;
volatile int btn_y_state = 0;
volatile int btn_r_state = 0;
volatile int btn_b_state = 0;
volatile int btn_g_state = 0;

void btn_callback(uint gpio, uint32_t events){
    if(gpio == BTN_PIN_R && events == GPIO_IRQ_EDGE_FALL){
        btn_r_state = 1;
    } else if (gpio == BTN_PIN_B && events == GPIO_IRQ_EDGE_FALL){
        btn_b_state = 1;
    } else if(gpio == BTN_PIN_Y && events == GPIO_IRQ_EDGE_FALL){
        btn_y_state = 1;
    } else if (gpio == BTN_PIN_G && events == GPIO_IRQ_EDGE_FALL){
        btn_g_state = 1;
    }
}

void play_sound(int btn, int indice){
    int freqs[4] = {440, 660, 880, 1100};
    int duration_ms = 1000;
    int t = 1000000/(freqs[indice]*2); // o 10^6 eh pq estamos convertendo para microsegundos e t = 1/f, e dividimos por 2 por ser metade da onda ligada e metade desligada
    int n = duration_ms / 10; // quantidade de vezes que fazemos a onda inteira
    for(int i = 0; i < n; i++){
        gpio_put(btn, 1);
        sleep_us(t);
        gpio_put(btn, 0);
        sleep_us(t);
    }
}

void um_quarto_de_volta(){
    for (int i = 0; i <= 512/4; i++){
        gpio_put(MOTOR_PIN_P, 1);
        sleep_ms(10);
        gpio_put(MOTOR_PIN_P, 0);
        gpio_put(MOTOR_PIN_B, 1);
        sleep_ms(10);
        gpio_put(MOTOR_PIN_B, 0);
        gpio_put(MOTOR_PIN_O, 1);
        sleep_ms(10);
        gpio_put(MOTOR_PIN_O, 0);
        gpio_put(MOTOR_PIN_Y, 1);
        sleep_ms(10);
        gpio_put(MOTOR_PIN_Y, 0);
    }
}

void play_acertou(){
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/880);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/880);
    }
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/440);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/440);
    }    
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/220);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/220);
    }
}

void play_errou(){
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/220);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/220);
    }
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/440);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/440);
    }    
    for(int i = 0; i < 50; i++){
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500000/880);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500000/880);
    }
}

void tocando_sequencia_nova(int sequencia[], int leds[], int btns[]){
    int indice = rand() % 4;
    sequencia[0] += 1;
    sequencia[sequencia[0]] = btns[indice];
    for(int i = 1; i < sequencia[0]; i++){
        gpio_put(leds[indice], 1);
        play_sound(sequencia[i], indice);
        gpio_put(leds[indice], 0);
    }
}

int checa_sequencia(int botao_certo, int botao_apertado){
    if(botao_apertado == botao_certo){
        play_acertou();
        return 1;
    } else {
        play_errou();
        return 0;
    }
}

int main() {
    stdio_init_all();

    gpio_init(MOTOR_PIN_P);
    gpio_set_dir(MOTOR_PIN_P, GPIO_OUT);
    gpio_init(MOTOR_PIN_B);
    gpio_set_dir(MOTOR_PIN_B, GPIO_OUT);
    gpio_init(MOTOR_PIN_O);
    gpio_set_dir(MOTOR_PIN_O, GPIO_OUT);
    gpio_init(MOTOR_PIN_Y);
    gpio_set_dir(MOTOR_PIN_Y, GPIO_OUT);

    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);
    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y, GPIO_OUT);
    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_B);
    gpio_set_dir(BTN_PIN_B, GPIO_IN);
    gpio_pull_up(BTN_PIN_B);

    gpio_init(BTN_PIN_Y);
    gpio_set_dir(BTN_PIN_Y, GPIO_IN);
    gpio_pull_up(BTN_PIN_Y);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_PIN_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_Y, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

    int leds[4] = {LED_PIN_B, LED_PIN_G, LED_PIN_R, LED_PIN_Y};
    int btns[4] = {BTN_PIN_B, BTN_PIN_G, BTN_PIN_R, BTN_PIN_Y};
    int sequencia[100000] = {1}; // obs: primeiro termo de sequencia eh o tamanho do proprio array
    int botao_apertado;
    int acertou = 1;

    while (true) {
        if(acertou){
            acertou = 0;
            tocando_sequencia_nova(sequencia, leds, btns);
            for(int i = 1; i < sequencia[0]; i++){
                if(btn_b_state){
                    botao_apertado = BTN_PIN_B;
                    btn_b_state = 0;
                } else if(btn_g_state){
                    botao_apertado = BTN_PIN_G;
                    btn_g_state = 0;
                } else if(btn_r_state){
                    botao_apertado = BTN_PIN_R;
                    btn_r_state = 0;
                } else if(btn_y_state){
                    botao_apertado = BTN_PIN_Y;
                    btn_y_state = 0;
                } else {
                    botao_apertado = 10;
                }
                if(botao_apertado != 10){
                    acertou = checa_sequencia(sequencia[i], botao_apertado);
                }
            }
        } else {
            main();
        }
    }
}