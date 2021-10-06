/*!
*------------------------------------------------------------------------*
* UNIVALI  	-		Universidade do Vale do Itaja�						*
* Projeto:  			Arkanoid Allegro										*
* Alunos:   			Anderson Ficagna Passos								*
*			 			Eduardo Alves da Silva								*
* Prof�:    			Elisangela Miranda									*
* Ultima Atualiza��o: 02/12/2010												*
*------------------------------------------------------------------------*
*/

/*

OBS: !!!

*/

#include "carrega_jogo.h"	// Carrega as constantes do jogo os ponteiros das imagens e a biblioteca utilizada
#include "blocos.h"			// Processa as informa��es referente aos blocos
#include "bola.h"			// Processa as informa��es referente a bola
#include "rebatedor.h"		// Processa as informa��es referente ao rebatedor
#include "ranking.h"		// Carrega e exibe o ranking
#include "processa_jogo.h"	// Processamento principal do jogo
#include "timer.h"			// Timer do jogo
#include "telas_apresentacao.h"// Menu e fim

int main(){

	inicia_allegro(); // Inicia as fun��es do allegro
	Player play[5]; // Cria as informa��es para o Ranking dos 5 jogadores
	Continue jogador;
	carrega_ranking(play); // Carrega as informa��es do arquivo de texto de ranking
	carrega_op_jogador(jogador); // Carrega as informa��es do arquivo de texto de partida encerrada pelo usu�rio

	char opcao; // Vari�vel para controlar o menu

	do{
		menu(opcao,jogador,play);
	}while(!(opcao == 's' || opcao == 'S'));

	salva_ranking(play); // Salva no arquivo de texto o conte�do contido no vetor da struct play
	salva_op_jogador(jogador);
	remove_keyboard();
	allegro_exit();	  // Encerra a execu��o do allegro
	return 0;

} END_OF_MAIN();
