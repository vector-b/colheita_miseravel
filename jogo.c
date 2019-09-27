#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "jogo.h"

//ALoca a matriz para o mapa
char** aloca_matriz (mapa mapa_in){
	int i;
	mapa_in.m = malloc (mapa_in.linha * sizeof(char*));
	for (i = 0; i < mapa_in.linha; i++)
		mapa_in.m[i] = malloc (mapa_in.coluna * sizeof(char));

	return(mapa_in.m);		
}

//Le os valroes do arquivo e salva na struct
mapa aloca_mapa(mapa mapa_in, FILE *arq){
	int i,j;
	//Le a linha e coluna do arquivo
	fscanf(arq, "%d", &mapa_in.linha);
	fscanf(arq, "%d", &mapa_in.coluna);

	//Chama a função para alocar a matriz
	mapa_in.m = aloca_matriz (mapa_in);
	//Le o mapa do arquivo
	for (i = 0; i < mapa_in.linha; i++)
		for(j = 0; j < mapa_in.coluna; j++)
			fscanf(arq, "%c", &mapa_in.m[i][j]);

	//Retorna com os valores atualizados
	return(mapa_in);

}
//gera o mapa na tela 
void gera_mapa (mapa m){

	for (int i = 0; i < m.linha; i++)
		for (int j = 0; j < m.coluna; j++)
			mvaddch(i,j,m.m[i][j]);

	mvprintw(0,40, "MOCHILA");
	mvprintw(m.linha,10, "FOME");
	mvprintw(m.linha+1,10, "0");
	mvprintw(m.linha,16, "SAUDE");
	mvprintw(m.linha+1,16, "100");
	mvprintw(m.linha,30, "FILA");
	mvprintw(35,0, "LEGENDA");
	mvprintw(36,0, ", - Batata ");	
	mvprintw(37,0, "B - Batata Plantada ");
	mvprintw(38,0, "o - Tomate ");
	mvprintw(39,0, "+ - Tomate Plantado ");
	mvprintw(40,0, "w - Alface ");
	mvprintw(41,0, "W - Alface Plantado ");
	mvprintw(42,0, "d - Batata Doce ");
	mvprintw(43,0, "D - Batata Doce Plantada ");
	mvprintw(44,0, "i - Personagem");
	mvprintw(45,0, ". - Semente");
	mvprintw(46,0, "w - Anda para cima");
	mvprintw(47,0, "s - Anda para baixo");
	mvprintw(48,0, "d - Anda para direita");
	mvprintw(49,0, "a - Anda para esquerda");
	mvprintw(46,0, "x - Coleta a semente");
	mvprintw(47,0, "p - Planta a semente");
	mvprintw(48,0, "c - Colhe a semente");
	mvprintw(49,0, "f - Como o que está no topo da pilha");
	mvprintw(49,0, "j - Joga o topo da pilha fora");
	mvprintw(50,0, "o - Mostra a fila");
	mvprintw(0,50, "plantas colhidas: ");
	mvprintw(0,80, "plantas estragadas: ");
}
//i-1 -> cima
//i+1 -> baixo
//j-1 -> esquerda
//j+1 -> direita
//Faz a troca de posição do personagem
void gera_semente(mapa mapa_in, int *c)
{
	if (*c <= 2)
	{
		time_t t;
		srand((unsigned) time(&t));
		int a,b;
		int p;
		do
		{
			a = rand()%17;
			b = rand()%36;

		} while (mapa_in.m[a][b] != ' ');
		char *valor;
		valor = malloc(sizeof(char));
		p = rand()%4;
		if (p == 0)
			strcpy(valor,"o");
		else if (p == 1)
			strcpy(valor,",");
		else if (p == 2)
			strcpy(valor,"w");
		else if (p == 3)
			strcpy(valor,"d");

		mapa_in.m[a][b] = *valor;
		mvprintw(a,b,valor);
		free(valor);
		*c += 1;
	}
	
}

tipo_semente *tpa;
tipo_semente *tpb;
tipo_semente *tpc;
tipo_semente *tpd;
void cria_tipos()
{
	tpa = inicializa_tipos(tpa,"tomate", 4, 0, "vivo");
	tpb = inicializa_tipos(tpb,"batata", 8, 0, "vivo");
	tpc = inicializa_tipos(tpc,"alface", 12, 0, "vivo");
	tpd = inicializa_tipos(tpd,"batata doce", 6, 0, "vivo");
}
	
