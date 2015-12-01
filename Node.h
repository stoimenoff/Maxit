#include"Position.cpp"
#include<vector>
using std::vector;
class Node
{
private:
    vector<Position*> available_moves;
    vector<Node*> children;
    Node *parent;
    Position *cursor;
    bool is_max_player;
    int difference;
    int depth;
public:
    static const int grid_size;
    Node(Node *parent, Position *cur, int diff, bool is_max);
    ~Node();
    Node *getParent() {return parent;}
    int getCursorRow() { return cursor->row(); }
    int getCursorCol() { return cursor->column(); }
    int getDiff() {return difference;}
    int getDepth() {return depth;}
    int getNumChildren() {return children.size();}
    int ungeneratedChildren() {return available_moves.size(); }
    int getNumAllChildren();
    Node* getFirstChild() {return children.front();}
    Node* getLastChild() {return children.back();}
    Node* getChild(int i) {return children.at(i);}
    Position* getNextMove() { return available_moves.back(); };
    Position* getCursorPosition() {return cursor;}
    void setParent(Node* node) {this->parent = node;}

    bool is_max() {return is_max_player;}
    bool isLeaf();

    void setMoveToUnavailable(Position *move_pos);
    void setMoveToUnavailable(int row, int col);

    void addChild(Node *child);
    Node* removeChild(int row, int col);
    Node* removeChild(Position *child_cursor);
};


