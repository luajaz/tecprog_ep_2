/* Módulo 3 */
#include "fx.h"
#include "audio_common.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

al_status al_fx_gain(float *buffer, size_t n, float gain) {
    // validacao
    if (buffer == NULL) return AL_ERR_NULL_ARG;
    if (n < 0)          return AL_ERR_INVALID_ARG;
    if (n == 0)         return AL_SUCCESS;

    for (size_t i=0; i < n; i++)
        buffer[i] *= gain;

    return AL_SUCCESS;
}


al_status al_fx_clip(float *buffer, size_t n, float clip_threshold) {
    // validacao
    if (buffer == NULL)        return AL_ERR_NULL_ARG;
    if (n < 0)                 return AL_ERR_INVALID_ARG;
    if (n == 0)                return AL_SUCCESS;
    if (clip_threshold < 0.0f) return AL_ERR_INVALID_ARG;


    for (size_t i=0; i < n; i++) {
        if (buffer[i] > clip_threshold)
            buffer[i] = clip_threshold;
        
        else if (buffer[i] < -clip_threshold)
            buffer[i] = -clip_threshold;
    }
    return AL_SUCCESS;
}


al_status al_fx_mix(float *buffer_1, size_t n_1, float *buffer_2, size_t n_2) {
    // validacao
    if (buffer_1 == NULL) return AL_ERR_NULL_ARG;
    if (buffer_2 == NULL) return AL_ERR_NULL_ARG;
    if (n_1 < 0)          return AL_ERR_INVALID_ARG;
    if (n_2 < 0)          return AL_ERR_INVALID_ARG;
    if (n_1 == 0)         return AL_SUCCESS;
    if (n_2 == 0)         return AL_SUCCESS;


    size_t n_min;

    if   (n_1 < n_2) n_min = n_1;
    else n_min = n_2;

    for (size_t i = 0; i < n_min; i++)
        buffer_2[i] += buffer_1[i];

    return AL_SUCCESS;
}


float al_buffer_peak(float *buffer, size_t n) {
    // validacao
    if (buffer == NULL) return 0.0f;
    if (n <= 0)         return 0.0f;

    
    float peak = 0.0f;

    for (size_t i = 0; i < n; i++) {
        if ((buffer[i] > peak) || (buffer[i] < -peak))
            peak = fabsf(buffer[i]);
    }

    return peak;
}


al_status al_buffer_copy(float *buffer_1, size_t n_1, float *buffer_2, size_t n_2) {
    // validacao
    if (buffer_1 == NULL) return AL_ERR_NULL_ARG;
    if (buffer_2 == NULL) return AL_ERR_NULL_ARG;
    if (n_1 < 0)          return AL_ERR_INVALID_ARG;
    if (n_2 < 0)          return AL_ERR_INVALID_ARG;
    if (n_1 == 0)         return AL_SUCCESS;
    if (n_2 == 0)         return AL_SUCCESS;
    

    size_t n_min;

    if   (n_1 < n_2) n_min = n_1;
    else n_min = n_2;

    for (size_t i = 0; i < n_min; i++)
        buffer_2[i] = buffer_1[i];

    return AL_SUCCESS;
}


// obs: ptrdiff_t é igual a size_t, mas com sinal
al_status al_buffer_delay(float *buffer, size_t n, size_t disp) {
    // validacao
    if (buffer == NULL) return AL_ERR_NULL_ARG;
    if (n < 0)          return AL_ERR_INVALID_ARG;
    if (n == 0)         return AL_SUCCESS;
    if (disp == 0)      return AL_SUCCESS;


    if (disp >= n) {
        for (size_t i = 0; i < n; i++)
            buffer[i] = 0.0f;

        return AL_SUCCESS;
    }
    else {
        // escrevemos de trás para frente para não modificar o que ainda vamos ler
        for (size_t i = n-1; i >= disp; i--)
            buffer[i] = buffer[i-disp];

        for (size_t  i = 0; i < disp; i++)
            buffer[i] = 0.0f;
    }
    
    return AL_SUCCESS;
}


al_status al_buffer_advance(float *buffer, size_t n, size_t disp) {
    // validacao
    if (buffer == NULL) return AL_ERR_NULL_ARG;
    if (n < 0)          return AL_ERR_INVALID_ARG;
    if (n == 0)         return AL_SUCCESS;
    if (disp == 0)      return AL_SUCCESS;

    
    if (disp >= n) {
        for (size_t i = 0; i < n; i++)
            buffer[i] = 0;

        return AL_SUCCESS;
    }
    else {
        for (size_t i = 0; i < n-disp; i++)
            buffer[i] = buffer[i+disp];
        
        for (size_t  i = n-disp; i < n; i++)
            buffer[i] = 0.0f;
    }
    
    return AL_SUCCESS;
}


// manter um displacement (soma dos delays até aqui). se disp > n (eco vai ficar todo dps do buffer)
// ou disp + n < 0 (eco vai ficar todo antes do buffer), break
al_status al_fx_delay(float *buffer, size_t n, ptrdiff_t delay_samples, float decay, float peak_threshold) {
    // validacao
    if (buffer == NULL)      return AL_ERR_NULL_ARG;
    if (n < 0)               return AL_ERR_INVALID_ARG;
    if (n == 0)              return AL_SUCCESS;
    if (delay_samples == 0)  return AL_ERR_INVALID_ARG;
    if (decay < 0)           return AL_ERR_INVALID_ARG;
    if (n == 0)              return AL_ERR_INVALID_ARG;
    if (peak_threshold < 0)) return AL_ERR_INVALID_ARG;


    float *echo_buffer = malloc(n*sizeof(float));

    if (echo_buffer == NULL) {
        return AL_ERR_MALLOC_FAIL;
    }

    al_buffer_copy(buffer, n, echo_buffer, n);

    float echo_peak = al_buffer_peak(echo_buffer, n);
    ptrdiff_t disp = delay_samples;

    while (echo_peak > peak_threshold) {
        // se não há interseccão entre buffer e eco... 
        if (disp >= (ptrdiff_t)n || disp <= -(ptrdiff_t)n)
            break;

        al_fx_gain(echo_buffer, n, decay);

        if (disp >= 0)
            al_buffer_delay(echo_buffer, n, (size_t)disp);
        else
            al_buffer_advance(echo_buffer, n, (size_t)(-disp));

        al_fx_mix(echo_buffer, n, buffer, n);
        echo_peak *= decay;
        disp += delay_samples;
    }

    free(echo_buffer);
    return AL_SUCCESS;
}


al_status al_fx_normalize(float *buffer, size_t n, float peak) {
    // validacao
    if (buffer == NULL)                 return AL_ERR_NULL_ARG;
    if (n < 0)                          return AL_ERR_INVALID_ARG;
    if (al_buffer_peak(buffer, n) == 0) return AL_ERR_INVALID_ARG;
    if (n == 0)                         return AL_SUCCESS;
    if (peak < 0)                       return AL_ERR_INVALID_ARG;


    float prev_peak = al_buffer_peak(buffer, n);
    
    if (prev_peak == 0)
        return AL_SUCCESS;

    // proteger contra prev_peak = INFINITY ou NAN
    if (!isfinite(prev_peak))
        return AL_ERR_INVALID_ARG;

    al_fx_gain(buffer, n, peak/prev_peak);
    return AL_SUCCESS;
}