tipo_semente* inicializa_tipos(tipo_semente *tp, char *nome, int tempo, int nivel_satisfacao, char *status)
{
	tp = malloc(sizeof(tp));
	tp -> nome = malloc(100*sizeof(char));
	tp -> status = malloc(7*sizeof(char));
	strcpy(tp -> nome,nome);
	tp -> tempo = tempo;
	tp -> nivel_satisfacao = nivel_satisfacao;
	tp -> status = status;
	return tp;
}

personagem iniciapersonagem(personagem p)
{
	p.fome = 0;
	p.saude = 100;
	p.m.tam = 10;
	p.m.quantidade = 0;

	return p;
}
personagem iniciamochila(personagem p)
{
	p.m.topo = malloc(sizeof(p.m.topo));
	p.m.topo = NULL;
	semente *nova_semente;
	nova_semente = malloc(sizeof(nova_semente));
	nova_semente -> tipo_semente = malloc(sizeof(nova_semente -> tipo_semente));
	int val;
	time_t ti;
	srand((unsigned) time(&ti));
	val = rand()%4;
	if (val == 0) // -> batata
	{
		tpa -> nome = "tomate";
		nova_semente -> tipo_semente = tpa;
	}
	else if (val == 1)
	{
		tpb -> nome = "batata";
		nova_semente -> tipo_semente = tpb;
	}
	else if (val == 2)
	{
		tpc -> nome = "alface";
		nova_semente -> tipo_semente = tpc;
	}
	else if (val == 3)
	{
		tpd -> nome = "batata doce";
		nova_semente -> tipo_semente = tpd;
	}
	nova_semente -> prox = NULL;
	p.m.topo = nova_semente;
	p.m.quantidade += 1;
	legenda(p);
	return p;

}
personagem perso_info(personagem p, mapa mapa_in,int *k){
	if ((p.fome == 100) && (*k % 2 == 0)){
		p.saude -= 1;
		mvprintw(mapa_in.linha+1,16, "   ");
		mvprintw(mapa_in.linha+1,16, "%d", p.saude);		
	}
	else if (p.fome < 100){
		p.fome += 1;  			
			//nao apaga nada aqui (dps eu explico)			
			mvprintw(mapa_in.linha+1,10,"   ");		
			mvprintw(mapa_in.linha+1,10, "%d", p.fome);
	}

	return p;
}
personagem anda_personagem(int *i, int *j, int ch, mapa mapa_in, personagem p, fila_plantio *fp, int *cont, tipo_semente *v,int *c, int *max, int *min)
{		
	switch (ch)
	{
	
		case 'w' :
			if ((mapa_in.m[*i-1][*j] != '|') && (mapa_in.m[*i-1][*j] != '.') && (mapa_in.m[*i-1][*j] != '-')  && (mapa_in.m[*i-1][*j] != '*') && (mapa_in.m[*i-1][*j] != 'o') && (mapa_in.m[*i-1][*j] != 'w') && (mapa_in.m[*i-1][*j] != 'd') && (mapa_in.m[*i-1][*j] != ',') && (mapa_in.m[*i-1][*j] != '+') && (mapa_in.m[*i-1][*j] != 'W') && (mapa_in.m[*i-1][*j] != 'D')&& (mapa_in.m[*i-1][*j] != 'B')&& (mapa_in.m[*i-1][*j] != 'X'))
			{		
			
				mvprintw(*i,*j," ");
				mvprintw(*i-1,*j,"i");
				*i = *i-1;
			}
		break;
		case 's' :
			if ((mapa_in.m[*i+1][*j] != '|') && (mapa_in.m[*i+1][*j] != '.') && (mapa_in.m[*i+1][*j] != '-') && (mapa_in.m[*i+1][*j] != '*') && (mapa_in.m[*i+1][*j] != 'o') && (mapa_in.m[*i+1][*j] != 'w') && (mapa_in.m[*i+1][*j] != 'd') && (mapa_in.m[*i+1][*j] != ',') && (mapa_in.m[*i+1][*j] != '+') && (mapa_in.m[*i+1][*j] != 'W') && (mapa_in.m[*i+1][*j] != 'D')&& (mapa_in.m[*i+1][*j] != 'B')&& (mapa_in.m[*i+1][*j] != 'X'))		
			{		
				mvprintw(*i,*j," ");
				mvprintw(*i+1,*j,"i");
				*i = *i+1;
			}	
		break;
		case 'a' :
			if ((mapa_in.m[*i][*j-1] != '|') && (mapa_in.m[*i][*j-1] != '.') && (mapa_in.m[*i][*j-1] != '-') && (mapa_in.m[*i][*j-1] != '*') && (mapa_in.m[*i][*j-1] != 'o') && (mapa_in.m[*i][*j-1] != 'w') && (mapa_in.m[*i][*j-1] != 'd')&&(mapa_in.m[*i][*j-1] != ',') && (mapa_in.m[*i][*j-1] != '+') && (mapa_in.m[*i][*j-1] != 'W') && (mapa_in.m[*i][*j-1] != 'D')&&(mapa_in.m[*i][*j-1] != 'B')&&(mapa_in.m[*i][*j-1] != 'X'))		
			{						
				mvprintw(*i,*j," ");
				mvprintw(*i,*j-1,"i");
				*j = *j-1;
			}
		break;
		case 'd' :
			if ((mapa_in.m[*i][*j+1] != '|') && (mapa_in.m[*i][*j+1] != '.') && (mapa_in.m[*i][*j+1] != '-') && (mapa_in.m[*i][*j+1] != '*') && (mapa_in.m[*i][*j+1] != 'o') && (mapa_in.m[*i][*j+1] != 'w') && (mapa_in.m[*i][*j+1] != 'd')&& (mapa_in.m[*i][*j+1] != ',') && (mapa_in.m[*i][*j+1] != '+') && (mapa_in.m[*i][*j+1] != 'W') && (mapa_in.m[*i][*j+1] != 'D')&& (mapa_in.m[*i][*j+1] != 'B')&& (mapa_in.m[*i][*j+1] != 'X'))		
			{								
				mvprintw(*i,*j," ");
				mvprintw(*i,*j+1,"i");
				*j = *j+1;
			}
		break;
		case 'x' :
			if (tem_semente(mapa_in,*i-1,*j))
			{
				p = empilha_semente(mapa_in,*i-1,*j,p,c);
				*c -= 1;
			}
			else if (tem_semente(mapa_in,*i,*j+1))
			{
				p = empilha_semente(mapa_in,*i,*j+1,p,c);
				*c -= 1;
			}
			else if(tem_semente(mapa_in,*i+1,*j))
			{
				p = empilha_semente(mapa_in,*i+1,*j,p,c);
				*c -= 1;
			}
			else if (tem_semente(mapa_in,*i,*j-1))
			{
				p = empilha_semente(mapa_in,*i,*j-1,p,c);
				*c -= 1;
			}
		break;
		case 'p' :
		if (p.m.topo != NULL){
			if (ehterreno(mapa_in,*i-1,*j) )
			{
				v[*cont].nome = p.m.topo -> tipo_semente -> nome;
				v[*cont].tempo  = p.m.topo -> tipo_semente -> tempo;
				v[*cont].linha = *i-1;
				v[*cont].coluna = *j;
				v[*cont].nivel_satisfacao = p.m.topo -> tipo_semente -> nivel_satisfacao;
				v[*cont].status = p.m.topo -> tipo_semente -> status;

				p = plantar(mapa_in,*i-1,*j,p,fp);
				*cont += 1;
			}
			else if (ehterreno(mapa_in,*i,*j+1))
			{
				v[*cont].nome = p.m.topo -> tipo_semente -> nome;
				v[*cont].tempo  = p.m.topo -> tipo_semente -> tempo;
				v[*cont].linha = *i;
				v[*cont].coluna = *j+1;
				v[*cont].nivel_satisfacao = p.m.topo -> tipo_semente -> nivel_satisfacao;
				v[*cont].status = p.m.topo -> tipo_semente -> status;
				p = plantar(mapa_in,*i,*j+1,p,fp);
				*cont += 1;
			}
			else if (ehterreno(mapa_in,*i+1,*j))
			{
				v[*cont].nome = p.m.topo -> tipo_semente -> nome;
				v[*cont].tempo  = p.m.topo -> tipo_semente -> tempo;
				v[*cont].linha = *i+1;
				v[*cont].coluna = *j;
				v[*cont].nivel_satisfacao = p.m.topo -> tipo_semente -> nivel_satisfacao;
				v[*cont].status = p.m.topo -> tipo_semente -> status;
				p = plantar(mapa_in,*i+1,*j,p,fp);
				*cont += 1;
			}
			else if (ehterreno(mapa_in,*i,*j-1))
			{
				v[*cont].nome = p.m.topo -> tipo_semente -> nome;
				v[*cont].tempo  = p.m.topo -> tipo_semente -> tempo;
				v[*cont].linha = *i;
				v[*cont].coluna = *j-1;
				v[*cont].nivel_satisfacao = p.m.topo -> tipo_semente -> nivel_satisfacao;
				v[*cont].status = p.m.topo -> tipo_semente -> status;
				p = plantar(mapa_in,*i,*j-1,p,fp);
				*cont += 1;
			}
		}
		break;
		case 'c' :	
			if (ehplanta(mapa_in,*i,*j-1))
			{			
				*max +=1;
				p = empilha_semente(mapa_in,*i,*j-1,p,c);
				*cont = tira_vetor(*i,*j-1,v,*cont);
			}
			else if (ehplanta(mapa_in,*i,*j+1))
			{		
				*max += 1;
				p = empilha_semente(mapa_in,*i,*j+1,p,c);
				*cont = tira_vetor(*i,*j+1,v,*cont);
			}
			else if (ehplanta(mapa_in,*i+1,*j))
			{		
				*max += 1;
				p = empilha_semente(mapa_in,*i+1,*j,p,c);
				*cont = tira_vetor(*i+1,*j,v,*cont);
			}
			else if (ehplanta(mapa_in,*i-1,*j))
			{		
				*max += 1;	
				p = empilha_semente(mapa_in,*i-1,*j,p,c);
				*cont = tira_vetor(*i-1,*j,v,*cont);
			}
			
		break;
		case 'j' :
			if (p.m.topo != NULL)
			{
				if ((mapa_in.m[*i-1][*j] != '|') && (mapa_in.m[*i-1][*j] != '.') && (mapa_in.m[*i-1][*j] != '-')  && (mapa_in.m[*i-1][*j] != '*') && (mapa_in.m[*i-1][*j] != 'o') && (mapa_in.m[*i-1][*j] != 'w') && (mapa_in.m[*i-1][*j] != 'b') && (mapa_in.m[*i-1][*j] != ',') && (mapa_in.m[*i-1][*j] != '+') && (mapa_in.m[*i-1][*j] != 'W') && (mapa_in.m[*i-1][*j] != 'D')&& (mapa_in.m[*i-1][*j] != 'B')&& (mapa_in.m[*i-1][*j] != 'X'))
				{				
					joga_fora(p,mapa_in,*i-1,*j);
					p = desempilha (mapa_in,*i-1,*j,p);
				}				
				else if ((mapa_in.m[*i+1][*j] != '|') && (mapa_in.m[*i+1][*j] != '.') && (mapa_in.m[*i+1][*j] != '-') && (mapa_in.m[*i+1][*j] != '*') && (mapa_in.m[*i+1][*j] != 'o') && (mapa_in.m[*i+1][*j] != 'w') && (mapa_in.m[*i+1][*j] != 'b') && (mapa_in.m[*i+1][*j] != ',') && (mapa_in.m[*i+1][*j] != '+') && (mapa_in.m[*i+1][*j] != 'W') && (mapa_in.m[*i+1][*j] != 'D')&& (mapa_in.m[*i+1][*j] != 'B')&& (mapa_in.m[*i+1][*j] != 'X'))
				{
					joga_fora(p,mapa_in,*i+1,*j);
					p = desempilha (mapa_in,*i-1,*j,p);		
				}				
				else 	if ((mapa_in.m[*i][*j-1] != '|') && (mapa_in.m[*i][*j-1] != '.') && (mapa_in.m[*i][*j-1] != '-') && (mapa_in.m[*i][*j-1] != '*') && (mapa_in.m[*i][*j-1] != 'o') && (mapa_in.m[*i][*j-1] != 'w') && (mapa_in.m[*i][*j-1] != 'b')&&(mapa_in.m[*i][*j-1] != ',') && (mapa_in.m[*i][*j-1] != '+') && (mapa_in.m[*i][*j-1] != 'W') && (mapa_in.m[*i][*j-1] != 'D')&&(mapa_in.m[*i][*j-1] != 'B')&&(mapa_in.m[*i][*j-1] != 'X'))
				{
					joga_fora(p,mapa_in,*i,*j-1);
					p = desempilha (mapa_in,*i-1,*j,p);		
				}		
				else if ((mapa_in.m[*i][*j+1] != '|') && (mapa_in.m[*i][*j+1] != '.') && (mapa_in.m[*i][*j+1] != '-') && (mapa_in.m[*i][*j+1] != '*') && (mapa_in.m[*i][*j+1] != 'o') && (mapa_in.m[*i][*j+1] != 'w') && (mapa_in.m[*i][*j+1] != 'b')&& (mapa_in.m[*i][*j+1] != ',') && (mapa_in.m[*i][*j+1] != '+') && (mapa_in.m[*i][*j+1] != 'W') && (mapa_in.m[*i][*j+1] != 'D')&& (mapa_in.m[*i][*j+1] != 'B')&& (mapa_in.m[*i][*j+1] != 'X'))
				{
					joga_fora(p,mapa_in,*i,*j+1);
					p = desempilha (mapa_in,*i-1,*j,p);		
				}		
		}
		break;
		case 'f' :
			if (p.m.topo != NULL){
				p = comer_semente(p);
				p = desempilha(mapa_in,*i,*j,p);
			}
		break;
		case 'o' :
			imprimir_fila(fp,*cont,mapa_in);
		break;
		}
		if(v != NULL)
			*min = diminui_tempo(*cont,v,mapa_in,*min);

		ordena_vetor(*cont,v,mapa_in);
		inicia_fila(fp);
		insere_planta(fp,*cont,v);			
		return p;
}

