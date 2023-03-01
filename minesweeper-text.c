#include <stdio.h>
#include <stdlib.h>

/*
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/

char MainMenu();
void FillGrid(int lenght, int height, int mines, int* grid);
void Display(int l, int h, int* tableau);
int MineCounter(int length, int height, int* grid, int targetAbs, int targetOrd);
int TurnManager(int length, int height, int* grid, int action, int targetAbs, int targetOrd);
void Dig(int length, int height, int* grid, int targetAbs, int targetOrd);
int AskCoord(int limit);

int main()
{
    // Grid and grid data
    int* grid = NULL;
    int length, height, mines, maxSpace;

    // Player input
    char menuChoice;
    int actionAbs, actionOrd, actionType;
    int inputReady = 0;

    // Game loop boolean
    int gameOver = 0;

    // Random seed initialization
    srand(time(NULL));

    printf("--- MINEWSEEPER ---\n\n");

    // Retrieval of menuChoice, initialize the grid if correct input, call MainMenu again if not
    do
    {
        menuChoice = MainMenu();

        switch (menuChoice)
        {
        case 'e':
            //int grid[80];
            length = 10, height = 8, mines = 10, maxSpace = 1000;
            grid = (int*)malloc(sizeof(int) * length * height);
            printf("\n<*>~ EASY MODE SELECTED ~<*>\n");
            FillGrid(length, height, mines, grid);
            break;

        case 'm':
            //int grid[80];
            length = 18, height = 14, mines = 40, maxSpace = 1000;
            grid = (int*)malloc(sizeof(int) * length * height);
            printf("\n<*>~ MEDIUM MODE SELECTED ~<*>\n");
            FillGrid(length, height, mines, grid);
            break;

        case 'h':
            length = 24, height = 20, mines = 99, maxSpace = 1000;
            grid = (int*)malloc(sizeof(int) * length * height);
            printf("\n<*>~ HARD MODE SELECTED ~<*>\n");
            FillGrid(length, height, mines, grid);
            break;

        case 'p':
            length = 50, height = 25, mines = length * height - 1, maxSpace = 1000;
            grid = (int*)malloc(sizeof(int) * length * height);
            printf("\n<*>~ HARD MODE SELECTED ~<*>\n");
            FillGrid(length, height, mines, grid);
            break;

        case 'c':
            printf("\n<!>~ ###[WIP]### ~<!>\n");
            printf("\nSELECT ANOTHER OPTION\n\n");
            break;

        default:
            printf("\n<!>~ THIS OPTION DOESN'T EXIST ~<!>\n\n");
            break;
        }
    } while (menuChoice != 'e' && menuChoice != 'm' && menuChoice != 'h' && menuChoice != 'c' && menuChoice != 'p');

    while (!gameOver)
    {
        // Input loop
        do
        {
            system("cls");
            Display(length, height, grid);

            // Ask for where the player wishes to act
            do
            {
                printf("\n\nEnter ord : ");
                actionOrd = AskCoord(height);
            } while (actionOrd < 0);
            do
            {
                printf("\nEnter abs : ");
                actionAbs = AskCoord(length);
            } while (actionAbs < 0);

            // Ask for what the player wishes to do
            do
            {
                printf("Enter action on [%d, %d] ('d'ig, 'f'lag, 'r'e-enter coords) : ", actionAbs, actionOrd);
                actionType = AskAction();
            } while (actionType < 0);
        } while (actionType == 3);

        gameOver = TurnManager(length, height, grid, actionType, actionAbs - 1, actionOrd - 1);
    }

    // Aftermath of the game
    if (gameOver == -1)
    {
        printf("\nYOU LOSE\n\n");
        Display(length, height, grid);
    }
    else
    {
        printf("\nYOU WIN");
    }

    return 0;
}

// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY
// ENTERING FUNCTION TERRITORY

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
        scanf_s(" %c", &choice);
        printf("\n");

        // Check if input for choice was within the alphabet, no matter the case
        if (choice == '\0' || (choice < 'A' || choice > 'Z') && (choice < 'a' || choice > 'z'))
        {
            printf("<!>~ YOU DID NOT ENTER A LETTER ~<!>\n\n");
        }

        // Lowercase choice if needed
        if (choice >= 'A' && choice <= 'Z')
        {
            choice += 32;
        }
    } while (choice < 'a' || choice > 'z');

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
}

void Display(int l, int h, int* tableau)
{
    /*15122
    bomb = 0 / 1
    flag/show/hidden = 1 / 2 / 3
    state bomb
    10 / 20 / 30 / 11 / 21 / 31
    */
    int bomb = 15, flag = 127, hidden = 219, show = 32/*32=' ' & 177='▒'*/;
    printf("  ");
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

    for (int i = 0; i < l; i++)
    {
        printf("%c%d", 186, (i - ((i + 1) / 10) * 10) + 1);
    }
    printf("%c", 186);

    int x = 0;
    for (int i = 0; i < h; i++)
    {
        printf("\n%c%c", 205, 205);
        for (int j = 0; j < l; j++)
        {

            printf("%c%c", 206, 205);
        }
        printf("%c", 185);

        if (i < 9) {
            printf("\n %d", i + 1);
        }
        else {
            printf("\n%d", i + 1);
        }
        for (int j = 0; j < l; j++)
        {
            if (tableau[x] == 10 || tableau[x] == 11) {
                printf("%c%c", 186, flag);
            }
            else if (tableau[x] == 20) {
                printf("%c%c", 186, show);
            }
            else if (tableau[x] == 21) {
                printf("%c%c", 186, bomb);
            }
            else if (tableau[x] == 30 || tableau[x] == 31) {
                printf("%c%c", 186, hidden);
            }
            else if (tableau[x] == 31) {
                printf("%c\033[38;2;0;255;255m%c\033[0m", 186, 177);
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

int TurnManager(int length, int height, int* grid, int action, int targetAbs, int targetOrd)
{
    int coord = targetAbs + targetOrd * length;

    // Check if the cell is shown. If so, skips the turn entirely
    if (grid[coord] / 10 == 2 || grid[coord] < 9)
    {
        printf("<?>~ What are you doing, it's already revealed ? ~<?>\n");
    }

    // Places a flag on the selected cell
    else if (action == 2)
    {
        // If no flags are found, places one. Otherwise, removes a flag if one is found
        if (grid[coord] / 10 == 3)
        {
            grid[coord] -= 20;
        }
        else
        {
            grid[coord] += 20;
        }
    }

    // Attempt a dig on the selected cell
    else
    {
        // Check if the cell was hidden. If not, doesn't dig anything and notifies the player
        if (grid[coord] / 10 == 1)
        {
            printf("<?>~ You can't dig up a flag... ~<?>\n");
        }

        // Returns 1 if the player discovered a mined cell
        if (grid[coord] % 2 == 1)
        {
            grid[coord] = 21;
            return -1;
        }

        // Discover the cell and it's "safe" neighborhood (meaning the neighbors don't have mined cell around them)
        else
        {
            Dig(length, height, grid, targetAbs, targetOrd);
        }
    }

    return 0;
}

void Dig(int length, int height, int* grid, int targetAbs, int targetOrd)
{
    int coord = targetAbs + targetOrd * length;
    int unsafeNeighborsCount;
    int newAbs, newOrd;

    // Checks if the current cell does not contain a mine
    if (grid[coord] % 2 == 0 && grid[coord] / 10 != 2)
    {
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
                        Dig(length, height, grid, newAbs, newOrd);
                    }
                }
            }
        }
    }
}

