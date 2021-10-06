/*!
*------------------------------------------------------------------------*
* UNIVALI  	-		Universidade do Vale do Itajaí						*
* Projeto:  			Arkanoid Allegro										*
* Alunos:   			Anderson Ficagna Passos								*
*			 			Eduardo Alves da Silva								*
* Profª:    			Elisangela Miranda									*
* Ultima Atualização: 02/12/2010												*
*------------------------------------------------------------------------*
*/

/*

OBS: !!!

*/

#include "carrega_jogo.h"	// Carrega as constantes do jogo os ponteiros das imagens e a biblioteca utilizada
#include "blocos.h"			// Processa as informações referente aos blocos
#include "bola.h"			// Processa as informações referente a bola
#include "rebatedor.h"		// Processa as informações referente ao rebatedor
#include "ranking.h"		// Carrega e exibe o ranking
#include "processa_jogo.h"	// Processamento principal do jogo
#include "timer.h"			// Timer do jogo
#include "telas_apresentacao.h"// Menu e fim

int main(){

	inicia_allegro(); // Inicia as funções do allegro
	Player play[5]; // Cria as informações para o Ranking dos 5 jogadores
	Continue jogador;
	carrega_ranking(play); // Carrega as informações do arquivo de texto de ranking
	carrega_op_jogador(jogador); // Carrega as informações do arquivo de texto de partida encerrada pelo usuário

	char opcao; // Variável para controlar o menu

	do{
		menu(opcao,jogador,play);
	}while(!(opcao == 's' || opcao == 'S'));

	salva_ranking(play); // Salva no arquivo de texto o conteúdo contido no vetor da struct play
	salva_op_jogador(jogador);
	remove_keyboard();
	allegro_exit();	  // Encerra a execução do allegro
	return 0;

} END_OF_MAIN();