personagem comer_semente(personagem p){
	if (strcmp(p.m.topo -> tipo_semente -> nome, "batatap") == 0){
		p.fome = p.fome - 10;
		if (p.fome < 0)
			p.fome = 0;
		p.m.topo -> tipo_semente -> nome = "batata";
	}else if (strcmp(p.m.topo -> tipo_semente -> nome, "alfacep") == 0){
		p.fome = p.fome - 20;
		if (p.fome < 0)
			p.fome = 0;
		p.m.topo -> tipo_semente -> nome = "alface";
	}else if (strcmp(p.m.topo -> tipo_semente -> nome, "tomatep") == 0){
		p.fome = p.fome - 30;
		if (p.fome < 0)
			p.fome = 0;
		p.m.topo -> tipo_semente -> nome = "tomate";
	}else if (strcmp(p.m.topo -> tipo_semente -> nome, "batata docep") == 0){
		p.fome = p.fome - 50;
		if (p.fome < 0)
			p.fome = 0;
		p.m.topo -> tipo_semente -> nome = "batata doce";

	}

	return(p);

}
personagem desempilha (mapa mapa_in, int linha, int coluna, personagem p)//DESEMPILHA SEMENTES DA MOCHILA
{
    char *aux_string;
    if (p.m.topo != NULL)
    {
        p.m.topo = p.m.topo -> prox;
        aux_string = "";
        deslegenda(aux_string,p);
        p.m.quantidade -= 1;
    }
    return p;
}
void joga_fora(personagem p, mapa mapa_in, int linha, int coluna){
	if (strcmp(p.m.topo -> tipo_semente -> nome,"batata") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome,"alface") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "tomate") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "batata doce") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "batatap") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
		p.m.topo -> tipo_semente -> nome = "batata";
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "alfacep") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
		p.m.topo -> tipo_semente -> nome = "alface";
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "tomatep") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
		p.m.topo -> tipo_semente -> nome = "tomate";
	}
	else if (strcmp(p.m.topo -> tipo_semente -> nome, "batata docep") == 0){
		mapa_in.m[linha][coluna] = ' ';
		mvprintw(linha,coluna," ");
		p.m.topo -> tipo_semente -> nome = "batata doce";
	}
}
int tira_vetor (int l, int c, tipo_semente *v, int tam)
{
	int i, j;	
	for (i = 0; i < tam; i++)
	{
		if ((v[i].linha == l) && (v[i].coluna == c))
		{
			for (j = i; j < tam; j++)
			{
				if ((j+1) < tam)				
					v[j] = v[j+1];
			}			
			tam--;
			break;		
		}
	}
	return(tam);
}

