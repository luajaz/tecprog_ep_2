#include "audio_common.h"
#include "test_util.h"
#include "notes.h"

// marcador para verificar que nada foi escrito
#define MARKER 255


// funcoes auxiliares para o test_scale_generate

// preenche o array inteiro com o valor marcador
static void mark(uint8_t *b, size_t n) {
  for (size_t i = 0; i < n; i++)
    b[i] = MARKER;
}
 
// confere que as n primeiras posicoes dos dois arrays sao iguais
static bool same(const uint8_t *a, const uint8_t *b, size_t n) {
  for (size_t i = 0; i < n; i++)
    if (a[i] != b[i])
      return false;
  return true;
}

// confere que o array inteiro ainda tem o valor marcador
static bool intact(const uint8_t *b, size_t n) {
  for (size_t i = 0; i < n; i++)
    if (b[i] != MARKER)
      return false;
  return true;
}


test_status test_midi_to_hz(void) {
  test_status st = TEST_SUCCESS;
  double hz;
  
  // normal
  EXPECT(al_midi_to_hz(69, &hz) == AL_SUCCESS);
  EXPECT(double_compare(hz, 440.0, 1e-9));
  
  EXPECT(al_midi_to_hz(81, &hz) == AL_SUCCESS);
  EXPECT(double_compare(hz, 880.0, 1e-9));
  
  EXPECT(al_midi_to_hz(60, &hz) == AL_SUCCESS);
  EXPECT(double_compare(hz, 261.6255653, 1e-3));
  
  
  // limite
  EXPECT(al_midi_to_hz(0, &hz) == AL_SUCCESS);
  EXPECT(double_compare(hz, 8.175798915, 1e-3));

  EXPECT(al_midi_to_hz(127, &hz) == AL_SUCCESS);
  EXPECT(double_compare(hz, 12543.853951, 1e-3));

  // invalido
  hz = -1.0;
  EXPECT(al_midi_to_hz(128, &hz) == AL_ERR_INVALID_ARG);
  EXPECT(double_compare(hz, 0.0, 0.0));

  hz = -1.0;
  EXPECT(al_midi_to_hz(255, &hz) == AL_ERR_INVALID_ARG);
  EXPECT(double_compare(hz, 0.0, 0.0));

  EXPECT(al_midi_to_hz(69, NULL) == AL_ERR_NULL_ARG);
  
  return st;
}


test_status test_interval_semitones(void) {
  test_status st = TEST_SUCCESS;
  int interval;
 
  // normal
  EXPECT(al_interval_semitones(60, 67, &interval) == AL_SUCCESS);
  EXPECT(interval == 7);
 
  EXPECT(al_interval_semitones(67, 60, &interval) == AL_SUCCESS);
  EXPECT(interval == -7);
 
  EXPECT(al_interval_semitones(60, 73, &interval) == AL_SUCCESS);
  EXPECT(interval == 13);
 
  // limite
  EXPECT(al_interval_semitones(60, 60, &interval) == AL_SUCCESS);
  EXPECT(interval == 0);
 
  EXPECT(al_interval_semitones(0, 127, &interval) == AL_SUCCESS);
  EXPECT(interval == 127);
 
  EXPECT(al_interval_semitones(127, 0, &interval) == AL_SUCCESS);
  EXPECT(interval == -127);
 
  // invalido
  interval = 99;
  EXPECT(al_interval_semitones(128, 60, &interval) == AL_ERR_INVALID_ARG);
  EXPECT(interval == 0);
 
  interval = 99;
  EXPECT(al_interval_semitones(60, 128, &interval) == AL_ERR_INVALID_ARG);
  EXPECT(interval == 0);
 
  interval = 99;
  EXPECT(al_interval_semitones(255, 255, &interval) == AL_ERR_INVALID_ARG);
  EXPECT(interval == 0);
 
  EXPECT(al_interval_semitones(60, 67, NULL) == AL_ERR_NULL_ARG);
 
  return st;
}
 
test_status test_interval_ratio(void) {
  test_status st = TEST_SUCCESS;
  double ratio;
 
  // normal
  EXPECT(al_interval_ratio(12, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 2.0, 1e-9));
 
  EXPECT(al_interval_ratio(0, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 1.0, 1e-9));
 
  EXPECT(al_interval_ratio(-12, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 0.5, 1e-9));
 
  EXPECT(al_interval_ratio(7, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 1.4983070768766815, 1e-9)); // quinta temperada
 
  // limite
  EXPECT(al_interval_ratio(127, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 1534.2664467217226, 1e-6));
 
  EXPECT(al_interval_ratio(-127, &ratio) == AL_SUCCESS);
  EXPECT(double_compare(ratio, 0.0006517772725439619, 1e-12));
 
  // invalido
  ratio = -1.0;
  EXPECT(al_interval_ratio(128, &ratio) == AL_ERR_INVALID_ARG);
  EXPECT(double_compare(ratio, 0.0, 0.0));
 
  ratio = -1.0;
  EXPECT(al_interval_ratio(-128, &ratio) == AL_ERR_INVALID_ARG);
  EXPECT(double_compare(ratio, 0.0, 0.0));
 
  EXPECT(al_interval_ratio(12, NULL) == AL_ERR_NULL_ARG);
 
  return st;
}

