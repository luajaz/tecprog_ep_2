/* Módulo 3 */
#ifndef AUDIO_WAVE_H
#define AUDIO_WAVE_H

#include "audio_common.h"
#include <stddef.h>

/*
 * Multiplica cada amostra do buffer pelo ganho.
 *
 * Entrada:
 * 
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira)
 * gain: fator de amplificação a ser aplicado no buffer. Um float qualquer.
 * inversão de fase.
 *
 * buffer: ponteiro float que será modificado, multiplicando cada
 * elemento pelo ganho.
 *
 * Retorno:
 * n amostras sobrescritas no buffer multiplicadas pelo fator de amplificação dado
 * pelo parâmetro gain. Note que valores de gain com módulo <1 representam reduções
 * de volume e valores negativos representam inversão de fase.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo (AL_ERR_NULL_ARG) 
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_gain(float *buffer, size_t n, float gain);

/*
 * Reduz a amplitude de amostras acima de um certo limite para esse limite.
 *
 * Entrada:
 * 
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira)
 * threshold: limite de amplitude das amostras. Um float não-negativo.
 *
 * buffer: ponteiro float que será modificado, reduzindo a amplitude de amostras excedentes.
 *
 * Retorno:
 * n amostras sobrescritas no buffer multiplicadas pelo fator de amplificação dado
 * pelo parâmetro gain.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo     (AL_ERR_NULL_ARG) 
 * threshold < 0  -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_clip(float *buffer, size_t n, float threshold);

/* Soma as primeiras min(n_1, n_2) amostras do buffer_2 às min(n_1, n_2) primeiras amostras de buffer_1.
*/
al_status al_fx_mix(float *buffer_1, size_t n_1, float *buffer_2, size_t n_2);

/*
 * Soma o buffer a si mesmo diversas vezes, transladado para o futuro e com volume reduzido,
 * até que o pico da onda a ser adicionada seja nulo ou as ondas não intersectem.
 *
 * Entrada:
 * 
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira). Um inteiro não-negativo.
 * delay: número de amostras entre repetições do buffer. Um inteiro não-negativo.
 * decay: ganho a ser aplicado em cada repetição. Note que valores negativos formam uma cauda, que é o efeito usual.]
 * Um float qualquer.
 *
 * buffer: ponteiro float que será modificado, sendo somado a cópias de si mesmo transladadas e com volume alterado.
 *
 * Retorno:
 * n amostras sobrescritas no buffer com cópias do buffer adicionadas a cada delay amostras, com um ganho decay aplicado
 * sucessivamente sobre cada uma.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo     (AL_ERR_NULL_ARG) 
 * delay < 0      -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_delay(float *buffer, size_t n, float delay, float decay);

/* Altera as primeiras n amostras do buffer para que o pico da onda tenha amplitude peak. 
*/
al_status al_fx_normalize(float *buffer, size_t n, float peak);

#endif