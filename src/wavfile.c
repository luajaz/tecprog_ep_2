/* Módulo 4 */
#include "wavfile.h"
#include "audio_common.h"
#include <math.h>
#include <stdio.h>

// funcoes auxiliares
static void put_tag(uint8_t* p, const char* tag) {
  for (size_t i = 0; i < 4; i++) {
    p[i] = (uint8_t) tag[i];
  }
}

static void put_u16(uint8_t *p, uint16_t v) {
  p[0] = v & 0xFF;
  p[1] = (v >> 8) & 0xFF;
}

static void put_u32(uint8_t *p, uint32_t v) {
  p[0] = v & 0xFF;
  p[1] = (v >> 8) & 0xFF;
  p[2] = (v >> 16) & 0xFF;
  p[3] = (v >> 24) & 0xFF;
}

al_status al_wav_write(const char *file_name, const float *buffer, size_t n,
                       uint32_t sample_rate) {
  // validacoes
  if (file_name == NULL || buffer == NULL)
    return AL_ERR_NULL_ARG;
  if (sample_rate == 0 || sample_rate > UINT32_MAX / 2)
    return AL_ERR_INVALID_ARG;
  if (n > (UINT32_MAX - 36) / 2)
    return AL_ERR_INVALID_ARG;

  // tamanho da amostra
  uint32_t data_size = (uint32_t)(n*2);

  // cabecalho de 44 bytes
  uint8_t header[44];
  put_tag(header + 0, "RIFF");
  put_u32(header + 4, 36 + data_size);
  put_tag(header + 8, "WAVE");
  put_tag(header + 12, "fmt ");
  put_u32(header + 16, 16);
  put_u16(header + 20, 1);
  put_u16(header + 22, 1);
  put_u32(header + 24, sample_rate);
  put_u32(header + 28, sample_rate * 2);
  put_u16(header + 32, 2);
  put_u16(header + 34, 16);
  put_tag(header + 36, "data");
  put_u32(header + 40, data_size);

  
  FILE *f = fopen(file_name, "wb");
  if (f == NULL) return AL_ERR_IO;
 
  if (fwrite(header, 1, 44, f) != 44) {
    fclose(f);
    return AL_ERR_IO;
  }
 
  for (size_t i = 0; i < n; i++) {
    float x = buffer[i];
 
    // limitando a amostra em [-1, 1]
    if (!(x >= -1.0f)) x = -1.0f;
    if (x > 1.0f)      x = 1.0f;
 
    int16_t sample = (int16_t)lrintf(x * 32767.0f);
    uint16_t bits = (uint16_t)sample;
 
    if (fputc(bits & 0xFF, f) == EOF || fputc(bits >> 8, f) == EOF) {
      fclose(f);
      return AL_ERR_IO;
    }
  }
 
  if (fclose(f) != 0) return AL_ERR_IO;
  
  return AL_SUCCESS;
}
