#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

void timer(){ // Realiza o manuseio do tempo no jogo

	segundos--; //Decrementa a vari�vel segundos a cada chamada da fun��o

	if(segundos <= 0){// Se a vari�vel segundos chegou a 0
		segundos = 59;// Atribui 59
		minutos--;// Decrementa os minutos
	}
}

#endif // TIMER_H_INCLUDED
