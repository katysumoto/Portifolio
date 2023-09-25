#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

void inicializar()
{
    srand(time(NULL));

    al_init();
    //Habilita a utilização de primitivas gráficas (formas geométricas)
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_init_image_addon();
    //Habilita o uso do teclado
    al_install_keyboard();
}

void limpar_matrizes(int tela[][22], int animacao[][30])
{
    //Define que a tela começará vazia
    for(int i=0; i<30; i++)
    {
        for(int j=0; j<22; j++)
        {
            tela[i][j] = 0;
        }
    }

    for(int i=0; i<15; i++)
    {
        for(int j=0; j<30; j++)
        {
            animacao[i][j] = 0;
        }
    }
}

void iniciar_animacao(int animacao[][30])
{
    int peca[2];
    for (int i=10; i<16; i++)
    {
        animacao[i][1] = animacao[i][4] = animacao[i][6] = animacao[i][13] = animacao[i][17] = animacao[i][23] = 1;
    }
    animacao[15][2] = animacao[15][3] = animacao[15][7] = animacao[15][8] = animacao[15][9] = 1;
    animacao[10][11] = animacao[10][12] = animacao[10][14] = animacao[10][15] = animacao[10][18] = animacao[10][19] = animacao[10][20] = 1;
    animacao[11][21] = animacao[12][19] = animacao[12][20] = animacao[13][19] = animacao[14][20] = animacao[15][21] = 1;
    animacao[10][26] = animacao[10][27] = animacao[11][25] = animacao[11][28] = animacao[12][26] = animacao[13][27] = 1;
    animacao[14][28] = animacao[14][25] = animacao[15][26] = animacao[15][27] = 1;

    for(int i=15; i>1; i--)
    {
        for(int j=0; j<29; j++)
        {
            if(animacao[i][j] == 1)
            {
                peca[0] = j;
                peca[1] = 0;

                while(peca[1] < i+1)
                {

                    al_draw_rectangle(peca[0]*13, peca[1]*13+60, peca[0]*13+13, peca[1]*13+13+60, al_map_rgb(255,255,255), 3);
                    for(int i=0; i<16; i++)
                    {
                        for(int j=0; j<30; j++)
                        {
                            if(animacao[i][j] == 2)
                            {
                                al_draw_rectangle(j*13, i*13+60, j*13+13, i*13+13+60, al_map_rgb(255,255,255), 3);
                            }
                        }
                    }
                    al_flip_display();
                    al_rest(0.01);
                    if(peca[1]==i)
                    {
                        animacao[i][j]=2;
                    }

                    peca[1]++;
                    al_clear_to_color(al_map_rgb(0,0,0));

                }



            }
        }
    }
    al_rest(1);
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<30; j++)
        {
            if(animacao[i][j] == 2)
            {
                al_draw_filled_rectangle(j*13, i*13+60, j*13+13, i*13+13+60, al_map_rgb(255,255,255));
            }
        }
    }
}

void limita_tela(int tela[][22])
{
    //Define limite inferior da tela
    for(int i=0; i<20; i++)
    {
        tela[30][i] = 1;
    }


    //Define limites laterais da tela
    for(int i=0; i<31; i++)
    {
        tela[i][-1] = 1;
        tela[i][20] = 1;
    }
}

void desenha_tela(int tela[][22])
{
    for(int i=0; i<31; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(tela[i][j] == 1)
            {
                al_draw_filled_rectangle(j*20, i*20, j*20+20, i*20+20, al_map_rgb(255,255,255));
            }
        }
    }
}

