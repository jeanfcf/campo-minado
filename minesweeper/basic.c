#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "basic.h"

 extern dimensions MAX;
 extern char* startAdss;


void gotoxy(char x, char y)
{
    if(x < 0 || y < 0) send_erro(150);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void send_erro(int erro){
        set_color(159);
        system("cls");
        printf("ERRO: %d!\n", erro); 
        exit(erro);
}

bool range(char in, char range_min, char range_max){
   return (in >= range_min) ? (in <= range_max) ? true : false : false;
}

void set_color(unsigned char in){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), in);
}

void colored(char in){
    switch(in){
        case 1:
        set_color(137);
        break;
        case 2:
        set_color(138);
        break;
        case 3:
        set_color(140);
        break;
        case 4:
        set_color(128);
        break;
        case 5:
        set_color(141);
        break;
        case 'p':
        set_color(128);
        break;
        case 7:
        set_color(142);
        break;
        case 8:
        set_color(133);
        break;
        default:
        set_color(143);
        break;

    }
}
dimensions dificuldade(char dificuldade){
    dimensions max;
    int x = 0, y = 0, bomb = 0;
    max.z = 2;
    switch(dificuldade){
        case 1:
        max.x = 9;
        max.y = 9;
        max.bomb = 10;
        break;
        case 2:
        max.x = 16;
        max.y = 16;
        max.bomb = 40;
        break;
        case 3:
        max.x = 30;
        max.y = 16;
        max.bomb = 99;
        break;
        default:
        do
        {
            system("cls");
            if((x * y) <  bomb) printf("valores invalidos! Insira valores validos para prosseguir:");
            printf("\n\n\n\tX:");
            printf("\tY:");
            printf("\tNumero de minas:\n");
            gotoxy('\t' + 1,3);
            scanf("%d", &x);
            gotoxy('\t' + 9,3);
            scanf("%d", &y);
            gotoxy(3 * ('\t' + 1) + 10,3);
            scanf("%d", &bomb);
        } while((x * y) <  bomb);        
        
        max.x = (char) x;
        max.y = (char) y;
        max.bomb = (short) bomb;
        system("cls");
        break;
    }
    return max;
}

void set_adss(dimensions max){
    MAX = max;
    startAdss = (char*) calloc((max.z * max.y * max.x), sizeof(char));
}

/************************************** SOMENTE PARA CHAR!!! *************************************/
char* decoderAdss_mtrz(char z, char y, char x) 
                        
{
    // caso o endereço especifico esteja "fora" da matriz, envie o erro 161(valor selecionado fora da matriz por excesso!).
    if( (z >= MAX.z ) || (y >= MAX.y ) || (x >= MAX.x )) send_erro(161);
    
    // caso o endereço inicial seja igual a NULL, envie o erro 160(valor inicial invalido!).
    else if (startAdss == NULL) send_erro(160);
    
    // caso o endereço especifico esteja "fora" da matriz, envie o erro 161(valor selecionado fora da matriz por falta!).
    else if ( (z < 0) || (y < 0) || (x < 0) ) send_erro(162);
    
    //retorne o endereço selecionado
    else return &startAdss[(z * MAX.x * MAX.y) + (y * MAX.x) + x];
}
