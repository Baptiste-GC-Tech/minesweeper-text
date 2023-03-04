#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TRUE  1
#define FALSE 0

typedef int Bool;

/*
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/

char MainMenu(char* menuValidChars, int size);
void FillGrid(int lenght, int height, int mines, int* grid);
void Display(int l, int h, int* tableau);
int MineCounter(int length, int height, int* grid, int targetAbs, int targetOrd);
int FlagCounter(int length, int height, int* grid, int targetAbs, int targetOrd);
int TurnManager(int length, int height, int* grid, char action, int targetAbs, int targetOrd);
void Dig(int length, int height, int* grid, int targetAbs, int targetOrd);
int AskInt(int lowLimit, int highLimit);
char AskChar(char* validChars, int size);

// Can be updated by any function without being passed back and forth
// Used to show to the user what he could have done wrong despite the console being cleared a lot
char* gErrorMsg[100];

int main()
{
    // Grid and grid data
    int* grid = (int*) malloc(sizeof(int) * 1);
    int length, height, mines, maxSpace;

    // Player input
    char menuChoice;
    char query[50];
    int actionAbs, actionOrd, actionType;

    // Input filters
    char menuValidChars[10] = { 'e', 'E', 'm', 'M', 'h', 'H', 'c', 'C', 'r', 'R' };
    char actionValidChars[6] = { 'd', 'D', 'f', 'F', 'r', 'R' };

    // Game loop boolean
    Bool menuLoop = TRUE;
    Bool gameOver = FALSE;
    Bool endProgram = FALSE;

    // Random seed initialization
    srand(time(NULL));

    do
    {
        printf("\033[0m");
        // Retrieval of menuChoice, initialize the grid if correct input, call MainMenu again if not
        do
        {
            menuChoice = MainMenu(menuValidChars, sizeof(menuValidChars) / sizeof(char));

            if (menuChoice >= 'A' && menuChoice <= 'Z')
            {
                menuChoice += 32;
            }

            switch (menuChoice)
            {
            case 'e':
                //int grid[80];
                length = 10, height = 8, mines = 10, maxSpace = 1000;
                grid = (int*)realloc(grid, sizeof(int) * length * height);
                printf("\033[38;2;111;245;66m\n<*>~ EASY MODE SELECTED ~<*>\n\n\033[0m");
                printf("\"LOADING\" FOR DRAMATIC EFFECT.\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT..\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT...\n"); Sleep(600);
                FillGrid(length, height, mines, grid);
                break;

            case 'm':
                //int grid[80];
                length = 18, height = 14, mines = 40, maxSpace = 1000;
                grid = (int*)realloc(grid, sizeof(int) * length * height);
                printf("\033[38;2;111;245;66m\n<*>~ MEDIUM MODE SELECTED ~<*>\n\n\033[0m");
                printf("\"LOADING\" FOR DRAMATIC EFFECT.\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT..\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT...\n"); Sleep(600);
                FillGrid(length, height, mines, grid);
                break;

            case 'h':
                length = 24, height = 20, mines = 99, maxSpace = 1000;
                grid = (int*)realloc(grid, sizeof(int) * length * height);
                printf("\033[38;2;111;245;66m\n<*>~ HARD MODE SELECTED ~<*>\n\n\033[0m");
                printf("\"LOADING\" FOR DRAMATIC EFFECT.\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT..\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT...\n"); Sleep(600);
                FillGrid(length, height, mines, grid);
                break;

            case 'c':
                printf("\n<!>~ CUSTOME MODE SELECTED ~<!>\n");
                // Asks for the custom grid length
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter a length (1 ~ 99)  ");
                    length = AskInt(1, 99);
                } while (length < 0);
                // Asks for the custom grid height
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter a width (1 ~ 99)  ");
                    height = AskInt(1, 99);
                } while (height < 0);
                // Asks for the custom grid amount of mines
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter an amount of mines (0 ~ %d)  ", length * height);
                    mines = AskInt(0, length * height);
                } while (mines < 0);

                printf("\033[38;2;111;245;66m\n<!>~ GRID SETUP SUCCESSFULL ~<!>\n\n\033[0m");
                printf("\"LOADING\" FOR DRAMATIC EFFECT.\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT..\n"); Sleep(600);
                printf("\"LOADING\" FOR DRAMATIC EFFECT...\n"); Sleep(600);

                grid = (int*) realloc(grid, sizeof(int) * length * height);
                FillGrid(length, height, mines, grid);
                break;

                case 'r':
                    length = 50, height = 25, mines = length * height - 1, maxSpace = 1000;
                    grid = (int*) realloc(grid, sizeof(int) * length * height);
                    printf("\033[38;2;156;22;22m\n\n<*>~ GOOD LUCK >:) ~<*>\n\033[0m"); Sleep(1500);
                    FillGrid(length, height, mines, grid);
                    break;
            }

            // Updates menuLoop "boolean"
            for (int x = 0; x < strlen(menuValidChars); x++)
            {
                if( menuChoice == menuValidChars[x])
                {
                    menuLoop = FALSE;
                    break;
                }
            }
        } while( menuLoop );

        while (!gameOver)
        {
            // Input loop
            do
            {
                system("cls");
                Display(length, height, grid);
                printf("%s", gErrorMsg);
                strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                if (menuChoice == 'r')
                {
                    // Special color for good luck >:)
                    system("color 04");
                }

                // Ask for where the player wishes to act
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter row : ");
                    actionOrd = AskInt(1, height);
                } while (actionOrd < 0);
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter col : ");
                    actionAbs = AskInt(1, length);
                } while (actionAbs < 0);

                // Ask for what the player wishes to do
                do
                {
                    printf("%s", gErrorMsg);
                    strcpy_s(gErrorMsg, sizeof(char) * 100, "");
                    printf("\nEnter action on [%d, %d] ('d'ig, 'f'lag, 'r'e-enter coords) : ", actionAbs, actionOrd);
                    actionType = AskChar(actionValidChars, strlen(actionValidChars));
                    if( actionType >= 'A' && actionType <= 'Z' )
                    {
                        actionType += 32;
                    }
                } while (actionType < 0);
            } while (actionType == 'r');

            gameOver = TurnManager(length, height, grid, actionType, actionAbs - 1, actionOrd - 1);
        }

        // Aftermath of the game
        if (gameOver == -1)
        {
            system("cls");
            printf("\nYOU LOSE\n\n");
            gameOver = FALSE;
            Display(length, height, grid);
        }
        else
        {
            system("cls");
            printf("\nYOU WIN\n\n");
            gameOver = FALSE;
            Display(length, height, grid);
        }

        endProgram = -1;
        do
        {
            printf("\n\nEnter 0 to get back to Main Menu, and 1 to close   ");
            endProgram = AskInt(0, 1);
        } while (endProgram < 0);
        
    } while( !endProgram );

    free(grid);
    return 0;
}

// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY

char MainMenu(char* menuValidChars, int size)
{
    char choice;

    do
    {
        // Display main menu
        system("cls");
        printf("--- MINEWSEEPER ---\n\n");

        printf("%s", gErrorMsg);
        strcpy_s(gErrorMsg, sizeof(char) * 100, "");

        printf("(e)Easy   - 10x 8, 10 mines\n");
        printf("(m)Medium - 18x14, 40 mines\n");
        printf("(h)Hard   - 24x20, 99 mines\n");
        printf("(c)Custom - ??x??, ?? mines\n\n");

        printf("Your choice : ");
        choice = AskChar(menuValidChars, size);
    } while (choice < 0);

    return choice;
}

void FillGrid(int length, int height, int mines, int* grid)
{
    int x, y, coord, minePlaced = mines;

    // Fills the whole grid with the code 30 (which represents a Hidden No-Bomb cell)
    for (int ord = 0; ord < height; ord++)
    {
        for (int abs = 0; abs < length; abs++)
        {
            coord = abs + ord * length;
            grid[coord] = 30;
        }
    }

    // Increment cells at random by 1, which creates 31 (which represents a Hidden With-Bomb cell), effectively placing the amount of mines desired
    for (minePlaced; minePlaced > 0; minePlaced--)
    {
        coord = (rand() % length) + (rand() % height) * length;

        if (grid[coord] != 31)
        {
            grid[coord] += 1;
        }
        else
        {
            minePlaced++;
        }
    }
    
    /*
    // Remove commentary to fill first 10 cells of a board with everything a cell can display. In order : Neighbor indicator from 1 to 8, Flag, Empty, Bomb, Detonated Bomb
    // The rest of the cells are Hidden
    
    grid[0] = 1;
    grid[1] = 2;
    grid[2] = 3;
    grid[3] = 4;
    grid[4] = 5;
    grid[5] = 6;
    grid[6] = 7;
    grid[7] = 8;
    grid[8] = 10;
    grid[9] = 20;
    grid[10] = 21;
    grid[11] = 22;
    */
}

