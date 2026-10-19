- [X] criar repo
- [X] criar to-do

IMPLEMENTAÇÃO

- [X] Módulo 1: notas e escalas 
	- [X] al_midi_to_hz: converte uma nota MIDI em frequência (Hz).
	- [X] al_interval_semitones: calcula a distância em semitons entre duas notas.
	- [X] al_interval_ratio: dá a razão de frequência de um intervalo em semitons.
	- [X] al_scale_generate: gera as notas de uma escala (maior, menor, pentatônica, cromática) a partir de uma nota inicial.
    - [X] al_scale_length: dá o comprimento da escala do tipo escolhido

- [X] Módulo 2: formas de onda
	- [X] al_wave_sine: preenche um buffer com senoide.
	- [X] al_wave_square: preenche com onda quadrada.
	- [X] al_wave_saw: preenche com dente de serra. 
	- [X] al_wave_triangle: preenche com onda triangular.

- [ ] Módulo 3: efeitos
	- [X] al_fx_gain: muda o volume.
	- [X] al_fx_clip: corta as amostras acima de um limite. 
	- [X] al_fx_delay: aplica eco.
	- [X] al_fx_normalize: ajusta o volume para que o pico chegue a um valor-alvo.
	- [X] al_fx_mix: soma um buffer em outro, útil para acordes.

- [ ] Módulo 4: arquivo WAV
	- [ ] al_wav_write: converte para int16_t, monta o cabeçalho e grava o .wav.

 - [ ] Main

RELATÓRIO TÉCNICO:
- [ ] começar kkk

README:
- [ ] começar kkk

MAKEFILE:
- [ ] começar kkk

APRESENTAÇÃO:
- [ ] Slides
- [ ] Video

TESTES:
- [ ] começar kkk

GERAL:
- [ ] Ver questão do bit depth (as funções não deveriam manter a amplitude da onda dentro do bit depth? Ou clipamos na hora de escrever?)
- [X] não deveriam haver guardas garantindo que n>=0?

<!-- podem criar identações entre as funções pra tarefas sobre cada uma :) --> 
