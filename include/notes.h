/* Módulo 1 */
#ifndef AUDIO_NOTES_H
#define AUDIO_NOTES_H

#include "audio_common.h"
#include <stddef.h>
#include <stdint.h>

// Maior tamanho possível de escala
#define AL_SCALE_MAX_LEN 13

typedef enum {
  AL_MAJOR = 0,
  AL_MINOR = 1,
  AL_MAJOR_PENTATONIC = 2,
  AL_MINOR_PENTATONIC = 3,
  AL_CHROMATIC = 4
} al_scale_type;

/*
 * Converte uma nota MIDI para frequência em Hz
 *
 * Entrada:
 * midi_note: uma nota MIDI, um valor entre 0 e 127, onde cada valor
 * representa uma nota
 *
 * hz: ponteiro double usado para o retorno da função
 *
 * Retorno:
 * a nota recebida convertida para sua frequência é retornada no
 * ponteiro hz de saída recebido na entrada
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * midi_note > 127 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * hz == NULL      -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro hz = 0, se hz != NULL
 *
 */
al_status al_midi_to_hz(uint8_t midi_note, double* hz);

/*
 * Calcula a distância, em semitons, entre duas notas
 *
 * Entrada:
 * midi_note_a; midi_note_b: duas notas MIDI, valores entre 0 e 127, onde cada
 * valor representa uma nota, a nota de origem é midi_note_a
 *
 * interval: ponteiro int usado para o retorno da função
 *
 * Retorno:
 * um valor inteiro retornado em interval, que representa o intervalo entre as
 * duas notas
 * valores positivos indicam um intervalo ascendente, enquanto valores negativos
 * indicam um intervalo descendente
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * midi_note_a ou midi_note_b > 127 -> Argumento inválido (AL_ERR_INVALID_ARG)
 * interval == NULL                 -> Argumento nulo     (AL_ERR_NULL_ARG)
 * 
 * em caso de erro interval = 0, se interval != NULL
 *
 */
al_status al_interval_semitones(uint8_t midi_note_a, uint8_t midi_note_b, int* interval);

/*
 * Calcula a razão de frequência de um intervalo em semitons
 *
 * Entrada:
 * interval: um intervalo em semitons
 *
 * Retorno:
 * um valor double que representa a mudança em frequência do intervalo
 *
 */
double al_interval_ratio(int interval);

/*
 * Gera uma escala do tipo escolhido num vetor, incluindo a nota raiz e oitava final,
 * com as notas em ordem crescente
 * os tipos possíveis são: maior(8 notas), menor(8 notas), pentatônica maior(6 notas),
 * pentatônica menor(6 notas), cromática(13 notas)
 *
 * Entrada:
 * midi_root: nota MIDI, valor entre 0 e 127, que representa a nota raiz da
 * escala
 * type: tipo da escala a ser gerada
 *
 * scale_out; out_len: ponteiros usados para o retorno da função
 * scale_out deve ter capacidade de pelo menos AL_SCALE_MAX_LEN
 *
 * Retorno:
 * a escala gerada retornada em scale_out, e a quantidade de notas geradas na
 * escala em out_len
 *
 * al_status retorna se a função foi bem sucedida ou ocorreu um erro
 *
 * Erros:
 * midi_root > 127                       -> Argumento inválido (AL_ERR_INVALID_ARG)
 * type != dos tipos disponíveis no enum -> Argumento inválido (AL_ERR_INVALID_ARG)
 * escala passando de 127                -> Argumento inválido (AL_ERR_INVALID_ARG)
 * scale_out ou out_len == NULL          -> Argumento nulo     (AL_ERR_NULL_ARG)
 *
 * em caso de erro out_len = 0, se out_len != NULL, e nada é escrito em scale_out
 * 
 */
al_status al_scale_generate(uint8_t midi_root, al_scale_type type, uint8_t* scale_out, size_t* out_len);

#endif
