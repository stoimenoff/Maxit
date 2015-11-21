#include"Node.cpp"
class Tree
{
private:
    static const int g_size = Node::grid_size;
    static const int MAX_DEPTH = 10;
    Node *root;
    int **grid;
    Position *best_move;
    void createNextChildOf(Node* node);
    int alphaBetaMiniMax(Node* node, int alpha, int beta);
public:
    static const int MAX_NUM = 20;
    Tree(int **initial_grid, Position *initial_pos);
    ~Tree();
    Node* getRoot() {return root;}
    bool makeMove(int row, int col); //returns 1 for success and 0 for failure
    bool makeBestMove();
    void printGrid();
};
