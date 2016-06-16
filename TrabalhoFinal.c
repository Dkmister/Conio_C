#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#define TAM 15

typedef struct cord{                                     // ESTRUTURA para coordenadas da plataforma
    int x;
    int y;
} CORD;

typedef struct plataforma{                               // ESTRUTURA com os atributos de uma plataforma.
    int tam;
    CORD pos;
    CORD dir;
    int vel;
} PLATAFORMA;

typedef struct jogador{
    int cor;
    CORD pos;
    CORD dir;
} JOGADOR;

void apagaPlataforma(PLATAFORMA p){                     // FUNÇÃO que imprime em preto, na tela, a plataforma em sua posição (x, y).
    int i;
    for(i = 0; i < p.tam; i ++){
        gotoxy(p.pos.x + i, p.pos.y);
        textcolor(BLACK);
        printf("%c", 219);
    }
    textcolor(15);
}

void desenhaPlataforma(PLATAFORMA p){                   // FUNÇÃO que imprime, na tela, a plataforma em sua posição (x, y).
    int i;
    for(i = 0; i < p.tam; i ++){                        // Faz-se um for para imprimir o texto.
        gotoxy(p.pos.x + i, p.pos.y);
        textbackground(LIGHTRED);                       // Cor do fundo do texto.
        textcolor(LIGHTRED);                            // Cor do texto.
        printf("%c", 219);                              // Imprime o conjunto (texto + fundo do texto).
    }
    textbackground(BLACK);
    textcolor(15);
}

void apagaJogador (JOGADOR j){
    gotoxy(j.pos.x, j.pos.y - 1);
    textcolor(BLACK);
    printf ("%c", 220);
    gotoxy(j.pos.x, j.pos.y);
    printf ("%c", 206);
    textcolor(15);
}

void desenhaJogador (JOGADOR j){
    textcolor(j.cor);
    gotoxy(j.pos.x, j.pos.y - 1);
    printf ("%c", 220);
    gotoxy(j.pos.x, j.pos.y);
    printf ("%c", 206);
}

void movePlataformaLR(PLATAFORMA *p, PLATAFORMA *p1){    // FUNÇÃO de movimentação. Modifica as posições y e x da plataforma.

    apagaPlataforma((*p));
    apagaPlataforma((*p1));
    if(p->pos.x + p->dir.x == 1){
        p->pos.x = 64;
        p->pos.y= rand() %17+5;
    }
    if(p1->pos.x + p1->dir.x == 64){
        p1->pos.x = 1;
        p->pos.y= rand() %17+5;
    }
    p->pos.x += p->dir.x;
    p1->pos.x += p1->dir.x;
    if (p->pos.x >= 3)desenhaPlataforma((*p));
    if (p1->pos.x <= 61)desenhaPlataforma((*p1));
}
void movePlataformaUpDown(PLATAFORMA *p3){
    p3->vel *=-1;
    if(p3->vel == 1){

        apagaPlataforma((*p3));


        if(p3->pos.y + p3->dir.y == 1){
            p3->pos.y = 23;
            p3->pos.x = rand() %60 + 2;
        }

        p3->pos.y += p3->dir.y;


        if (p3->pos.y >= 3)desenhaPlataforma((*p3));
    }
}


void moveJogador (JOGADOR *j, PLATAFORMA *p, PLATAFORMA *p1,  PLATAFORMA *p3){
    int code = 3;
        apagaJogador((*j));
        if(j->cor == 15){
    if ((j->pos.x >= p->pos.x && j->pos.x <= p->pos.x + TAM && j->pos.y == p->pos.y -1) ||
        (j->pos.x >= p1->pos.x && j->pos.x <= p1->pos.x + TAM && j->pos.y == p1->pos.y -1)||
        (j->pos.x >= p3->pos.x && j->pos.x <= p3->pos.x + TAM && j->pos.y == p3->pos.y -1)){               // Verifica se o jogador está em cima da plataforma.
        if (GetAsyncKeyState(VK_SPACE)){
        code = 0;
        }
        if (GetAsyncKeyState(VK_RIGHT)){
        code = 1;
        }
        if (GetAsyncKeyState(VK_LEFT)){
        code = 2;
        }
            if(j->pos.x >= p->pos.x && j->pos.x <= p->pos.x + TAM && j->pos.y == p->pos.y -1){
                switch (code){
                    case 0: j->pos.y += j->dir.y; j->pos.x += j->dir.x;
                            desenhaJogador((*j));
                            break;
                    case 1: j->pos.x -= j->dir.x; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                    case 2: j->pos.x += j->dir.x - 1; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                    case 3: j->pos.x += j->dir.x; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                }
            }
            if(j->pos.x >= p1->pos.x && j->pos.x <= p1->pos.x + TAM && j->pos.y == p1->pos.y -1){
                    j->dir.x *= -1;
                switch (code){
                    case 0: j->pos.y += j->dir.y; j->pos.x += j->dir.x;
                            desenhaJogador((*j));
                            break;
                    case 1: j->pos.x += j->dir.x +1; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                    case 2: j->pos.x -= j->dir.x; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                    case 3: j->pos.x += j->dir.x; if (j->pos.x != 9){desenhaJogador((*j));};
                            break;
                }
                 j->dir.x *= -1;
            }
            if(j->pos.x >= p3->pos.x && j->pos.x <= p3->pos.x + TAM && j->pos.y == p3->pos.y -1){


            }

        }



    else{
            apagaJogador((*j));
            j->pos.y -= j->dir.y + 3;
            desenhaJogador((*j));
    }
    }
}

int main(){

        PLATAFORMA p;
        PLATAFORMA p1;
        PLATAFORMA p2;
        PLATAFORMA p3;
        JOGADOR j;
        srand(time(NULL));
        p.pos.x = 63;
        p.pos.y = rand() %17+5;
        p.dir.x = -1;
        p.tam = TAM;
        j.cor = 15;
        j.pos.x = p.pos.x + 7;
        j.pos.y = p.pos.y -1;
        j.dir.x = p.dir.x;
        j.dir.y = -4;
        p1.pos.x = 1;
        p1.pos.y = rand()%17+5;
        p1.dir.x = 1;
        p1.tam =TAM;
        p2.pos.x = rand() %60 + 2;
        p2.pos.y = 2;
        p2.dir.x = 0;
        p2.dir.y = 1;
        p2.tam = TAM;
        p3.pos.x = rand() %60 + 2;
        p3.pos.y = 23;
        p3.dir.x = 0;
        p3.dir.y = -1;
        p3.tam = TAM;
        p3.vel = -1;
        desenhaPlataforma((p));
        Sleep(50);
        desenhaPlataforma((p1));
        Sleep(50);
        desenhaPlataforma((p3));
        Sleep(50);
        desenhaJogador((j));
        while(!GetAsyncKeyState(j.pos.y < 24)){

            movePlataformaLR(&p, &p1);
            movePlataformaUpDown(&p3);
            Sleep(100);
            moveJogador((&j), (&p), (&p1), (&p3));
        }

  return 0;
}
