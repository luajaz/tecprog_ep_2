/* Aplicação principal */
#include "audio_common.h"
#include "audiolib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NOTE_DURATION 0.4

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
  if (argc < 2) {
    fprintf(stderr, "Uso: <nota1> [nota2 nota3 ...]");
    return 1;
  }

  // valores pre-estabelecidos, tem que fazer ser personalizavel depois
  double sample_rate = 44100.0;
  double amp = 0.5;

  size_t num_notes = (size_t) argc - 1;
  size_t samples_per_note = (size_t)(sample_rate * NOTE_DURATION);
  size_t total_samples = samples_per_note * num_notes;

  al_status st = AL_SUCCESS;

  // vetor das notas e buffer de audio
  uint8_t *midi_notes = malloc(num_notes * sizeof(uint8_t));
  float *buffer = malloc(total_samples * sizeof(float));

  if (buffer == NULL || midi_notes == NULL) {
    free(midi_notes);
    free(buffer);
    fprintf(stderr, "Ocorreu um erro: Erro de alocação de memória\n");
    return 1;
  }

  // Convertendo as notas para midi e guardando em um vetor
  for (size_t i = 1; i <= num_notes; i++) {
    uint8_t midi;
    st = parse_note(argv[i], &midi); 
    if (st != AL_SUCCESS) {
      free(midi_notes);
      free(buffer);
      fprintf(stderr, "Ocorreu um erro na nota %s: %s\n", argv[i], al_status_to_str(st));
      return 1;
    }
    
    midi_notes[i-1] = midi;
  }

  // Sintese de cada nota
  for (size_t i = 0; i < num_notes; i++) {
    float* slice = buffer + (i * samples_per_note);
    double freq = 0.0;
    st = al_midi_to_hz(midi_notes[i], &freq);
    if (st != AL_SUCCESS) {
      free(midi_notes);
      free(buffer);
      fprintf(stderr, "Ocorreu um erro na conversão para Hz: %s\n", al_status_to_str(st));
      return 1;
    }
    // chamando a funcao de seno primeiro, depois tem que dar a opcao de escolher o tipo de onda
    st = al_wave_sine(slice, samples_per_note, freq, amp, sample_rate);
    if (st != AL_SUCCESS) {
      free(midi_notes);
      free(buffer);
      fprintf(stderr, "Ocorreu um erro na sintetização da onda: %s\n", al_status_to_str(st));
      return 1;
    }
  }

  // Escrever o wav
  st = al_wav_write("out.wav", buffer, total_samples, sample_rate);
  if (st != AL_SUCCESS) {
    free(midi_notes);
    free(buffer);
    fprintf(stderr, "Ocorreu um erro na escrita do arquivo: %s\n", al_status_to_str(st));
    return 1;
  }

  free(midi_notes);
  free(buffer);
  return 0;
}