int vira_peca(int pecam, int pecan, int peca[], int tela[][22])
{
    if(pecan == 1 && pecam == 1 or pecan == 1 && pecam == 3)
    {
        if(tela[peca[1]][peca[0]+2] == 1)
        {
        }
        else
        {
            pecam++;
        }
    }
    else if(pecan == 2 && pecam == 1)
    {
        if(tela[peca[1]][peca[0]+1] == 1 or tela[peca[1]][peca[0]+2] == 1 or tela[peca[1]][peca[0]+3] == 1)
        {
        }
        else
        {
            pecam++;
        }
    }
    else if(pecan == 3 && pecam == 0)
    {
        if(tela[peca[1]][peca[0]+2] == 1)
        {
        }
        else
        {
            pecam++;
        }
    }
    else if(pecan == 4 && pecam == 1 or pecan == 4 && pecam == 3)
    {
        if(tela[peca[1]][peca[0]+2] == 1)
        {
        }
        else
        {
            pecam++;
        }
        }
        else
        pecam++;
        return pecam;
}

void mover_esquerda(int pecan, int pecam, int peca[], int tela[][22])
{
    switch(pecan)
    {
        case 0:
            if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0)
            {
                peca[0]--;
            }
            break;
        case 1:
            switch(pecam%4)
            {
            case 0:
                if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
                break;
            case 1:
                if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
                break;
            case 2:
                if(tela[peca[1]][peca[0]+1] == 0 && tela[peca[1]+1][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
                break;
            case 3:
                if(tela[peca[1]][peca[0]] == 0 && tela[peca[1]+1][peca[0]] == 0 && tela[peca[1]+2][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
                break;
            }

            break;
        case 2:
            switch(pecam%2)
            {
                case 0:
                    if(tela[peca[1]][peca[0]-1] == 0)
                    {
                        peca[0]--;
                    }
                    break;
                case 1:
                    if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]-1] == 0 && tela[peca[1]+3][peca[0]-1] == 0)
                    {
                        peca[0]--;
                    }
                    break;
            }
        break;
        case 3:
            switch(pecam%2)
            {
                case 0:
                    if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]] == 0)
                    {
                        peca[0]--;
                    }
                break;
                case 1:
                    if(tela[peca[1]][peca[0]] == 0 && tela[peca[1]+1][peca[0]-1] == 0)
                    {
                        peca[0]--;
                    }
                    break;

            }
            break;

        case 4:
        switch(pecam%4)
        {
            case 0:
                if(tela[peca[1]][peca[0]] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
            break;
            case 1:
                if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]-1] == 0)
                {
                    peca[0]--;
                }
                break;
                case 2:
                    if(tela[peca[1]][peca[0]-1] == 0 && tela[peca[1]+1][peca[0]] == 0)
                    {
                        peca[0]--;
                    }
                break;
                case 3:
                    if(tela[peca[1]][peca[0]] == 0 && tela[peca[1]+1][peca[0]-1] == 0 && tela[peca[1]+2][peca[0]] == 0)
                    {
                        peca[0]--;
                    }
                break;
            }
            break;
        }
}

