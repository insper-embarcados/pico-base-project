#ifndef GAME_FEATURES_H
#define GAME_FEATURES_H

#include <stdint.h> // Para uint64_t

int calcularTempo(int rodada);
void geraSequencia(char* sequencia, int tamanho_sequencia, uint64_t tempo_inicial);
void mostrarAcertos(int acertos, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL);
void mostraCor(char cor, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL, int t_delay);
void mostrarSequencia(char* sequencia, int rodada, char* sequenciaRodada, int t_delay, int BUZZER, int LED_VERMELHO, int LED_VERDE, int LED_AZUL);

#endif // GAME_FEATURES_H
