#include "tools.c"

extern dimensions MAX;
char menu(char limite, char  menuText[])
{
    char coord_atual= 1;
    char coord_anterior;
    printf("Selecione um intem: (pressione ENTER para confirmar)\n");
    printf("%s", menuText);
    gotoxy(6, 1);
    printf(">");

    while(1)
    {
        coord_anterior = coord_atual;
        switch (getch())
        {
        case up:
            --coord_atual;
            break;
        case down:
            ++coord_atual;
            break;

        case enter:
            system("cls");
            return coord_atual;
            break;

        }
        if (coord_atual< 1)
        {
            coord_atual = limite;
        }
        else if (coord_atual> limite)
        {
            coord_atual= 1;
        }

        gotoxy( 6, coord_atual);
        printf(">");
        gotoxy( 6, coord_anterior);
        printf(" ");
        gotoxy( 6, coord_atual);

    }
}

void window(short col, short lin){
    
    SMALL_RECT size = {-(col + 3), -2, col + 3, lin + 2}; 
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &size);
    
}

int main(void)
{
    //matriz 3d com o tamanho máximo do campo(30x16).
    system("color 8F");
////////////////////////////////////////////////////////////////////////////////////////////////////
    dimensions position, start;
    start.x = 2;
    start.y = 0;
    set_adss(dificuldade(menu(4,"\tFacil\n\tMedio\n\tDficil\n\tPersonalizado")));
    window(MAX.x, MAX.y);
    set_Campo();
    print_Campo( start.x, start.y);

    position = frist_select( start);
////////////////////////////////////////////////////////////////////////////////////////////////////
    while(1)
    {
        position = nvg( position, start);
        if(*decoderAdss_mtrz(1, position.y, position.x) == (signed char) mina)
        {
            Beep(820,340);
            print_Campo( start.x, start.y);
            printf("\n\nFIM DE JOGO!!!");
            getchar();
            Sleep(421);
            return 0;
        }
        else
        show_around( position, start);
    }
}