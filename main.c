#include <stdio.h>

//  15 = ☼

int main()
{
    int l, L;

    printf("Entrer longueur de grille : "); scanf("%d", &l);
    printf("Entrer hauteur de grille : "); scanf("%d", &L);

    char board[l*L];

    for(int i = 0; i < l*L; i++)
    {
        printf("%dth element : %c\n", i, board[i]);
    }

    printf("###\n");
    printf("###\n");
    printf("###\n");

    return 0;
}
