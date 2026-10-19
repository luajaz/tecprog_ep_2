/* Módulo 3 */
#ifndef AUDIO_WAVE_H
#define AUDIO_WAVE_H

#include "audio_common.h"
#include <stddef.h>

/*
 * Multiplica cada amostra do buffer pelo ganho.
 *
 * Entrada:
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira)
 * gain: fator de amplificação a ser aplicado no buffer. Um float qualquer.
 * inversão de fase.
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
 * n < 0          -> Argumento inválido (AL_ERR_INVALID_ARG) 
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_gain(float *buffer, size_t n, float gain);

/*
 * Reduz a amplitude de amostras acima de um certo limite para esse limite.
 *
 * Entrada:
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira)
 * threshold: limite de amplitude das amostras. Um float não-negativo.
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
 * n < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 * threshold < 0  -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_clip(float *buffer, size_t n, float threshold);

/*
 * Soma as primeiras min(n_1, n_2) amostras do buffer_1 às min(n_1, n_2) primeiras amostras de buffer_2.
 *
 * Entrada:
 * n_1: quantidade máxima de amostras de buffer_1 que serão lidas.
 * n_2: quantidade máxima de amostras de buffer_2 que serão sobrescritas.
 * buffer_1: ponteiro de floats a ser apenas lido para soma no buffer_2
 * buffer_2: ponteiro de floats a ser sobrescrito com a soma com amostras de buffer_1.
 *
 * Retorno:
 * min(n_1, n_2) amostras de buffer_2 sobrescrita com a soma com as primeiras min(n_1, n_2) amostras
 * de buffer_1.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer_1 == NULL -> Argumento nulo (AL_ERR_NULL_ARG)
 * buffer_2 == NULL -> Argumento nulo (AL_ERR_NULL_ARG)
 * n_1 < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 * n_2 < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_mix(float *buffer_1, size_t n_1, float *buffer_2, size_t n_2);

/*
 * Retorna a maior amplitude de amostra do buffer, ou seja, a amplitude do pico.
 *
 * Entrada:
 * n: quantidade de amostras do buffer que serão lidas.
 * buffer: ponteiro float que será apenas lido e cuja amplitude do pico será retornada.
 *
 * Retorno:
 * float contendo a amplitude (positiva) do maior pico do buffer. Um float não-negativo.
 * se n == 0, 0.0f é retornado
 *
 * Erros:
 * buffer == NULL -> return 0.0f
 * n < 0          -> return 0.0f
 *
 */
float al_buffer_peak(float *buffer, size_t n);

/*
 * Copia as primeiras min(n_1, n_2) amostras de buffer_1 em buffer_2.
 *
 * Entrada:
 * n_1: quantidade máxima de amostras de buffer_1 que serão lidas.
 * n_2: quantidade máxima de amostras de buffer_2 que serão sobrescritas.
 * buffer_1: ponteiro de floats a ser lido para cópia no buffer_2
 * buffer_2: ponteiro de floats a ser sobrescrito com cópia do buffer_1.
 *
 * Retorno:
 * min(n_1, n_2) amostras sobrescritas em buffer_2 com as primeiras min(n_1, n_2) amostras
 * de buffer_1.
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer_1 == NULL -> Argumento nulo (AL_ERR_NULL_ARG)
 * buffer_2 == NULL -> Argumento nulo (AL_ERR_NULL_ARG)
 * n_1 < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 * n_2 < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_buffer_copy(float *buffer_1, size_t n_1, float *buffer_2, size_t n_2);

/*
 * Translada as amostras do buffer para o futuro.
 *
 * Entrada:
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira).
 * disp: quantidade de amostras em que o buffer será transladado para o futuro.
 * buffer: ponteiro float que será modificado, tendo suas amostras transladadas para o futuro.
 *
 * Retorno:
 * n amostras sobrescritas no buffer com todas as amostras transladadas para o futuro por disp
 * amostras, e as anteriores sobrescritas com 0.0f.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo (AL_ERR_NULL_ARG) 
 * n < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_buffer_delay(float *buffer, size_t n, size_t disp);

/*
 * Translada as amostras do buffer para o passado.
 *
 * Entrada:
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira).
 * disp: quantidade de amostras em que o buffer será transladado para o passado.
 * buffer: ponteiro float que será modificado, tendo suas amostras transladadas para o passado.
 *
 * Retorno:
 * n amostras sobrescritas no buffer com todas as amostras transladadas para o passado por disp
 * amostras, e as próximas sobrescritas com 0.0f.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo (AL_ERR_NULL_ARG) 
 * n < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_buffer_advance(float *buffer, size_t n, size_t disp);

/*
 * Soma o buffer a si mesmo diversas vezes, transladado para o futuro e com volume reduzido,
 * até que o pico da onda a ser adicionada seja menor que um limiar ou as ondas não intersectem.
 *
 * Entrada:
 * 
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira). Um inteiro não-negativo.
 * delay_samples: número de amostras entre repetições do buffer. Um inteiro não-negativo.
 * decay: ganho a ser aplicado em cada repetição. Note que valores negativos formam uma cauda, que é o efeito usual. Um float qualquer.
 * peak_threshold: ecos com pico abaixo dessa amplitude serão silenciados. 
 * buffer: ponteiro float que será modificado, sendo somado a cópias de si mesmo transladadas e com volume alterado.
 *
 * Retorno:
 * 
 * n amostras sobrescritas no buffer com cópias do buffer adicionadas a cada "delay_samples" amostras, com um ganho "decay" aplicado
 * sucessivamente sobre cada uma.
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL -> Argumento nulo     (AL_ERR_NULL_ARG) 
 * n < 0          -> Argumento inválido (AL_ERR_INVALID_ARG)
 * delay < 0      -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 * 
 */
al_status al_fx_delay(float *buffer, size_t n, ptrdiff_t delay_samples, float decay, float peak_threshold);

/* Altera as primeiras n amostras do buffer para que o pico da onda tenha amplitude peak. 
 * 
 * Entrada:
 * 
 * n: quantidade de amostras do buffer que serão modificados (a partir da primeira). Um inteiro não-negativo.
 * peak: o pico do buffer após processamento.
 * 
 * buffer: ponteiro float que será modificado, tendo todas as suas amostras multiplicadas para que tenha pico "peak".
 * Não deve ser todo nulo.
 *
 * Retorno:
 * n amostras sobrescritas no buffer com um amplificação ou redução de amplitude das amostras, de modo que
 * seu pico seja precisamente "peak".
 * se n == 0 nada é escrito no buffer, e a função retorna sucesso
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * buffer == NULL                   -> Argumento nulo     (AL_ERR_NULL_ARG)
 * n < 0                            -> Argumento inválido (AL_ERR_INVALID_ARG)
 * buffer[i] == 0 sempre            -> Argumento inválido (AL_ERR_INVALID_ARG)
 * peak < 0                         -> Argumento inválido (AL_ERR_INVALID_ARG)
 * pico do buffer é NAN ou INFINITY -> Argumento inválido (AL_ERR_INVALID_ARG)
 *
 * em caso de erro nada é escrito em buffer
 *
 */
al_status al_fx_normalize(float *buffer, size_t n, float peak);

#endif
