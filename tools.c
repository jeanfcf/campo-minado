#include "tools.h"

extern dimensions MAX;
void printr(dimensions local, dimensions base){
    gotoxy( base.x + (local.x * 2) + 1, base.y + local.y + 1);
    colored(*decoderAdss_mtrz( 0,  local.y, local.x));
    if(range(*decoderAdss_mtrz( 0,  local.y, local.x), 1, 8))
    printf("%2d", *decoderAdss_mtrz( 0, local.y,  local.x));
    
    else
    printf("%2c", *decoderAdss_mtrz( 0,  local.y,  local.x));
}

void cover_traces(dimensions now, char write, dimensions last, dimensions start)
{
    gotoxy( start.x + (now.x * 2) + 1, now.y + start.y + 1);
    set_color(140);
    printf("%2c", cursor);
    printr( last,  start);
    gotoxy(start.x + (now.x * 2) + 1, now.y + start.y + 1);
    fflush(stdout);
}

dimensions limite(dimensions in)
{
    if (in.x < 0) in.x = MAX.x - 1;
    
    else if (in.y < 0) in.y = MAX.y - 1;
    
    else if (in.x >= MAX.x) in.x = 0;
    
    else if (in.y >= MAX.y) in.y = 0;
    
    return in;
}

dimensions nvg(dimensions start, dimensions base)
{
    dimensions anterior, atual;
    atual = start;
    gotoxy(base.x + (start.x) * 2 + 1, base.y + start.y + 1);
    set_color(140);
    printf("%2c", cursor);
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
            if (*decoderAdss_mtrz( 0,  atual.y,  atual.x) != bandeira)
            return atual;
            
            break;
            
        case bandeira:
            if (*decoderAdss_mtrz( 0,  atual.y,  atual.x) == bandeira)
            {
                *decoderAdss_mtrz( 0,  atual.y,  atual.x) = piso;
            }
            else if ( *decoderAdss_mtrz( 0,  atual.y,  atual.x) == (signed char) piso)
            {
                printf("%c", bandeira);
                *decoderAdss_mtrz( 0,  atual.y,  atual.x) = bandeira;
            }
            break;
        }

        atual = limite(atual);
        cover_traces(atual, cursor, anterior, base);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void show_around( dimensions selected, dimensions base){
    
    dimensions print = selected;
    
    
    register char e, f, g, h, i, j, k, l, m, n;

    for ( k = -1 ;  k<= 1 ; k+=2)
    {
        for(j = selected.y; range(j, 0,  MAX.y - 1); j+=k)
        {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
            for ( l = -1 ;  l<= 1 ; l+=2)
            {
                for(i = selected.x; range(i, 0,  MAX.x - 1) && *decoderAdss_mtrz( 1, j, i) < 9; i+=l)
                {
                
                    print.x = i;
                    print.y = j;
                    *decoderAdss_mtrz( 0, j, i) = *decoderAdss_mtrz( 1, j, i);
                    printr(print, base);
                    if(*decoderAdss_mtrz( 1, j, i) != 0) break;
                    for ( m = -1; m <= 1; m+=2)
                    {                        
                        for(n = j + m; range(n, 0,  MAX.y - 1) && *decoderAdss_mtrz( 1, n, i) < 9; n+=m)
                        {
                            print.x = i;
                            print.y = n;
                            *decoderAdss_mtrz( 0, n, i) = *decoderAdss_mtrz( 1, n, i);
                            printr(print, base);
                            if(*decoderAdss_mtrz( 1, n, i) != 0) break;
                            for (g = -1; g <= 1; g+=2)
                            {
                                
                                for(f = i + g; range(f, 0,  MAX.x - 1) && *decoderAdss_mtrz( 1, n, f) < 9; f+=g)
                                {
                                    print.x = f;
                                    print.y = n;
                                    *decoderAdss_mtrz( 0, n, f) = *decoderAdss_mtrz( 1, n, f);
                                    printr(print, base);
                                    if(*decoderAdss_mtrz( 1, n, f) != 0) break;
                                    for (h = -1; h <= 1; h+=2)
                                    {
                                        
                                        for(e = n + h; range(e, 0,  MAX.y - 1) && *decoderAdss_mtrz( 1, e, f) < 9; e+=h)
                                        {
                                            print.x = f;
                                            print.y = n;
                                            *decoderAdss_mtrz( 0, e, f) = *decoderAdss_mtrz( 1, e, f);
                                            printr(print, base);
                                            
                                            if(*decoderAdss_mtrz( 1, e, f) != 0) break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(*decoderAdss_mtrz( 1, j, selected.x) != 0) break;
        }
    }
}

dimensions frist_select(dimensions base)
{
    dimensions frist_S;
    frist_S.x = 0;
    frist_S.y = 0;
    frist_S = nvg(frist_S, base);
    srand(time(NULL));
    set_bomb(frist_S.x, frist_S.y);
    show_around(frist_S, base);
    return frist_S;
}
