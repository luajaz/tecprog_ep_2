/* Módulo 2 */
#ifndef AUDIO_WAVE_H
#define AUDIO_WAVE_H

#include "audio_common.h"
#include <stddef.h>

/*
 * Gera uma onda com formato senoidal no buffer, a onda começa em 0 e sobe
 *
 * Entrada:
 * n: quantidade de amostras a ser geradas
 * freq: frequencia, em Hz, da onda gerada
 * amp: amplitude de pico, a altura da onda, valor entre 0.0 e 1.0
 * sample_rate: taxa de amostragem
 *
 * buffer: ponteiro float usado para o retorno da função, onde a onda é escrita,
 * deve ter capacidade de pelo menos n
 *
 * Retorno:
 * n amostras entre -amp e amp geradas no ponteiro de saida buffer, com o
 * conteúdo prévio de buffer sendo sobrescrito
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * freq <= 0 ou >= sample_rate / 2 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * amp < 0 ou > 1                  -> Argumento inválido (AL_ERR_INVALID_ARG)
 * sample_rate <= 0                -> Argumento inválido (AL_ERR_INVALID_ARG)
 * buffer == NULL                  -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro nada é escrito em buffer
 *
 */
al_status al_wave_sine(float *buffer, size_t n, double freq, double amp,
                       double sample_rate);

/*
 * Gera uma onda com formato quadrado no buffer, a onda começa em +amp
 *
 * Entrada:
 * n: quantidade de amostras a ser geradas
 * freq: frequencia, em Hz, da onda gerada
 * amp: amplitude de pico, a altura da onda, valor entre 0.0 e 1.0
 * sample_rate: taxa de amostragem
 *
 * buffer: ponteiro float usado para o retorno da função, onde a onda é escrita,
 * deve ter capacidade de pelo menos n
 *
 * Retorno:
 * n amostras entre -amp e amp geradas no ponteiro de saida buffer, com o
 * conteúdo prévio de buffer sendo sobrescrito
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * freq <= 0 ou >= sample_rate / 2 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * amp < 0 ou > 1                  -> Argumento inválido (AL_ERR_INVALID_ARG)
 * sample_rate <= 0                -> Argumento inválido (AL_ERR_INVALID_ARG)
 * buffer == NULL                  -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro nada é escrito em buffer
 *
 */
al_status al_wave_square(float *buffer, size_t n, double freq, double amp,
                         double sample_rate);

/*
 * Gera uma onda com formato dente de serra no buffer, a onda começa em -amp e sobe
 *
 * Entrada:
 * n: quantidade de amostras a ser geradas
 * freq: frequencia, em Hz, da onda gerada
 * amp: amplitude de pico, a altura da onda, valor entre 0.0 e 1.0
 * sample_rate: taxa de amostragem
 *
 * buffer: ponteiro float usado para o retorno da função, onde a onda é escrita,
 * deve ter capacidade de pelo menos n
 *
 * Retorno:
 * n amostras entre -amp e amp geradas no ponteiro de saida buffer, com o
 * conteúdo prévio de buffer sendo sobrescrito
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * freq <= 0 ou >= sample_rate / 2 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * amp < 0 ou > 1                  -> Argumento inválido (AL_ERR_INVALID_ARG)
 * sample_rate <= 0                -> Argumento inválido (AL_ERR_INVALID_ARG)
 * buffer == NULL                  -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro nada é escrito em buffer
 *
 */
al_status al_wave_saw(float *buffer, size_t n, double freq, double amp,
                      double sample_rate);
/*
 * Gera uma onda com formato triangular no buffer, a onda começa em +amp e desce
 *
 * Entrada:
 * n: quantidade de amostras a ser geradas
 * freq: frequencia, em Hz, da onda gerada
 * amp: amplitude de pico, a altura da onda, valor entre 0.0 e 1.0
 * sample_rate: taxa de amostragem
 *
 * buffer: ponteiro float usado para o retorno da função, onde a onda é escrita,
 * deve ter capacidade de pelo menos n
 *
 * Retorno:
 * n amostras entre -amp e amp geradas no ponteiro de saida buffer, com o
 * conteúdo prévio de buffer sendo sobrescrito
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * freq <= 0 ou >= sample_rate / 2 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * amp < 0 ou > 1                  -> Argumento inválido (AL_ERR_INVALID_ARG)
 * sample_rate <= 0                -> Argumento inválido (AL_ERR_INVALID_ARG)
 * buffer == NULL                  -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro nada é escrito em buffer
 *
 */
al_status al_wave_triangle(float *buffer, size_t n, double freq, double amp,
                           double sample_rate);

#endif
