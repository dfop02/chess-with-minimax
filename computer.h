#ifndef COMPUTER_H
#define COMPUTER_H
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>
#include "regras.h"
#include "models.h"

#define TAM 10

int totalCalculatedPlays = 0;

// Create the list with all moves by computer
Lista_ia* inicializarLista(){
    Lista_ia *tmp = (Lista_ia*)malloc(sizeof(Lista_ia));
    if(tmp != NULL){
        tmp->head = NULL;  
        return tmp;  
    }
    return NULL;      
}

bool estaNaLista(int val, int arr[], int len){
    int i;
    for (i=0; i <= len; i++) {
        if (arr[i] == val){
            return true;
        }
    }
    return false;
}

int pontuar_jogadas(int tabuleiro[TAM][TAM], int x, int y);

// Just test to check the possible plays
void mostrar_movimentos_possiveis(Lista_ia *Allmoves){
	Jogadas *aux = (Jogadas*)malloc(sizeof(Jogadas));
    printf("----------------- Lista de Possiveis Movimentos do Player 2 -----------------\n\n");
    for(aux = Allmoves->head; aux != NULL; aux = aux->prox){
    	printf("Movimento de [Lin: %d][Col: %d] para [Lin: %d][Col: %d] || Score: %d\n\n", aux->lin_atual, aux->col_atual, aux->lin_dps, aux->col_dps, aux->pontuacao);
    }
    free(aux);
    system("pause>null");
}

// Computer is ever the player 2
// Minimax algorithm
// First step, take all possible plays by player 2
void verificar_jogadas_possiveis(int tabuleiro[TAM][TAM], Lista_ia *Allmoves, int Player){
	int i, j, m, n;
	Jogadas *tmp;
	for(i=1; i<9; i++){
		for(j=1; j<9; j++){
			if(checar_peca_inimiga(tabuleiro[i][j]) == Player){
				for(m=1; m<9; m++){
					for(n=1; n<9; n++){
						tmp = (Jogadas*)malloc(sizeof(Jogadas));
						tmp->lin_atual = i;
						tmp->col_atual = j;
						tmp->lin_dps = m;
						tmp->col_dps = n;
						if(validar_jogada(tabuleiro, tmp) == 1){
							tmp->pontuacao = pontuar_jogadas(tabuleiro, m, n);
							//tmp->pontuacao = 0;
							tmp->prox = Allmoves->head;
							Allmoves->head = tmp;
						}
                        else{
	                        // Free memory space
	                        free(tmp);
	                    }
					}
				}
			}
		}
	}
}

