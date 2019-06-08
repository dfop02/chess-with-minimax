#ifndef MODELS_H_INCLUDED
// block the repeat of variables
#define MODELS_H_INCLUDED

typedef struct jogadas{
	int lin_atual;
	int col_atual;
	int lin_dps;
	int col_dps;
	int pontuacao;
	struct jogadas *prox;
}Jogadas;

typedef struct turno{
    int turn;
    struct turno *prox;
}Turno;

typedef struct lista_ia{
	struct jogadas *head;
}Lista_ia;

#endif // MODELS_H_INCLUDED
