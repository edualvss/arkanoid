#ifndef CARREGA_JOGO_H_INCLUDED
#define CARREGA_JOGO_H_INCLUDED

#define PAREDE_SUPERIOR 1		// Define o pixel de localização da parede superior
#define PAREDE_ESQUERDA 2		// Define o pixel de localização da parede da esquerda
#define PAREDE_DIREITA 659		// Define o pixel de localização da parede da direita

#define VELOCIDADE_REBATEDOR 5	// Define a qtd de incremento ou decremento do rebatedor em pixels
#define VELOCIDADE_INICIAL_BOLA 6// Define a qtd de incremento ou decremento da bola em pixels

#define VELOCIDADE_GIRO 5		// Define a qtd de incremento ou decremento em pixels do giro da bola e das rodas do rebatedor

#define REBATEDOR_Y 550			// Define a posição do rebatedor na vertical

#define LIN_BLOCOS 8			// Define a qtd de linhas na matriz dos blocos
#define COL_BLOCOS 11			// Define a qtd de colunas na matriz dos blocos

#include <allegro.h>
#include <fstream>

using namespace std;

struct Player{  // Struct feita para controlar o ranking
	char *nome;
	int pontos;
	int min,seg;
};
struct Bonus{  // Struct feita para controlar os bônus
	int x;
	int y;
	int dx;
	int dy;
	bool ativo;
};
struct Continue{
	Player play;
	int fase;
	int sim;
	int vidas;
};

    BITMAP *buffer = NULL;		// Onde as imagens serão desenhadas
    BITMAP *rebatedor = NULL;	// Onde o rebatedor será carregado
    BITMAP *bola = NULL;		// Onde a bola será carregada
    BITMAP *fundo[5];			// Onde o plano de fundo será carregado
    BITMAP *bloco[7];			// Onde os blocos serão carregados
    BITMAP *roda = NULL;		// Onde as rodas serão carregadas
    BITMAP *select_menu = NULL; // Onde a bola do seletor no menu é carregada
    BITMAP *fundo_menu = NULL;	// Onde o fundo do menu é carregado
    BITMAP *fim = NULL;			// Onde a imagem de finalização será carregada
    BITMAP *bonuss = NULL;		// Onde o bônus será carregado
    BITMAP *ranking = NULL;		// Onde será carregada a tela de ranking
    BITMAP *novo_recorde = NULL;// Onde será carregada a tela de novo recorde
    BITMAP *continuar = NULL;	// Onde será carregada a imagem de continuar do menu
    BITMAP *password = NULL; 	// Onde será carregada a tela de password

	// Únicas variáveis globais além dos ponteiros que carregam as imagens. Usadas para o timer
	volatile int minutos = NULL,segundos = NULL;

void timer(); // Protótipo da função timer

////////////////////////////////////////////////////////////////////////////////////////////////////
void inicia_allegro(){
////////////////////////////////////////////////////////////////////////////////////////////////////

	set_uformat(U_ASCII); // Define o modo da fonte para ascii

	allegro_init();		  // Inicializa a biblioteca Allegro

	set_window_title("Arkanoid <<--|-->>  <<Eduardo Alves da Silva & Anderson Ficagna Passos>>"); // Seta o título da janela

	set_color_depth(32); // Seta a qtd de cores em bits que serão usadas no jogo
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0); // Cria a janela de execução do jogo

	install_keyboard(); // Habilita o uso do teclado no jogo

	install_timer(); // Habilita o contador de tempo do allegro
	install_int_ex(timer,SECS_TO_TIMER(1)); // define a chamada da função timer a cada 1 segundo

//	set_config_string("system", "keyboard", "pt"); // Seta o teclado para o modelo de teclado português

