#include "setup.h"


extern dimensions MAX;
void set_dicas( char px, char py)
{
    char  i, j;
    if(( px < 0) || ( py < 0)) send_erro(260);
    if(( px >= MAX.x) || ( py >= MAX.y)) send_erro(261);

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {   
            /* circule o ponto dado e cheque se é possivel escreve a dica. */
            if(range((py + i), 0, MAX.y - 1) && range((px + j), 0, MAX.x - 1) && range(*decoderAdss_mtrz( 1,  (py + i),  (px + j)), 0, 7))
             *decoderAdss_mtrz( 1,  (py + i),  (px + j)) += 1;
            
            else if(range((py + i), 0, MAX.y - 1) && range(*decoderAdss_mtrz( 1, (py + i), (px + 0) ), 0, 7)) 
                *decoderAdss_mtrz( 1, (py + i), (px + 0)) += 1;
            
            else if(range((px + j), 0, MAX.x - 1) && range(*decoderAdss_mtrz( 1, (py + 0), (px + j) ), 0, 7)) 
                *decoderAdss_mtrz( 1, (py + 0), (px + j)) += 1;
            
            if(i == 0 && j == 0) *decoderAdss_mtrz( 1,  (py + i),  (px + j)) = mina;
            
        }
    }

}


void set_bomb(char start_y, char start_x){
    int px, py;
    /*  referente a numeração da bomba.  */
    static unsigned short n_bomb = 0;
    
    /* se a contagem das minas for maior q o numero máximo, envie o erro(230).  */
    if(n_bomb > MAX.bomb) send_erro(230);
    
    /* adiciona um valor randonico para a varivel referente a localização de x. */
    px = rand() % (MAX.x - 1);
    
    /*  adiciona um valor randonico para a varivel referente a localização de y.  */
    py = rand() % (MAX.y - 1);
    
    /*  se o local for uma area permitida (sem bomba e longe da primeira escolha) adicione uma a bomba e as dicas ao redor.  */
    if(check_bomb(py, px, start_y, start_x)) 
    {
        n_bomb++;
        set_dicas(px, py);
        *decoderAdss_mtrz( 1, py, px) = mina;
    }
    
    /*  se a numeração da bomba não for a maxima, passe para a próxima, se for encerre a função.  */
    if(n_bomb >= MAX.bomb) return;
    else set_bomb(start_y, start_x);
}


bool check_bomb(char py,char px, char start_y, char start_x)
{
    bool check;
    
    /*  se a posição de x e de y estiverem dentro do range proibido check recebe falso.  */
    check = (range(px, start_x - 1, start_x + 1) && range(py, start_y - 1, start_y + 1)) ? false : true;
    
    /* se check for verdadeiro e o local das cordenadas xy não for uma mina, retorne a permissão como permitida(verdadeira).  */
    return (check && (*decoderAdss_mtrz( 1, py, px) < 8)) ? true : false;
}


void set_Campo()
{
    char y,x;
    for ( y = 0; y < MAX.y; y++)
    {
        for ( x = 0; x < MAX.x; x++)
        {
            /* nivela o valor da matriz mais externa para o caracter referente ao "piso".  */
            *decoderAdss_mtrz( 0,  y,  x) = (signed char)piso;
        }
    }
}



void print_Campo( char start_x, char start_y)
{
    register char x, y;
    static char c = 0; /* determina qual a camada da matriz a ser impressa. */

/************************************* Inicio da impressão. ***************************************/

    /*  vá pra posição inicial dada, para impressão da matriz  */
    gotoxy(start_x, start_y); 
    /* declare a cor de saida como "branca com fundo cinza".  */
    set_color(143); 
    printf("%c", quina_sup_esquerda);
    for (x = 0; x < (MAX.x * 2) + 1; x++) /* imprima as bordas superiores.  */
    {
        printf("%c", borda_horizontal);
    }

    printf("%c", quina_sup_direita);
    gotoxy(start_x, start_y + 1);


/************************ Impressão das bordas laterais e da matriz. ******************************/

    for (y = 0; y < MAX.y; y++)
    {
        printf("%-2c", borda_vertical);
        for ( x = 0; x < MAX.x; x++)
       {    
            colored( *decoderAdss_mtrz( c,  y, x));
            /*  se for o valor da matriz for uma dica, imprima a matriz em numeros inteiros.  */
            if(range(*decoderAdss_mtrz( c,  y, x), 1, 8))
            printf("%-2d", *decoderAdss_mtrz( c, y, x));
            /*  se for, imprima em caracteres.  */
            else
            printf("%-2c", *decoderAdss_mtrz( c, y, x));
        
        }
        set_color(143);
        printf("%c", borda_vertical);
        gotoxy(start_x,start_y + y + 2);/* vá para a proxima linha.  */
    }
    printf("%c", quina_inf_esquerda);

/***************************** Impressão das bordas inferiores.************************************/
    for ( x = 0; x < (MAX.x * 2) + 1; x++) printf("%c", borda_horizontal);
    
    set_color(143);
    printf("%c", quina_inf_direita);
    if(c < 1) c++;
}