personagem colhe_semente(int linha, int coluna, mapa mapa_in, personagem p)
{
	//tpa = tomate
	//tpb = batata
	//tpc = maconha
	//tpd = batata doce			
	if (mapa_in.m[linha][coluna] == 'B')
	{
		if (tpb->nivel_satisfacao > p.fome)
			p.fome = 0;
		else				
			p.fome -= tpb->nivel_satisfacao;
		mapa_in.m[linha][coluna] = '.';
		mvprintw(linha,coluna,".");		
	}
	else if (mapa_in.m[linha][coluna] == 'W')
	{			
		if (tpc->nivel_satisfacao > p.fome)
			p.fome = 0;		
		else				
			p.fome -= tpc->nivel_satisfacao;
		mapa_in.m[linha][coluna] = '.';
		mvprintw(linha,coluna,".");			
	}
	else if (mapa_in.m[linha][coluna] == '+')
	{
		if (tpa->nivel_satisfacao > p.fome)
			p.fome = 0;
		else				
			p.fome -= tpa->nivel_satisfacao;
		mapa_in.m[linha][coluna] = '.';
		mvprintw(linha,coluna,".");	
	}
	else if (mapa_in.m[linha][coluna] == 'D')
	{
		if (tpd->nivel_satisfacao > p.fome)
			p.fome = 0;
		else				
			p.fome -= tpd->nivel_satisfacao;
		mapa_in.m[linha][coluna] = '.';
		mvprintw(linha,coluna,".");
	}
	
	return(p);
}
void ordena_vetor (int cont, tipo_semente *v, mapa mapa_in){
	int i,j;
	tipo_semente aux;
	for (i = 1; i < cont; i++) {
	j = i;
		while (j > 0 && v[j - 1].tempo < v[j].tempo){
			aux = v[j];
			v[j] = v[j - 1];
			v[j - 1] = aux;
		j--;
		}
	}
}
int diminui_tempo(int cont, tipo_semente *v, mapa mapa_in, int min)
{
	int a,b,c,d;
	a = -10;
	b = -15;
	c = -20;
	d = -30;
	for (int i = 0; i < cont; i++){
		//BATATA ATT
		if ((strcmp(v[i].nome, "batata") == 0) && (v[i].tempo == 0)&& (strcmp(v[i].status, "vivo") == 0)) //batata
		{
			mvprintw(v[i].linha,v[i].coluna,"B");
			mapa_in.m[v[i].linha][v[i].coluna] = 'B';
			v[i].tempo -= 1;	

		//BATATA MORTA
		}else if((strcmp(v[i].nome, "batata") == 0) && (v[i].tempo == a) && (strcmp(v[i].status, "vivo") == 0)){
			mvprintw(v[i].linha,v[i].coluna,"X");
			mapa_in.m[v[i].linha][v[i].coluna] = 'X';
			v[i].status="morto";
			min ++;

		}else if ((strcmp(v[i].nome, "batata") == 0) && (v[i].tempo > a))
			v[i].tempo -= 1;
		//alface ATT
		if ((strcmp(v[i].nome, "alface") == 0) && (v[i].tempo == 0)) //alface
		{
			mvprintw(v[i].linha,v[i].coluna,"W");
			mapa_in.m[v[i].linha][v[i].coluna] = 'W';
			v[i].tempo -= 1;

		//MOKNHA MORTA
		}else if((strcmp(v[i].nome, "alface") == 0) && (v[i].tempo == b)&& (strcmp(v[i].status, "vivo") == 0)){
			mvprintw(v[i].linha,v[i].coluna,"X");
			mapa_in.m[v[i].linha][v[i].coluna] = 'X';
			v[i].status="morto";
			min ++;

		}else if ((strcmp(v[i].nome, "alface") == 0) && (v[i].tempo > b))
			v[i].tempo -= 1;
		//TOMOATE ATT
		if ((strcmp(v[i].nome, "tomate") == 0) && (v[i].tempo == 0))//tomate
		{
			mvprintw(v[i].linha,v[i].coluna,"+");
			mapa_in.m[v[i].linha][v[i].coluna] = '+';
			v[i].tempo -= 1;

		//TOMATE MORTO
		}else if((strcmp(v[i].nome, "tomate") == 0) && (v[i].tempo == c)&& (strcmp(v[i].status, "vivo") == 0)){
			mvprintw(v[i].linha,v[i].coluna,"X");
			mapa_in.m[v[i].linha][v[i].coluna] = 'X';
			v[i].status="morto";
			min ++;

		}else if ((strcmp(v[i].nome, "tomate") == 0) && (v[i].tempo > c))
			v[i].tempo -= 1;
		//BATATA DOCE ATT
		if ((strcmp(v[i].nome, "batata doce")) == 0 && (v[i].tempo == 0)){
			mvprintw(v[i].linha,v[i].coluna,"D");
			mapa_in.m[v[i].linha][v[i].coluna] = 'D';
			v[i].tempo -= 1;

		//BATATA DOCE MORTA
		}else if((strcmp(v[i].nome, "batata doce")) == 0 && (v[i].tempo == d)&& (strcmp(v[i].status, "vivo") == 0)){
			mvprintw(v[i].linha,v[i].coluna,"X");
			mapa_in.m[v[i].linha][v[i].coluna] = 'X';
			v[i].status="morto";
			min ++;

		}else if ((strcmp(v[i].nome, "batata doce") == 0) && (v[i].tempo > d))
			v[i].tempo -= 1;
	}	
	return(min);
}
personagem empilha_semente(mapa mapa_in, int linha, int coluna, personagem p, int *c)
{
	tipo_semente aux;	
	semente *nova_semente;
	nova_semente = malloc(sizeof(nova_semente));
	nova_semente -> tipo_semente = malloc(sizeof(nova_semente -> tipo_semente));
	
	if (mapa_in.m[linha][coluna] == ',') // -> batata
	{
		aux.nome = "batata";
		nova_semente -> tipo_semente = tpb;
		nova_semente -> tipo_semente -> nome = aux.nome;
		mvprintw(linha,coluna," ");
		mapa_in.m[linha][coluna] = ' ';

	}
	else if (mapa_in.m[linha][coluna] == 'w') // -> alface
	{	
		aux.nome = "alface";
		nova_semente  -> tipo_semente = tpc;
		//nova_semente -> tipo_semente -> nome = aux.nome;
		mvprintw(linha,coluna," ");
		mapa_in.m[linha][coluna] = ' ';
	}
	else if (mapa_in.m[linha][coluna] == 'o') // -> tomate
	{
		aux.nome = "tomate";
		nova_semente  -> tipo_semente = tpa;
		nova_semente -> tipo_semente -> nome = aux.nome;
		mvprintw(linha,coluna," ");
		mapa_in.m[linha][coluna] = ' ';
	}
	else if (mapa_in.m[linha][coluna] == 'd') // -> batata_doce
	{
		aux.nome = "batata doce";
		nova_semente -> tipo_semente = tpd;
		//nova_semente -> tipo_semente -> nome = aux.nome;
		mvprintw(linha,coluna," ");
		mapa_in.m[linha][coluna] = ' ';
	}
	else if (mapa_in.m[linha][coluna] == 'B') // -> batata
	{
		aux.nome = "batatap";
		nova_semente -> tipo_semente = tpb;
		nova_semente -> tipo_semente -> nome = aux.nome; 		
		mvprintw(linha,coluna,".");
		mapa_in.m[linha][coluna] = '.';

	}
	else if (mapa_in.m[linha][coluna] == 'W') // -> alface
	{
		aux.nome = "alfacep";
		nova_semente  -> tipo_semente = tpc;
		nova_semente -> tipo_semente -> nome = aux.nome; 		
		mvprintw(linha,coluna,".");
		mapa_in.m[linha][coluna] = '.';
	}
	else if (mapa_in.m[linha][coluna] == '+') // -> tomate
	{
		aux.nome = "tomatep";	
		nova_semente  -> tipo_semente = tpa;
		nova_semente -> tipo_semente -> nome = aux.nome; 		
		mvprintw(linha,coluna,".");
		mapa_in.m[linha][coluna] = '.';
	}
	else if (mapa_in.m[linha][coluna] == 'D') // -> batata_doce
	{
		aux.nome = "batata docep";
		nova_semente -> tipo_semente = tpd;
		nova_semente -> tipo_semente -> nome = aux.nome; 		
		mvprintw(linha,coluna,".");
		mapa_in.m[linha][coluna] = '.';
	}
	nova_semente -> prox = NULL;
	if (p.m.topo != NULL)
	{
		nova_semente -> prox = p.m.topo;
	}
	p.m.topo = nova_semente;

	p.m.quantidade += 1;
	legenda(p);
	return p;
}
personagem plantar (mapa mapa_in, int linha , int coluna, personagem p, fila_plantio *fp)//DESEMPILHA SEMENTES DA MOCHILA
{
	char *aux_string;
	if (p.m.topo != NULL)
	{
		if (strcmp(p.m.topo -> tipo_semente -> nome,"alface") == 0 )
		{
			mvprintw(linha,coluna,"*");
			mapa_in.m[linha][coluna] = '*';
		}
		else if (strcmp(p.m.topo -> tipo_semente -> nome,"batata") == 0 )
		{
			mvprintw(linha,coluna,"*");
			mapa_in.m[linha][coluna] = '*';
		}
		else if (strcmp(p.m.topo -> tipo_semente -> nome,"tomate") == 0 )
		{
			mvprintw(linha,coluna,"*");
			mapa_in.m[linha][coluna] = '*';
		}
		else if (strcmp(p.m.topo -> tipo_semente -> nome,"batata doce") == 0 )
		{
			mvprintw(linha,coluna,"*");
			mapa_in.m[linha][coluna] = '*';
		}
		else{
			return p;
		}
		semente *aux;
		aux = p.m.topo;
		p.m.topo = p.m.topo -> prox;
		free(aux);
		aux_string = "";
		deslegenda(aux_string,p);
		p.m.quantidade -= 1;
	}
	return p;
}
void inicia_fila(fila_plantio *fp)
{
	fp -> max = 30;
	fp -> tam = 0;
	fp -> inicio = 0;
	fp -> fim = -1;
	fp -> dados = (tipo_semente*) malloc(fp -> max * sizeof(int));	
}

