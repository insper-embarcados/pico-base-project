// Pinos dos botões e LEDs
const int BTN_B = 6;
const int BTN_G = 7;
const int BTN_R = 8;
const int BTN_Y = 9;
const int BTN_START = 20;

const int BUZZER = 19;

const int LED_B = 16;
const int LED_G = 17;
const int LED_R = 18;


// Flags para os botões
volatile bool PRESSED_B = false;
volatile bool PRESSED_G = false;
volatile bool PRESSED_R = false;
volatile bool PRESSED_Y = false;
volatile int PRESSED_START = 0;

void buzz(char cor, int tempo, int BUZZER);
void pisca_led(int cor, int t_delay, int LED_AZUL, int LED_VERMELHO, int LED_VERDE);