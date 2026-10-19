/* Aplicação principal */
#include "audio_common.h"
#include "audiolib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef al_status (*wave_fn)(float *, size_t, double, double, double);

static const char *al_status_to_str(al_status st) {
  switch (st) {
  case AL_SUCCESS:
    return "Sucesso!";
  case AL_ERR_INVALID_ARG:
    return "Erro de argumento inválido!";
  case AL_ERR_NULL_ARG:
    return "Erro de argumento nulo!";
  case AL_ERR_MALLOC_FAIL:
    return "Erro de alocação de memória!";
  case AL_ERR_IO:
    return "Erro de manipulação do arquivo!";
  }
  return "Status desconhecido!";
}

static al_status parse_note(const char *note, uint8_t *midi) {
  if (note == NULL || midi == NULL)
    return AL_ERR_NULL_ARG;
  int n;
  
  // lendo a nota
  switch (note[0]) {
  case 'C':
    n = 0;
    break;
  case 'D':
    n = 2;
    break;
  case 'E':
    n = 4;
    break;
  case 'F':
    n = 5;
    break;
  case 'G':
    n = 7;
    break;
  case 'A':
    n = 9;
    break;
  case 'B':
    n = 11;
    break;
  default:
    return AL_ERR_INVALID_ARG;
  }

  // lendo os acidentes possiveis, sustenido ou bemol
  int i = 1;
  if(note[i] == '#') {
    n++;
    i++;
  } else if (note[i] == 'b') {
    n--;
    i++;
  }

  // lendo a oitava
  int octave = note[i] - '0';
  if (octave < 0 || octave > 9)
    return AL_ERR_INVALID_ARG;
  i++;

  // verificando que nao ha mais caracteres
  if (note[i] != '\0')
    return AL_ERR_INVALID_ARG;

  // convertendo a nota para a nota midi e conferindo que esta no intervalo valido
  int int_midi = 12 * (octave + 1) + n;
  if (int_midi < 0 || int_midi > 127) {
    return AL_ERR_INVALID_ARG;
  }

  *midi = (uint8_t)int_midi;

  return AL_SUCCESS;
}

int main(int argc, char* argv[]) {
  al_status st = AL_SUCCESS;

  // valores padrao
  wave_fn wave = al_wave_sine;
  double amp = 0.5;
  double duration = 0.4;
  long r = 44100;
  const char *out_file = "out.wav";
  int use_gain = 0, use_delay = 0, use_norm = 0, use_clip = 0;
  double gain = 1.0, delay_ms = 0.0, decay = 0.5, norm_peak = 1.0, clip = 1.0;

  // lendo as opcoes, no padrao "-letra valor"
  int i = 1;
  while (i + 1 < argc && argv[i][0] == '-') {
    char opt = argv[i][1];
    const char *val = argv[i + 1];

    if (opt == 'w') {
      if      (strcmp(val, "sine") == 0)     wave = al_wave_sine;
      else if (strcmp(val, "square") == 0)   wave = al_wave_square;
      else if (strcmp(val, "saw") == 0)      wave = al_wave_saw;
      else if (strcmp(val, "triangle") == 0) wave = al_wave_triangle;
      else {
        fprintf(stderr, "Ocorreu um erro: Onda desconhecida: %s\n", val);
        return 1;
      }
    }
    else if (opt == 'a') amp = atof(val);
    else if (opt == 'r') r = atol(val);
    else if (opt == 't') duration = atof(val);
    else if (opt == 'o') out_file = val;
    else if (opt == 'g') { gain = atof(val);      use_gain = 1; }
    else if (opt == 'd') { delay_ms = atof(val);  use_delay = 1; }
    else if (opt == 'e') decay = atof(val);
    else if (opt == 'n') { norm_peak = atof(val); use_norm = 1; }
    else if (opt == 'c') { clip = atof(val);      use_clip = 1; }
    else {
      fprintf(stderr, "Ocorreu um erro: Opcao desconhecida: %s\n", argv[i]);
      return 1;
    }
    i += 2;
  }

  // a partir de i sao as notas
  if (i >= argc) {
    fprintf(stderr, "Uso: %s [opcoes] NOTA [NOTA NOTA ...]\n", argv[0]);
    return 1;
  }

  if(r <= 0 || r > 384000) {
    fprintf(stderr, "Ocorreu um erro: Taxa de amostragem deve ser positiva\n");
    return 1;
  }
  sample_rate = (uint32_t) r;

  if(!(duration > 0)) {
    fprintf(stderr, "Ocorreu um erro: Duração deve ser positiva\n");
    return 1;
  }

  size_t num_notes = (size_t)(argc - i);
  size_t samples_per_note = (size_t)(sample_rate * duration);
  size_t total_samples = samples_per_note * num_notes;

  if(samples_per_note == 0) {
    fprintf(stderr, "Ocorreu um erro: Duração muito curta\n");
    return 1;
  }

  // vetor das notas e buffer de audio
  uint8_t *midi_notes = malloc(num_notes * sizeof(uint8_t));
  float *buffer = malloc(total_samples * sizeof(float));

  if (buffer == NULL || midi_notes == NULL) {
    fprintf(stderr, "Ocorreu um erro: Erro de alocação de memória\n");
    goto cleanup;
  }

  // Convertendo as notas para midi e guardando em um vetor
  for (size_t j = 0; j < num_notes; j++) {
    uint8_t midi;
    st = parse_note(argv[i + j], &midi); 
    if (st != AL_SUCCESS) {
      fprintf(stderr, "Ocorreu um erro na nota %s: %s\n", argv[i + j], al_status_to_str(st));
      goto cleanup;
    }
    
    midi_notes[j] = midi;
  }

  // Sintese de cada nota
  for (size_t j = 0; j < num_notes; j++) {
    float* slice = buffer + (j * samples_per_note);
    double freq = 0.0;
    st = al_midi_to_hz(midi_notes[j], &freq);
    if (st != AL_SUCCESS) {
      fprintf(stderr, "Ocorreu um erro na conversão para Hz: %s\n", al_status_to_str(st));
      goto cleanup;
    }
    st = wave(slice, samples_per_note, freq, amp, sample_rate);
    if (st != AL_SUCCESS) {
      fprintf(stderr, "Ocorreu um erro na sintetização da onda: %s\n", al_status_to_str(st));
      goto cleanup;
    }
  }

  // Escrever o wav
  st = al_wav_write(out_file, buffer, total_samples, sample_rate);
  if (st != AL_SUCCESS) {
    fprintf(stderr, "Ocorreu um erro na escrita do arquivo: %s\n", al_status_to_str(st));
    goto cleanup;
  }

  free(midi_notes);
  free(buffer);
  return 0;

 cleanup:
  free(midi_notes);
  free(buffer);
  return 1;
}

