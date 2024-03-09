#include "game_features.h"
#include <stdlib.h> // Para a função rand()


//Aumento de dificuldade progressivo
int calcularTempo(int rodada) {

    // A cada 5 rodadas, o tempo diminui 200ms e para de diminir em 200ms
    if (rodada <= 5)
        return 1000;
    else if (rodada <= 10)
        return 800;
    else if (rodada <= 15)
        return 600;
    else if (rodada <= 20)
        return 400;
    else if (rodada <= 25)
        return 200;
    else
        return 200;

}

// Gera uma sequência de cores aleatórias
// A funcao recebe um vetor de caracteres e um inteiro
void geraSequencia(char* sequencia, int tamanho_sequencia, uint64_t tempo_inicial) {
    // Vetor de cores
    char cores[4] = {'R', 'G', 'B', 'Y'};
        
    for (int i = 0; i < tamanho_sequencia; i++) {
        // Atribui uma cor aleatória a cada posição do vetor
        #include <stdlib.h> // Include the <stdlib.h> header file for the 'rand' function

        sequencia[i] = cores[rand() % 4];
    }
    // Adiciona o caractere nulo ao final da sequência
    sequencia[tamanho_sequencia] = '\0';

    //Imprime a sequencia gerada -- Debug
    // printf("Sequencia gerada: %s\n", sequencia);
}


// Mostra a quantidade de acertos
void mostrarAcertos(int acertos, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL) {
    // Indica que o jogador errou a sequencia
    buzz('F', 200, BUZZER);
    pisca_led('R', 200, LED_AZUL, LED_VERMELHO, LED_VERDE);

    // Mostra a quantidade de acertos
    for (int i = 0; i <= acertos; i++) {
        //Pisca LED
        pisca_led('B', 500, LED_AZUL, LED_VERMELHO, LED_VERDE);       
    }
}

void mostraCor(char cor, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL, int t_delay){
    //Print
    printf("Cor: %c\n", cor);

    //Pisca LED
    pisca_led(cor, t_delay, LED_AZUL, LED_VERMELHO, LED_VERDE);

    //Toca som
    buzz(cor, t_delay, BUZZER);
}


// Mostra a sequência de cores e define qual vai ser a sequência da rodada
void mostrarSequencia(char* sequencia, int rodada, char* sequenciaRodada, int t_delay, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL) {

    for (int i = 0; i < rodada; i++) {
        char cor = sequencia[i];

        //Adiciona a cor na sequencia da rodada
        sequenciaRodada[i] = cor;

        mostraCor(cor, BUZZER, LED_VERMELHO, LED_VERDE, LED_AZUL, t_delay);
    }
    sequenciaRodada[rodada] = '\0';
}

