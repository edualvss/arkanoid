#ifndef TELAS_APRESENTACAO_H_INCLUDED
#define TELAS_APRESENTACAO_H_INCLUDED
void finaliza();
////////////////////////////////////////////////////////////////////////////////////////////////////
void menu(char &op,Continue &jogador,Player play[5]){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Desenha o menu

	blit(fundo_menu,buffer,0,0,0,0,800,600);// Desenha o fundo do menu
	textprintf_ex(buffer, font, 283, 440 , makecol(255, 0, 0),-1,"Digite a primeira letra da opção desejada!");

	if(jogador.sim == 1){
		blit(continuar,buffer,0,0,406,560,148,37); // Desenha a palavra continuar caso o jogador possa continuar
	}

	blit(buffer,screen,0,0,0,0,800,600);// Desenha o buffer na tela (double buffering)
	clear(buffer);// Limpa o buffer para a tela não ficar piscando ou distorcendo a imagem a cada volta no laço
	vsync();	  // Otimiza o processamento do jogo para um valor constante

	clear_keybuf(); // Limpa o buffer do teclado
	op = readkey();	// Aguarda uma tecla ser pressionada para o jogo iniciar // readkey() == getch() // da conio2

	if(op == 'i' || op == 'I'){
		jogo(play,jogador,op);
	}else if(op == 'c' || op == 'C'){
		if(jogador.sim == 1){
			bool flag_senha;
			char *temp = new char[20];
			flag_senha = verifica_senha(jogador,temp);
			if(flag_senha){
				jogo(play,jogador,op);
				clear_keybuf();
			}else{
				allegro_message("Senha incorreta para retomar a partida!");
			}
		}else{
			allegro_message("Opção indisponível");
		}
	}else if(op == 'r' || op == 'R'){
		exibe_ranking(play);
	}else if(op == 's' || op == 'S'){
		finaliza();
	}else{
		allegro_message("Opção inválida!");
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void finaliza(){
////////////////////////////////////////////////////////////////////////////////////////////////////
//Desenha a imagem de saída do jogo

	blit(fim,buffer,0,0,0,0,800,600);// Desenha a imagem de finalização

	blit(buffer,screen,0,0,0,0,800,600);// Desenha o buffer na tela (double buffering)
	clear(buffer);// Limpa o buffer para a tela não ficar piscando ou distorcendo a imagem a cada volta no laço
	vsync();	  // Otimiza o processamento do jogo para um valor constante

	rest(5000);

}

#endif // TELAS_APRESENTACAO_H_INCLUDED