void mover_direita(int pecam, int pecan, int peca[], int tela[][22])
{
                        switch(pecan)
                        {
                        case 0:
                            if(tela[peca[1]][peca[0]+2] == 0 && tela[peca[1]+1][peca[0]+2] == 0)
                                {
                                    peca[0]++;
                                }
                            break;
                            case 1:
                                switch(pecam%4)
                                {
                                case 0:
                                    if(tela[peca[1]][peca[0]+1] == 0 && tela[peca[1]+1][peca[0]+3] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 1:
                                    if(tela[peca[1]][peca[0]+2] == 0 && tela[peca[1]+1][peca[0]+1] == 0 && tela[peca[1]+2][peca[0]+1] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 2:
                                    if(tela[peca[1]][peca[0]+3] == 0 && tela[peca[1]+1][peca[0]+3] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 3:
                                    if(tela[peca[1]][peca[0]+2] == 0 && tela[peca[1]+1][peca[0]+2] == 0 && tela[peca[1]+2][peca[0]+2] == 0)
                                        {
                                            peca[0]++;
                                        }
                                        break;
                                }
                            break;
                            case 2:
                                switch(pecam%2)
                                {
                                case 0:
                                    if(tela[peca[1]][peca[0]+4] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 1:
                                    if(tela[peca[1]][peca[0]+1] == 0)
                                    {
                                        peca[0]++;
                                    }
                                }
                                break;
                            break;
                            case 3:
                                switch(pecam%2)
                                {
                                case 0:
                                    if(tela[peca[1]+1][peca[0]+2] == 0 && tela[peca[1]+2][peca[0]+2] == 0 && tela[peca[1]][peca[0]+1] == 0)
                                    {
                                        peca[0]++;
                                    }
                                break;
                                case 1:
                                    if(tela[peca[1]][peca[0]+3] == 0 && tela[peca[1]+1][peca[0]+2] == 0)
                                    {
                                        peca[0]++;
                                    }
                                break;
                                }

                            break;
                            case 4:
                                switch(pecam%4)
                                {
                                case 0:
                                    if(tela[peca[1]][peca[0]+2] == 0 && tela[peca[1]+1][peca[0]+3] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 1:
                                    if(tela[peca[1]][peca[0]+1] == 0 && tela[peca[1]+1][peca[0]+2] == 0 && tela[peca[1]+2][peca[0]+1] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 2:
                                    if(tela[peca[1]][peca[0]+3] == 0 && tela[peca[1]+1][peca[0]+2] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;
                                case 3:
                                    if(tela[peca[1]][peca[0]+2] == 0 && tela[peca[1]+1][peca[0]+2] == 0 && tela[peca[1]+2][peca[0]+2] == 0)
                                    {
                                        peca[0]++;
                                    }
                                    break;

                                }
                            break;
                        }
}

void desenha_peca(int peca[], int pecam, int pecan)
{
    switch(pecan)
            {
            case 0:
                for(int i=0; i<2; i++)
                {
                    for(int j=0; j<2; j++)
                    {
                        al_draw_rectangle(peca[0]*20+i*20, peca[1]*20+j*20, peca[0]*20+20+i*20, peca[1]*20+20+j*20, al_map_rgb(255,255,255), 2);
                    }
                }
            break;
            case 1:
                switch(pecam%4)
                {
                case 0:
                    al_draw_rectangle(peca[0]*20, peca[1]*20, peca[0]*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+20, peca[0]*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+40, peca[1]*20+20, peca[0]*20+60, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    break;
                case 1:
                    al_draw_rectangle(peca[0]*20, peca[1]*20, peca[0]*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+20, peca[0]*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+40, peca[0]*20+20, peca[1]*20+60, al_map_rgb(255,255,255), 2);
                    break;
                case 2:
                    al_draw_rectangle(peca[0]*20, peca[1]*20, peca[0]*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+40, peca[1]*20+20, peca[0]*20+60, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+40, peca[1]*20, peca[0]*20+60, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    break;
                case 3:
                    al_draw_rectangle(peca[0]*20, peca[1]*20+40, peca[0]*20+20, peca[1]*20+60, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+40, peca[0]*20+40, peca[1]*20+60, al_map_rgb(255,255,255), 2);
                    break;
                }

            break;
            case 2:
                switch(pecam%2)
                {
                case 0:
                    for(int i=0; i<4; i++)
                    {
                        al_draw_rectangle(peca[0]*20+i*20, peca[1]*20, peca[0]*20+i*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    }
                    break;
                case 1:
                    for(int i=0; i<4; i++)
                    {
                        al_draw_rectangle(peca[0]*20, peca[1]*20+i*20, peca[0]*20+20, peca[1]*20+i*20+20, al_map_rgb(255,255,255), 2);
                    }

                }
                break;
            case 3:
                switch(pecam%2)
                {
                    case 0:
                        for(int i=0; i<2; i++)
                        {
                            al_draw_rectangle(peca[0]*20, peca[1]*20+i*20, peca[0]*20+20, peca[1]*20+20+i*20, al_map_rgb(255,255,255), 2);
                            al_draw_rectangle(peca[0]*20+20, peca[1]*20+i*20+20, peca[0]*20+40, peca[1]*20+40+i*20, al_map_rgb(255,255,255), 2);
                        }
                        break;
                    case 1:
                        for(int i=0; i<2; i++)
                        {
                            al_draw_rectangle(peca[0]*20+i*20+20, peca[1]*20, peca[0]*20+i*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                            al_draw_rectangle(peca[0]*20+i*20, peca[1]*20+20, peca[0]*20+i*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                        }

                        break;


                }


            break;
            case 4:
                switch(pecam%4)
                {
                case 0:
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+20, peca[0]*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+40, peca[1]*20+20, peca[0]*20+60, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    break;
                case 1:
                    al_draw_rectangle(peca[0]*20, peca[1]*20, peca[0]*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+20, peca[0]*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20, peca[1]*20+40, peca[0]*20+20, peca[1]*20+60, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    break;
                case 2:
                    al_draw_rectangle(peca[0]*20, peca[1]*20, peca[0]*20+20, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+40, peca[1]*20, peca[0]*20+60, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    break;
                case 3:
                    al_draw_rectangle(peca[0]*20, peca[1]*20+20, peca[0]*20+20, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20, peca[0]*20+40, peca[1]*20+20, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+20, peca[0]*20+40, peca[1]*20+40, al_map_rgb(255,255,255), 2);
                    al_draw_rectangle(peca[0]*20+20, peca[1]*20+40, peca[0]*20+40, peca[1]*20+60, al_map_rgb(255,255,255), 2);
                    break;
                }

            break;


            }

}

bool detecta_colisao(int pecan, int pecam, int peca[], int tela[][22])
{
    bool colisao = false;
    //Detecta colisão e grava posição na tela
            switch(pecan)
            {
                case 0:
                    if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1)
                    {
                        colisao = true;
                        tela[peca[1]][peca[0]] = tela[peca[1]+1][peca[0]] = tela[peca[1]][peca[0]+1] =tela[peca[1]+1][peca[0]+1] = 1;
                    }
                break;
                case 1:
                    switch(pecam%4)
                    {
                        case 0:
                        {
                            if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1 or tela[peca[1]+2][peca[0]+2] == 1)
                            {
                                colisao = true;
                                tela[peca[1]][peca[0]] = tela[peca[1]+1][peca[0]] = tela[peca[1]+1][peca[0]+1] =tela[peca[1]+1][peca[0]+2] = 1;
                            }
                        }
                        break;
                        case 1:
                        if(tela[peca[1]+3][peca[0]] == 1 or tela[peca[1]+1][peca[0]+1] == 1)
                            {
                                colisao = true;
                                tela[peca[1]][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]] =tela[peca[1]+2][peca[0]] = 1;
                            }
                            break;
                        case 2:
                            if(tela[peca[1]+1][peca[0]] == 1 or tela[peca[1]+1][peca[0]+1] == 1 or tela[peca[1]+2][peca[0]+2] == 1)
                            {
                                colisao = true;
                                tela[peca[1]][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]][peca[0]+2] =tela[peca[1]+1][peca[0]+2] = 1;
                            }
                            break;
                        case 3:
                            if(tela[peca[1]+3][peca[0]] == 1 or tela[peca[1]+3][peca[0]+1] == 1)
                            {
                                colisao = true;
                                tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]+1] = tela[peca[1]+2][peca[0]+1] =tela[peca[1]+2][peca[0]] = 1;
                            }
                            break;
                        }
                    break;
                case 2:
                    switch(pecam%2)
                    {
                    case 0:
                        if(tela[peca[1]+1][peca[0]] == 1 or tela[peca[1]+1][peca[0]+1] == 1 or tela[peca[1]+1][peca[0]+2] == 1 or tela[peca[1]+1][peca[0]+3])
                        {
                            colisao = true;
                            tela[peca[1]][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]][peca[0]+2] =tela[peca[1]][peca[0]+3] = 1;
                        }
                        break;
                    case 1:
                        if(tela[peca[1]+4][peca[0]] == 1)
                        {
                            colisao = true;
                            tela[peca[1]][peca[0]] = tela[peca[1]+1][peca[0]] = tela[peca[1]+2][peca[0]] =tela[peca[1]+3][peca[0]] = 1;
                        }
                        break;

                    }

                break;
                case 3:
                    switch(pecam%2)
                    {
                        case 0:
                            if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+3][peca[0]+1] == 1)
                            {
                                colisao = true;
                                tela[peca[1]][peca[0]] = tela[peca[1]+1][peca[0]] = tela[peca[1]+1][peca[0]+1] =tela[peca[1]+2][peca[0]+1] = 1;
                            }
                            break;
                        case 1:
                            if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1 or tela[peca[1]+1][peca[0]+2] == 1)
                            {
                                colisao = true;
                                tela[peca[1]+1][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]+1] =tela[peca[1]][peca[0]+2] = 1;
                            }
                            break;

                    }

                break;
                case 4:
                    switch(pecam%4)
                    {
                    case 0:
                        if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1 or tela[peca[1]+2][peca[0]+2] == 1)
                        {
                            colisao = true;
                            tela[peca[1]+1][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]+1] =tela[peca[1]+1][peca[0]+2] = 1;
                        }
                        break;
                    case 1:
                        if(tela[peca[1]+3][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1)
                        {
                            colisao = true;
                            tela[peca[1]][peca[0]] = tela[peca[1]+1][peca[0]] = tela[peca[1]+2][peca[0]] =tela[peca[1]+1][peca[0]+1] = 1;
                        }
                        break;
                    case 2:
                        if(tela[peca[1]+1][peca[0]] == 1 or tela[peca[1]+2][peca[0]+1] == 1 or tela[peca[1]+1][peca[0]+2] == 1)
                        {
                            colisao = true;
                            tela[peca[1]][peca[0]] = tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]+1] =tela[peca[1]][peca[0]+2] = 1;
                        }
                        break;
                    case 3:
                        if(tela[peca[1]+2][peca[0]] == 1 or tela[peca[1]+3][peca[0]+1] == 1)
                        {
                            colisao = true;
                            tela[peca[1]][peca[0]+1] = tela[peca[1]+1][peca[0]+1] = tela[peca[1]+2][peca[0]+1] =tela[peca[1]+1][peca[0]] = 1;
                        }
                        break;


                    }

                break;
            }
            return colisao;
}

