#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "acionamentos.h"
#include "game_features.h"

// Callbacks dos botões
void btn_callback_b(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        PRESSED_B = true;
    }
}

void btn_callback_g(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        PRESSED_G = true;
    }
}

void btn_callback_r(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        PRESSED_R = true;
    }
}

void btn_callback_y(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        PRESSED_Y = true;
    }
}

void btn_callback_start(uint gpio, uint32_t events) {
    if (events == 0x4) { // fall edge
        PRESSED_START = 1;
    }
}


int main() {
    //Inicializa perifericos ____________________________________________________________________________________________________

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
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &btn_callback_b);
    gpio_set_irq_enabled_with_callback(BTN_G, GPIO_IRQ_EDGE_FALL, true, &btn_callback_g);
    gpio_set_irq_enabled_with_callback(BTN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback_r);
    gpio_set_irq_enabled_with_callback(BTN_Y, GPIO_IRQ_EDGE_FALL, true, &btn_callback_y);
    gpio_set_irq_enabled_with_callback(BTN_START, GPIO_IRQ_EDGE_FALL, true, &btn_callback_start);

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

    uint64_t tempo_inicial = to_us_since_boot(get_absolute_time());


    while (true) {
        //Define Parâmetros iniciais do jogo ____________________________________________________________________________________________________
        int rodada = 0; //rodada

        int tamanho_sequencia = 100000; //tamanho da sequência (grande o suficiente para nenhum ser humano conseguir ganhar o jogo)
        char sequencia[tamanho_sequencia + 1]; // Definindo a lista com a sequencia de cores (+1 para o caractere nulo)
//Tempo inicial do jogo --> Seed para a geração de números aleatórios
        geraSequencia(sequencia, tamanho_sequencia, tempo_inicial); //Gera a sequência de cores aleatórias

        int inGame = 1; //Flag para começar o jogo

        while (inGame) {
            if (PRESSED_START) { //So começa o jogo quando o botão de start é pressionado
                char sequenciaRodada[rodada]; //A sequencia da rodada é a sequencia até a rodada atual
                //char sequenciaJogador[rodada+1]; //A sequencia do jogador é a sequencia até a rodada atual
                //sequenciaJogador[rodada] = '\0'; //Adiciona o caractere nulo no final da sequencia do jogador

                int t_delay = calcularTempo(rodada); //Calcula o tempo de delay para mostrar a sequencia

                mostrarSequencia(sequencia, rodada, sequenciaRodada, t_delay, BUZZER, LED_R, LED_G, LED_B); //O tamanho da sequencia é a rodada, de forma que a sequencia é mostrada até a rodada atual

                //Aguarda o jogador apertar as cores
                for (int i = 0; i < rodada; i++) {
                    char cor = sequenciaRodada[i];
                    while (true) {
                        if (PRESSED_B && cor == 'B') {
                            //sequenciaJogador[i] = 'B';
                            PRESSED_B = false;
                            break;
                        }
                        if (PRESSED_G && cor == 'G') {
                            //sequenciaJogador[i] = 'G';
                            PRESSED_G = false;
                            break;
                        }
                        if (PRESSED_R && cor == 'R') {
                            //sequenciaJogador[i] = 'R';
                            PRESSED_R = false;
                            break;
                        }
                        if (PRESSED_Y && cor == 'Y') {
                            //sequenciaJogador[i] = 'Y';
                            PRESSED_Y = false;
                            break;
                        }
                        else {
                            inGame = 0; //Se o jogador errar a sequencia, o jogo acaba
                        }
                    }
                }        
                rodada++; //Aumenta a rodada
            }


        }

        //Fim de jogo
        printf("Fim de jogo! Você chegou até a rodada %d", rodada);
        mostrarAcertos(rodada, BUZZER, LED_R, LED_G, LED_B);
        PRESSED_START = 0; //Reseta o botão de start

        return 0;
    }
}
