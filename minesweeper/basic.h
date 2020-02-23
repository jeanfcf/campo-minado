#ifndef BASIC_H
#define BASIC_H

//struct pra dimensionss do jogo tanto para o tamanho quanto para as minas.
typedef struct dimensions {
	char x;
	char y;
	char z;
	short bomb; 
} dimensions;

dimensions MAX;
char* startAdss;

//valores das teclas de navegação.
enum nvgkeys {  up = 72, down = 80, left = 75, right = 77, enter = 13 };

//valores dos caracteres usados como interface gráfica.
enum componentes_visuais
{
    mina = 15, bandeira = 'p', cursor = 169, piso = 254,
    borda_horizontal   = 205 , borda_vertical    =  186,
    quina_sup_esquerda = 201 , quina_sup_direita =  187,
    quina_inf_esquerda = 200 , quina_inf_direita =  188,
};

//valores boleanos para auxilio de leitura.
enum boleano { true = 1, false = 0 };
// tipo boleno
typedef enum boleano bool;

// Direciona o cursor do console, sendo x = a coluna e y = a linha.
void gotoxy(char x, char y);

// Limpa a tela, imprime e envia o valor de entrada como saida do programa.
void send_erro(int erro);

// Retorna um valor booleano (V ou F) em condição da variavel de entrada e as de comparação.
bool range(char in, char range_min, char range_max);

void set_color(unsigned char in);

// Define a coloração q sera impressa o próximo caracter, de acordo com a entrada. 
void colored(char in);

// Retorna uma struct contendo os valores com o tamanho do campo e a quantidade de minas.
dimensions dificuldade(char dificuldade);

void set_adss(dimensions max);

// Aponta um determinado endereço de uma matriz de no maximo 3 dimensões. 
char *decoderAdss_mtrz(char z, char y, char x);
#endif // BASIC_H