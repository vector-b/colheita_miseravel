#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include "jogo.h"


int main(int argc, char **argv)
{
	int i,j,cont;
	int ch;
	mapa mapa_in;
	FILE *arq;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();

	arq = fopen ("mapa.txt", "r");
	if (!arq)
	{
		printf("Mapa não encontrado\n");
		exit(1);
	}
	//Faz a geração do mapa
	mapa_in = aloca_mapa(mapa_in,arq);
	//Gera o mapa utilizando o ncurses
	gera_mapa(mapa_in);
	//Coloca o personagem no meio do mapa
	mvprintw(mapa_in.linha/2,mapa_in.coluna/2, "i");

	//Arruma as posições do personagem (coordenadas)
	i = mapa_in.linha/2;
	j = mapa_in.coluna/2;

	//Inicia os componentes dos personagens baseado nas structs

	personagem p;
	fila_plantio fp;


	curs_set(0);
	p = iniciapersonagem(p);
	tipo_semente *v;
	v = malloc(30 * sizeof(tipo_semente));
	cria_tipos();
	p = iniciamochila(p);
	inicia_fila(&fp);
	//Quantidade de movimentos que o personagem tem
	cont = 0;
	int k = 0;
	int c = 3;
	int max = 0;
	int min = 0;
	while (1 && max < 10 && min < 10)
	{
		gera_semente(mapa_in,&c);
		//Selecionaa a tecla digitada no teclado
		ch = getch();
		//Faz a atualização do personagem no mapa
		p = anda_personagem(&i,&j,ch,mapa_in,p,&fp,&cont,v,&c,&max,&min);
		//Saude do personagem
		p = perso_info(p,mapa_in,&k);
		if((p.saude == 0) || (min == 10)){
			printf("YOU LOSE");
			break;
		}
		if (max == 10){
			printf("YOU WIN");
			break;
		}
	mvprintw(0,68,"%d", max);
	mvprintw(0,100,"%d", min);
	k += 1;
	}
	//Libera a matriz alocada no mapa
	mapa_in = libera_matriz(mapa_in);
	//Coisas do ncurses
	refresh();
	getch();
	endwin();
	
	fclose(arq);
	return (0);
}