int calcula_pontos(int tela[][22])
{
    int bonus, pontos;

    //Váriavel que guarda quantas peças estão na mesma linha e define quando os blocos sumirão
        int n = 0;
        bonus = pontos = 0;
        for(int i=0; i<30; i++)
        {
                for(int j=0; j<20; j++)
                {
                    if(tela[i][j] == 1)
                    {
                        n++;
                    }
                }
                if(n==20)
                {
                    bonus++;
                    for(int j=i; j>0; j--)
                    {
                        for(int k=0; k<20; k++)
                        {
                            tela[j][k] = tela[j-1][k];
                        }
                    }
                    for(int j=0; j<20; j++)
                    {
                        tela[0][j] = 0;
                    }
                }

                n = 0;
        }
        switch(bonus)
        {
        case 1:
            pontos = pontos + 100;
            break;
        case 2:
            pontos = pontos + 300;
            break;
        case 3:
            pontos = pontos + 500;
            break;
        case 4:
            pontos = pontos + 1000;
            break;
        }
        return pontos;
}

bool fim_de_jogo(int tela[][22])
{
    bool jogo = true;
    for(int i=0; i<20; i++)
        {
            if(tela[0][i] == 1)
            {
                jogo = false;
                cout << "FIM DE JOGO" << endl;
                al_clear_to_color(al_map_rgb(0,0,0));

                al_flip_display();
                return 0;
            }
        }
        return jogo;
}
