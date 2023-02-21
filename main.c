#include <stdio.h>
#include <stdlib.h>

char MainMenu();

int main()
{
    int length, width, mines, maxSpace = 1000;
    char choice;

    printf("--- MINEWSEEPER ---\n\n");

    // Retrieval of choice, initialize the grid if correct input, call MainMenu again if not
    do
    {
        choice = MainMenu();

        switch (choice)
        {
            case 'e':
                printf("\n<*>~ EASY MODE SELECTED ~<*>");
                char grid[80];
                unsigned int size = sizeof(grid)/sizeof(grid[0]);
                FillGrid(10, 8, 10, *grid, size);
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
