#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <iostream>

/// Arquivo usando funções de allegro

////////////////////////////////////////////////////////////////////////////////////////////////////
void assign_player(Player &p,char *tipo){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Carrega a informação do arquivo de texto do jogador atual

	p.nome = (char*)get_config_string(tipo,"nome","Vazio");
	p.pontos = get_config_int(tipo,"pontos",0);
	p.min = get_config_int(tipo,"minutos",0);
	p.seg = get_config_int(tipo,"segundos",0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void ordena_ranking(Player play[5]){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Ordena o ranking

	for(int i = 0; i < 4; i++){
		for(int j = i+1; j < 5; j++){
			if(play[i].pontos < play[j].pontos){
				std::swap(play[i],play[j]);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void carrega_ranking(Player play[5]){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que carrega o ranking do arquivo de texto

	set_config_file("ranking.dat");// Seta o arquivo para leitura

	assign_player(play[0] , "top");// Passa os dados contidos em 'top' no arquivo, para a struct play[0]
	assign_player(play[1] , "segundo");// Passa 'segundo' para play[1]
	assign_player(play[2] , "terceiro");// Passa 'terceiro' para play[2]
	assign_player(play[3] , "quarto");// Passa 'quarto' para play[3]
	assign_player(play[4] , "quinto");// Passa 'quinto' para play[4]

	ordena_ranking(play);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void assign_file(Player p,char *tipo){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Passa as informações contidas na struct, para o arquivo.

	set_config_string(tipo,"nome",p.nome);
	set_config_int(tipo,"pontos",p.pontos);
	set_config_int(tipo,"minutos",p.min);
	set_config_int(tipo,"segundos",p.seg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void salva_ranking(Player play[5]){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Seta arquivo para a gravação, e manda gravar as informações contida na struct

	override_config_file("ranking.dat"); // Seta o arquivo para gravação

	assign_file(play[0] , "top");
	assign_file(play[1] , "segundo");
	assign_file(play[2] , "terceiro");
	assign_file(play[3] , "quarto");
	assign_file(play[4] , "quinto");

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void exibe_ranking(Player *play){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Exibe o ranking

	do{
		blit(ranking,buffer,0,0,0,0,800,600);// Desenha a imagem de finalização

		textprintf_ex(buffer, font, 200, 430 , makecol(255, 0, 0),-1,"Nome");
		textprintf_ex(buffer, font, 400, 430 , makecol(255, 0, 0),-1,"Pontos");
		textprintf_ex(buffer, font, 550, 430 , makecol(255, 0, 0),-1,"Tempo");

		// Top Player
		textprintf_ex(buffer, font, 200, 460 , makecol(255, 255, 255),-1,"%s",play[0].nome);
		textprintf_ex(buffer, font, 400, 460 , makecol(255, 255, 255),-1,"%d",play[0].pontos);
		textprintf_ex(buffer, font, 550, 460 , makecol(255, 255, 255),-1,"%d:%d",play[0].min,play[0].seg);
		// Player 2
		textprintf_ex(buffer, font, 200, 480 , makecol(255, 255, 255),-1,"%s",play[1].nome);
		textprintf_ex(buffer, font, 400, 480 , makecol(255, 255, 255),-1,"%d",play[1].pontos);
		textprintf_ex(buffer, font, 550, 480 , makecol(255, 255, 255),-1,"%d:%d",play[1].min,play[1].seg);
		// Player 3
		textprintf_ex(buffer, font, 200, 500 , makecol(255, 255, 255),-1,"%s",play[2].nome);
		textprintf_ex(buffer, font, 400, 500 , makecol(255, 255, 255),-1,"%d",play[2].pontos);
		textprintf_ex(buffer, font, 550, 500 , makecol(255, 255, 255),-1,"%d:%d",play[2].min,play[2].seg);
		// Player 4
		textprintf_ex(buffer, font, 200, 520 , makecol(255, 255, 255),-1,"%s",play[3].nome);
		textprintf_ex(buffer, font, 400, 520 , makecol(255, 255, 255),-1,"%d",play[3].pontos);
		textprintf_ex(buffer, font, 550, 520 , makecol(255, 255, 255),-1,"%d:%d",play[3].min,play[3].seg);
		//Player 5
		textprintf_ex(buffer, font, 200, 540 , makecol(255, 255, 255),-1,"%s",play[4].nome);
		textprintf_ex(buffer, font, 400, 540 , makecol(255, 255, 255),-1,"%d",play[4].pontos);
		textprintf_ex(buffer, font, 550, 540 , makecol(255, 255, 255),-1,"%d:%d",play[4].min,play[4].seg);

		textprintf_ex(buffer, font, 350, 580 , makecol(0, 255, 0),-1,"Pressione ESC");

		blit(buffer,screen,0,0,0,0,800,600);// Desenha o buffer na tela (double buffering)
		clear(buffer);// Limpa o buffer para a tela não ficar piscando ou distorcendo a imagem a cada volta no laço

	}while(!key[KEY_ESC]);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool verifica_recorde(int atual,int menor){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Verifica se a pontuação do jogador atual é maior que a do ultimo jogador do ranking

	if(atual > menor){
		return true;
	}
	return false;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void cadastra_novo_player(char *temp){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Entrada do nome do jogador que atingiu o recorde

	const int TAM_NOME = 20;// Tamanho máximo permitido para o nome do jogador
	char i_nome[TAM_NOME];
	clear_keybuf();
	// Entrada de dados em allegro
	int pos_cursor = 0;
	do{
		blit(novo_recorde,buffer,0,0,0,0,800,600);
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
		textout(buffer, font, i_nome, 370, 580, makecol(255, 255, 255));
		textprintf_ex(buffer, font, 350, 560 , makecol(255, 0, 0),-1,"Digite seu nome!");
		vline(buffer, pos_cursor * 8 + 370, 580, 588, makecol(255, 255, 255));
		blit(buffer, screen, 0, 0, 0, 0, 800, 600);
		clear(buffer);
   }while(!key[KEY_ENTER]);

	strcpy(temp,i_nome);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void cadastra(Player atual,Player play[5],int pontos){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Realiza procedimentos necessários para cadastrar player de novo recorde

	bool flag_recorde = false;
	char *temp = new char[20];

	atual.pontos = pontos;
	atual.min = minutos;
	atual.seg = segundos;
	flag_recorde = verifica_recorde(atual.pontos,play[4].pontos);
	if(flag_recorde){
		cadastra_novo_player(temp);
		atual.nome = temp;
		play[4] = atual;
		ordena_ranking(play);
	}
}

#endif // RANKING_H_INCLUDED