test_status test_scale_generate(void) {
  test_status st = TEST_SUCCESS;
  uint8_t buf[AL_SCALE_MAX_LEN];
 
  const uint8_t c_major[] = {60, 62, 64, 65, 67, 69, 71, 72};
  const uint8_t a_minor[] = {69, 71, 72, 74, 76, 77, 79, 81};
  const uint8_t major_pent[] = {60, 62, 64, 67, 69, 72};
  const uint8_t minor_pent[] = {60, 63, 65, 67, 70, 72};
  const uint8_t chromatic[] = {60, 61, 62, 63, 64, 65, 66,
                               67, 68, 69, 70, 71, 72};
 
  // normal, um caso por tipo, conferindo a lista inteira e que nada
  // foi escrito depois da ultima nota
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, AL_MAJOR, buf) == AL_SUCCESS);
  EXPECT(same(buf, c_major, sizeof c_major));
  EXPECT(buf[sizeof c_major] == MARKER);
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(69, AL_MINOR, buf) == AL_SUCCESS);
  EXPECT(same(buf, a_minor, sizeof a_minor));
  EXPECT(buf[sizeof a_minor] == MARKER);
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, AL_MAJOR_PENTATONIC, buf) == AL_SUCCESS);
  EXPECT(same(buf, major_pent, sizeof major_pent));
  EXPECT(buf[sizeof major_pent] == MARKER);
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, AL_MINOR_PENTATONIC, buf) == AL_SUCCESS);
  EXPECT(same(buf, minor_pent, sizeof minor_pent));
  EXPECT(buf[sizeof minor_pent] == MARKER);
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, AL_CHROMATIC, buf) == AL_SUCCESS);
  EXPECT(same(buf, chromatic, sizeof chromatic));
 
  // limite
  EXPECT(al_scale_generate(0, AL_CHROMATIC, buf) == AL_SUCCESS);
  EXPECT(buf[0] == 0 && buf[12] == 12);
 
  EXPECT(al_scale_generate(115, AL_MAJOR, buf) == AL_SUCCESS);
  EXPECT(buf[7] == 127);
 
  EXPECT(al_scale_generate(115, AL_CHROMATIC, buf) == AL_SUCCESS);
  EXPECT(buf[12] == 127);
 
  // invalido, o array nao pode ser tocado
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(120, AL_MAJOR, buf) == AL_ERR_INVALID_ARG);
  EXPECT(intact(buf, sizeof buf));
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(116, AL_MAJOR, buf) == AL_ERR_INVALID_ARG);
  EXPECT(intact(buf, sizeof buf));
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(128, AL_MAJOR, buf) == AL_ERR_INVALID_ARG);
  EXPECT(intact(buf, sizeof buf));
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, (al_scale_type)99, buf) == AL_ERR_INVALID_ARG);
  EXPECT(intact(buf, sizeof buf));
 
  mark(buf, sizeof buf);
  EXPECT(al_scale_generate(60, (al_scale_type)-1, buf) == AL_ERR_INVALID_ARG);
  EXPECT(intact(buf, sizeof buf));
 
  EXPECT(al_scale_generate(60, AL_MAJOR, NULL) == AL_ERR_NULL_ARG);
 
  return st;
}
 
test_status test_scale_length(void) {
  test_status st = TEST_SUCCESS;
  size_t len;
 
  // normal
  EXPECT(al_scale_length(AL_MAJOR, &len) == AL_SUCCESS);
  EXPECT(len == 8);
 
  EXPECT(al_scale_length(AL_MINOR, &len) == AL_SUCCESS);
  EXPECT(len == 8);
 
  EXPECT(al_scale_length(AL_MAJOR_PENTATONIC, &len) == AL_SUCCESS);
  EXPECT(len == 6);
 
  EXPECT(al_scale_length(AL_MINOR_PENTATONIC, &len) == AL_SUCCESS);
  EXPECT(len == 6);
 
  EXPECT(al_scale_length(AL_CHROMATIC, &len) == AL_SUCCESS);
  EXPECT(len == 13);
 
  // limite, nenhuma escala pode ser maior que AL_SCALE_MAX_LEN, e a maior
  // tem exatamente esse tamanho
  size_t maior = 0;
  for (int t = AL_MAJOR; t <= AL_CHROMATIC; t++) {
    EXPECT(al_scale_length((al_scale_type)t, &len) == AL_SUCCESS);
    EXPECT(len <= AL_SCALE_MAX_LEN);
    if (len > maior)
      maior = len;
  }
  EXPECT(maior == AL_SCALE_MAX_LEN);
 
  // invalido
  len = 99;
  EXPECT(al_scale_length((al_scale_type)5, &len) == AL_ERR_INVALID_ARG);
  EXPECT(len == 0);
 
  len = 99;
  EXPECT(al_scale_length((al_scale_type)-1, &len) == AL_ERR_INVALID_ARG);
  EXPECT(len == 0);
 
  EXPECT(al_scale_length(AL_MAJOR, NULL) == AL_ERR_NULL_ARG);
 
  return st;
}

int main(void) {
  int failed = 0; // TEST_FAIL vale 1, entao a soma conta as funcoes que falharam
 
  failed += test_midi_to_hz();
  failed += test_interval_semitones();
  failed += test_interval_ratio();
  failed += test_scale_generate();
  failed += test_scale_length();
 
  if (failed == 0) {
    printf("TODOS OS TESTES PASSARAM\n");
    return 0;
  }
  printf("%d TESTE(S) FALHARAM\n", failed);
  return 1;
}
