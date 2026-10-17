/* Módulo 3 */
#include "fx.h"
#include "audio_common.h"
#include <math.h>
#include <stddef.h>

al_status al_fx_gain(float *buffer, size_t n, float gain) {
    // validacao
    if (buffer == NULL)
        return AL_ERR_NULL_ARG;

    for (size_t i=0; i < n; i++) {
        buffer[i] *= gain;
    }

    return AL_SUCCESS;
}

al_status al_fx_clip(float *buffer, size_t n, float clip_threshold) {
    // validacao
    if (buffer == NULL)
        return AL_ERR_NULL_ARG;

    if (clip_threshold < 0.0f)
        return AL_ERR_INVALID_ARG;

    for (size_t i=0; i < n; i++) {
        if (buffer[i] > clip_threshold) {
            buffer[i] = clip_threshold;
        }
        else if (buffer[i] < -clip_threshold) {
            buffer[i] = -clip_threshold;
        }
    }

    return AL_SUCCESS;
}