void Display(int l, int h, int* tableau)
{

    /*
    bomb = 0 / 1
    flag/show/hidden = 1 / 2 / 3
    state bomb
    10 / 20 / 30 / 11 / 21 / 31
    */

    // Set ASCII codes for the cells
    int bomb = 15, flag = 127, hidden = 219, show = 32;
    printf("  ");

    // Prints the tenth for the columns
    for (int i = 0; i < l; i++)
    {
        if (i < 9)
        {
            printf("%c ", 186);
        }
        else {
            printf("%c%d", 186, (i + 1) / 10);
        }
    }
    printf("%c", 186);
    printf("\n  ");

    // Prints the units for the columns
    for (int i = 0; i < l; i++)
    {
        printf("%c%d", 186, (i - ((i + 1) / 10) * 10) + 1);
    }
    printf("%c", 186);

    int x = 0;
    for (int i = 0; i < h; i++)
    {
        // Prints the adequate box part
        printf("\n%c%c", 205, 205);
        for (int j = 0; j < l; j++)
        {

            printf("%c%c", 206, 205);
        }
        printf("%c", 185);

        // Prints the row number, align the units with themselves
        if (i < 9) {
            printf("\n %d", i + 1);
        }
        else {
            printf("\n%d", i + 1);
        }

        // Prints the cell content, given the value it holds
        for (int j = 0; j < l; j++)
        {
            // "Coded" part. Prints a character given the arbitrarily defined code for it
            if (tableau[x] == 10 || tableau[x] == 11) {
                printf("%c\033[38;2;0;0;0m\033[48;2;255;255;0m%c\033[0m", 186, flag);
            }
            else if (tableau[x] == 20) {
                printf("%c%c", 186, show);
            }
            else if (tableau[x] == 21) {
                printf("%c\033[38;2;0;0;0m\033[48;2;255;196;0m%c\033[0m", 186, bomb);
            }
            else if (tableau[x] == 22) {
                printf("%c\033[38;2;0;0;0m\033[48;2;255;47;0m%c\033[0m", 186, bomb);
            }
            else if (tableau[x] == 30 || tableau[x] == 31) {
                printf("%c%c", 186, hidden);
            }

            // "Raw" part. Prints the value found in the cell with a unique color given the value (used to show neighbor mines)
            else if (tableau[x] == 1){
                printf("%c\033[38;2;0;0;255m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 2) {
                printf("%c\033[38;2;0;255;0m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 3) {
                printf("%c\033[38;2;255;0;0m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 4) {
                printf("%c\033[38;2;255;0;255m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 5) {
                printf("%c\033[38;2;150;86;17m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 6) {
                printf("%c\033[38;2;0;0;255m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 7) {
                printf("%c\033[38;2;0;255;255m%d\033[0m", 186, tableau[x]);
            }
            else if (tableau[x] == 8) {
                printf("%c\033[38;2;0;0;255m%d\033[0m", 186, tableau[x]);
            }
            else {
                printf("%c%d", 186, tableau[x]);
            }
            x = x + 1;
        }
        printf("%c", 186);
    }
    printf("\n%c", 205);
    for (int j = 0; j < l; j++)
    {

        printf("%c%c", 205, 202);
    }
    printf("%c%c", 205, 188);
}

int MineCounter(int length, int height, int* grid, int targetAbs, int targetOrd)
{
    int coord, neighborMine = 0;

    // Go through the 3 neighbor coordinates of the targeted cell
    for (int ord = -1; ord < 2; ord++)
    {
        for (int abs = -1; abs < 2; abs++)
        {
            // Skip the test if it would be performed on the target, or if the cell tested is out of range
            if (!(abs == 0 && ord == 0) && (targetAbs + abs > -1 && targetAbs + abs < length) && (targetOrd + ord > -1 && targetOrd + ord < height))
            {
                coord = (targetAbs + abs) + (targetOrd + ord) * length;
                if (grid[coord] >= 10 && grid[coord] % 2 == 1)
                {
                    neighborMine++;
                }
            }
        }
    }

    // Returns the number of neighbor mines
    return neighborMine;
}

int FlagCounter(int length, int height, int* grid, int targetAbs, int targetOrd)
{
    int coord, neighborFlag = 0;

    // Go through the 3 neighbor coordinates of the targeted cell
    for (int ord = -1; ord < 2; ord++)
    {
        for (int abs = -1; abs < 2; abs++)
        {
            // Skip the test if it would be performed on the target, or if the cell tested is out of range
            if (!(abs == 0 && ord == 0) && (targetAbs + abs > -1 && targetAbs + abs < length) && (targetOrd + ord > -1 && targetOrd + ord < height))
            {
                coord = (targetAbs + abs) + (targetOrd + ord) * length;
                if (grid[coord] / 10 == 1)
                {
                    neighborFlag++;
                }
            }
        }
    }

    // Returns the number of neighbor mines
    return neighborFlag;
}

int TurnManager(int length, int height, int* grid, char action, int targetAbs, int targetOrd)
{
    int coord = targetAbs + targetOrd * length;

    // Check if the cell is shown. If so, skips the turn entirely
    if (grid[coord] == 20)
    {
        strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;21;223;230m\n<?>~ What are you doing, it's already revealed ? ~<?>\n\033[0m");
        return FALSE;
    }

    // Places a flag on the selected cell
    else if (action == 'f')
    {
        // If no flags are found, places one. Otherwise, removes a flag if one is found
        if( grid[coord] < 10)
        {
            strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;21;223;230m\n<?>~ No point in placing a flag there... ~<?>\n\033[0m");
        }
        else if (grid[coord] / 10 == 3)
        {
            grid[coord] -= 20;
        }
        else
        {
            grid[coord] += 20;
        }
        return FALSE;
    }

    // Attempt a dig on the selected cell
    else
    {
        // Check if the cell was hidden. If not, doesn't dig anything and notifies the player
        if (grid[coord] / 10 == 1)
        {
            printf("\n<?>~ You can't dig up a flag... ~<?>");
            strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;21;223;230m\n<?>~ You can't dig up a flag... ~<?>\n\033[0m");
        }

        // Discover the cell and all it's 8 neighbor if it has mined neighbors but a sufficient amount of flag have been placed
        // This doesn't check if the flags are indeed covering a mine, and can still dig up one
        else if( grid[coord] < 10)
        {
            int newAbs, newOrd;
            if( FlagCounter(length, height, grid, targetAbs, targetOrd) == grid[coord] )
            {
                for (int offsetAbs = -1; offsetAbs < 2; offsetAbs++)
                {
                    for (int offsetOrd = -1; offsetOrd < 2; offsetOrd++)
                    {
                        newAbs = targetAbs + offsetAbs;
                        newOrd = targetOrd + offsetOrd;

                        if (!(offsetAbs == 0 && offsetOrd == 0) && (newAbs > -1 && newAbs < length) && (newOrd > -1 && newOrd < height) && grid[newAbs + newOrd * length] / 10 != 1)
                        {
                            Dig(length, height, grid, newAbs, newOrd);
                        }
                    }
                }
            }
            else
            {
                strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;79;224;181m\n<=> You might want to check the amount of flags around there <=>\n\033[0m");
            }
        }

        // Returns 1 if the player discovered a mined cell, and reveal every other mines
        else if (grid[coord] % 2 == 1)
        {
            grid[coord] = 22;
            for (int i = 0; i < length * height; i++)
            {
                if (grid[i] == 31)
                {
                    grid[i] = 21;
                }
            }
            return -1;
        }
        
        // Discover the cell and it's "safe" neighborhood (meaning the neighbors don't have mined cell around them)
        else
        {
            Dig(length, height, grid, targetAbs, targetOrd);
        }

        // Checks if the player has won. If he didn't, return 0. This check is avoided if no cell was dug, or if he lost already
        for (int i = 0; i < length * height; i++)
        {
            if( grid[i] == 30)
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

void Dig(int length, int height, int* grid, int targetAbs, int targetOrd)
{
    int coord = targetAbs + targetOrd * length;
    int unsafeNeighborsCount;
    int newAbs, newOrd;

    unsafeNeighborsCount = MineCounter(length, height, grid, targetAbs, targetOrd);

    // Reveals only the targeted cell if it has unsafe neighborhood
    if (unsafeNeighborsCount != 0)
    {
        grid[coord] = unsafeNeighborsCount;
    }

    // Reveals the targeted cell and attempt do to the same to it's neighbors if it has safe neighborhood
    else
    {
        grid[coord] = 20;

        for (int offsetAbs = -1; offsetAbs < 2; offsetAbs++)
        {
            for (int offsetOrd = -1; offsetOrd < 2; offsetOrd++)
            {
                newAbs = targetAbs + offsetAbs;
                newOrd = targetOrd + offsetOrd;

                if (!(offsetAbs == 0 && offsetOrd == 0) && (newAbs > -1 && newAbs < length) && (newOrd > -1 && newOrd < height))
                {
                    // Only Dig if the cell is hidden to begin with. Avoids an infinite loop of trying to Dig already revealed neighbors
                    if( grid[newAbs + newOrd * length] / 10 == 3)
                    {
                        Dig(length, height, grid, newAbs, newOrd);
                    }
                }
            }
        }
    }
}

int AskInt(int lowLimit, int highLimit)
{
    char query[50];
    int nbDigit = 1;

    scanf_s(" %[^\n]s", &query,50);
    

    // Determining the maximum amount of digits to write highLimit
    for (int var = 10; highLimit % var != highLimit; var *= 10)
    {
        nbDigit++;
    }

    // If the input contains more digits than expected, discard as invalid immediately (code : -1)
    if (strlen(query) > nbDigit)
    {
        strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;255;64;0m<!>~ INPUT TOO LONG ~<!>\n\033[0m");
        return -1;
    }

    // If any characters of the query is not a number, discard as invalid as soon as something else is found (code : -2)
    for (int x = 0; x < strlen(query); x++)
    {
        if (query[x] < '0' || query[x] > '9')
        {
            strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;255;64;0m<!>~ INVALID INPUT ~<!>\n\033[0m");
            return -2;
        }
    }

    // If the input result doesn't fit in between the limits, discard as invalid (code : -3)
    if (atoi(query) < lowLimit || atoi(query) > highLimit)
    {
        strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;255;64;0m<!>~ INPUT OUT OF RANGE ~<!>\n\033[0m");
        return -3;
    }

    return atoi(query);
}

char AskChar(char* validChars, int size)
{
    char query[50];
    Bool validCharFound = FALSE;

    scanf_s(" %[^\n]s", &query,50);

    // If the input contains more than 1 character, discard as invalid immediately (code : -1)
    if (strlen(query) > 1)
    {
        strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;255;64;0m<!>~ INPUT TOO LONG ~<!>\n\033[0m");
        return -1;
    }

    // If the character matches with any of the accepted ones, returns it
    for (int x = 0; x < size; x++)
    {
        if( query[0] == validChars[x] )
        {
            return query[0];
        }
    }

    // If the character failed to match any of the accepted ones, discard as invalid (code : -2)
    strcpy_s(gErrorMsg, sizeof(char) * 100, "\033[38;2;255;64;0m<!>~ INPUT DOESN'T MATCH ANY OPTIONS ~<!>\n\033[0m");
    return -2;
}


/*15122
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/
