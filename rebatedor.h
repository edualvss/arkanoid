#ifndef REBATEDOR_H_INCLUDED
#define REBATEDOR_H_INCLUDED

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rebatidas_rebatedor(int reb_pos_x,int bola_x,int bola_y,int &dir_bol_x,int &dir_bol_y,int velo_bola,int &cont_velo_bola){
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que verifica se há colisão da bola com o rebatedor

	if(bola_x >= reb_pos_x-10 && bola_x <= reb_pos_x + 23){// Testa se há colisão na  parte 1 do rebatedor
		dir_bol_y = dir_bol_x = -velo_bola;// Rebate a bola de acordo com a posição que ela colidiu
		cont_velo_bola++;// Incrementa a variável de rebatidas da bola no rebatedor
	}
	if((bola_x >= reb_pos_x + 24 && bola_x <= reb_pos_x + 52)||(bola_x >= reb_pos_x + 68 && bola_x <= reb_pos_x+97)){// Testa se há colisão nas partes 2 e 4 do rebatedor
		dir_bol_y = -velo_bola;// Rebate a bola de acordo com a posição que ela colidiu
		cont_velo_bola++;// Incrementa a variável de rebatidas da bola no rebatedor
	}
	if(bola_x >= reb_pos_x + 98 && bola_x <= reb_pos_x + 135){// Testa se há colisão com a parte 5 do rebatedor
		dir_bol_x = velo_bola;// Rebate a bola de acordo com a posição que ela colidiu
		dir_bol_y = -velo_bola;// Rebate a bola de acordo com a posição que ela colidiu
		cont_velo_bola++;// Incrementa a variável de rebatidas da bola no rebatedor
	}
	if(bola_x >= reb_pos_x + 53 && bola_x <= reb_pos_x+67){// Testa se há colisão com a parte 3 do rebatedor
		dir_bol_x = 0;// Rebate a bola de acordo com a posição que ela colidiu
		dir_bol_y = -velo_bola;// Rebate a bola de acordo com a posição que ela colidiu
		cont_velo_bola++;// Incrementa a variável de rebatidas da bola no rebatedor
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void movimenta_rebatedor(int &rebatedor_x){
////////////////////////////////////////////////////////////////////////////////////////////////////
// Procedimento que realiza o movimento do rebatedor
	if(key[KEY_LEFT] && rebatedor_x>PAREDE_ESQUERDA){// Verifica se o rebatedor esta após a parede da esquerda
		rebatedor_x-=VELOCIDADE_REBATEDOR;// Realiza o movimento do rebatedor a esquerda
	}else if(key[KEY_RIGHT] && rebatedor_x<PAREDE_DIREITA-140){// Verifica se o rebatedor está antes da parede da direita
		rebatedor_x+=VELOCIDADE_REBATEDOR;// Realiza o movimento do rebatedor a direita
	}
}

#endif // REBATEDOR_H_INCLUDED
