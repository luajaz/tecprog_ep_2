/* Módulo 1 */
#include "notes.h"
#include "audio_common.h"
#include <math.h>
#include <stddef.h>

typedef struct {
  uint8_t count;
  uint8_t steps[12]; // 12 é maximo de passos possíveis, na maior escala há 13 notas
} scale_def;

static const scale_def SCALES[] = {{7, {2, 2, 1, 2, 2, 2, 1}},
                               {7, {2, 1, 2, 2, 1, 2, 2}},
                               {5, {2, 2, 3, 2, 3}},
                               {5, {3, 2, 2, 3, 2}},
                               {12, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}};

#define N_SCALES (sizeof SCALES / sizeof SCALES[0])

al_status al_midi_to_hz(uint8_t midi_note, double *hz) {
  
  
  if (hz == NULL)
    return AL_ERR_NULL_ARG;

  *hz = 0;

  if (midi_note > 127)
    return AL_ERR_INVALID_ARG;

  *hz = 440.0 * pow(2.0, (midi_note - 69) / 12.0);

  return AL_SUCCESS;
}

al_status al_interval_semitones(uint8_t midi_note_a, uint8_t midi_note_b,
                                int *interval) {
  
  if (interval == NULL)
    return AL_ERR_NULL_ARG;

  *interval = 0;

  if (midi_note_a > 127 || midi_note_b > 127)
    return AL_ERR_INVALID_ARG;

  *interval = (int)midi_note_b - midi_note_a;

  return AL_SUCCESS;
}

al_status al_interval_ratio(int interval, double *ratio) {
  
  if (ratio == NULL)
    return AL_ERR_NULL_ARG;

  *ratio = 0;

  if (interval > 127 || interval < -127)
    return AL_ERR_INVALID_ARG;

  *ratio = pow(2.0, interval / 12.0);

  return AL_SUCCESS;
}

al_status al_scale_generate(uint8_t midi_root, al_scale_type type,
                            uint8_t* scale) {
  if (scale == NULL)
    return AL_ERR_NULL_ARG;

  if (midi_root > 127 || (size_t) type >= N_SCALES)
    return AL_ERR_INVALID_ARG;

  int sum = 0;
  for (size_t i = 0; i < SCALES[type].count; i++) {
    sum += SCALES[type].steps[i];
  }

  if ((int)midi_root + sum > 127)
    return AL_ERR_INVALID_ARG;

  scale[0] = midi_root;
  for (size_t i = 0; i < SCALES[type].count; i++) {
    scale[i+1] = (uint8_t) (scale[i] + SCALES[type].steps[i]);
  }

  return AL_SUCCESS;
}

al_status al_scale_length(al_scale_type type, size_t* len) {
  if (len == NULL)
    return AL_ERR_NULL_ARG;

  *len = 0;

  if ((size_t) type >= N_SCALES)
    return AL_ERR_INVALID_ARG;

  *len = SCALES[type].count + 1;

  return AL_SUCCESS;
}
