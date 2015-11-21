#include"Tree.h"
#include<iostream>
Tree::Tree(int **initial_grid, Position *initial_pos)
{
    grid = new int*[g_size];
    for(int i = 0; i < g_size; i++)
    {
        grid[i] = new int[g_size];
    }
    for(int i = 0; i < g_size; i++)
    {
        for(int j = 0; j < g_size; j++)
        {
            grid[i][j] = initial_grid[i][j];
        }
    }
    grid[initial_pos->row()][initial_pos->column()] = MAX_NUM;


    root = new Node(nullptr, initial_pos, 0, false);
    best_move = new Position();
}
Tree::~Tree()
{
    for(int i = 0; i < g_size; i++)
    {
        delete[] grid[i];
    }
    delete root;
    delete best_move;
}
void Tree::createNextChildOf(Node* node)
{
    if(node != nullptr && node->ungeneratedChildren() > 0)
    {
        //prepare child vars
        Position *child_cursor = node->getNextMove();
        bool child_is_max = !node->is_max();
        int diff = node->getDiff();
        if(child_is_max)
        {
            diff -= grid[child_cursor->row()][child_cursor->column()];
        }
        else
        {
            diff += grid[child_cursor->row()][child_cursor->column()];
        }
        Node *child = new Node(node, child_cursor, diff, child_is_max);
        node->addChild(child);
        //remove unavailable moves from child
        Node *node_iterator = node;
        Position *itterator_move;
        do
        {
            itterator_move = node_iterator->getCursorPosition();
            child->setMoveToUnavailable(itterator_move);
            node_iterator = node_iterator->getParent();
        }
        while(node_iterator != nullptr);
        for(int i = 0; i < g_size; i++)
        {
            if(child_is_max && grid[i][child->getCursorCol()] == MAX_NUM)
            {
                child->setMoveToUnavailable(i, child->getCursorCol());
            }
            if(!child_is_max && grid[child->getCursorRow()][i] == MAX_NUM)
            {
                child->setMoveToUnavailable(child->getCursorRow(), i);
            }
        }
        //std::cout<<"Created new node\n";
    }
}
bool Tree::makeMove(int row, int col)
{
    if(row >= g_size || row < 0) return false;
    if(col >= g_size || col < 0) return false;
    if(grid[row][col] == MAX_NUM) return false;
    //if(root->is_max() && root->getCursorCol() != col) return false;
    //if(!root->is_max() && root->getCursorRow()!= row) return false;

    Node* new_root = root->removeChild(row, col);

    while(new_root == nullptr) //this child haven't been created
    {
        createNextChildOf(root);
        new_root = root->removeChild(row, col);
    }
    new_root->setParent(nullptr);
    //update grid
    grid[row][col] = MAX_NUM;
    //change root
    delete root;
    root = new_root;
    //reset best move
    best_move->reset();
    //std::cout<<"Root is row, col : " << root->getCursorRow() << " " << root->getCursorCol() << "\n";
    return true;
}
int Tree::alphaBetaMiniMax(Node* node, int alpha, int beta)
{
    if(node->getDepth() - root->getDepth() >= MAX_DEPTH)
    {
        //std::cout<<"Hit the floor depth !\n";
        return node->getDiff();
    }
    if(node->isLeaf())
    {
        //std::cout<<"Hit the floor - leaf !\n";
        if(node == root)
        {
            std::cout<<"Root is leaf\n";
            best_move->reset();
        }
        return node->getDiff();
    }
    if(node == root)
    {
        createNextChildOf(root);
        best_move->setTo( node->getFirstChild()->getCursorPosition() );
        if(node->getNumAllChildren() == 1)
        {
            //std::cout<<"Node is root and have only 1 child !\n";
            return 0; //exit
        }
    }
    int result = 0;
    Node* child = nullptr;
    if(node->is_max())
    {
        //std::cout<<"Node is max !\n";
        for(int i = 0; i < node->getNumAllChildren(); i++)
        {
            if(i < node->getNumChildren())
            {
                child = node->getChild(i);
            }
            else
            {
                createNextChildOf(node);
                child  = node->getLastChild();
            }
            result = alphaBetaMiniMax(child, alpha, beta);
            if(result > alpha)
            {
                alpha = result;
                if (node == root)
                {
                    best_move->setTo( child->getCursorPosition() );
                }
            }
            if(alpha >= beta)
                return alpha;
        }
        return alpha;
    }
    else //min turn
    {
        //std::cout<<"Node is min !\n";
        for(int i = 0; i < node->getNumAllChildren(); i++)
        {
            //std::cout<<node->getNumAllChildren() << " " << node->getNumChildren() << " " << i << "\n";
            if(i < node->getNumChildren())
            {
                child = node->getChild(i);
            }
            else
            {
                createNextChildOf(node);
                child  = node->getLastChild();
            }
            result = alphaBetaMiniMax(child, alpha, beta);
            if(result < beta)
            {
                beta = result;
                if (node == root)
                {
                    best_move->setTo( child->getCursorPosition() );
                }
            }
            if(alpha >= beta)
                return beta;
        }
        return beta;
    }
}
bool Tree::makeBestMove()
{
    const int g_size = Node::grid_size;
    int alpha = -g_size * g_size * MAX_NUM;
    int beta = g_size * g_size * MAX_NUM;
    alphaBetaMiniMax(root, alpha, beta); //calculate best move
    //std::cout<<"best move calculated : "<<best_move->row()<<" "<<best_move->column()<<std::endl;
    return makeMove(best_move->row(), best_move->column());
}

void Tree::printGrid()
{
    const int g_size = Node::grid_size;
    std::cout<<"\n|----|";
    for(int j = 0; j < g_size - 1; j++)
    {
        std::cout<<"-----|";
    }
    std::cout<<"\n";
    for(int i = 0; i < g_size; i++)
    {
        std::cout<<"|";
        for(int j = 0; j < g_size; j++)
        {
            if(grid[i][j] != MAX_NUM)
            {
                if(grid[i][j] >= 0 && grid[i][j] < 10)
                    std::cout<<"  "<<grid[i][j]<<" | ";
                if(grid[i][j] >= 10 || (grid[i][j] < 0 && grid[i][j] > -10))
                    std::cout<<" "<<grid[i][j]<<" | ";
                if(grid[i][j] <= -10)
                    std::cout<<grid[i][j]<<" | ";
            }
            else
            {
                if(i == root->getCursorRow() && j == root->getCursorCol())
                    std::cout<<"*** | ";
                else
                    std::cout<<"    | ";
            }
        }
        std::cout<<"\n|----|";
        for(int j = 0; j < g_size - 1; j++)
        {
            std::cout<<"-----|";
        }
        std::cout<<"\n";
    }
}
