#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "acionamentos.h"
#include "game_features.h"

// Definição das variáveis globais
volatile int PRESSED_B = 0;
volatile int PRESSED_G = 0;
volatile int PRESSED_R = 0;
volatile int PRESSED_Y = 0;
volatile char PRESSED_COLOR = 'S';
volatile int PRESSED_START = 0;

// Callbacks dos botões
#define DEBOUNCE_MS 200 // Atraso de debounce de 200 milissegundos

// Variável para armazenar a última vez que um botão foi pressionado
uint64_t last_press_time = 0;

// Callbacks dos botões
void btn_callback(uint gpio, uint32_t events) {
    uint64_t now = to_us_since_boot(get_absolute_time());
    if (events == 0x4 && (now - last_press_time > DEBOUNCE_MS * 1000)) { // fall edge e debounce
        last_press_time = now;
        if (gpio == BTN_B){
            // printf("Pressed B \n"); //DEBUG
            PRESSED_B = 1;
            PRESSED_COLOR = 'B';
        }
        if (gpio == BTN_G){
            // printf("Pressed G \n"); // DEBUG
            PRESSED_G = 1;
            PRESSED_COLOR = 'G';
        }
        if (gpio == BTN_R){
            // printf("Pressed R \n"); // DEBUG
            PRESSED_R = 1;
            PRESSED_COLOR = 'R';
        }
        if (gpio == BTN_Y){
            // printf("Pressed Y \n"); // DEBUG
            PRESSED_Y = 1;
            PRESSED_COLOR = 'Y';
        }
        if (gpio == BTN_START){
            // printf("Pressed START \n");
            PRESSED_START = 1;
        }
        // printf("PRESSED COLOR = %c\n", PRESSED_COLOR); //DEBUG
    }
}

int main() {
    //Inicializa perifericos __________________________________

    // Inicializa os botões
    // Botão B
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
    // Botão G
    gpio_init(BTN_G);
    gpio_set_dir(BTN_G, GPIO_IN);
    gpio_pull_up(BTN_G);
    // Botão R
    gpio_init(BTN_R);
    gpio_set_dir(BTN_R, GPIO_IN);
    gpio_pull_up(BTN_R);
    // Botão Y
    gpio_init(BTN_Y);
    gpio_set_dir(BTN_Y, GPIO_IN);
    gpio_pull_up(BTN_Y);
    // Botão Start
    gpio_init(BTN_START);
    gpio_set_dir(BTN_START, GPIO_IN);
    gpio_pull_up(BTN_START);

    // Configura os callbacks dos botões
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled(BTN_G, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_R, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_Y, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BTN_START, GPIO_IRQ_EDGE_FALL, true);

    // Inicializa o buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Inicializa os LEDs
    // LED B
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    // LED G
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    // LED R
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    stdio_init_all();

    while(!PRESSED_START){

    }

    uint64_t tempo_inicial = to_us_since_boot(get_absolute_time());  //Tempo inicial do jogo --> Seed para a geração de números aleatórios


    int loopJogo = 1;
    while (loopJogo) {
        //Define Parâmetros iniciais do jogo __________________________________
        int rodada = 0; //rodada inicial

        int tamanho_sequencia = 100000; //tamanho da sequência (grande o suficiente para nenhum ser humano conseguir ganhar o jogo)
        char sequencia[tamanho_sequencia + 1]; // Definindo a lista com a sequencia de cores (+1 para o caractere nulo)
        geraSequencia(sequencia, tamanho_sequencia, tempo_inicial); //Gera a sequência de cores aleatórias

        int inGame = 1; //Flag para começar o jogo

        while (inGame) {
            if (PRESSED_START) {
                rodada++;// Aumenta a rodada apenas se todas as cores corretas forem pressionadas
                char sequenciaRodada[rodada];
                int t_delay = calcularTempo(rodada);
                mostrarSequencia(sequencia, rodada, sequenciaRodada, t_delay, BUZZER, LED_R, LED_G, LED_B);

                for (int i = 0; i < rodada; i++) {
                    char cor = sequenciaRodada[i];

                    while (!PRESSED_B && !PRESSED_G && !PRESSED_R && !PRESSED_Y) {
                        //Espera o jogador pressionar uma cor
                    }
                    char cor_press = PRESSED_COLOR;
                    pisca_led(cor_press, 200, LED_B, LED_R, LED_G, BUZZER); //Pisca a cor pressionada
                    
                    if (cor_press == cor) {
                    }
                    else if (PRESSED_COLOR != cor && PRESSED_COLOR != 'S') {
                        inGame = 0; // Sai do loop
                        i = rodada; // Sai do loop
                    }
                    // Reseta as flags para a próxima iteração
                    PRESSED_B = 0;
                    PRESSED_G = 0;
                    PRESSED_R = 0;
                    PRESSED_Y = 0;
                    PRESSED_COLOR = 'S';
                            
                }
            }
            
        }

        //Fim de jogo
        printf("Fim de jogo! Você chegou até a rodada %d", rodada);
        mostrarAcertos(rodada-1, BUZZER, LED_R, LED_G, LED_B);
        PRESSED_START = 0; //Reseta o botão de start

    }
    return 0;

}