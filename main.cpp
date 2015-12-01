#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#include"Tree.cpp"
using namespace std;
int main()
{
    //generate grid
    srand(time(NULL));
    int grid = Node::grid_size;
    int **f = new int*[grid];
    for(int i = 0; i < grid; i++)
    {
        f[i] = new int[grid];
    }
    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            f[i][j] = rand() % 39 - 19;
        }
    }
    //create game tree
    Position *pos = new Position(0, 0);
    Tree *game_t = new Tree(f, pos, 20, 10);
    //play the game
    game_t->printGrid();
    while(game_t->makeBestMove())
    {
        game_t->printGrid();
    }
    //print game result
    cout<<"Difference : "<<game_t->getRoot()->getDiff()<<endl;
    //free memory
    delete game_t;
    delete pos;
    for(int i = 0; i < grid; i++)
    {
        delete[] f[i];
    }
    delete f;
    return 0;
}