int posso_morrer(int tabuleiro[TAM][TAM], int x, int y, int player){
    int i = 0;
    int piece = 0;
    int lista_size = 0;
    bool mata = false;
    // 10, 20, 30, 40, 50, 60, 70, 80 and 11, 21, 31, 51, 41, 61, 71, 81 is:
    // Tower, Horse, Bishop, Quenn, King, Bisp, Horse, Tower in this order


    // Mesma linha
    for (i = 1; i <= 8; i++){
        if(checar_peca_inimiga(tabuleiro[x][y + i]) != player && checar_peca_inimiga(tabuleiro[x][y + i]) != 0){
            piece = tabuleiro[x][y + i];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {81, 51, 11};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {81, 51, 41, 11};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Mesma linha
    for (i = 1; i > 0; i--){
        if(checar_peca_inimiga(tabuleiro[x][y - 1]) != player && checar_peca_inimiga(tabuleiro[x][y - 1]) != 0){
            piece = tabuleiro[x][y - 1];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {81, 51, 11};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {81, 51, 41, 11};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Mesma Coluna
    for (i = 1; i <= 8; i++){
        if(checar_peca_inimiga(tabuleiro[x + i][y]) != player && checar_peca_inimiga(tabuleiro[x + i][y]) != 0){
            piece = tabuleiro[x + i][y];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {81, 51, 11};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {81, 51, 41, 11};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }

            if(mata){
                return 1;
            }

        }
    }

    // Mesma Coluna
    for (i = 1; i > 0; i--){
        if(checar_peca_inimiga(tabuleiro[x - i][y]) != player && checar_peca_inimiga(tabuleiro[x - i][y]) != 0){
            piece = tabuleiro[x - i][y];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {81, 51, 11};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {81, 51, 41, 11};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Diagonal esquerda e cima
    for(i = 1; i <= 8; i++){
        if(checar_peca_inimiga(tabuleiro[x + i][y + i]) != player, checar_peca_inimiga(tabuleiro[x + i][y + i]) != 0){
            piece = tabuleiro[x + i][y + i];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {51, 21, 71};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {51, 21, 71, 41};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Diagonal esquerda e baixo
    for(i = 1; i<=8; i++){
        if(checar_peca_inimiga(tabuleiro[x + i][y - i]) != 1 && checar_peca_inimiga(tabuleiro[x + i][y - i]) != 0){
            piece = tabuleiro[x + i][y - i];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {51, 21, 71};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[5] = {51, 21, 71, 41, 13};
                lista_size = 5;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Direita e cima
    for(i = 1; i <= 8; i++){
        if(checar_peca_inimiga(tabuleiro[x - i][y + i]) != player && checar_peca_inimiga(tabuleiro[x - i][y + i]) != 0){
            piece = tabuleiro[x - i][y + i];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {51, 21, 71};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[4] = {51, 21, 71, 41};
                lista_size = 4;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    // Direita e baixo
    for(i = 1; i <= 8; i++){
        if(checar_peca_inimiga(tabuleiro[x - i][y - i]) != player && checar_peca_inimiga(tabuleiro[x - i][y - i]) != 0){
            piece = tabuleiro[x - i][y - i];
            lista_size = 0;
            if (i > 1){
                int enemies[3] = {51, 21, 71};
                lista_size = 3;
                mata = estaNaLista(piece, enemies, lista_size);

            }else if (i == 1){
                int enemies[5] = {51, 21, 71, 41, 13};
                lista_size = 5;
                mata = estaNaLista(piece, enemies, lista_size);

            }
            if(mata){
                return 1;
            }
        }
    }

    return 0;
}


// Create a score for each piece killed
int pontuar_jogadas(int tabuleiro[TAM][TAM], int x, int y){
	int pontuacao = 0;

	if(tabuleiro[x][y] != 00){
		// Player 1 Pawn
		if(tabuleiro[x][y] == 13)
			pontuacao += 10;
		// Player 2 Pawn
		if(tabuleiro[x][y] == 12)
			pontuacao -= 10;
		// Player 1 Tower
		if(tabuleiro[x][y] == 11)
			pontuacao += 50;
		// Player 2 Tower
		if(tabuleiro[x][y] == 10)
			pontuacao -= 50;
		// Player 1 Horse
		if(tabuleiro[x][y] == 21)
			pontuacao += 30;
		// Player 1 Horse
		if(tabuleiro[x][y] == 20)
			pontuacao -= 30;
		// Player 1 Bisphop
		if(tabuleiro[x][y] == 31)
			pontuacao += 30;
		// Player 2 Bisphop
		if(tabuleiro[x][y] == 30)
			pontuacao -= 30;
		// Player 1 Queen
		if(tabuleiro[x][y] == 51)
			pontuacao += 100;
		// Player 2 Queen
		if(tabuleiro[x][y] == 40)
			pontuacao -= 100;
		// Player 1 King
		if(tabuleiro[x][y] == 41)
			pontuacao += 900;
		// Player 2 King
		if(tabuleiro[x][y] == 50)
			pontuacao -= 900;
	}
	return pontuacao;
}

// Pick the best score move in possible moves
Jogadas* escolher_jogada_pontuada(int tabuleiro[TAM][TAM], Lista_ia *Allmoves, int Player){
	int MaiorValor = 0;
	int MenorValor = 0;
	Jogadas *aux = (Jogadas*)malloc(sizeof(Jogadas));
	Jogadas *tmp = (Jogadas*)malloc(sizeof(Jogadas));
	for(aux = Allmoves->head; aux != NULL; aux = aux->prox){
		if(Player == 2){
			if(aux->pontuacao >= MaiorValor){
				MaiorValor = aux->pontuacao;
				tmp->lin_atual = aux->lin_atual;
				tmp->lin_dps = aux->lin_dps;
				tmp->col_atual = aux->col_atual;
				tmp->col_dps = aux->col_dps;
				tmp->pontuacao = MaiorValor;
				// TEST
				//printf("PIECE: %d PARA: %d | %d\n", tabuleiro[tmp->lin_atual][tmp->col_atual], tmp->lin_dps, tmp->col_dps);
				//system("pause>null");
			}
		}
		else{
			if(aux->pontuacao <= MenorValor){
				MaiorValor = aux->pontuacao;
				tmp->lin_atual = aux->lin_atual;
				tmp->lin_dps = aux->lin_dps;
				tmp->col_atual = aux->col_atual;
				tmp->col_dps = aux->col_dps;
				tmp->pontuacao = MenorValor;
				// TEST
				//printf("PIECE: %d PARA: %d | %d\n", tabuleiro[tmp->lin_atual][tmp->col_atual], tmp->lin_dps, tmp->col_dps);
				//system("pause>null");
			}
		}
	}
	free(aux);
	return tmp;
}

// liberando o lixo acumulado
void LiberarMemoria(Lista_ia* root){
    Jogadas* next = root->head;
    while(next != NULL){
        Jogadas* tmp = next;
        next = next->prox;
        free(tmp);
    }
    free(root);
}

// Simulate 5 turn ahead for choose the best current move
Jogadas *minimax(int tabuleiro[TAM][TAM], int depth, int Player, int alpha, int beta, Jogadas* novaJogada){
	// Copy the board for don't change it
	int i, j, copia[TAM][TAM];
	for(i=0; i<=9; i++){
		for(j=0; j<=9; j++){
			copia[i][j] = tabuleiro[i][j];
		}
	}
	
	copia[novaJogada->lin_dps][novaJogada->col_dps] = copia[novaJogada->lin_atual][novaJogada->col_atual];
    copia[novaJogada->lin_atual][novaJogada->col_atual] = 0;
	
	totalCalculatedPlays++;
	
	// TESTS
	//mostra_tabuleiro(copia);
	//Sleep(500);
	// TESTS

	if(depth == 0){
		novaJogada->pontuacao = pontuar_jogadas(copia, novaJogada->lin_dps, novaJogada->col_dps);
		return novaJogada;
	}

    Lista_ia *Moves = inicializarLista();

    verificar_jogadas_possiveis(copia, Moves, Player);
	
    Jogadas *tmp;

	// Simulating the current Player 2 (Computer) move
	if(Player == 2){
		novaJogada->pontuacao = -9999;

		for(tmp = Moves->head; tmp != NULL; tmp = tmp->prox){
			
			Jogadas *BestMove = minimax(copia, depth - 1, 1, alpha, beta, tmp);
			
			if(BestMove->pontuacao > novaJogada->pontuacao){
				novaJogada->pontuacao = BestMove->pontuacao;
			}
			if(alpha < BestMove->pontuacao){
				alpha = BestMove->pontuacao;
			}
			if(beta <= alpha){
				return BestMove;
			}
		}
		LiberarMemoria(Moves);
		return novaJogada;
	}
	// Simulating the best Player 1 move
	else{
		novaJogada->pontuacao = 9999;

		for(tmp = Moves->head; tmp != NULL; tmp = tmp->prox){
			
			Jogadas *BestMove = minimax(copia, depth - 1, 2, alpha, beta, tmp);

			if(BestMove->pontuacao < novaJogada->pontuacao){
				novaJogada->pontuacao = BestMove->pontuacao;
			}
			if(beta < BestMove->pontuacao){
				beta = BestMove->pontuacao;
			}
			if(beta <= alpha){
				return BestMove;
			}
		}
		LiberarMemoria(Moves);
		return novaJogada;
	}
}

Jogadas *IniciarMinMax(int tabuleiro[TAM][TAM], int depth){
	Lista_ia *Moves = inicializarLista();
	totalCalculatedPlays = 0;
	// Copy the board for don't change it
	int i, j, copia[TAM][TAM];
	for(i=0; i<=9; i++){
		for(j=0; j<=9; j++){
			copia[i][j] = tabuleiro[i][j];
		}
	}
	
	verificar_jogadas_possiveis(copia, Moves, 2);

    Jogadas *bestMove = NULL;
    Jogadas *tmp;
    
    for(tmp = Moves->head; tmp != NULL; tmp = tmp->prox){
        // iniciando busca
        Jogadas *current = minimax(copia, depth - 1, 1, -10000, 10000, tmp);
        if(bestMove == NULL || current->pontuacao > bestMove->pontuacao){
            bestMove = current;
        }
    }
    // clonando resultado para retornar antes de liberar a memoria
    Jogadas *result = (Jogadas*)malloc(sizeof(Jogadas));
    result = bestMove;

    LiberarMemoria(Moves);

    return result;
}

// Run the game
void start_ia(int tabuleiro[TAM][TAM]){
	int i, j, x, y, xeque, pode_jogar, cont, player, Player = 2, movimento_anterior_lin, movimento_anterior_col;
	bool continuar = true;
	Lista_ia *Rei_Pode_Jogar;
	Jogadas *movimentos;
	Turno *game = (Turno*)malloc(sizeof(Turno));
	game->turn = 1;
	
	// Inform to players who is player 1 and player 2
	system("cls");
	printf("\tComputer || TIME VERMELHO\n\n\n\t\t VS\n\n\n\tPLAYER 1 || TIME VERDE\n");
	// Wait 2 seconds before continue
	Sleep(2000);
	
	while(continuar == true){
		// Show the board
		mostra_tabuleiro(tabuleiro);
		
		// Show if the move do a xeque!
		if(xeque == 1){
			printf("\n\t\t        Xeque! \n");
		}
		// Show the current turn and who will play
		if((game->turn % 2) == 0){
			player = 2;
			printf("\n\t\tTurno %d  ||  Jogador %d\n", game->turn, player);
		}
		if((game->turn % 2) == 1){
			player = 1;
			printf("\n\t\tTurno %d  ||  Jogador %d\n", game->turn, player);
		}
		// Block if you are not the piece of player 1
		if(player == 1){
			// If is current in xeque and don't have anyplace to go
			if((xeque == 1) && (Rei_Pode_Jogar->head == NULL)){
				// CheckMate - Game Over
				pode_jogar = 999;
			}
			else{
				// Get the last enemy move for a Check compare
				if(game->turn != 1){
					movimento_anterior_lin = movimentos->lin_dps;
					movimento_anterior_col = movimentos->col_dps;
				}
				// Get the moves just for player 1
				movimentos = digitar_jogada();
				// If the player wrong the moves
				if((movimentos->lin_atual == '0') || (movimentos->col_atual == '0') || (movimentos->lin_dps == '0') || (movimentos->col_dps == '0')){
					pode_jogar = 0;
				}
				// If the player moves are ok
				else{
					if(checar_peca_inimiga(tabuleiro[movimentos->lin_atual][movimentos->col_atual]) == 1){
						// Check if that moves can play
						pode_jogar = validar_jogada(tabuleiro, movimentos);
						
						// If the King is current in Check, look if the next move he and continue in Check
						if(xeque == 1){
							Jogadas *aux = (Jogadas*)malloc(sizeof(Jogadas));
							if(tabuleiro[movimentos->lin_atual][movimentos->col_atual] == 41){
							// If the king can do while in Check
								for(aux = Rei_Pode_Jogar->head; aux != NULL; aux = aux->prox){
									if((movimentos->lin_dps != aux->lin_dps) && (movimentos->col_dps != aux->col_dps)){
										// Check error, and block the move
										pode_jogar = 50;
									}
									else{
										// Can play if that place don't have Check
										pode_jogar = 1;
									}
								}
							}	
							else{
								// If other piece kill and cancel the Check
								if((movimentos->lin_dps == movimento_anterior_lin) && (movimentos->col_dps = movimento_anterior_col)){
									pode_jogar = 1;
								}
								else{
									// Check error, and block the move
									pode_jogar = 50;
								}
							}
							free(aux);
						}	
					}
					else if(checar_peca_inimiga(tabuleiro[movimentos->lin_atual][movimentos->col_atual]) == 0){
						// If don't exist the moved piece
						pode_jogar = 0;
					}
					else{
						// If try move the opponent piece
						pode_jogar = 10;
					}
				}
			}
		}
		// Block if you are not the piece of player 2
		if(player == 2){
			// If is current in xeque and don't have anyplace to go
			if(gameover(tabuleiro) == 1){
				// CheckMate - Game Over
				pode_jogar = 999;
			}
			else{
				clock_t start, end;
				
				// So mostra o tempo necessario pra calcular tudo... //
				double cpu_time_used;
				start = clock();
				// -- //
				
				movimentos = IniciarMinMax(tabuleiro, 5);
				
				// So mostra o tempo necessario pra calcular tudo... //
				end = clock();
 				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 				// -- //
 				
				pode_jogar = 1;
				
				printf("\n Tempo: %.2f segundos", cpu_time_used);
				printf("\n Total de jogadas calculadas: %d", totalCalculatedPlays);
				
				system("pause>null");
				
			}
		}
		// Do the move of the pieces if the move can play
		if(pode_jogar == 1){		
			tabuleiro[movimentos->lin_dps][movimentos->col_dps] = tabuleiro[movimentos->lin_atual][movimentos->col_atual];
			tabuleiro[movimentos->lin_atual][movimentos->col_atual] = 00;
			// Next turn
			game->turn++;
			// Check if the current play do a xeque
			Rei_Pode_Jogar = inicializarLista();
			xeque = checar_xeque(tabuleiro, player, Rei_Pode_Jogar);
		}
		// except, if the player try play with the enemy piece
		else if(pode_jogar == 10){
			printf("\n\tMovimento inválido, não é a sua vez!\n");
			system("pause>null");
		}
		else if(pode_jogar == 50){
			printf("\n\tMovimento inválido, seu Rei continuará em xeque!\n");
			system("pause>null");
		}
		else if(pode_jogar == 999){
			if(player == 2){
				system("cls");
				printf("\n\t\t    Xeque-Mate!\n");
				// Player 1 win
				printf("\tPARABÉNS! O PLAYER 1 VENCEU!\n\n\tDigite qualquer tecla para voltar ao menu.");
				system("pause>null");
				continuar = false;
			}
			else{
				system("cls");
				printf("\n\t\t    Xeque-Mate!\n");
				// Player 1 win
				printf("\tPARABÉNS! O PLAYER 2 VENCEU!\n\n\tDigite qualquer tecla para voltar ao menu.");
				system("pause>null");
				continuar = false;
			}
		}
		// default error
		else{
			printf("\n\tMovimento inválido, tente novamente.\n");
			system("pause>null");
		}
		
		// Pode_jogar: 0 - Default Error // 1 - Can Play // 10 - Wrong Player try play // 50 - King Check, need save him

	};
}
#endif
