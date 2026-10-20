/* Arquivo que agrupa os codigos de status comuns a toda a biblioteca */
#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H

/*
 * Enum que agrupa os status de retorno das funções
 *
 * SUCCESS: sucesso
 * ERR_INVALID_ARG: erro de argumento inválido
<<<<<<< HEAD
 * ERR_NULL_ARG: erro de argumento nulo
 * ERR_MALLOC_FAIL: erro na alocação de memória
 * ERR_IO: erro de input/output
 *
=======
 *    ERR_NULL_ARG: erro de argumento nulo
 * ERR_MALLOC_FAIL: erro de alocação de memória
>>>>>>> 946ab9c7655c8836c468347b03f772a2bf12327d
 */
typedef enum {
  AL_SUCCESS = 0,
  AL_ERR_INVALID_ARG = 1,
  AL_ERR_NULL_ARG = 2,
  AL_ERR_MALLOC_FAIL = 3,
  AL_ERR_IO = 4
} al_status;

  #endif
