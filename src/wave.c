/* Módulo 2 */
#include "wave.h"
#include "audio_common.h"
#include <math.h>
#include <stddef.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

al_status al_wave_sine(float *buffer, size_t n, double freq, double amp,
                       double sample_rate) {
  // validacao
  if (buffer == NULL)
    return AL_ERR_NULL_ARG;

  // verificacao invertida evita problema com NaN
  if (!(freq > 0) || !(freq < sample_rate / 2) || !(amp >= 0) || !(amp <= 1) ||
      !(sample_rate > 0))
    return AL_ERR_INVALID_ARG;

  // logica central da geracao da onda
  double phase_increase = freq / sample_rate; // tamanho do passo de cada fase
  double phase = 0.0;                         // posição inicial
  
  for (size_t i = 0; i < n; i++) {
    buffer[i] = (float) (amp * sin(2.0 * PI * phase));
    phase += phase_increase;

    if(phase >= 1.0) phase -= 1.0;
  }
  
  return AL_SUCCESS;
}

al_status al_wave_square(float *buffer, size_t n, double freq, double amp,
                         double sample_rate) {
  // validacao
  if (buffer == NULL)
    return AL_ERR_NULL_ARG;

  // verificacao invertida evita problema com NaN
  if (!(freq > 0) || !(freq < sample_rate / 2) || !(amp >= 0) || !(amp <= 1) ||
      !(sample_rate > 0))
    return AL_ERR_INVALID_ARG;

  // logica central da geracao da onda
  double phase_increase = freq / sample_rate; // tamanho do passo de cada fase
  double phase = 0.0;                         // posição inicial
  
  for (size_t i = 0; i < n; i++) {
    buffer[i] = amp * ((phase < 0.5) ? 1.0 : -1.0);
    phase += phase_increase;

    if(phase >= 1.0) phase -= 1.0;
  }  
  
  return AL_SUCCESS;
}

al_status al_wave_saw(float *buffer, size_t n, double freq, double amp,
                      double sample_rate) {
  // validacao
  if (buffer == NULL)
    return AL_ERR_NULL_ARG;

  // verificacao invertida evita problema com NaN
  if (!(freq > 0) || !(freq < sample_rate / 2) || !(amp >= 0) || !(amp <= 1) ||
      !(sample_rate > 0))
    return AL_ERR_INVALID_ARG;

  // logica central da geracao da onda
  double phase_increase = freq / sample_rate; // tamanho do passo de cada fase
  double phase = 0.0;                         // posição inicial
  
  for (size_t i = 0; i < n; i++) {
    buffer[i] = (float) (amp * (2.0 * phase - 1.0));
    phase += phase_increase;

    if(phase >= 1.0) phase -= 1.0;
  }
  
  return AL_SUCCESS;
}

al_status al_wave_triangle(float *buffer, size_t n, double freq, double amp,
                           double sample_rate) {
  // validacao
  if (buffer == NULL)
    return AL_ERR_NULL_ARG;

  // verificacao invertida evita problema com NaN
  if (!(freq > 0) || !(freq < sample_rate / 2) || !(amp >= 0) || !(amp <= 1) ||
      !(sample_rate > 0))
    return AL_ERR_INVALID_ARG;

  // logica central da geracao da onda
  double phase_increase = freq / sample_rate; // tamanho do passo de cada fase
  double phase = 0.0;                         // posição inicial
  
  for (size_t i = 0; i < n; i++) {
    buffer[i] = (float) (amp * (4.0 * fabs(phase - 0.5) - 1.0));
    phase += phase_increase;

    if(phase >= 1.0) phase -= 1.0;
  }
  
  return AL_SUCCESS;
}
