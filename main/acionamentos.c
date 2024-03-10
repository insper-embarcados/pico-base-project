#include "acionamentos.h"
#include <stdio.h>
#include <unistd.h> 
#include "pico/stdlib.h"
#include <pico/time.h> 

// Definição das constantes
const int BTN_B = 18;
const int BTN_G = 19;
const int BTN_R = 20;
const int BTN_Y = 17;
const int BTN_START = 21;

const int BUZZER = 14;
const int LED_B = 15;
const int LED_G = 16;
const int LED_R = 26;



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


void pisca_led(char cor, int t_delay, int LED_AZUL, int LED_VERMELHO, int LED_VERDE, int BUZZER){
    //O delay de quanto tempo o led ficará aceso vem do buzzer
    if (cor == 'B'){
        sleep_ms(t_delay);
        gpio_put(LED_AZUL, 1);
        buzz('B', t_delay, BUZZER);
        gpio_put(LED_AZUL, 0);
    }
    else if (cor == 'G'){
        gpio_put(LED_VERDE, 1);
        buzz('G', t_delay, BUZZER);
        gpio_put(LED_VERDE, 0);
        sleep_ms(t_delay);
    }
    else if (cor == 'R'){
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 1);
        buzz('R', t_delay, BUZZER);
        gpio_put(LED_VERMELHO, 0);
    }
    else if (cor == 'Y'){
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        buzz('Y', t_delay, BUZZER);
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 0);
    }
    else if (cor == 'F'){ // F de fail
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 1);
        buzz('F', t_delay, BUZZER);
        gpio_put(LED_VERMELHO, 0);
    }
}