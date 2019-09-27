#ifndef __JOGO__
#define __JOGO__

typedef struct mapa{
	int linha;
	int coluna;
	char **m;
}mapa;

typedef struct tipo_semente
{
	char *nome;
	int tempo;
	int linha;
	int coluna;
	int nivel_satisfacao;
	char *status;	
}tipo_semente;

typedef struct semente {
    tipo_semente* tipo_semente;
    struct semente *prox;
} semente;

typedef struct mochila{
	semente* topo;
	int tam;
	int quantidade;
//	semente* v[10];
}mochila;

typedef struct personagem{
	int fome; //max -> 100
	int saude; //max -> 100
	struct mochila m;
}personagem;

//nodo
typedef struct planta{
	struct semente s;
	//int estado_planta; 
	//int nivel_satisfacao;
	struct planta *prox;
	struct planta *ant;
}planta;

typedef struct fila_plantio
{
	int max;
	int tam;
	int inicio;
	int fim;
	tipo_semente* dados;

}fila_plantio;

personagem comer_semente(personagem p);

personagem desempilha (mapa mapa_in, int linha, int coluna, personagem p);

void joga_fora(personagem p, mapa mapa_in, int linha, int coluna);

void lista (tipo_semente *v, int tam, int k, mapa mapa_in);

int tira_vetor (int l, int c, tipo_semente *v, int tam);

tipo_semente* inicializa_tipos(tipo_semente *tp, char *nome, int tempo, int nivel_satisfacao, char *status);

personagem iniciapersonagem(personagem p);

personagem iniciamochila(personagem p);

mapa aloca_mapa(mapa mapa_in, FILE *arq);

void gera_mapa(mapa mapa_in);

char** aloca_matriz (mapa mapa_in);

mapa libera_matriz (mapa mapa_in);

char gera_posicao (mapa mapa_in);

personagem perso_info(personagem p, mapa mapa_in,int *k);

personagem anda_personagem(int *i, int *j, int ch, mapa mapa_in, personagem p, fila_plantio *fp, int *cont, tipo_semente *v, int *c, int *max, int *min);

int diminui_tempo(int cont, tipo_semente *v, mapa mapa_in, int min);

personagem plantar (mapa mapa_in, int linha , int coluna, personagem p, fila_plantio *fp);

personagem colhe_semente(int linha, int coluna, mapa mapa_in, personagem p);

void ordena_vetor (int cont, tipo_semente *v, mapa mapa_in);

int ehterreno(mapa mapa_in, int linha , int coluna);

int ehplanta (mapa mapa_in, int linha, int coluna);

int tem_semente(mapa mapa_in, int linha, int coluna);

personagem empilha_semente(mapa mapa_in, int linha, int coluna, personagem p, int *c);

void gera_semente(mapa mapa_in, int *c);

void inicia_fila(fila_plantio *fp);

void insere_planta(fila_plantio *fp, int cont, tipo_semente *v);

void imprimir_fila(fila_plantio *fp, int cont, mapa mapa_in);

tipo_semente colhe_planta(fila_plantio *fp);

int vazia(fila_plantio *fp);

void cria_tipos();

void legenda(personagem p);

void deslegenda (char *aux_string,personagem p);

#endif