void insere_planta(fila_plantio *fp, int cont, tipo_semente *v)
{
	if(fp->fim == fp->max-1)
		fp->fim = -1;

	for (int i = 0; i < cont; i++){
		fp->fim += 1;
		fp->dados[fp->fim] = v[i]; // incrementa ultimo e insere
		fp->tam += 1; // mais um item inserido
	}

}
void imprimir_fila(fila_plantio *fp, int cont, mapa mapa_in){
	for(int i = 0; i <= 28; i++){
		mvprintw(mapa_in.linha+1+i,30,"                                  ");
	}
	for (int i = 0; i < cont; i++)
		mvprintw(mapa_in.linha+1+i,30, "%s %d %d %s",fp -> dados[i].nome,fp -> dados[i].linha,fp -> dados[i].coluna,fp -> dados[i].status);
}	
tipo_semente colhe_planta(fila_plantio *fp)
{ // pega o item do começo da fila

	tipo_semente temp = fp->dados[fp->inicio++]; // pega o valor e incrementa o primeiro
	if(fp->inicio == fp->max)
		fp->inicio = 0;

	fp->tam--;  // um item retirado
	return temp;
}

int vazia(fila_plantio *fp)
{ // retorna verdadeiro se a fila estÃ¡ vazia
	return (fp->tam==0);
}

