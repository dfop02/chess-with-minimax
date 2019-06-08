#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "regras.h"
#include "computer.h"

#define TAM 10

// Save the plays of each player here
struct tabuleiro{
    struct posicao_tabuleiro *head;
};

void menu(){
    int op, loop = 1;
    do{
    	// First lin and col to say the position
		// Others numbers means the pieces of chess, for example 12/13 are the pawns
	    int tabuleiro[TAM][TAM] = {
	    	// 10, 20, 30, 40, 50, 60, 70, 80 and 11, 21, 31, 51, 41, 61, 71, 81 is:
	    	// Tower, Horse, Bishop, Quenn, King, Bisp, Horse, Tower in this order
	    	// All 12 and 13 are pawns.
	    	// The 00's means a empty square.
	    	// The 15 it's empty space.
	        {99, 91, 92, 93, 94, 95, 96, 97, 98, 99},
	        { 8, 10, 20, 30, 40, 50, 60, 70, 80,  8},
	        {07, 12, 12, 12, 12, 12, 12, 12, 12, 07},
	        {06, 00, 00, 00, 00, 00, 00, 00, 00, 06},
	        {05, 00, 00, 00, 00, 00, 00, 00, 00, 05},
	        {04, 00, 00, 00, 00, 00, 00, 00, 00, 04},
	        {03, 00, 00, 00, 00, 00, 00, 00, 00, 03},
	        {02, 13, 13, 13, 13, 13, 13, 13, 13, 02},
	        {01, 11, 21, 31, 41, 51, 61, 71, 81, 01},
			{99, 91, 92, 93, 94, 95, 96, 97, 98, 99}
		};
				
	    system("cls");
	    printf("\tBem Vindo ao XXadreZZ | By Diogo F.\n\n");
	    printf("[1] Novo Jogo - Player 1 Vs Player 2\n");
	    printf("[2] Novo Jogo - Player Vs Computador (Em Testes)\n");
	    printf("[3] Novo Jogo - Computer Vs Computer (Em Testes)\n");
	    printf("[4] Tutorial de como jogar\n");
	    printf("[5] Sair\n\n");
	    scanf("%d", &op);
	        switch(op){
	            case 1:
	            	// Game Player vs Player
	                start(tabuleiro);
	                break;
	            case 2:
	            	// import the struct "Jogadas" from regras.h for not conflit
	            	// Game Player vs Computer
	                start_ia(tabuleiro);
	                break;
	            case 3:
	            	break;
	            case 4:
	                tutorial();
	                break;
	            case 5:
	            	exit(0);
	            default:
	                printf("\nOpção inválida. Por favor digite apenas uma das alternativas\n");
	                system("pause>null");
	                break;
	        }
    }while(loop == 1);
}

main(){
	char *locale;

    locale = setlocale(LC_ALL, "");
    
    menu();
        
    system("pause>null");
}