//	install_mouse(); // Habilita o usa do mouse no jogo

	/// Carrega as imagens do jogo
	buffer = create_bitmap(800,600);			// Cria o local onde será desenhado o jogo (pelo fato de o jogo ser double buffering)
	rebatedor = load_bmp("rebatedor.bmp",NULL);	// Carrega a imagem do rebatedor no ponteiro "rebatedor"
	bola = load_bmp("bola.bmp",NULL);			// Carrega a imagem da bola no ponteiro "bola"
	fundo[0] = load_bmp("fundo_1.bmp",NULL);	// Carrega a imagem de fundo_1 no ponteiro "fundo[0]"
	fundo[1] = load_bmp("fundo_2.bmp",NULL);	// Carrega a imagem de fundo_2 no ponteiro "fundo[1]"
	fundo[2] = load_bmp("fundo_3.bmp",NULL);	// Carrega a imagem de fundo_3 no ponteiro "fundo[2]"
	fundo[3] = load_bmp("fundo_4.bmp",NULL);	// Carrega a imagem de fundo_4 no ponteiro "fundo[3]"
	fundo[4] = load_bmp("fundo_5.bmp",NULL);	// Carrega a imagem de fundo_5 no ponteiro "fundo[4]"
	bloco[0] = load_bmp("bloco_1.bmp",NULL);	// Carrega a imagem do primeiro bloco na posição 0 do vetor ponteiro "bloco"
	bloco[1] = load_bmp("bloco_2.bmp",NULL);	// Carrega a imagem do segundo bloco na posição 1 do vetor ponteiro "bloco"
	bloco[2] = load_bmp("bloco_3.bmp",NULL);	// Carrega a imagem do terceiro bloco na posição 2 do vetor ponteiro "bloco"
	bloco[3] = load_bmp("bloco_4.bmp",NULL);	// Carrega a imagem do quarto bloco na posição 3 do vetor ponteiro "bloco"
	bloco[4] = load_bmp("bloco_5.bmp",NULL);	// Carrega a imagem do quinto bloco na posição 4 do vetor ponteiro "bloco"
	bloco[5] = load_bmp("bloco_6.bmp",NULL);	// Carrega a imagem do sexto bloco na posição 5 do vetor ponteiro "bloco"
	bloco[6] = load_bmp("bloco_10.bmp",NULL);	// Carrega a imagem do sétimo bloco na posição 6 do vetor ponteiro "bloco"
	roda = load_bmp("roda.bmp",NULL);			// Carrega a imagem da roda do rebatedor no ponteiro "roda"
	select_menu = load_bmp("select_menu.bmp",NULL);	// Carrega a imagem da bola seletora no menu
	fundo_menu = load_bmp("menu.bmp",NULL);		// Carrega a imagem de fundo do menu
	fim = load_bmp("fim.bmp",NULL);				// Carrega a imagem de finalização do jogo
	bonuss = load_bmp("bonus.bmp",NULL);		// Carrega a imagem do bônus
	ranking = load_bmp("ranking.bmp",NULL);		// Carrega a imagem da tela de ranking
	novo_recorde = load_bmp("novo_recorde.bmp",	NULL);// Carrega a imagem de novo recorde
	continuar = load_bmp("continuar.bmp",NULL);	// Carrega a imagem de continuar do menu
	password = load_bmp("password.bmp",NULL);	// Carrega a imagem do password

	// Inicia o gerador de numeros randômicos
	srand(time(NULL));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void carrega_op_jogador(Continue &jogador){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Carrega o arquivo de texto contendo as informações para o jogador continuar o jogo de onde parou

	ifstream fin;

	char buff[20];
	int cont = 0;
	char *temp = new char[20];

	fin.open("jogador.dat");
	if(fin.is_open()){
		while(fin){
			fin.getline(buff,20);
			cont++;
			switch(cont){
				case 1: strcpy(temp, buff);break;
				case 2: jogador.fase = atoi(buff);break;
				case 3: jogador.sim = atoi(buff);break;
				case 4: jogador.play.min = atoi(buff);break;
				case 5: jogador.play.seg = atoi(buff);break;
				case 6: jogador.play.pontos = atoi(buff);break;
				case 7: jogador.vidas = atoi(buff);break;
			}
		}
	}else{
		temp = "Vazio";
		jogador.fase = 1;
		jogador.sim = 0;
		jogador.play.min = 20;
		jogador.play.seg = 1;
		jogador.play.pontos = 0;
		jogador.vidas = 3;
	}

	jogador.play.nome = temp;

	fin.close();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void salva_op_jogador(Continue jogador){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Salva um arquivo de texto contendo as informações do jogador no momento em que parou a fase

	ofstream fout("jogador.dat");

	fout << jogador.play.nome << '\n' << jogador.fase << '\n'
		 << jogador.sim << '\n' << jogador.play.min << '\n'
		 << jogador.play.seg << '\n' << jogador.play.pontos << '\n'
		 << jogador.vidas;

	fout.close();

}

#endif // CARREGA_JOGO_H_INCLUDED
