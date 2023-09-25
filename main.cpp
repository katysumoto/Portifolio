#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "cabeca.h"

using namespace std;

int main()
{
    //Ponteiro para a janela
    ALLEGRO_DISPLAY *janela = NULL;
    //Ponteiro para fila de eventos
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    //Ponteiros para as imagens usadas no jogo
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_BITMAP *game_over = NULL;
    ALLEGRO_BITMAP *pause = NULL;
    //Ponteiro para audio do jogo
    ALLEGRO_AUDIO_STREAM *musica = NULL;

    //Inicializa fun��es da biblioteca ALLEGRO
    inicializar();

    //Cria vari�vel para fila de eventos
    fila_eventos = al_create_event_queue();
    //Registra o evento digitar no teclado para ser reconhecido na lista de eventos
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    //Cria tela e define seu tamanho
    janela = al_create_display(400, 600);
    //Define m�sica
    musica = al_load_audio_stream("musica.flac", 4, 1024);

    //Declara��o das variaveis usadas no jogo
    int tela[31][22], peca[2], animacao[15][30], pontos;
    float vel;
    bool jogo, colisao, pausar;
    //Variavel jogo que ter� de permanecer verdadeira enquanto o jogador estiver jogando
    jogo = true;
    //Vari�vel que armazena quantidade de pontos
    pontos = 0;
    imagem = al_load_bitmap("ultris.bmp");
    game_over = al_load_bitmap("game over.jpg");
    pause = al_load_bitmap("pause.png");

    //Limpa tela do jogo e das anima��es
    limpar_matrizes(tela, animacao);
    //Executa a anima��o de entrada
    iniciar_animacao(animacao);

    //Atualiza tela e desenha imagem
    al_flip_display();
    al_draw_bitmap(imagem, 30, 280, 0);
    al_flip_display();
    al_rest(3);

    //Define limites da tela do jogo
    limita_tela(tela);

    //Inicia m�sica
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);

    //Loop que mant�m o jogo rodando
    while(jogo == true)
    {

        //Define velocidade e posi��o inicial da pe�a
        vel = 0.3;
        peca[0] = 9;
        peca[1] = -1;
        colisao = false;
        system("cls");
        cout << "Pontos : " << pontos << endl;

        //Define aleatoriedade das pe�as que caem
        int pecan = rand()%5;
        //Define posi��o angular de cada pe�a
        int pecam = 0;

        //Loop que mant�m pe�a caindo e se movimentando
        while(colisao == false)
        {
            //Altera posi��o em Y da pe�a
            peca[1]++;
            //Loop que detecta se o jogador clicou em alguma tecla
            while(!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    switch(evento.keyboard.keycode)
                    {
                        //Tecla espa�o
                        case ALLEGRO_KEY_SPACE:
                            pecam = vira_peca(pecam, pecan, peca, tela);
                        break;
                        //Tecla direcional para baixo
                        case ALLEGRO_KEY_DOWN:
                            vel = 0.01;
                            break;
                        //Tecla direcional para esquerda
                        case ALLEGRO_KEY_LEFT:
                            mover_esquerda(pecan, pecam, peca, tela);
                            break;
                        //Tecla direcional para direita
                        case ALLEGRO_KEY_RIGHT:
                            mover_direita(pecam, pecan, peca, tela);
                            break;
                        case ALLEGRO_KEY_ENTER:
                            pausar = true;
                            al_draw_bitmap(pause, 150, 180, 0);
                            al_flip_display();
                            ALLEGRO_EVENT stop;
                            while(pausar == true)
                            {

                                al_wait_for_event(fila_eventos, &stop);
                                if (stop.type == ALLEGRO_EVENT_KEY_DOWN)
                                {
                                    if(stop.keyboard.keycode == ALLEGRO_KEY_ENTER)
                                    {
                                        pausar = false;
                                    }
                                }
                            }

                            break;

                    }
                }
            }

            //Desenha pe�as que j� colidiram na tela
            desenha_tela(tela);
            //Desenha pe�a caindo
            desenha_peca(peca, pecam, pecan);

            //Atualiza tela
            al_flip_display();
            //Espera pelo tempo de rea��o do jogador
            al_rest(vel);
            al_clear_to_color(al_map_rgb(0,0,0));
            //Detecta colis�o entre pe�as
            colisao = detecta_colisao(pecan, pecam, peca, tela);
            //Calcula pontos
            pontos = pontos + calcula_pontos(tela);
            //Encerra o jogo caso as pe�as passem pelo limite superior da tela.
            jogo = fim_de_jogo(tela);

        }
    }
    //Desenha GAME OVER
    al_draw_bitmap(game_over, 14, 180, 0);
    al_flip_display();
    system("pause");

    return 0;
}
