#include "acionamentos.h"
#include <stdio.h>
#include <unistd.h> 
#include "pico/stdlib.h"
#include <pico/time.h> 

// Definição das constantes
const int BTN_B = 6;
const int BTN_G = 7;
const int BTN_R = 8;
const int BTN_Y = 9;
const int BTN_START = 20;

const int BUZZER = 19;
const int LED_B = 16;
const int LED_G = 17;
const int LED_R = 18;

// Definição das variáveis globais
volatile bool PRESSED_B = false;
volatile bool PRESSED_G = false;
volatile bool PRESSED_R = false;
volatile bool PRESSED_Y = false;
volatile int PRESSED_START = 0;

// Implementação das funções buzz e pisca_led
// ...



void buzz(char cor, int tempo, int BUZZER){ 
    int freq;
    if (cor == 'B'){
        freq = 494;
    }
    else if (cor == 'G'){
        freq = 329;
    }
    else if (cor == 'R'){
        freq = 261;
    }
    else if (cor == 'Y'){
        freq = 392;
    }
    else if (cor == 'F'){ // F de fail
        freq = 800;
    }

    int i;
    int tempo_total = (1000000 / (freq * 2)+50);
    int n = tempo * freq / 1000;
    for (i = 0; i < n; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(tempo_total);
        gpio_put(BUZZER, 0);
        sleep_us(tempo_total);
    }
}


void pisca_led(char cor, int t_delay, int LED_AZUL, int LED_VERMELHO, int LED_VERDE){
    if (cor == 'B'){
        gpio_put(LED_AZUL, 1);
        sleep_ms(t_delay);
        gpio_put(LED_AZUL, 0);
        sleep_ms(t_delay);
    }
    else if (cor == 'G'){
        gpio_put(LED_VERDE, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERDE, 0);
        sleep_ms(t_delay);
    }
    else if (cor == 'R'){
        gpio_put(LED_VERMELHO, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 0);
        sleep_ms(t_delay);
    }
    else if (cor == 'Y'){
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 0);
        sleep_ms(t_delay);
    }
}