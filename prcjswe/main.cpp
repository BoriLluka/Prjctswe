#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 20
#define M 40

int i, j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs, a, b, var, dir, score, HighScore, Speed;





fstream f;
void GameOver();
void snakeInitialization()
{
    f.open("highscore.txt", ios::in);
    f >> HighScore;
    f.close();

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            Field[i][j] = 0;
        }
    }

    x = N / 2;
    y = M / 2;
    Gy = y;
    Head = 5;
    Tail = 1;
    Game = 0;
    Frogs = 0;
    dir = 'd';
    score = 0;
    Speed = 99;

    for (i = 0; i < Head; i++)
    {
        Gy++;
        Field[x][Gy - Head] = i + 1;
    }
}


void print()
{
    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            cout << char(201);
        }
        else if (i == M + 1)
        {
            cout << char(187);
        }
        else
        {
            cout << char(205);
        }
    }
    cout << "   Current Score: " << score << "  HighScore: " << HighScore << endl;

    for (i = 0; i < N; i++)
    {
        cout << char(186);

        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == 0)
                cout << " ";
            if (Field[i][j] > 0 && Field[i][j] != Head)
                cout << char(176);
            if (Field[i][j] == Head)
                cout << char(178);
            if (Field[i][j] == -1)
                cout << char(15);
            if (j == M - 1)
                cout << char(186);
        }
        cout << endl;
    }

    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            cout << char(200);
        }
        else if (i == M + 1)
        {
            cout << char(188);
        }
        else
        {
            cout << char(205);
        }
    }
}

void ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void Random()
{
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;

    if (Frogs == 0 && Field[a][b] == 0)
    {
        Field[a][b] = -1;
        Frogs = 1;
        if (Speed > 10 && score != 0)
            Speed = Speed - 5;
    }
}

int getch_noblock()
{
    if (_kbhit())
        return _getch();
    else
        return -1;
}

void movement()
{
    var = getch_noblock();
    var = tolower(var);

    if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5))
        dir = var;
    if (dir == 'd')
    {
        y++;
        if (y == M - 1)
            y = 0;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }

        Head++;
        Field[x][y] = Head;
    }

    if (dir == 'a')
    {
        y--;
        if (y == 0)
            y = M - 1;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if (dir == 'w')
    {
        x--;
        if (x == -1)
            x = N - 1;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if (dir == 's')
    {
        x++;
        if (x == N - 1)
            x = 0;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }
}

void TailRemove()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == Tail)
            {
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}

void GameOver()
{
    cout << "\a";
    Sleep(1500);
    system("cls");

    if (score > HighScore)
    {
        cout << "  New HighScore " << score << "!!!!!!\n\n";
        system("pause");
        f.open("highscore.txt", ios::out);
        f << score;
        f.close();
    }

    system("cls");
    cout << "\n\n         GAME OVER !!!!!!\n";
    cout << "             Score : " << score << "\n\n";
    cout << "             Press ENTER to play again or ESC to exit ... \n";

    while (true)
    {
        var = getch_noblock();
        if (var == 13)
        {
            Game = 0;
            snakeInitialization();
            break;
        }
        else if (var == 27)
        {
            Game = 1;
            break;
        }
    }
    system("cls");
}
void displayMenu()
{
    system("cls");
    cout << "===========================" << endl;
    cout << "        SNAKE GAME          " << endl;
    cout << "===========================" << endl;
    cout << "           MENU             " << endl;
    cout << "===========================" << endl;
    cout << "  1. Play Game              " << endl;
    cout << "  2. High Scores            " << endl;
    cout << "  3. Quit                   " << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

// Function to handle menu selection
void handleMenuChoice(int choice)
{
    switch (choice)
    {
        case 1:
            snakeInitialization();
            break;
        case 2:
            // Implement high scores functionality
            break;
        case 3:
            Game = 1; // Quit the game
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

int main()
{
    Game = 0; // Game state: 0 - Menu, 1 - Quit

    while (Game == 0)
    {
        displayMenu();
        cin >> var;

        handleMenuChoice(var);

        while (Game == 0)
        {
            print();
            ResetScreenPosition();
            Random();
            movement();
            TailRemove();
            Sleep(Speed);
        }
    }

    return 0;
}
