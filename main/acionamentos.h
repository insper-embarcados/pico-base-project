#include "pico/stdlib.h"
#include "hardware/gpio.h"

void buzz(char cor, int tempo, int BUZZER){ 
    if cor == 'B'{
        int freq = 494;
    }
    else if cor == 'G'{
        int freq = 329;
    }
    else if cor == 'R'{
        int freq = 261;
    }
    else if cor == 'Y'{
        int freq = 392;
    }
    else if cor == 'F'{ // F de fail
        int freq = 800;
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

void pisca_led(int cor, int t_delay, int LED_AZUL, int LED_VERMELHO, int LED_VERDE){
    if cor == 'B'{
        gpio_put(LED_AZUL, 1);
        sleep_ms(t_delay);
        gpio_put(LED_AZUL, 0);
        sleep_ms(t_delay);
    }
    else if cor == 'G'{
        gpio_put(LED_VERDE, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERDE, 0);
        sleep_ms(t_delay);
    }
    else if cor == 'R'{
        gpio_put(LED_VERMELHO, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 0);
        sleep_ms(t_delay);
    }
    else if cor == 'Y'{
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        sleep_ms(t_delay);
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 0);
        sleep_ms(t_delay);
    }
}