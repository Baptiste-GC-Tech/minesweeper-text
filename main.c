#include <stdio.h>

void display(l,h){/*===============ATTENTION (pas de type donc check si erreur)=======================================*/
    printf("  ");
    for (int i=0;i<l;i++)
    {
        if(i<9)
        {
            printf("%c ",186);
        }else{
            printf("%c%d",186,(i+1)/10);
        }
    }

    printf("\n  ");

    for (int i=0;i<l;i++)
    {
        printf("%c%d",186,(i-((i+1)/10)*10)+1);
    }


    for (int i=0;i<h;i++)
    {
        printf("\n%c%c",205,205);
        for (int j=0;j<l;j++)
        {
            printf("%c%c",206,205);
        }

        if (i<9){
            printf("\n %d",i+1);
            for (int j=0;j<l;j++)
            {
                printf("%c%c",186,219);
            }
        }else{
            printf("\n%d",i+1);
            for (int j=0;j<l;j++)
            {
                printf("%c%c",186,219);
            }
        }
    }
}




/*
bomb = 0 / 1
flag/hidden/show = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/


int main()
{
    int l=3, h=3;
    int * tableau[l*h] ={31,30,20,21,20,20,11,10,20}
    /*printf("Entrer longueur de grille : "); scanf("%d", &l);
    printf("Entrer hauteur de grille : "); scanf("%d", &h);
    while (l>99||h>99)
    {
        printf("Entrer longueur de grille : "); scanf("%d", &l);
        printf("Entrer hauteur de grille : "); scanf("%d", &h);
    }*/

    char board[l*h];
    display(l,h);
    return 0;
}
