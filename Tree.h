#include"Node.cpp"
class Tree
{
private:
    static const int g_size = Node::grid_size;
    int MAX_DEPTH;
    int MAX_NUM;
    Node *root;
    int **grid;
    Position *best_move;
    void createNextChildOf(Node* node);
    int alphaBetaMiniMax(Node* node, int alpha, int beta);
public:
    Tree(int **initial_grid, Position *initial_pos, int max_num, int max_depth);
    ~Tree();

    Node* getRoot() {return root;}

    bool makeMove(int row, int col); //returns 1 for success and 0 for failure
    bool makeBestMove();
    void printGrid();
    bool gameOver() { return root->isLeaf(); }
};
