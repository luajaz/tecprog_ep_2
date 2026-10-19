/* Módulo 4 */
#ifndef AUDIO_WAVFILE_H
#define AUDIO_WAVFILE_H

#include "audio_common.h"
#include <stddef.h>
#include <stdint.h>

/*
 * Escreve um arquivo .wav a partir do buffer de audio recebido
 *
 * Entrada:
 * file_name: uma string contendo o nome do arquivo a ser escrito
 * buffer: o buffer de audio contendo as ondas sintetizadas
 * n: total de amostras no buffer
 * sample_rate: a taxa de amostragem do arquivo
 *
 * Retorno:
 * a função escreve o arquivo .wav com base nos dados recebidos, saída é mono,
 * PCM 16 bits 
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * sample_rate == 0 ou sample_rate > UINT32_MAX/2  -> Argumento inválido (AL_ERR_INVALID_ARG)
 * n > (UINT32_MAX-36)/2                           -> Argumento inválido (AL_ERR_INVALID_ARG)
 * file_name == NULL                               -> Argumento nulo     (AL_ERR_NULL_ARG)
 * buffer == NULL                                  -> Argumento nulo     (AL_ERR_NULL_ARG)
 * falha ao manipular o arquivo (AL_ERR_IO)
 * 
 */
al_status al_wav_write(const char* file_name, const float *buffer, size_t n, uint32_t sample_rate);

#endif
