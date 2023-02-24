#include <stdio.h>
#include <stdlib.h>

char MainMenu();
void FillGrid(int lenght, int height, int mines, int *grid, unsigned int size);
void display(int l,int h,int*tableau);
void discover(int l, int h);


int main()
{
    int grid[80];
    srand(time(NULL));

    int length=10, height=8, mines=10, maxSpace = 1000;
    char choice;


    printf("--- MINEWSEEPER ---\n\n");

    // Retrieval of choice, initialize the grid if correct input, call MainMenu again if not
    /*do
    {
        choice = MainMenu();

        switch (choice)
        {
            case 'e':
                printf("\n<*>~ EASY MODE SELECTED ~<*>\n");
                unsigned int size = sizeof(grid)/sizeof(grid[0]);
                FillGrid(length, height, mines, grid, size);
                break;

            case 'm':
                printf("\n<*>~ MEDIUM MODE SELECTED ~<*>\n");
                printf("\nYou can't play it just yet, we lack blessing from the memory Gods...\n\n");
                break;

            case 'h':
                printf("\n<*>~ HARD MODE SELECTED ~<*>\n");
                printf("\nYou can't play it just yet, we lack blessing from the memory Gods...\n\n");
                break;

            case 'c':
                printf("\n<!>~ ###[WIP]### ~<!>\n");
                printf("\nSELECT ANOTHER OPTION\n\n");
                break;

            default:
                printf("\n<!>~ THIS OPTION DOESN'T EXIST ~<!>\n\n");
                break;
        }
    } while( choice != 'e' && choice != 'm' && choice != 'h' && choice != 'c' );
    display(length,height,grid);*/
    discover(length,height);
}

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
            }else if (tableau[x]==21||tableau[x]==31){
                printf("%c%c",186,bomb);
            }else if (tableau[x]==30){
                printf("%c%c",186,hidden);
            }
            x=x+1;
        }
    }
}


void FillGrid(int length, int height, int mines, int *grid, unsigned int size)
{
    int x, y, coord, minePlaced = mines;

    // Fills the whole grid with the code 30 (which represents a Hidden No-Bomb cell)
    for(int ord = 0; ord < height; ord++)
    {
        for(int abs = 0; abs < length; abs++)
        {
            coord = abs + ord * length;
            grid[coord] = 30;
        }
    }

    // Increment cells at random by 1, which creates 31 (which represents a Hidden With-Bomb cell), effectively placing the amount of mines desired
    for(minePlaced; minePlaced > 0; minePlaced--)
    {
        coord = ( rand() % length ) + ( rand() % height ) * length;

        if( grid[coord] != 31 )
        {
            grid[coord] += 1;
        }
        else
        {
            minePlaced++;
        }
    }
}

char MainMenu()
{
    char choice;

    do
    {
        // Display main menu
        printf("(e)Easy   - 10x 8, 10 mines\n");
        printf("(m)Medium - 18x14, 40 mines\n");
        printf("(h)Hard   - 24x20, 99 mines\n");
        printf("(c)Custom - ??x??, ?? mines\n\n");

        printf("Your choice : ");
        scanf(" %c", &choice);
        printf("\n");

        // Check if input for choice was within the alphabet, no matter the case
        if( choice == '\0' || (choice < 'A' || choice > 'Z') && (choice < 'a' || choice > 'z') )
        {
            printf("<!>~ YOU DID NOT ENTER A LETTER ~<!>\n\n");
        }

        // Lowercase choice if needed
        if( choice >= 'A' && choice <= 'Z' )
        {
            choice += 32;
        }
    } while( choice < 'a' || choice > 'z' );

    return choice;
}


void discover(int l, int h){
    int abcisse;
    printf("abcisse\n");
    int error=scanf("%d", &abcisse);
    while (abcisse>10000){//||abcisse<0){
        if (error==1){
            printf("error size\n%d\nabcisse\n",abcisse);
            error=scanf("%d", abcisse);
        }else{
            for(int i=0,i<10,i++){
                if (abcisse[i]>10){


                }
            }
            printf("error no letter accept\n%d\nabcisse\n",abcisse);
            abcisse=10000;
            error=scanf("%d", abcisse);

        }
    }
    printf("ok\n%d\n",abcisse);

    /*if (strlen(abcisse)>4)
    {
        printf("error size\n");
        printf("%d\n",strlen(abcisse));
        //printf("%c",error);

    }else if(abcisse>9||abcisse<0){
        printf("error no letter accept\n");
        printf("%c\n",abcisse);
        //printf("%c",error);
        //int abcisse[5];
    }else{
        printf("%c\n",abcisse);
        printf("%d\n",abcisse);
        //printf("%d\n",error);
    }*/
    discover(l,h);
}

/*15122
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/