int AskCoord(int limit)
{
    char query[50];

    scanf_s(" %[^\n]s", &query);


    // If the input could be in the 4 digit range, discard as invalid immediately (code : -1)
    if (strlen(query) > 3)
    {
        printf("<!>~ INPUT TOO LONG ~<!>\n");
        return -1;
    }

    // If any characters of the query is not a number, discard as invalid as soon as something else is found (code : -2)
    for (int x = 0; x < strlen(query); x++)
    {
        if (query[x] < '0' || query[x] > '9')
        {
            printf("<!>~ INVALID INPUT ~<!>\n");
            return -2;
        }
    }

    // If the input result doesn't fit into the grid, or is 0, discard as invalid (code : -3)
    if (atoi(query) < 1 || atoi(query) > limit)
    {
        printf("<!>~ INPUT OUT RANGE ~<!>\n");
        return -3;
    }

    return atoi(query);
}

int AskAction()
{
    char query[50];

    scanf_s(" %[^\n]s", &query);

    // If the input more than 1 character, discard as invalid immediately (code : -1)
    if (strlen(query) > 1)
    {
        printf("<!>~ INPUT TOO LONG ~<!>\n");
        return -1;
    }

    // If any characters of the query is not a letter (regardless of case), discard as invalid as soon as something else is found (code : -2)
    for (int x = 0; x < strlen(query); x++)
    {
        if ((query[x] < 'a' || query[x] > 'z') && (query[x] < 'A' || query[x] > 'Z'))
        {
            printf("<!>~ INVALID INPUT ~<!>\n");
            return -2;
        }
    }

    if (query[0] < 'Z' && query[0] > 'A')
    {
        query[0] += 32;
    }

    switch (query[0])
    {
    case 'd':
        return 1;

    case 'f':
        return 2;

    case 'r':
        return 3;

    default:
        return -3;
    }
}


/*15122
bomb = 0 / 1
flag/show/hidden = 1 / 2 / 3
state bomb
10 / 20 / 30 / 11 / 21 / 31
*/
