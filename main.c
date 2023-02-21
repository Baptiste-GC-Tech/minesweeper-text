#include <stdio.h>

char MainMenu();

int main()
{
    int length, width, mines, maxSpace = 1000;
    char choice;

    printf("--- MINEWSEEPER ---\n\n");

    choice = MainMenu();
    printf("Here is choice = %c\n", choice);

    // Sets up internal values to generate the grid
    /*switch (choice)
    {
        case 'e':
            length = 10, width = 8, mines = 10;
            printf("\n<*> EASY MODE SELECTED <*>\n\n");
            break;

        case 'm':
            length = 18, width = 14, mines = 40;
            printf("\n<*> MEDIUM MODE SELECTED <*>\n\n");
            break;

        case 'h':
            length = 24, width = 20, mines = 99;
            printf("\n<*> HARD MODE SELECTED <*>\n\n");
            break;

        case 'c':
            length = width = mines = -1;
            do
            {
                if(length < 0)
            }

        default:

    }*/

    return 0;
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

        printf("Your choice : "); gets(&choice); printf("\n");

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

        printf("\n    #$ choice = %c\n", choice);
    } while( choice < 'a' || choice > 'z' );

    printf("\nOUT OF LOOP WITH %c\n", choice);

    return choice;
}
