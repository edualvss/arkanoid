#ifndef PROCESSA_JOGO_H_INCLUDED
#define PROCESSA_JOGO_H_INCLUDED
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void desenha_jogo(int rebat,int pos_bola_x,int pos_bola_y,int blocos[LIN_BLOCOS][COL_BLOCOS],int fase,int pontos,int vidas,int bonus[LIN_BLOCOS][COL_BLOCOS],Bonus ctrl_bonus[7]){
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza os desenhos na tela!

	blit(fundo[fase-1],buffer,0,0,0,0,800,600); // Desenha o plano de fundo do jogo

	for (int l = 0; l < LIN_BLOCOS; l++){ // Desenha os blocos
		for (int c = 0; c < COL_BLOCOS; c++){
			if(blocos[l][c] == 0)
				continue;

			blit(bloco[blocos[l][c]-1],buffer,0,0,c*60,l*14,60,14);
		}
	}

	// Para saber onde o bônus fica
//	for (int l = 0; l < LIN_BLOCOS; l++){ // Desenha os bônus
//		for (int c = 0; c < COL_BLOCOS; c++){
//			if(bonus[l][c] == 0)
//				continue;
//
//			draw_sprite(buffer,bonuss,c*60+28,l*14+2); // Desenha os bônus
//		}
//	}

	draw_sprite(buffer,rebatedor,rebat,REBATEDOR_Y); // Desenha o rebatedor

	rotate_sprite(buffer,bola, pos_bola_x,pos_bola_y, itofix(-pos_bola_x*VELOCIDADE_GIRO)); // Desenha e rotaciona bola

	rotate_sprite(buffer,roda, rebat+27,REBATEDOR_Y+20, itofix(rebat*VELOCIDADE_GIRO));	// Desenha e rotaciona a roda da esquerda do rebatedor
	rotate_sprite(buffer,roda, rebat+88,REBATEDOR_Y+20, itofix(rebat*VELOCIDADE_GIRO));	// Desenha e rotaciona a roda da direita do rebatedor

// Informações do canto direito do jogo!
	textprintf_ex(buffer, font, 670, 10 , makecol(255, 0, 0),-1,"ESC para Sair");
	textprintf_ex(buffer, font, 670, 40 , makecol(255, 0, 0),-1,"Barra de espaço");
	textprintf_ex(buffer, font, 710, 50 , makecol(255, 0, 0),-1,"para");
	textprintf_ex(buffer, font, 670, 60 , makecol(255, 0, 0),-1,"usar o trunfo!");
	textprintf_ex(buffer, font, 670, 90 , makecol(255, 0, 0),-1,"(P)ausa!");
	textprintf_ex(buffer, font, 670, 120, makecol(255, 0, 0),-1,"Vidas = %d", vidas);
	textprintf_ex(buffer, font, 670, 150, makecol(255, 0, 0),-1,"Fase = %d", fase);
	textprintf_ex(buffer, font, 670, 180, makecol(255, 0, 0),-1,"Tempo: %i:%i",minutos,segundos);
	textprintf_ex(buffer, font, 670, 210, makecol(255, 0, 0),-1,"Pontos = %d", pontos);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void principal(int blocos[LIN_BLOCOS][COL_BLOCOS],int *tecla,int fase,int &pontos,int &vidas,int pont1,int pont2,int bonus[LIN_BLOCOS][COL_BLOCOS],Bonus ctrl_bonus[7],int pont_bonus){
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento responsável pela execução do jogo

	int cont_trunfo = 1,velo_bola = VELOCIDADE_INICIAL_BOLA; // Variáveis que controlam a velocidade da bola e a qtd de trunfos por fase
	int rebatedor_pos_x = 270; // Posição inicial do rebatedor
	int posicao_bola_x,posicao_bola_y = bola->h / 2 + 115, dir_bola_x,dir_bola_y = velo_bola; // Variáveis da bola
	int cont_velo_bola = 0; // Contador para o aumento da velocidade da bola na décima rebatida no rebatedor
	bool flag_termino, flag_velocidade_bola = false; // Flags para a velocidade da bola ser aumentada apenas uma vez, e para identificar o fim da partida
	int cont_bonus = 0;

	inicia_bola(posicao_bola_x); // Sorteia um local aleatório para o inicio da bola
	primeiro_movimento(dir_bola_x,velo_bola); // Sorteia uma direção aleatória para a bola iniciar

	for(int i = 0; i < 7; i++){
		ctrl_bonus[i].ativo = false;
	}

	while(posicao_bola_y < REBATEDOR_Y+30){ // Realiza a execução do jogo
//		rebatedor_pos_x = mouse_x;// Caso seja usado o mouse // OBS: Não está totalmente funcional
		flag_termino = true; // Atribui verdadeiro para o flag indicando que ainda há blocos
		movimenta_rebatedor(rebatedor_pos_x); // Realiza o movimento do rebatedor
		movimenta_bola(posicao_bola_x,posicao_bola_y,dir_bola_x,dir_bola_y,velo_bola);// Movimenta a bola respeitando os limites de paredes
		if(posicao_bola_y >= REBATEDOR_Y && posicao_bola_y <= REBATEDOR_Y + 25){// Se a bola estiver na faixa do rebatedor em relação as linhas(pixels)
			rebatidas_rebatedor(rebatedor_pos_x,posicao_bola_x,posicao_bola_y,dir_bola_x,dir_bola_y,velo_bola,cont_velo_bola);// Verifica se há colisão da bola com o rebatedor
		}
		if(cont_velo_bola == 10 && !flag_velocidade_bola){ //Verifica a qtd de rebatidas da bola no rebatedor para aumentar a velocidade da mesma
			velo_bola *= 1.4; // Aumenta 40% a velocidade na 10ª rebatida
			flag_velocidade_bola = true;// Indica que já foi aumentada a velocidade da bola
			switch(dir_bola_x){// Condições para a primeira colisão lateral da bola com as paredes após o aumento da velocidade da bola
				case VELOCIDADE_INICIAL_BOLA: dir_bola_x = velo_bola;break;
				case -VELOCIDADE_INICIAL_BOLA: dir_bola_x = -velo_bola;break;
			}
			switch(dir_bola_y){// Condições para a primeira colisão superior da bola com as paredes após o aumento da velocidade da bola
				case VELOCIDADE_INICIAL_BOLA: dir_bola_y = velo_bola;break;
				case -VELOCIDADE_INICIAL_BOLA: dir_bola_y = -velo_bola;break;
			}
		}
		if(posicao_bola_y < 112){// Se a bola situar-se onde há possibilidade de colisão com blocos
			colisao_blocos(blocos,posicao_bola_x,posicao_bola_y,dir_bola_x,dir_bola_y,fase,pontos,pont1,pont2,bonus,ctrl_bonus,cont_bonus);// Verifica se há colisão ou não!
		}

		desenha_jogo(rebatedor_pos_x,posicao_bola_x,posicao_bola_y,blocos,fase,pontos,vidas,bonus,ctrl_bonus);// Desenha tudo no buffer

		for(int i = 0; i < cont_bonus; i++){ // Percorre os bonus ja ativos
			if(ctrl_bonus[i].ativo){ // verifica se o bônus é ativo
				movimenta_bonus(ctrl_bonus,i);// Realiza o movimento do bônus
				if(ctrl_bonus[i].y >= REBATEDOR_Y && ctrl_bonus[i].y <= REBATEDOR_Y + 25){// Se o bônus estiver na faixa do rebatedor em relação as linhas(pixels)
					colisao_bonus_rebatedor(ctrl_bonus,i,rebatedor_pos_x,pontos,pont_bonus);// Verifica se há colisão do bônus com o rebatedor
				}
				draw_sprite(buffer,bonuss,ctrl_bonus[i].x,ctrl_bonus[i].y); // Desenha o bônus na tela
			}
		}

		blit(buffer,screen,0,0,0,0,800,600);// Desenha o buffer na tela (double buffering)
		clear(buffer);// Limpa o buffer para a tela não ficar piscando ou distorcendo a imagem a cada volta no laço
		vsync();	  // Otimiza o processamento do jogo para um valor constante
		if(key[KEY_P]){ // Verifica se o jogador pausou o jogo
			allegro_message("Jogo pausado, clique em ok para continuar!");// Pausa o jogo exibindo uma msg de pausa
		}

		if(key[KEY_SPACE] && cont_trunfo > 0){ // Trunfo caso o movimento da bola não seja o suficiente para rebater em todos os blocos
			dir_bola_y = -dir_bola_y;
			cont_trunfo--;
		}

		for(int l = 0; l < LIN_BLOCOS; l++){// Percorre a matriz dos blocos
			for(int c = 0; c < COL_BLOCOS; c++){
				if(blocos[l][c] > 0 && blocos[l][c] < 7){// Verifica se ainda há blocos
					flag_termino = false; // Caso haja, atribui falso ao flag que termina a fase
				}
			}
		}

		if(flag_termino){ // Se não houver mais blocos termina a fase
			*tecla = 0;// Indica que a fase foi concluida
			break;
		}
		if(key[KEY_ESC]){ // Se o usuário pressionar ESC aborta o jogo
			*tecla = 1;// Indica que o usuário abortou o jogo
			break;
		}
		if(minutos < 0){ // Se o tempo acabar encerra o jogo
			*tecla = 3;// Indica que o tempo acabou
			break;
		}
		if(key[KEY_Z]){// Shifter para passar para a próxima fase -> somente para fins de teste
			*tecla = 0;
			break;
		}

	}
	if(posicao_bola_y >= REBATEDOR_Y+30){// Verifica se a saída do laço do jogo foi por perda de uma vida
		*tecla = 2;// Indica que foi perdida uma vida
	}
//	rest(1000); //rest() == _sleep() // da conio2
//	keypressed(); == kbhit() // da conio2
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void cadastra_senha(char *temp){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Entrada de dados (senha)

	const int TAM_NOME = 20;// Tamanho máximo permitido para o nome do jogador
	char i_nome[TAM_NOME];
	clear_keybuf();
	// Entrada de dados em allegro
	int pos_cursor = 0;
	do{
		blit(password,buffer,0,0,0,0,800,600);
		if(keypressed()){
			int  nova_tecla = readkey();
			char ASCII      = nova_tecla & 0xff;
			char scancode   = nova_tecla >> 8;
			// Uma tecla foi pressionada(keypressed); adicionar a string
			if(ASCII >= 32 && ASCII <= 126){
				if(pos_cursor < TAM_NOME - 1){
					i_nome[pos_cursor] = ASCII;
					pos_cursor++;
					i_nome[pos_cursor] = '\0';
				}
			}else if(scancode == KEY_BACKSPACE){
				if (pos_cursor > 0){
					pos_cursor--;
				}
				i_nome[pos_cursor] = '\0';
			}
		}
		// Desenha na tela o que está sendo digitado
		textprintf_ex(buffer, font, 400, 295, makecol(255, 255, 255),-1,"%s",i_nome);
		textprintf_ex(buffer, font, 310, 227, makecol(27, 27, 27),-1,"Cadastre uma senha para acessar o jogo na fase em que parou!");
		vline(buffer, pos_cursor * 8 + 400, 295, 303, makecol(255, 255, 255));
		blit(buffer, screen, 0, 0, 0, 0, 800, 600);
		clear(buffer);
   }while(!key[KEY_ENTER]);

	strcpy(temp,i_nome);

	allegro_message("Senha cadastrada com sucesso!");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool verifica_senha(Continue jogador,char *temp){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Entrada de dados (senha)

	const int TAM_NOME = 20;// Tamanho máximo permitido para o nome do jogador
	char i_nome[TAM_NOME];
	clear_keybuf();
	// Entrada de dados em allegro
	int pos_cursor = 0;
	do{
		blit(password,buffer,0,0,0,0,800,600);
		if(keypressed()){
			int  nova_tecla = readkey();
			char ASCII      = nova_tecla & 0xff;
			char scancode   = nova_tecla >> 8;
			// Uma tecla foi pressionada(keypressed); adicionar a string
			if(ASCII >= 32 && ASCII <= 126){
				if(pos_cursor < TAM_NOME - 1){
					i_nome[pos_cursor] = ASCII;
					pos_cursor++;
					i_nome[pos_cursor] = '\0';
				}
			}else if(scancode == KEY_BACKSPACE){
				if (pos_cursor > 0){
					pos_cursor--;
				}
				i_nome[pos_cursor] = '\0';
			}
		}
		// Desenha na tela o que está sendo digitado
		textprintf_ex(buffer, font, 400, 295, makecol(255, 255, 255),-1,"%s",i_nome);
		textprintf_ex(buffer, font, 310, 227, makecol(27, 27, 27),-1,"Digite a senha para acessar o jogo anterior!");
		vline(buffer, pos_cursor * 8 + 400, 295, 303, makecol(255, 255, 255));
		blit(buffer, screen, 0, 0, 0, 0, 800, 600);
		clear(buffer);
   }while(!key[KEY_ENTER]);

	strcpy(temp,i_nome);

	if(strcmp(temp,jogador.play.nome) == 0){
		return true;
	}else{
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void jogo(Player play[5],Continue &jogador,char opcao){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inicia o processamento de uma nova partida

	int vidas = 3, pontos = 0, ponto_1 = 1, ponto_2 = 5,pont_bonus;// Controlam a execução do jogo
	int blocos[LIN_BLOCOS][COL_BLOCOS], fase = 1,qtd_linhas;// Matriz dos blocos
	int tecla = 10; // Variável de indicação do que ocorreu na execução do jogo
	int bonus[LIN_BLOCOS][COL_BLOCOS];// Bônus
	Player atual;
	Bonus ctrl_bonus[7];

	if(opcao == 'i' || opcao == 'I'){
		minutos = 20;// Tempo em minutos para cada partida iniciada
		segundos = 1;// Tempo inicial em segundos(OBS: É '1' pelo fato de ja decrementar no primeiro momento de execução)
		jogador.fase = fase;
		jogador.play.min = minutos;
		jogador.play.seg = segundos;
		jogador.play.pontos = pontos;
		jogador.vidas = vidas;
	}else if(opcao == 'c' || opcao == 'C'){
		minutos = jogador.play.min;
		segundos = jogador.play.seg;
		fase = jogador.fase;
		jogador.sim = 0;
		pontos = jogador.play.pontos;
		vidas = jogador.vidas;
		switch(fase){
			case 2:
			case 3:
			case 4:ponto_1 = 5;ponto_2 = 10;pont_bonus = 50;break;
			case 5:ponto_1 = 5;ponto_2 = 10;pont_bonus = 60;break;
		}
	}
	qtd_linhas = preenche_matriz_blocos(blocos,fase,bonus);// Preenche a matriz dos blocos para a primeira fase
	sorteia_blocos_pontos(blocos,fase,qtd_linhas);// Sorteia os blocos com pontuação especial para a primeira fase
	if(fase > 1)
		sorteia_blocos_fixos(blocos,fase,qtd_linhas);  // Sorteia os blocos fixos de acordo com a fase
	if(fase > 2){ // Se for após a fase 2 as fases possuem blocos especiais
		sorteia_blocos_especiais(blocos,fase,qtd_linhas);// Sorteia os blocos especiais
	}
	if(fase>3){
		sorteia_bonus(blocos,fase,qtd_linhas,bonus);
	}

	do{

		principal(blocos,&tecla,fase,pontos,vidas,ponto_1,ponto_2,bonus,ctrl_bonus,pont_bonus);// Chama a execução do jogo
		if(tecla == 0){// Verifica se houve conclusão na fase
			fase++;// Passa para a próxima fase
			jogador.fase = fase;
			jogador.play.min = minutos;
			jogador.play.seg = segundos;
			jogador.play.pontos = pontos;
			jogador.vidas = vidas;
			allegro_message("Parabéns!");// Exibe a msg
			qtd_linhas = preenche_matriz_blocos(blocos,fase,bonus);// Preenche a matriz dos blocos de acordo com a fase
			sorteia_blocos_pontos(blocos,fase,qtd_linhas); // Sorteia os blocos com pontuação especial de acordo com a fase
			sorteia_blocos_fixos(blocos,fase,qtd_linhas);  // Sorteia os blocos fixos de acordo com a fase
			if(fase > 2){ // Se for após a fase 2 as fases possuem blocos especiais
				sorteia_blocos_especiais(blocos,fase,qtd_linhas);// Sorteia os blocos especiais
			}
			if(fase>3){
				sorteia_bonus(blocos,fase,qtd_linhas,bonus);
			}
			tecla = 10;// Limpa o indicador de ocorrência
			switch(fase){// Condições para setar a qtd incremento de pontos de acordo com a fase
				case 2: ponto_1 = 5;ponto_2 = 10;break;
				case 3: ponto_1 = 5;ponto_2 = 10;break;
				case 4: ponto_1 = 5;ponto_2 = 10;pont_bonus = 50;break;
				case 5: ponto_1 = 5;ponto_2 = 10;pont_bonus = 60;break;
				// Na 3ª,4ª e 5ª fase não é necessário alterar o valor do ponto 1 e 2 pq é o mesmo valor da fase anterior(2)
			}
		}
		if(fase > 5){ // Caso tenha terminado as fases
			allegro_message("Parabéns você ganhou!\nSua pontuação: %d",pontos); // Exibe a msg
			cadastra(atual,play,pontos);
			tecla = 3;
			break; // Encerra a partida
		}
		if(tecla == 1){// Caso o jogo tenha sido abortado, realiza o que é necessário
			allegro_message("Jogo encerrado pelo usuário!");
			break; // Encerra a partida
		}
		if(tecla == 2){// Caso tenha perdido uma vida
			vidas--; // Decrementa as vidas
			if(vidas != 0)// Caso ainda haja vidas
				allegro_message("Perdeu 1 vida\nPressione ok para continuar!");// Exibe a msg
			tecla = 10;// Limpa o indicador de ocorrência
		}
		if(vidas == 0 || tecla == 3){ // Condições para o encerramento por game over
			allegro_message("Você perdeu!");// Exibe a msg
			cadastra(atual,play,pontos);
			break;// Encerra a partida
		}

	}while(true); // Executa o jogo

	if(tecla == 1){
		jogador.sim = 1;
		char *temp = new char[20];
		cadastra_senha(temp);
		jogador.play.nome = temp;
	}else{
		jogador.sim = 0;
	}
}

#endif // PROCESSA_JOGO_H_INCLUDED
