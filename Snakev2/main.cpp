#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
#define k cout << "kek";
class Snake
{

private:
    struct body
    {
        int x,y;
    };

public:
    vector<body> snake;


    void startingPosition(int vertical, int horizontal)
    {
        snake.push_back(body());
        snake[0].x = vertical/2;
        snake[0].y = horizontal/2;
    };
    void addingBodyToSnake()
    {
        snake.push_back(body());
    };
};

class Map
{

public:
    int vertical;
    int horizontal;
    vector<vector<int> > field;
    Map() {}

    void setVertical(int ver)
    {
        vertical = ver;
    }

    void setHorizontal(int hor)
    {
        horizontal = hor;
    }

    void setMapa()
    {
        vector<int> v;
        for(int j=0; j<horizontal; j++)
        {
            v.push_back(2);
        }
        field.push_back(v);
        for (int i=1; i<vertical-1; i++)
        {
            v.clear();
            v.push_back(2);
            for(int j=1; j<horizontal-1; j++)
            {
                v.push_back(1);
            }
            v.push_back(2);
            field.push_back(v);
            v.clear();
        }
        for (int j=0; j<horizontal; j++)
        {
            v.push_back(2);
        }
        field.push_back(v);
        v.clear();
    }


    void printMap()
    {
        field[0][0]=2; // fix " " bug
        for (int i=0; i<vertical; i++)
        {
            for(int j=0; j<horizontal; j++)
            {
                if(field[i][j]==0)
                    cout << "O";
                if(field[i][j]==1)
                    cout << " ";
                if(field[i][j]==2)
                    cout << "*";
                if(field[i][j]==3)
                    cout << "a";
            }
            cout << endl;
        }
    }

};

class Game
{

private:
    Snake snake;
    Map mapa;
    char direction, earlier_direction=0;
    enum directionEnum {RIGHT, LEFT, UP, DOWN};
    int speedDecrease = 0;
    int score = 0;

public:
    Game(int vertical, int horizontal)
    {
        mapa.setVertical(vertical);
        mapa.setHorizontal(horizontal);
        mapa.setMapa();
        snake.startingPosition(vertical,horizontal);
    }

    void startGame()
    {
        mapa.field[snake.snake[0].x][snake.snake[0].y] = 0; //snake starting position on Map
        appleGenerator();
        mapa.printMap();

        direction = getch();
        system("cls"); // fix double map bug


        if(direction==97 || direction==100 || direction==115 || direction==119)
        {
            while(direction !=27)
            {
                if (kbhit()) // change direction
                {
                    direction = getch();
                }
                if(directionCheck())
                {

                    if(direction==97 && earlier_direction!=100) // left direction
                    {
                        if(!walking(LEFT))
                            break;
                    }
                    if(direction==100 && earlier_direction!=97) // right direction
                    {
                        if(!walking(RIGHT))
                            break;
                    }
                    if(direction==119 && earlier_direction!=115) // up direction
                    {
                        if(!walking(UP))
                            break;
                    }
                    if(direction==115 && earlier_direction!=119) // down direction
                    {
                        if(!walking(DOWN))
                            break;
                    }

                    if(direction==97 || direction==100 || direction==115 || direction==119) // direction must have those value
                        earlier_direction = direction;

                    _sleep(150 - speedDecrease);
                    system("cls");
                }
                else
                {
                    if(directionCheckOpposite())
                    {
                        direction = earlier_direction;
                    }
                    if (kbhit())
                    {
                        direction = getch();
                        earlier_direction = direction;
                    }
                }


            }
            cout << "GAME OVER" << endl;
        }
    }
    void scorePrint()
    {
        cout << "Wynik: " << score;
        _sleep(5000);
    }

private:

    bool directionCheck()
    {
        if((direction ==97  && earlier_direction!=100) || (direction ==100 && earlier_direction!=97) || (direction==115 && earlier_direction!=119) || (direction==119 && earlier_direction!=115)) // display bug fixing
        {
            return true;
        }
        else
            return false;
    }

    bool directionCheckOpposite()
    {
        //
        if((earlier_direction==97 && earlier_direction!=100) || (earlier_direction==100 && earlier_direction!=97) || (earlier_direction==115 && earlier_direction!=119) || (earlier_direction==119 &&  earlier_direction!=115)) // earlier_direction
        {
            return true;
        }
        else
            return false;
    }

