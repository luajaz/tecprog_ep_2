# tecprog_ep_2

# Ideia: Biblioteca que gera áudio

Converte notas em frequências, sintetiza formas de onda, aplica efeitos simples e gera um arquivo `.wav` com o resultado.

## Visão geral

- Módulos têm responsabilidades distintas.
- **Cliente:** programa que utiliza a biblioteca para gerar uma pequena melodia e gerar o `.wav`.

## Módulos

1. **Notas e escalas**  
   Parte "musical" da biblioteca. Converte notas MIDI em frequência (Hz), calcula intervalo entre notas e gera escalas (maior, menor, pentatônica, cromática).

2. **Geração de formas de onda**  
   Parte da síntese. Preenche buffers de memória com senoide, onda quadrada, dente de serra e onda triangular.

3. **Efeitos simples de áudio**  
   Processamento. Recebe um buffer e aplica ganho (volume), clipping (limitação de amplitude) e delay (eco).

4. **Arquivo .wav**  
   Parte da saída. Monta o cabeçalho do formato WAV e grava o buffer em disco.

## Fluxo

`Notas -> Ondas -> Efeitos -> Arquivo`

O módulo 1 mexe com toda a parte de "teoria musical" utilizando as notas MIDI e só no final converte isso para Hz.

O módulo 2 monta a onda com base no tipo escolhido: senoide, quadrada, etc.

Depois disso, com esse buffer, o módulo 3 vai aplicar os efeitos desejados.

E, por fim, o módulo 4, com esse buffer com os efeitos aplicados, converte isso de `float` para `int16_t` e escreve o arquivo `.wav`.

## Funções

### Módulo 1: notas e escalas

1. `al_midi_to_hz`: converte uma nota MIDI em frequência (Hz).
2. `al_interval_semitones`: calcula a distância em semitons entre duas notas.
3. `al_interval_ratio`: dá a razão de frequência de um intervalo em semitons.
4. `al_scale_generate`: gera as notas de uma escala (maior, menor, pentatônica, cromática) a partir de uma nota inicial.

### Módulo 2: formas de onda

5. `al_wave_sine`: preenche um buffer com senoide.
6. `al_wave_square`: preenche com onda quadrada.
7. `al_wave_saw`: preenche com dente de serra.
8. `al_wave_triangle`: preenche com onda triangular.

### Módulo 3: efeitos

9. `al_fx_gain`: muda o volume.
10. `al_fx_clip`: corta as amostras acima de um limite.
11. `al_fx_delay`: aplica eco.
12. `al_fx_normalize`: ajusta o volume para que o pico chegue a um valor-alvo.
13. `al_fx_mix`: soma um buffer em outro, útil para acordes.

### Módulo 4: arquivo WAV

14. `al_wav_write`: converte para `int16_t`, monta o cabeçalho e grava o `.wav`.