int ehterreno(mapa mapa_in, int linha , int coluna)
{
	if (mapa_in.m[linha][coluna] == '.')
		return 1;
	else
		return  0;
}

int ehplanta (mapa mapa_in, int linha, int coluna)
{

	if (mapa_in.m[linha][coluna] == 'B' || mapa_in.m[linha][coluna] == 'D' || mapa_in.m[linha][coluna] == 'W' || mapa_in.m[linha][coluna] == '+')
		return 1;
	else
		return 0;
}

int tem_semente(mapa mapa_in, int linha, int coluna)
{
	if (mapa_in.m[linha][coluna] == ',' || mapa_in.m[linha][coluna] == 'o' || mapa_in.m[linha][coluna] == 'd' || mapa_in.m[linha][coluna] == 'w')
		return 1;
	else
		return 0;
	//empilhatp -> tempo = tempo;
}

void legenda(personagem p)
{
	mvprintw(p.m.quantidade,40,"%s\n",p.m.topo -> tipo_semente -> nome);

}

void deslegenda(char *aux_string, personagem p)
{
	mvprintw(p.m.quantidade,40,"%s\n",aux_string);

}
//Função para liberar a matriz alocada
mapa libera_matriz (mapa mapa_in)
{
	for (int i = 0; i < mapa_in.linha; i++)
		free(mapa_in.m[i]);
	free(mapa_in.m);
	return(mapa_in);
		
}