    bool walking(directionEnum direction)
    {
        mapa.field[snake.snake.back().x][snake.snake.back().y]=1 ; // O -> "
        for(int i=snake.snake.size()-1; i>0; i--)
        {
            snake.snake[i].x = snake.snake[i-1].x;
            snake.snake[i].y = snake.snake[i-1].y;
        }
        if(direction == LEFT)
            snake.snake[0].y = snake.snake[0].y-1;
        if(direction == RIGHT)
            snake.snake[0].y = snake.snake[0].y+1;
        if(direction == UP)
            snake.snake[0].x = snake.snake[0].x-1;
        if(direction == DOWN)
            snake.snake[0].x = snake.snake[0].x+1;

        if(mapa.field[snake.snake[0].x][snake.snake[0].y]!=0)
        {
            if(mapa.field[snake.snake[0].x][snake.snake[0].y]!=2)
            {
                if(mapa.field[snake.snake[0].x][snake.snake[0].y]==3)
                {
                    mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // a -> O
                    snake.addingBodyToSnake();
                    appleGenerator();
                }
                else
                    mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // " " -> O
            }
            else
            {
                if(direction == LEFT)
                {
                    if(mapa.field[(snake.snake[0].x)][mapa.horizontal-2]!=3)
                    {
                        snake.snake[0].y = mapa.horizontal-2;
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // " " -> O
                        mapa.field[snake.snake[0].x][0] = 2;
                        mapa.field[snake.snake[0].x][mapa.horizontal-1]=2;
                    }
                    else
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // a -> O
                        snake.addingBodyToSnake();
                        appleGenerator();
                    }
                }
                if(direction == RIGHT)
                {
                    if(mapa.field[(snake.snake[0].x)][mapa.horizontal-2]!=3)
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y] = mapa.field[(snake.snake[0].x)][1];
                        snake.snake[0].y = 1;
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // " " -> O
                        mapa.field[snake.snake[0].x][mapa.horizontal-1] = 2;
                        mapa.field[snake.snake[0].x][0]=2;
                    }
                    else
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // a -> O
                        snake.addingBodyToSnake();
                        appleGenerator();
                    }
                }
                if(direction == UP)
                {
                    if(mapa.field[(snake.snake[0].x)][mapa.horizontal-2]!=3)
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y] = mapa.field[mapa.vertical-1][snake.snake[0].y];
                        snake.snake[0].x = mapa.vertical-2;
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // " " -> O
                        mapa.field[0][snake.snake[0].y] = 2;
                        mapa.field[mapa.vertical-1][snake.snake[0].y]=2;
                    }
                    else
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // a -> O
                        snake.addingBodyToSnake();
                        appleGenerator();
                    }
                }
                if(direction == DOWN)
                {
                    if(mapa.field[(snake.snake[0].x)][mapa.horizontal-2]!=3)
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y] = mapa.field[1][snake.snake[0].y];
                        snake.snake[0].x = 1;
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // " " -> O
                        mapa.field[0][snake.snake[0].y] = 2;
                        mapa.field[mapa.vertical-1][snake.snake[0].y]=2;
                    }
                    else
                    {
                        mapa.field[snake.snake[0].x][snake.snake[0].y]=0; // a -> O
                        snake.addingBodyToSnake();
                        appleGenerator();
                    }
                }
            }
        }
        else return false;

        mapa.printMap();
        return true;
    }

    void appleGenerator()
    {
        int x_position_of_apple;
        int y_position_of_apple;
        bool true_apple = true;
        while(true_apple)
        {
            x_position_of_apple = rand()%(mapa.vertical-2)+1;
            y_position_of_apple = rand()%(mapa.horizontal-2)+1;
            for (int i=0; i<snake.snake.size(); i++)
            {
                if (snake.snake[i].x!=x_position_of_apple || snake.snake[i].y!=y_position_of_apple)
                {
                    true_apple = false;
                }
                else
                {
                    true_apple = true;
                    break;
                }
            }
        }
        //mapa.field[x_position_of_apple][x_position_of_apple] = 3; // generate next apple
        mapa.field.at(x_position_of_apple).at(y_position_of_apple) = 3;
        speedDecrease =  speedDecrease +5;
        score++;
    }


};

int main()
{
    Game game(8,20);
    game.startGame();
    game.scorePrint();
    return 0;
}
