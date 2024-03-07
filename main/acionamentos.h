#ifndef ACIONAMENTOS_H
#define ACIONAMENTOS_H

#include <stdbool.h>

// Declaração dos pinos dos botões e LEDs como externos
extern const int BTN_B;
extern const int BTN_G;
extern const int BTN_R;
extern const int BTN_Y;
extern const int BTN_START;

extern const int BUZZER;

extern const int LED_B;
extern const int LED_G;
extern const int LED_R;

// Declaração das flags para os botões como externas
extern volatile bool PRESSED_B;
extern volatile bool PRESSED_G;
extern volatile bool PRESSED_R;
extern volatile bool PRESSED_Y;
extern volatile int PRESSED_START;

void buzz(char cor, int tempo, int BUZZER);
void pisca_led(int cor, int t_delay, int LED_AZUL, int LED_VERMELHO, int LED_VERDE);

#endif 