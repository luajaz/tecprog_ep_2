#include "audio_common.h"
#include "test_util.h"
#include "wave.h"

typedef al_status (*wave_fn)(float *, size_t, double, double, double);

// marcador para verificar que nada foi escrito
#define MARKER 2.0f

// funcoes auxiliares 

// preenche o array inteiro com o valor marcador
static void mark(float *b, size_t n) {
  for (size_t i = 0; i < n; i++)
    b[i] = MARKER;
}

// confere que o array inteiro ainda tem o valor marcador
static bool intact(const float *b, size_t n) {
  for (size_t i = 0; i < n; i++)
    if (b[i] != MARKER)
      return false;
  return true;
}

// confere que as n primeiras amostras sao os valores esperados vezes scale
static bool matches(const float *b, const double *expected, size_t n,
                    double scale) {
  for (size_t i = 0; i < n; i++)
    if (!double_compare(b[i], expected[i] * scale, 1e-6))
      return false;
  return true;
}
 
// chama as funcoes de onda com argumentos invalidos
static bool rejected(wave_fn f, double freq, double amp, double sample_rate) {
  float buf[8];
  mark(buf, 8);
  return f(buf, 4, freq, amp, sample_rate) == AL_ERR_INVALID_ARG &&
         intact(buf, 8);
}
 
// casos invalidos, iguais para as quatro ondas
static test_status invalid_cases(wave_fn f) {
  test_status st = TEST_SUCCESS;
 
  EXPECT(f(NULL, 4, 1.0, 1.0, 4.0) == AL_ERR_NULL_ARG);
 
  EXPECT(rejected(f, 1.0, 1.0, 0.0));
  EXPECT(rejected(f, 1.0, 1.0, -4.0));
  EXPECT(rejected(f, 0.0, 1.0, 4.0));
  EXPECT(rejected(f, -1.0, 1.0, 4.0));
  EXPECT(rejected(f, 2.0, 1.0, 4.0));
  EXPECT(rejected(f, 3.0, 1.0, 4.0));
  EXPECT(rejected(f, 1.0, -0.1, 4.0));
  EXPECT(rejected(f, 1.0, 1.1, 4.0));
 
  return st;
}
 
test_status test_wave_sine(void) {
  test_status st = TEST_SUCCESS;
  float buf[8];
  const double expected[] = {0.0, 1.0, 0.0, -1.0};
 
  // normal
  mark(buf, 8);
  EXPECT(al_wave_sine(buf, 4, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 1.0));
  EXPECT(buf[4] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_sine(buf, 4, 1.0, 0.5, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.5));
 
  // limite
  mark(buf, 8);
  EXPECT(al_wave_sine(buf, 4, 1.0, 0.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.0));
 
  EXPECT(al_wave_sine(buf, 4, 22049.0, 1.0, 44100.0) == AL_SUCCESS);
 
  mark(buf, 8);
  EXPECT(al_wave_sine(buf, 1, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 1, 1.0));
  EXPECT(buf[1] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_sine(buf, 0, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(intact(buf, 8));
 
  // invalido
  EXPECT(invalid_cases(al_wave_sine) == TEST_SUCCESS);
 
  return st;
}
 
test_status test_wave_square(void) {
  test_status st = TEST_SUCCESS;
  float buf[8];
  const double expected[] = {1.0, 1.0, -1.0, -1.0};
 
  // normal
  mark(buf, 8);
  EXPECT(al_wave_square(buf, 4, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 1.0));
  EXPECT(buf[4] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_square(buf, 4, 1.0, 0.5, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.5));
 
  // limite
  mark(buf, 8);
  EXPECT(al_wave_square(buf, 4, 1.0, 0.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.0));
 
  EXPECT(al_wave_square(buf, 4, 22049.0, 1.0, 44100.0) == AL_SUCCESS);
 
  mark(buf, 8);
  EXPECT(al_wave_square(buf, 1, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 1, 1.0));
  EXPECT(buf[1] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_square(buf, 0, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(intact(buf, 8));
 
  // invalido
  EXPECT(invalid_cases(al_wave_square) == TEST_SUCCESS);
 
  return st;
}
 
test_status test_wave_saw(void) {
  test_status st = TEST_SUCCESS;
  float buf[8];
  const double expected[] = {-1.0, -0.5, 0.0, 0.5};
 
  // normal
  mark(buf, 8);
  EXPECT(al_wave_saw(buf, 4, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 1.0));
  EXPECT(buf[4] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_saw(buf, 4, 1.0, 0.5, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.5));
 
  // limite
  mark(buf, 8);
  EXPECT(al_wave_saw(buf, 4, 1.0, 0.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.0));
 
  EXPECT(al_wave_saw(buf, 4, 22049.0, 1.0, 44100.0) == AL_SUCCESS);
 
  mark(buf, 8);
  EXPECT(al_wave_saw(buf, 1, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 1, 1.0));
  EXPECT(buf[1] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_saw(buf, 0, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(intact(buf, 8));
 
  // invalido
  EXPECT(invalid_cases(al_wave_saw) == TEST_SUCCESS);
 
  return st;
}
 
test_status test_wave_triangle(void) {
  test_status st = TEST_SUCCESS;
  float buf[8];
  const double expected[] = {1.0, 0.0, -1.0, 0.0};
 
  // normal
  mark(buf, 8);
  EXPECT(al_wave_triangle(buf, 4, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 1.0));
  EXPECT(buf[4] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_triangle(buf, 4, 1.0, 0.5, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.5));
 
  // limite
  mark(buf, 8);
  EXPECT(al_wave_triangle(buf, 4, 1.0, 0.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 4, 0.0));
 
  EXPECT(al_wave_triangle(buf, 4, 22049.0, 1.0, 44100.0) == AL_SUCCESS);
 
  mark(buf, 8);
  EXPECT(al_wave_triangle(buf, 1, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(matches(buf, expected, 1, 1.0));
  EXPECT(buf[1] == MARKER);
 
  mark(buf, 8);
  EXPECT(al_wave_triangle(buf, 0, 1.0, 1.0, 4.0) == AL_SUCCESS);
  EXPECT(intact(buf, 8));
 
  // invalido
  EXPECT(invalid_cases(al_wave_triangle) == TEST_SUCCESS);
 
  return st;
}
 
int main(void) {
  int failed = 0; // TEST_FAIL vale 1, entao a soma conta as funcoes que falharam
 
  failed += test_wave_sine();
  failed += test_wave_square();
  failed += test_wave_saw();
  failed += test_wave_triangle();
 
  if (failed == 0) {
    printf("TODOS OS TESTES PASSARAM\n");
    return 0;
  }
  printf("%d TESTE(S) FALHARAM\n", failed);
  return 1;
}
 
