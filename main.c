#include <stdio.h>

void display(int l,int h,int*tableau){
    int bomb=15, flag=127, hidden=219,show=177;
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

    int x=0;
    for (int i=0;i<h;i++)
    {
        printf("\n%c%c",205,205);
        for (int j=0;j<l;j++)
        {

            printf("%c%c",206,205);
        }

        if (i<9){
            printf("\n %d",i+1);
        }else{
            printf("\n%d",i+1);
        }
        for (int j=0;j<l;j++)
        {
            if (tableau[x]==10||tableau[x]==11){
                printf("%c%c",186,flag);
            }else if (tableau[x]==20){
                printf("%c%c",186,show);
            }else if (tableau[x]==21){
                printf("%c%c",186,bomb);
            }else if (tableau[x]==30||tableau[x]==31){
                printf("%c%c",186,hidden);
            }
            x=x+1;
        }
    }
}


int main()
{
    srand( time( NULL ));
    int l=5, h=5;
    int tableau[9]={};


    display(l,h,tableau);
    char board[l*h];
    return 0;
}

/*
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/
