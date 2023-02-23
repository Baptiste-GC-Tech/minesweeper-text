#include <stdio.h>
#include <stdlib.h>

char MainMenu();
void FillGrid(int lenght, int height, int mines, int *grid, unsigned int size);
void display(int l,int h,int*tableau);
int AllNeighborSafe(int length, int height, int *grid, int size, int targetAbs, int targetOrd);

int main()
{
    srand(time(NULL));

    int length = 10, height = 8, mines = 10, maxSpace = 1000;
    int grid[80];
    unsigned int size = sizeof(grid)/sizeof(grid[0]);
    char choice;


    printf("--- MINEWSEEPER ---\n\n");

    // Retrieval of choice, initialize the grid if correct input, call MainMenu again if not
    do
    {
        choice = MainMenu();

        switch (choice)
        {
            case 'e':
                printf("\n<*>~ EASY MODE SELECTED ~<*>\n\n");
                FillGrid(length, height, mines, grid, size);
                break;

            case 'm':
                printf("\n<*>~ MEDIUM MODE SELECTED ~<*>");
                printf("\nYou can't play it just yet, we lack blessing from the memory Gods...\n\n");
                break;

            case 'h':
                printf("\n<*>~ HARD MODE SELECTED ~<*>");
                printf("\nYou can't play it just yet, we lack blessing from the memory Gods...\n\n");
                break;

            case 'c':
                printf("\n<!>~ ###[WIP]### ~<!>");
                printf("\nSELECT ANOTHER OPTION\n\n");
                break;

            default:
                printf("\n<!>~ THIS OPTION DOESN'T EXIST ~<!>\n\n");
                break;
        }
    } while( choice != 'e' && choice != 'm' && choice != 'h' && choice != 'c' );

    for(int i = 0; i < size; i++)
    {

    }

    display(length,height,grid);
    printf("\n#$  (3,3) safe : %d", AllNeighborSafe(length, height, grid, size, 3, 3));
}

// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY


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

int AllNeighborSafe(int length, int heigth, int *grid, int size, int targetAbs, int targetOrd)
{
    int coord, neighborMine = 0;

    // Go through the 3 neighbor coordinates of the targeted cell
    for(int ord = -1; ord < 2; ord++)
    {
        for(int abs = -1; abs < 2; abs++)
        {
            printf("\n#$  abs = %d && ord = %d, so testing on [%d,%d]", abs, ord, (targetAbs + abs)+1, (targetOrd + ord)+1);

            // Skip the test if it would be performed on the target, or if the cell tested is out of range
            if( !(abs == 0 && ord == 0) && (targetAbs+abs > -1 && targetAbs+abs < length) && (targetOrd + ord > -1 && targetOrd + ord < heigth) )
            {
                printf("  <--- Tested");

                coord = (targetAbs + abs) + (targetOrd + ord) * length;
                if( grid[coord] >= 10 && grid[coord] % 2 == 1 )
                {
                    printf(" /!\\ Mine found");
                    neighborMine++;
                }
            }
        }
    }

    // Returns 1 (all are safe) by default, if no contradictions have been met earlier
    return neighborMine;
}
/*
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/
