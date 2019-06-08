#ifndef REGRAS_H
#define REGRAS_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <locale.h>
#include <windows.h>
#include "models.h"

#define TAM 10
// shows the current board
void mostra_tabuleiro(int tabuleiro[TAM][TAM]){
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Save the standard console color
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int i, j;

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){
            if(tabuleiro[i][j] == 00){
                printf("|   |");
            }
            else if((tabuleiro[i][j] == 12) || (tabuleiro[i][j] == 13)){
            	printf("| ");
                if (tabuleiro[i][j] == 12){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 13){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("P");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf(" |");
            }
            else if((tabuleiro[i][j] == 10) || (tabuleiro[i][j] == 11) || (tabuleiro[i][j] == 80) || (tabuleiro[i][j] == 81)){
                printf("| ");
				if (tabuleiro[i][j] == 10 || tabuleiro[i][j] == 80){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 11 || tabuleiro[i][j] == 81){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("T");
                SetConsoleTextAttribute(hConsole, saved_attributes);
				printf(" |");
            }
            else if((tabuleiro[i][j] == 20) || (tabuleiro[i][j] == 21) || (tabuleiro[i][j] == 70) || (tabuleiro[i][j] == 71)){
                printf("| ");
				if (tabuleiro[i][j] == 20 || tabuleiro[i][j] == 70){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 21 || tabuleiro[i][j] == 71){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("C");
                SetConsoleTextAttribute(hConsole, saved_attributes);
				printf(" |");
            }
            else if((tabuleiro[i][j] == 30) || (tabuleiro[i][j] == 31) || (tabuleiro[i][j] == 60) || (tabuleiro[i][j] == 61)){
                printf("| ");
				if (tabuleiro[i][j] == 30 || tabuleiro[i][j] == 60){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 31 || tabuleiro[i][j] == 61){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("B");
                SetConsoleTextAttribute(hConsole, saved_attributes);
				printf(" |");
            }
            else if((tabuleiro[i][j] == 40) || (tabuleiro[i][j] == 51)){
                printf("|");
				if (tabuleiro[i][j] == 40){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 51){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("Rai");
                SetConsoleTextAttribute(hConsole, saved_attributes);
				printf("|");
            }
            else if((tabuleiro[i][j] == 50) || (tabuleiro[i][j] == 41)){
            	printf("|");
                if (tabuleiro[i][j] == 50){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                };
                if (tabuleiro[i][j] == 41){
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                };
                printf("Rei");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("|");
            }
            else if((tabuleiro[i][j]) > 90){
                if(tabuleiro[i][j] == 91)
                    printf("|-A-|");
                if(tabuleiro[i][j] == 92)
                    printf("|-B-|");
                if(tabuleiro[i][j] == 93)
                    printf("|-C-|");
                if(tabuleiro[i][j] == 94)
                    printf("|-D-|");
                if(tabuleiro[i][j] == 95)
                    printf("|-E-|");
                if(tabuleiro[i][j] == 96)
                    printf("|-F-|");
                if(tabuleiro[i][j] == 97)
                    printf("|-G-|");
                if(tabuleiro[i][j] == 98)
                    printf("|-H-|");
                if(tabuleiro[i][j] == 99)
                    printf("     ");
            }
            else{
                printf("|-%d-|", tabuleiro[i][j]);
            }
            if((j == 0) || (j == 8))
                printf(" ");
        }
        if((i == 0) || (i == 8))
            printf("\n");
        printf("\n");
    }
}

int checar_peca_inimiga(int piece){
    int i;
    int player1[9] = {13, 11, 21, 31, 41, 51, 61, 71, 81};
    int player2[9] = {12, 10, 20, 30, 40, 50, 60, 70, 80};
    for(i=0 ; i<=8; i++){
        if (player1[i] == piece)
            return 1;
        if (player2[i] == piece)
            return 2;
    }
    return 0;
}

// Check if the current play is possible and return 1 to true and 0 to false
int validar_jogada(int tabuleiro[TAM][TAM], Jogadas *tmp){
	int piece, x1, y1, x2, y2, i;
	x1 = tmp->lin_atual;
	y1 = tmp->col_atual;
	x2 = tmp->lin_dps;
	y2 = tmp->col_dps;
	piece = tabuleiro[x1][y1];

	// Block if the player try kill yourself
	if(piece == tabuleiro[x2][y2])
		return 0;
	// PAWNS //
	//  12 is a Pawns of player 2
	if(piece == 12){
		if(y1 == y2){
			if(x1 == 2 && (x2 == 3 || x2 == 4)){
				if(checar_peca_inimiga(tabuleiro[3][y2]) != 0){
	                return 0;
	            }
	            if(checar_peca_inimiga(tabuleiro[4][y2]) != 0){
	                return 0;
	            }
	        	return 1;
			}
			else if (x2 - x1 == 1) {
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) != 0){
	                return 0;
	            }
	        	return 1;
			}
		}
		if(y1 + 1 == y2 || y1 - 1 == y2){
			if (x2 - x1 == 1){
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	        	return 0;
			}
		}
	}
	//  13 is a Pawns of player 1
	if(piece == 13){
		if(y1 == y2){
			if(x1 == 7 && (x2 == 6 || x2 == 5)){
				if(checar_peca_inimiga(tabuleiro[6][y2]) != 0){
	                return 0;
	            }
	        	if(checar_peca_inimiga(tabuleiro[5][y2]) != 0){
	                return 0;
	            }
	        	return 1;
			}
			else if (x1 - x2 == 1) {
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) != 0){
	                return 0;
	            }
	        	return 1;
			}
		}
		if(y1 + 1 == y2 || y1 - 1 == y2){
			if (x1 - x2 == 1){
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	        	return 0;
			}
		}
	}
	// TOWERS //
	// 10 and 80 are Towers of player 2
	if((piece == 10) || (piece == 80)){
		// Tower is in same line
        if (x1 == x2){
            // Tower walk in left to right
            if (y1 < y2){
                // if any piece on way, friend: stop or enemy: eat
                for (i = y1+1; i < y2; i++){
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 0;
                }
                return 1;
            }
			else{
				// Tower walk in right to left
                for (i = y2-1; i > y1; i--){
					// if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 0;
                }
                return 1;
			}
        }
        // Tower is in same col
		else if(y1 == y2){
            // Tower is in down to up
            if(x1 < x2){
                for (i = x1+1; i < x2; i++){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 0;
                }
                return 1;
            }
            // Tower is in up to down
			else{
                for (i = x2-1; i > x1; i--){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 0;
                }
                return 1;
            }
        }
	}
	// 11 and 81 are Towers of player 1
	if((piece == 11) || (piece == 81)){
		// Tower is in same line
        if (x1 == x2){
            // Tower walk in left to right
            if (y1 < y2){
                // if any piece on way, stop or eat
                for (i = y1+1; i < y2; i++){
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 0;
                }
                return 1;
            }
			else{
				// Tower walk in right to left
                for (i = y2-1; i > y1; i--){
					// if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 0;
                }
                return 1;
			}
        }
        // Tower is in same col
		else if(y1 == y2){
            // Tower is in down to up
            if(x1 > x2){
                for (i = x1-1; i > x2; i--){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 0;
                }
                return 1;
            }
            // Tower is in up to down
			else{
                for (i = x2+1; i < x1; i++){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 0;
                }
                return 1;
            }
        }
	}
	// HORSES //
	// Horse of player 2
	if((piece == 20) || (piece == 70)){
		// if line um up or down
		if((x1 == x2-1) || (x1 == x2+1)){
			if(y1 == y2-2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
			if(y1 == y2+2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
		}
		// if cols left or right
		if((y1 == y2-1) || (y1 == y2+1)){
			if(x1 == x2-2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
			if(x1 == x2+2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
		}
	}
	// Horse of player 1
	if((piece == 21) || (piece == 71)){
		// if line um up or down
		if((x1 == x2-1) || (x1 == x2+1)){
			if(y1 == y2-2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
			if(y1 == y2+2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
		}
		// if cols left or right
		if((y1 == y2-1) || (y1 == y2+1)){
			if(x1 == x2-2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
			if(x1 == x2+2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
		}
	}
	// BISHOP //
	// Bishop of player 2
	if((piece == 31) || (piece == 61)){
        if (abs(x2 - x1) != abs(y2 - y1)){
            return 0;
        }
		if((x1 < x2) && (y1 < y2)){
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 2){
		            	return 0;
		            }
		        }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		if((x1 < x2) && (y1 > y2)){
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 2){
		            	return 0;
		            }
		        }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		if((x1 > x2) && (y1 < y2)){
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 2){
		            	return 0;
		            }
		        }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		if((x1 > x2) && (y1 > y2)){
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 2){
		            	return 0;
		            }
	            }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
	}
	// Bishop of player 1
	if((piece == 31) || (piece == 61)){
        if (abs(x2 - x1) != abs(y2 - y1)){
            return 0;
        }
		if((x1 < x2) && (y1 < y2)){
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 1){
		            	return 0;
		            }
		        }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		if((x1 < x2) && (y1 > y2)){
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 1){
		            	return 0;
		            }
		        }
	        }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		if((x1 > x2) && (y1 < y2)){
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 1){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		if((x1 > x2) && (y1 > y2)){
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 1){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
	}
	// QUENNS //
	// Queen of player 2
	if(piece == 40){
		// Queen is in same line
        if (x1 == x2){
            // Quenn walk in left to right
            if (y1 < y2){
                // if any piece on way, friend: stop or enemy: eat
                for (i = y1+1; i < y2; i++){
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                	return 0;
                }
                return 1;
            }
			else{
				// Quenn walk in right to left
                for (i = y1-1; i > y2; i--){
					// if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                	return 0;
                }
                return 1;
			}
        }
        // Quenn is in same col
		else if(y1 == y2){
            // Quenn is in down to up
            if(x1 < x2){
                for (i = x1+1; i < x2; i++){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                	return 0;
                }
                return 1;
            }
            // Quenn is in up to down
			else{
                for (i = x2-1; i > x1; i--){
                    // if any piece on way, stop
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                	return 0;
                }
                return 1;
            }
        }
        else if((x1 < x2) && (y1 < y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 2){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		else if((x1 < x2) && (y1 > y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 2){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		else if((x1 > x2) && (y1 < y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 2){
		            	return 0;
		            }
	            }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		else if((x1 > x2) && (y1 > y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 1){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 2){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 0;
            }
	        return 1;
		}
		return 0;
	}
	// Quenn of player 1
	if(piece == 51){
		// Queen is in same line
        if (x1 == x2){
            // Quenn walk in left to right
            if (y1 < y2){
                // if any piece on way, friend: stop or enemy: eat
                for (i = y1+1; i < y2; i++){
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                	return 0;
                }
                return 1;
            }
			else{
				// Quenn walk in right to left
                for (i = y2-1; i > y1; i--){
					// if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[x2][i]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                	return 0;
                }
                return 1;
			}
        }
        // Quenn is in same col
		else if(y1 == y2){
            // Quenn is in down to up
            if(x1 < x2){
                for (i = x1-1; i > x2; i--){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                	return 0;
                }
                return 1;
            }
            // Quenn is in up to down
			else{
                for (i = x2+1; i < x1; i++){
                    // if any piece on way, stop or eat
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 2){
                        return 0;
                    }
                    if(checar_peca_inimiga(tabuleiro[i][y2]) == 1){
                    	return 0;
                    }
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                    return 1;
                }
                if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                	return 0;
                }
                return 1;
            }
        }
        else if((x1 < x2) && (y1 < y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1+i]) == 1){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		else if((x1 < x2) && (y1 > y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1+i < x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1+i][y1-i]) == 1){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		else if((x1 > x2) && (y1 < y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1+i < y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1+i]) == 1){
		            	return 0;
		            }
		        }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		else if((x1 > x2) && (y1 > y2)){
            if (abs(x2 - x1) != abs(y2 - y1)){
                return 0;
            }
			for(i=1; i<=8; i++){
				if((x1-i > x2) && (y1-i > y2)){
					if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 2){
		                return 0;
		            }
		            if(checar_peca_inimiga(tabuleiro[x1-i][y1-i]) == 1){
		            	return 0;
		            }
	            }
	        }
	        if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 0;
            }
	        return 1;
		}
		return 0;
	}
	// KINGS //
	// King of player 2
	if(piece == 50){
		if(x1 == x2){
			if(y1+1 == y2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
			if(y1-1 == y2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
		}
		if(y1 == y2){
			if(x1+1 == x2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
			if(x1-1 == x2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	            	return 0;
	            }
	            return 1;
	        }
		}
		if((x1+1 == x2) && (y1+1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
            	return 0;
            }
            return 1;
        }
		if((x1+1 == x2) && (y1-1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
            	return 0;
            }
            return 1;
		}
		if((x1-1 == x2) && (y1+1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
            	return 0;
            }
            return 1;
        }
		if((x1-1 == x2) && (y1-1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
            	return 0;
            }
            return 1;
		}
	}
	// King of player 1
	if(piece == 41){
		if(x1 == x2){
			if(y1+1 == y2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
			if(y1-1 == y2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
		}
		if(y1 == y2){
			if(x1+1 == x2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
			if(x1-1 == x2){
				if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
	                return 1;
	            }
	            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
	            	return 0;
	            }
	            return 1;
	        }
		}
		if((x1+1 == x2) && (y1+1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
            	return 0;
            }
            return 1;
        }
		if((x1+1 == x2) && (y1-1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
            	return 0;
            }
            return 1;
		}
		if((x1-1 == x2) && (y1+1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
            	return 0;
            }
            return 1;
        }
		if((x1-1 == x2) && (y1-1 == y2)){
			if(checar_peca_inimiga(tabuleiro[x2][y2]) == 2){
                return 1;
            }
            if(checar_peca_inimiga(tabuleiro[x2][y2]) == 1){
            	return 0;
            }
            return 1;
		}
	}
	// if players 1 or 2 choose a outside board (lin 0 col 0 and lin 9 col 9)
	else{
		return 0;
	}
}

int checar_xeque(int tabuleiro[TAM][TAM], int player,  Lista_ia *Rei_Pode_Jogar){
	int i, j, m, n, enemy, xeque;
	
	Lista_ia *EnemyPlays = (Lista_ia*)malloc(sizeof(Lista_ia));
	EnemyPlays->head = NULL;
	
	Lista_ia *KingMoves = (Lista_ia*)malloc(sizeof(Lista_ia));
	KingMoves->head = NULL;
	
	Jogadas *TMP;
	Jogadas *SaveKingMoves;
	
	if(player == 2){
		enemy = 1;
	}
	else{
		enemy = 2;
	}	
    for(i=1 ; i<=8; i++){
		for(j=1; j<=8; j++){
			// First step, get all possible plays from Player 1 or Player 2
			if(checar_peca_inimiga(tabuleiro[i][j]) == player){
				for(m=1; m<=8; m++){
					for(n=1; n<=8; n++){
						TMP = (Jogadas*)malloc(sizeof(Jogadas));
						TMP->lin_atual = i;
						TMP->col_atual = j;
						TMP->lin_dps = m;
						TMP->col_dps = n;
						if(validar_jogada(tabuleiro, TMP) == 1){
							TMP->prox = EnemyPlays->head;
							EnemyPlays->head = TMP;
						}
					}
				}
			}
		}
	}
	free(TMP);
	for(i=1 ; i<=8; i++){
		for(j=1; j<=8; j++){
			if(enemy == 2){
				// Second step, get all possible plays from King of Player 2
				if(tabuleiro[i][j] == 50){
					for(m=1; m<=8; m++){
						for(n=1; n<=8; n++){
							SaveKingMoves = (Jogadas*)malloc(sizeof(Jogadas));
							SaveKingMoves->lin_atual = i;
							SaveKingMoves->col_atual = j;
							SaveKingMoves->lin_dps = m;
							SaveKingMoves->col_dps = n;
							if(validar_jogada(tabuleiro, SaveKingMoves) == 1){
								SaveKingMoves->prox = KingMoves->head;
								KingMoves->head = SaveKingMoves;
							}
						}
					}
				}
			}
			else{
				// Second step, get all possible plays from King of Player 1
				if(tabuleiro[i][j] == 41){
					for(m=1; m<=8; m++){
						for(n=1; n<=8; n++){
							SaveKingMoves = (Jogadas*)malloc(sizeof(Jogadas));
							SaveKingMoves->lin_atual = i;
							SaveKingMoves->col_atual = j;
							SaveKingMoves->lin_dps = m;
							SaveKingMoves->col_dps = n;
							if(validar_jogada(tabuleiro, SaveKingMoves) == 1){
								SaveKingMoves->prox = KingMoves->head;
								KingMoves->head = SaveKingMoves;
							}
						}
					}
				}
			}
		}
	}
	free(SaveKingMoves);

	// TESTS IF IS WORKING
	/*
	Jogadas *test;
    printf("----------------- Lista de Possiveis Movimentos do KING %d -----------------\n\n", enemy);
    for(test = KingMoves->head; test != NULL; test = test->prox){
    	printf("Movimento de [Lin: %d][Col: %d] para [Lin: %d][Col: %d]\n\n", test->lin_atual, test->col_atual, test->lin_dps, test->col_dps);
    }
    free(test);
    system("pause>null");
    
    Jogadas *Test;
    printf("----------------- Lista de seus Possiveis Movimentos -----------------\n\n");
    for(Test = EnemyPlays->head; Test != NULL; Test = Test->prox){
    	printf("Movimento de [Lin: %d][Col: %d] para [Lin: %d][Col: %d]\n\n", Test->lin_atual, Test->col_atual, Test->lin_dps, Test->col_dps);
    }
    free(Test);
    system("pause>null");
    */
    // TESTS
	
	Jogadas *aux = (Jogadas*)malloc(sizeof(Jogadas));
	Jogadas *tmp = (Jogadas*)malloc(sizeof(Jogadas));
	Jogadas *mover_rei = (Jogadas*)malloc(sizeof(Jogadas));
	// For each move from KING
	for(aux = KingMoves->head; aux != NULL; aux = aux->prox){
		// Check if any enemy piece can kill the KING on current place or around place
		for(tmp = EnemyPlays->head; tmp != NULL; tmp = tmp->prox){
			// Moves that King can do while in Check
			if((aux->lin_dps != tmp->lin_dps) && (aux->col_dps != tmp->col_dps)){
				mover_rei->lin_atual = aux->lin_atual;
				mover_rei->col_atual = aux->col_atual;
				mover_rei->lin_dps = aux->lin_atual;
				mover_rei->col_dps = aux->col_dps;
				// If that more is not repeated
				if(mover_rei != Rei_Pode_Jogar->head){
					mover_rei->prox = Rei_Pode_Jogar->head;
					Rei_Pode_Jogar->head = mover_rei;					
				}
			}
			// If the King is Current Check
			if((aux->lin_atual == tmp->lin_dps) && (aux->col_atual == tmp->col_dps)){
				xeque = 1;
			}
		}
	}
	free(tmp);
	free(aux);
	free(mover_rei);
	if(xeque == 1){
		return 1;
	}
    return 0;
}

int gameover(int tabuleiro[TAM][TAM]){
	Lista_ia *Rei_Pode_Jogar;
	if(checar_xeque(tabuleiro, 1,  Rei_Pode_Jogar) == 1){
		if(Rei_Pode_Jogar == NULL){
			// Check Mate!
			return 1;
		}
	}
	else if(checar_xeque(tabuleiro, 2, Rei_Pode_Jogar) == 1){
		if(Rei_Pode_Jogar == NULL){
			// Check Mate!
			return 1;
		}
	}
	else{
		return 0;
	}
}

// Take the current place of piece and the future place that player will play with lin and col
Jogadas* digitar_jogada(){
	char onde_esta[3], onde_vai[3];
	Jogadas *tmp = (Jogadas*)malloc(sizeof(Jogadas));

	// Default is 0
	tmp->lin_atual = 0;
	tmp->col_atual = 0;
	tmp->lin_dps = 0;
	tmp->col_dps = 0;

	printf("\n\tDigite onde está a peça que deseja jogar: ");
	scanf("%s", onde_esta);

	printf("\n\tDigite onde deseja jogar: ");
	scanf("%s", onde_vai);

	// Get the current line
	if((onde_esta[0] == 'A') || (onde_esta[0] == 'a'))
		tmp->col_atual = 1;
	if((onde_esta[0] == 'B') || (onde_esta[0] == 'b'))
		tmp->col_atual = 2;
	if((onde_esta[0] == 'C') || (onde_esta[0] == 'c'))
		tmp->col_atual = 3;
	if((onde_esta[0] == 'D') || (onde_esta[0] == 'd'))
		tmp->col_atual = 4;
	if((onde_esta[0] == 'E') || (onde_esta[0] == 'e'))
		tmp->col_atual = 5;
	if((onde_esta[0] == 'F') || (onde_esta[0] == 'f'))
		tmp->col_atual = 6;
	if((onde_esta[0] == 'G') || (onde_esta[0] == 'g'))
		tmp->col_atual = 7;
	if((onde_esta[0] == 'H') || (onde_esta[0] == 'h'))
		tmp->col_atual = 8;

	// Get the after line
	if((onde_vai[0] == 'A') || (onde_vai[0] == 'a'))
		tmp->col_dps = 1;
	if((onde_vai[0] == 'B') || (onde_vai[0] == 'b'))
		tmp->col_dps = 2;
	if((onde_vai[0] == 'C') || (onde_vai[0] == 'c'))
		tmp->col_dps = 3;
	if((onde_vai[0] == 'D') || (onde_vai[0] == 'd'))
		tmp->col_dps = 4;
	if((onde_vai[0] == 'E') || (onde_vai[0] == 'e'))
		tmp->col_dps = 5;
	if((onde_vai[0] == 'F') || (onde_vai[0] == 'f'))
		tmp->col_dps = 6;
	if((onde_vai[0] == 'G') || (onde_vai[0] == 'g'))
		tmp->col_dps = 7;
	if((onde_vai[0] == 'H') || (onde_vai[0] == 'h'))
		tmp->col_dps = 8;

	// Get the current cols
	if(onde_esta[1] == '1')
		tmp->lin_atual = 8;
	if(onde_esta[1] == '2')
		tmp->lin_atual = 7;
	if(onde_esta[1] == '3')
		tmp->lin_atual = 6;
	if(onde_esta[1] == '4')
		tmp->lin_atual = 5;
	if(onde_esta[1] == '5')
		tmp->lin_atual = 4;
	if(onde_esta[1] == '6')
		tmp->lin_atual = 3;
	if(onde_esta[1] == '7')
		tmp->lin_atual = 2;
	if(onde_esta[1] == '8')
		tmp->lin_atual = 1;

	// Get the after cols
	if(onde_vai[1] == '1')
		tmp->lin_dps = 8;
	if(onde_vai[1] == '2')
		tmp->lin_dps = 7;
	if(onde_vai[1] == '3')
		tmp->lin_dps = 6;
	if(onde_vai[1] == '4')
		tmp->lin_dps = 5;
	if(onde_vai[1] == '5')
		tmp->lin_dps = 4;
	if(onde_vai[1] == '6')
		tmp->lin_dps = 3;
	if(onde_vai[1] == '7')
		tmp->lin_dps = 2;
	if(onde_vai[1] == '8')
		tmp->lin_dps = 1;

	return tmp;
}

void tutorial(){
	system("cls");
	printf("Bem vindo ao jogo de xadrez.\n\n");
	Sleep(1500);
	printf("O jogo funciona assim:\n\n");
	Sleep(2000);
	printf("Nas bordas do tabuleiro há números e letras que correspondem a cada cada do jogo.\n\n");
	Sleep(1800);
	printf("O jogador deve digitar aonde está a peça que deseja mover no tabuleiro e dar enter.\n\n");
	Sleep(1800);
	printf("Depois o jogador deve digitar aonde no tabuleiro ele deseja que a peça selecionada seja movida e dar enter novamente.\n\n");
	Sleep(1800);
	printf("Bem simples não? Bom jogo!\n\n");
	Sleep(1800);
	system("pause");
}

// Run the game
void start(int tabuleiro[TAM][TAM]){
	int i, j, x, y, xeque, pode_jogar, player, movimento_anterior_lin, movimento_anterior_col;
	bool continuar = true;
	Lista_ia *Rei_Pode_Jogar;
	Jogadas *movimentos;
	Turno *game = (Turno*)malloc(sizeof(Turno));
	game->turn = 1;

	// Inform to players who is player 1 and player 2
	system("cls");
	printf("\tPLAYER 2 || TIME VERMELHO\n\n\n\t\t VS\n\n\n\tPLAYER 1 || TIME VERDE\n");
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
				// Get the moves
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
			if((xeque == 1) && (Rei_Pode_Jogar->head == NULL)){
				// CheckMate - Game Over
				pode_jogar = 999;
			}
			else{
				movimento_anterior_lin = movimentos->lin_dps;
				movimento_anterior_col = movimentos->col_dps;
				// Get the moves
				movimentos = digitar_jogada();
				// If the player wrong the moves
				if((movimentos->lin_atual == '0') || (movimentos->col_atual == '0') || (movimentos->lin_dps == '0') || (movimentos->col_dps == '0')){
					pode_jogar = 0;
				}
				else{
					if(checar_peca_inimiga(tabuleiro[movimentos->lin_atual][movimentos->col_atual]) == 2){
							// Check if that moves can play
						pode_jogar = validar_jogada(tabuleiro, movimentos);
						// If the King is current in Check, look if the next move he and continue in Check
						if(xeque == 1){
							Jogadas *aux = (Jogadas*)malloc(sizeof(Jogadas));
							if(tabuleiro[movimentos->lin_atual][movimentos->col_atual] == 50){
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
		// Do the move of the pieces if the move can play
		if(pode_jogar == 1){
			if(tabuleiro[movimentos->lin_dps][movimentos->col_dps] == 50){
				// Player 1 win
				system("cls");
				printf("\tPARABÉNS! O PLAYER 1 VENCEU!\n\n\tDigite qualquer tecla para voltar ao menu.");
				system("pause>null");
				continuar = false;
			}
			if(tabuleiro[movimentos->lin_dps][movimentos->col_dps] == 41){
				// Player 2 win
				system("cls");
				printf("\tPARABÉNS! O PLAYER 2 VENCEU!\n\n\tDigite qualquer tecla para voltar ao menu.");
				system("pause>null");
				continuar = false;
			}
			tabuleiro[movimentos->lin_dps][movimentos->col_dps] = tabuleiro[movimentos->lin_atual][movimentos->col_atual];
			tabuleiro[movimentos->lin_atual][movimentos->col_atual] = 00;
			// Next turn
			game->turn++;
			// Reset the list
			Rei_Pode_Jogar = (Lista_ia*)malloc(sizeof(Lista_ia));
			Rei_Pode_Jogar->head = NULL;
			// Check if the current play do a xeque
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
				printf("\n\t\t    Xeque-Mate!\n\n");
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

		// Test
		//printf("\nLin: %d Col: %d\nLin: %d Col: %d", movimentos->lin_atual, movimentos->col_atual, movimentos->lin_dps, movimentos->col_dps);
		//system("pause>null");
	};
}
#endif
