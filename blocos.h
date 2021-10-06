#ifndef BLOCOS_H_INCLUDED
#define BLOCOS_H_INCLUDED

////////////////////////////////////////////////////////////////////////////////////////////////////
int preenche_matriz_blocos(int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int bonus[LIN_BLOCOS][COL_BLOCOS]){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que limpa o lixo de mem�ria da matriz dos blocos, e identifica quantas linhas de blocos haver� dependendo da fase

	int linhas = 0;

	for (int l = 0; l < LIN_BLOCOS; l++){// Zerar a matriz inteira, blocos e b�nus
		for (int c = 0; c < COL_BLOCOS; c++){
			blocos[l][c] = 0;
			bonus[l][c] = 0;
		}
	}

	switch (fase){ //Selecionar a qtd de linhas de blocos dependendo da fase
		case 1: linhas = 3;break; // Se for a fase 1, ter� 3 linhas de blocos
		case 2: linhas = 5;break; // Se for a fase 2, ter� 5 linhas de blocos
		case 3: linhas = 5;break; // Se for a fase 3, ter� 5 linhas de blocos
		case 4: linhas = (rand() % 4) + 4;break; // Se for a fase 4, ter� de 4 a 7 linhas de blocos
		case 5: linhas = (rand() % 3) + 6;break; // Se for a fase 5, ter� de 6 a 8 linhas de blocos
	// Condi��es para as outras fases
	}

	for (int l = 0; l < linhas; l++){ // Preencher linhas necess�rias para a fase atual
		for (int c = 0; c < COL_BLOCOS; c++){
			blocos[l][c] = 1; // Identifica com 1 os blocos que ser�o usados na fase atual
		}
	}
	return linhas;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void sorteia_blocos_pontos(int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int qtd_lin){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o sorteio dos blocos com pontua��o especial

	int qtd_sorteios = NULL, sort_lin = 0,sort_col = 0;

	switch (fase){ //Selecionar a qtd de blocos que tem pontua��o especial dependendo da fase
		case 1: qtd_sorteios = 10;break; // Se for a fase 1, ter� 10 blocos == 30%
		case 2: qtd_sorteios = 19;break; // Se for a fase 2, ter� 19 blocos == 35%
		case 3: qtd_sorteios = 19;break; // Se for a fase 3, ter� 19 blocos == 35%
		case 4: qtd_sorteios = (qtd_lin * 3) + (qtd_lin/2);// 35%
		case 5: qtd_sorteios = (qtd_lin * 3) + (qtd_lin/2);// 35%
	// Condi��es para as outras fases
	}

	for (int i = 0; i < qtd_sorteios; i++){ // Realiza o sorteio da posi��o dos blocos com pontua��o especial
		label: // Ponto de partida caso o bloco sorteado ja esteja com alguma propriedade especial
		sort_col = rand() % COL_BLOCOS;// Sorteia a posi��o nas colunas poss�veis para o bloco especial
		sort_lin = rand() % qtd_lin;   // Sorteia a posi��o nas linhas poss�veis da fase atual
		if(blocos[sort_lin][sort_col] == 1){ //Verifica se o sorteio foi em um bloco poss�vel para atribui��o de pontua��o especial sem afetar uma outra caracter�stica especial
			blocos[sort_lin][sort_col] = 6; // Atribui ao local sorteado o valor do bloco especial para a pontua��o
		}else{ // Caso o sorteio seja numa posi��o com outra caracter�stica especial ou at� mesmo ja tenha sido sorteado, realiza o processo de sorteio novamente
			goto label; // Vai para o ponto de partida do sorteio
		}
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void sorteia_blocos_fixos(int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int qtd_lin){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o sorteio dos blocos fixos

	int qtd_sorteios = NULL, sort_lin = 0,sort_col = 0;

	switch (fase){ //Selecionar a qtd de blocos fixos dependendo da fase
		case 2: qtd_sorteios = 3;break; // Se for a fase 2, ter� 3 blocos
		case 3: qtd_sorteios = 3;break; // se for a fase 3, ter� 3 blocos
		case 4: qtd_sorteios = qtd_lin;break;// se for a fase 4, ter� 10% dos blocos s�o fixos
		case 5: qtd_sorteios = qtd_lin;break;// fase 5 = 10% fixos
	// Condi��es para as outras fases
	}

	for (int i = 0; i < qtd_sorteios; i++){// Realiza o mesmo que � feito com os blocos de pontua��o especial
		label:
		sort_col = rand() % COL_BLOCOS;
		sort_lin = rand() % qtd_lin;
		if(blocos[sort_lin][sort_col] == 1){
			blocos[sort_lin][sort_col] = 7;
		}else{
			goto label;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void sorteia_blocos_especiais(int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int qtd_lin){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o sorteio dos blocos especiais
	int qtd_sorteios = NULL, sort_lin = 0,sort_col = 0;

	switch (fase){ //Selecionar a qtd de blocos especiais dependendo da fase
		case 3: qtd_sorteios = 5;break; // se for a fase 3, ter� 5 blocos == 10%
		case 4: qtd_sorteios = qtd_lin + qtd_lin/2;break;
		case 5: qtd_sorteios = qtd_lin + qtd_lin/2;break;
	// Condi��es para as outras fases
	}

	for (int i = 0; i < qtd_sorteios; i++){// Realiza o mesmo que � feito com os blocos de pontua��o especial
		label:
		sort_col = rand() % COL_BLOCOS;
		sort_lin = rand() % qtd_lin;
		if(blocos[sort_lin][sort_col] == 1){
			blocos[sort_lin][sort_col] = rand() % 4 + 2; //Sorteia a vida do bloco! De 2 a 5!
		}else{
			goto label;
		}
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sorteia_bonus(int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int qtd_lin,int bonus[LIN_BLOCOS][COL_BLOCOS]){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o sorteio dos b�nus
	int qtd_sorteios = NULL, sort_lin = 0, sort_col = 0;

	switch(fase){
		case 4: qtd_sorteios = qtd_lin - 1;
		case 5: qtd_sorteios = qtd_lin - 1;
	// Condi��es para as pr�ximas fases
	}

	for(int i = 0; i < qtd_sorteios; i++){ // Realiza o mesmo que os blocos especias, fixo etc, s� que para os b�nus
		label:
		sort_col = rand() % COL_BLOCOS;
		sort_lin = rand() % qtd_lin;
		if(blocos[sort_lin][sort_col] == 1){
			bonus[sort_lin][sort_col] = 1;
		}else{
			goto label;
		}
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void colisao_blocos(int blocos[LIN_BLOCOS][COL_BLOCOS],int bola_x,int bola_y,int &dir_x,int &dir_y,int fase,int &pontos,int pont1,int pont2,int bonus[LIN_BLOCOS][COL_BLOCOS],Bonus ctrl_bonus[7],int &cont_bonus){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que verifica se h� colis�o da bola com algum bloco

	int pos_x = (bola_x+5)/60, pos_y = bola_y/14;// Vari�veis recebem a equivalencia da posi��o da bola com o indice da matriz dos blocos

	// Verifica a colis�o acima ou abaixo dos blocos
	if(blocos[pos_y][pos_x] != 0){					// Verifica se h� bloco na matriz na posi��o que equivale a posi��o da bola na tela
		if(bonus[pos_y][pos_x] == 1){
			ctrl_bonus[cont_bonus].ativo = true;
			ctrl_bonus[cont_bonus].x = pos_x * 60 + 28;
			ctrl_bonus[cont_bonus].y = pos_y * 14 + 2;
			ctrl_bonus[cont_bonus].dy = 1;
			switch(fase){
                case 5:{ int dx = rand() % 3;
						switch(dx){
							case 0: ctrl_bonus[cont_bonus].dx = 0;break;
							case 1: ctrl_bonus[cont_bonus].dx = 1;break;
							case 2: ctrl_bonus[cont_bonus].dx = -1;break;
						}
						break;
                }
                default:
                    ctrl_bonus[cont_bonus].dx = 0;
                    break;
			}
			cont_bonus++;
		}
		dir_y = -dir_y;								// Se houver rebate a bola
		if(blocos[pos_y][pos_x] != 7){				// Verifica se � um bloco quebr�vel
			if(blocos[pos_y][pos_x] == 1 && bonus[pos_y][pos_x] == 0){// Verifica se � um bloco de pontua��o normal e se n�o h� bonus nele
				pontos += pont1;					// Soma o valor do ponto normal a pontua��o
			}else if(blocos[pos_y][pos_x] == 6){	// Se n�o for de ponto normal verifica se � de pontua��o diferenciada.
				pontos += pont2;					// Soma o valor do ponto diferente a pontua��o
				blocos[pos_y][pos_x] = 1;			// Atribui 1 ao bloco de ponto diferente para no decremento abaixo deixa-lo em 0 para quebr�-lo
			}else if(blocos[pos_y][pos_x] == 2){
				pontos += 15;						// Incrementa 15 a pontua��o para quando o bloco tiver vida 1 incrementar 5 e fechar a soma em 20 pontos para os blocos especiais
			}
			blocos[pos_y][pos_x]--;					// Se for quebr�vel decrementa a vida do bloco
		}
	}
	// Verifica a colis�o lateral, na direita do bloco
	if((dir_x < 0 && bola_x > PAREDE_ESQUERDA + 20) && ((bola_x - 3)/60 < pos_x)){
		pos_x = (bola_x - 3)/60;
		if(blocos[pos_y][pos_x] != 0){// Realiza as mesmas verifica��es que as colis�es acima e abaixo
			if(bonus[pos_y][pos_x] == 1){
				ctrl_bonus[cont_bonus].ativo = true;
				ctrl_bonus[cont_bonus].x = pos_x * 60 + 28;
				ctrl_bonus[cont_bonus].y = pos_y * 14 + 2;
				ctrl_bonus[cont_bonus].dy = 1;
				switch(fase){
					case 5: ctrl_bonus[cont_bonus].dx = rand() % 3;break;
					default:ctrl_bonus[cont_bonus].dx = 0;break;
				}
				cont_bonus++;
			}
			dir_x = -dir_x;
			if(blocos[pos_y][pos_x] != 7){
				if(blocos[pos_y][pos_x] == 1 && bonus[pos_y][pos_x] == 0){
					pontos += pont1;
				}else if(blocos[pos_y][pos_x] == 6){
					pontos += pont2;
					blocos[pos_y][pos_x] = 1;
				}else if(blocos[pos_y][pos_x] == 2){
					pontos += 15;
				}
				blocos[pos_y][pos_x]--;
			}
		}
	}
	// Verifica a colis�o lateral, na direita do bloco
	if(((dir_x > 0) && (bola_x < PAREDE_DIREITA - 20)) && ((bola_x + 13)/60 > pos_x)){
		pos_x = (bola_x + 13)/60;
		if(blocos[pos_y][pos_x] != 0){// Realiza as mesmas verifica��es que as colis�es acima e abaixo
			if(bonus[pos_y][pos_x] == 1){
				ctrl_bonus[cont_bonus].ativo = true;
				ctrl_bonus[cont_bonus].x = pos_x * 60 + 28;
				ctrl_bonus[cont_bonus].y = pos_y * 14 + 2;
				ctrl_bonus[cont_bonus].dy = 1;
				switch(fase){
					case 5: ctrl_bonus[cont_bonus].dx = rand() % 3;break;
					default:ctrl_bonus[cont_bonus].dx = 0;break;
				}
				cont_bonus++;
			}
			dir_x = -dir_x;
			if(blocos[pos_y][pos_x] != 7){
				if(blocos[pos_y][pos_x] == 1 && bonus[pos_y][pos_x] == 0){
					pontos += pont1;
				}else if(blocos[pos_y][pos_x] == 6){
					pontos += pont2;
					blocos[pos_y][pos_x] = 1;
				}else if(blocos[pos_y][pos_x] == 2){
					pontos += 15;
				}
				blocos[pos_y][pos_x]--;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void movimenta_bonus(Bonus ctrl_bonus[7],int i){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento respons�vel por movimentar os b�nus

	if(ctrl_bonus[i].x <= PAREDE_ESQUERDA){// Verifica se o b�nus est� colidindo com a parede da esquerda
		ctrl_bonus[i].x = PAREDE_DIREITA - 11; // Posiciona-o na parede da direita
	}
	if(ctrl_bonus[i].x >= PAREDE_DIREITA - 10){// Verifica se o b�nus est� colidindo com a parede da direita
		ctrl_bonus[i].x = PAREDE_ESQUERDA + 1; // Posiciona-o na parede da esquerda
	}

	ctrl_bonus[i].x += ctrl_bonus[i].dx; // Realiza o movimento do b�nus na horizontal
	ctrl_bonus[i].y += ctrl_bonus[i].dy; // Realiza o movimento do b�nus na vertical

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void colisao_bonus_rebatedor(Bonus ctrl_bonus[7],int i,int rebat_pos_x,int &pontos,int pont_bonus){
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que verifica a colis�o do b�nus com o rebatedor

	if(ctrl_bonus[i].x >= rebat_pos_x - 10 && ctrl_bonus[i].x <= rebat_pos_x + 135){ // Testa se o b�nus est� na faixa do rebatedor
		ctrl_bonus[i].ativo = false;
		pontos += pont_bonus;
	}
	if(ctrl_bonus[i].y > REBATEDOR_Y + 30){ // Se o b�nus ja passou do rebatedor desativa-o
		ctrl_bonus[i].ativo = false;
	}

}

#endif // BLOCOS_H_INCLUDED
