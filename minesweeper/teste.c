#include "setup.c"

void cover_traces(dimensions now, char write, dimensions last, dimensions start, char *coverAdss)
{
    gotoxy( (now.x + start.x + 1) * 2, now.y + start.y + 1);
    printf("\x1b[31;1m%c\x1b[0m", cursor);
    gotoxy( (last.x + start.x + 1) * 2, last.y + start.y + 1);
    colored(*decoderAdss_mtrz(coverAdss, Z_MAX, Y_MAX, X_MAX, 0,  last.y, last.x));
    
    if(range(*decoderAdss_mtrz(coverAdss, Z_MAX, Y_MAX, X_MAX, 0,  last.y, last.x), 1, 8))
    printf("%-2d\x1b[0m", *decoderAdss_mtrz(coverAdss, Z_MAX, Y_MAX, X_MAX, 0, last.y,  last.x));
    
    else
    printf("%-2c\x1b[0m", *decoderAdss_mtrz(coverAdss, Z_MAX, Y_MAX, X_MAX, 0,  last.y,  last.x));

    gotoxy((now.x + start.x + 1) * 2, now.y + start.y + 1);
    fflush(stdout);
}

dimensions limite(dimensions in, dimensions limite)
{
    if (in.x < 0)
    {
        in.x = limite.x - 1;

    }
    else if (in.y < 0)
    {
        in.y = limite.y - 1;
    }
    else if (in.x >= limite.x)
    {
        in.x = 0;
    }
    else if (in.y >= limite.y)
    {
        in.y = 0;
    }
    return in;
}

dimensions nvg(char d, dimensions start, dimensions base, char * mtrzAdss)
{
    dimensions anterior, atual;
    atual = start;
    gotoxy((base.x + start.x + 1) * 2, base.y + start.y + 1);
    printf("\x1b[31;1m%c\x1b[0m", cursor);
////////////////////////////////////////////////////////////////////////////////////////////////////
    while(1)
    {
        anterior = atual;
        switch (getch())
        {

        case right:
            ++atual.x;
            break;

        case left:
            --atual.x;
            break;

        case up:
            --atual.y;
            break;
            

        case down:
            ++atual.y;
            break;

        case enter:
            if (*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) != bandeira)
            {
                gotoxy(((atual.x + base.x)*2) + 1, atual.y + base.y + 1);
                return atual;
            }
            break;
            
        case bandeira:
            if (*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) == bandeira)
            {
                *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) = piso;
            }
            else if (*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) != 0 /*&& *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) == piso*/)
            {
                printf("%c", bandeira);
                *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0,  atual.y,  atual.x) = bandeira;
            }
            break;
        }

        atual = limite(atual, dificuldade(d));
        cover_traces(atual, cursor, anterior, base, mtrzAdss);
    }
}

dimensions permission(dimensions in, char i, char j){
    dimensions out;
    if(range(in.x + j, 0, X_MAX - 1) && range(in.y + i, 0, Y_MAX - 1))
    {
        out.x = in.x + j;
        out.y = in.y + i;
       
    }
    else if(range(in.y + i, 0, Y_MAX-1))
    {               
        
        out.x = in.x;
        out.y = in.y + i;
       
    }
    else if(range(in.x + j, 0, X_MAX-1))
    {              
        
        out.x = in.x + j;
        out.y = in.y;

    }
    else
    {
        out = in;
    }
    return out;

}
void show_around(char *mtrzAdss, dimensions selected, dimensions base){
    
    dimensions maneger = selected;
    char i, j, k, l;
    bool check = true;    
    for (k = 0; check; k+=3)
    {
	    for (i = -1; i <= 1; i++)
	    {
	        for (j = -1; j <= 1; j++)
	        {

	            maneger = permission( selected,  i,  j + k);

	            if(*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 1, maneger.y, maneger.x) == 0)
	            {
	                *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0, maneger.y, maneger.x) = *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 1, maneger.y, maneger.x);
	                cover_traces(maneger, ' ', maneger, base, mtrzAdss);
	            }
	            else if (*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 1, maneger.y, maneger.x) < 9)
	            {
	            	*decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 0, maneger.y, maneger.x) = *decoderAdss_mtrz(mtrzAdss, Z_MAX, Y_MAX, X_MAX, 1, maneger.y, maneger.x);
	                cover_traces(maneger, ' ', maneger, base, mtrzAdss);
	            	check = false;
	            }
	            else check = false;
	        }
	    }    	
    }
    
}

dimensions frist_select(char d, dimensions base, char *mtrzAdss)
{
    dimensions frist_S;
    frist_S.x = 0;
    frist_S.y = 0;
    frist_S = nvg(d, frist_S, base, mtrzAdss);
    srand(time(NULL));
    set_bomb(d, frist_S.x, frist_S.y, mtrzAdss);
    show_around(mtrzAdss, frist_S, base);
    return frist_S;
}

int main(int argc, char const *argv[])
{
	char campo[Z_MAX][Y_MAX][X_MAX];
    system("color 8F");
////////////////////////////////////////////////////////////////////////////////////////////////////
    dimensions position, comeco;
    comeco.x = 0;
    comeco.y = 0;
    char campo_size = 1;

    set_Campo((char *)&campo);
    print_Campo(campo_size, comeco.x, comeco.y, (char*)&campo);



    position = frist_select(campo_size, comeco, (char *)&campo);
	return 0;
}