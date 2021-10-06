#ifndef BOLA_H_INCLUDED
#define BOLA_H_INCLUDED

////////////////////////////////////////////////////////////////////////////////////////////////////
void movimenta_bola(int &pos_x,int &pos_y,int &dir_x,int &dir_y,int velo_bola){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o movimento da bola

	if(pos_x <= PAREDE_ESQUERDA && dir_x == -velo_bola){// Verifica se a bola está colidindo com a parede da esquerda
		dir_x = -dir_x; // Inverte a direção
	}
	if(pos_x >= PAREDE_DIREITA - 10 && dir_x == velo_bola){// Verifica se a bola está colidindo com a parede da direita
		dir_x = -dir_x; // Inverte a direção
	}
	if(pos_y <= PAREDE_SUPERIOR && dir_y == -velo_bola){// Verifica se a bola está colidindo com a parede superior
		dir_y = -dir_y; // Inverte a direção
	}
	pos_x += dir_x; // Realiza o movimento da bola na horizontal
    pos_y += dir_y; // Realiza o movimento da bola na vertical
//    pos_y += ((pos_y+100)/50) * dir_y; // Realiza o movimento da bola na vertical simulando a gravidade
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void primeiro_movimento(int &dir,int velo_bola){
////////////////////////////////////////////////////////////////////////////////////////////////////
//Procedimento que sorteia a direção inicial da bola

	int dir_sortiada;
	dir_sortiada = rand() % 3;// Sorteia as três direções possíveis para a bola iniciar
	switch(dir_sortiada){
		case 0: dir = velo_bola; break;	// Sorteio = 0, a bola iniciará na direção sudeste
		case 1: dir = 0; break;			// Sorteio = 1, a bola iniciará na direção sul
		case 2: dir = -velo_bola; break; 	// Sorteio = 2, a bola iniciará na direção sudoeste
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void inicia_bola(int &pos_x){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza a posição inicial da bola
	int pos_sortiada;

	pos_sortiada = rand() % 12 + 1;// Sorteia 12 possíveis locais para a bola iniciar

	pos_x = (bola->w / 2)+(pos_sortiada * 50);// Multiplica por 50 para dar um espaçamento notável de uma posição sorteada para outra
}

#endif // BOLA_H_INCLUDED
