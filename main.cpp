#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#include"Tree.cpp"
using namespace std;
int main()
{
    int player_wins = 0;
    int computer_wins = 0;
    int draws = 0;
    for(int s = 0; s < 100; s++)
    {
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
    Position *pos = new Position(0, 0);
    Tree *game_t = new Tree(f, pos);
    game_t->printGrid();
    while(game_t->makeBestMove())
    {
        game_t->printGrid();
    }
    game_t->printGrid();
    cout<<endl<<game_t->getRoot()->getNumAllChildren()<< " = ";
    cout<<game_t->getRoot()->getNumChildren() << " + ";
    cout<<game_t->getRoot()->ungeneratedChildren() <<endl;
    cout<<"Cursor : "<<game_t->getRoot()->getCursorCol()<<" ";
    cout<<game_t->getRoot()->getCursorRow()<<endl;
    cout<<"Difference : "<<game_t->getRoot()->getDiff()<<endl;
    player_wins += (game_t->getRoot()->getDiff() < 0);
    computer_wins += (game_t->getRoot()->getDiff() > 0);
    draws += (game_t->getRoot()->getDiff() == 0);
    }
    cout<<endl<<"Player wins: "<<player_wins<<endl;
    cout<<"Computer wins: "<<computer_wins<<endl;
    cout<<"Draws: "<<draws<<endl;
    return 0;
}
