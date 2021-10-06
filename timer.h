#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

void timer(){ // Realiza o manuseio do tempo no jogo

	segundos--; //Decrementa a variável segundos a cada chamada da função

	if(segundos <= 0){// Se a variável segundos chegou a 0
		segundos = 59;// Atribui 59
		minutos--;// Decrementa os minutos
	}
}

#endif // TIMER_H_INCLUDED
