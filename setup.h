#include "basic.h"
#include "basic.c"
#ifndef SETUP_H
#define SETUP_H
// configura as posições das minas randoniamente e o numero de minas de acordo com a dificuldade:
void set_bomb(char start_y, char start_x);

// checa se o ponto dado por px e py, é posssivel colocar uma mina. Retorna a permição.
bool check_bomb(char py,char px, char start_y, char start_x);

// escreve as dicas na matriz ao do ponto dado(cordenadas da mina).
void set_dicas( char px, char py);

// nivela a os valores da matriz por camada.
void set_Campo();

// imprime a matriz declarada por "set_adss" (a camada a ser impressa muda de acordo com o numero de chamadas efetuadas da função).
void print_Campo( char start_x, char start_y);
#endif // SETUP_H