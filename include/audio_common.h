/* Arquivo que agrupa os codigos de status comuns a toda a biblioteca */
#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H

/*
 * Enum que agrupa os status de retorno das funções
 *
 *         SUCCESS: sucesso
 * ERR_INVALID_ARG: erro de argumento inválido
 *    ERR_NULL_ARG: erro de argumento nulo
 */
typedef enum {
  AL_SUCCESS = 0,
  AL_ERR_INVALID_ARG = 1,
  AL_ERR_NULL_ARG = 2
} al_status;

  #endif
