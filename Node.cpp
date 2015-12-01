#include"Node.h"
#include<iostream>
const int Node::grid_size = 5;
Node::Node(Node *parent, Position *cur, int diff, bool is_max)
{
    this->parent = parent;
    this->cursor = new Position(cur->row(), cur->column());
    this->is_max_player = is_max;
    this->difference = diff;
    if(parent == nullptr)
    {
        this->depth = 0;
    }
    else
    {
        this->depth = parent->getDepth() + 1;
    }
    for(int i = 0; i < grid_size; i++)
    {
        if(is_max)
        {
            available_moves.push_back(new Position(i, cursor->column()));
        }
        else
        {
            available_moves.push_back(new Position(cursor->row(), i));
        }
    }
    setMoveToUnavailable(cur);
}
Node::~Node()
{
    //delete children
    while(children.size() > 0)
    {
        delete children.back();
        children.pop_back();
    }

    while(available_moves.size() > 0)
    {
        delete available_moves.back();
        available_moves.pop_back();
    }
    children.clear();
    available_moves.clear();
    delete cursor;
}
void Node::addChild(Node *child)
{
    if(*(available_moves.back()) == *(child->getCursorPosition()))
    {
        children.push_back(child);
        child->setParent(this);
        delete available_moves.back();
        available_moves.pop_back();
    }
}
Node* Node::removeChild(int row, int col)
{
    for(std::vector<Node*>::size_type i = 0; i != children.size(); i++)
    {
        if(children[i]->getCursorRow() == row && children[i]->getCursorCol() == col)
        {
            Node* child = children[i];
            children.erase(children.begin() + i);
            return child;
        }
    }
    return nullptr;
}
Node* Node::removeChild(Position *child_cursor) {
    return removeChild(child_cursor->row(), child_cursor->column());
}
bool Node::isLeaf()
{
    if(children.size() == 0 && available_moves.size() == 0)
    {
        return true;
    }
    return false;
}
int Node::getNumAllChildren()
{
    return children.size() + available_moves.size();
}
void Node::setMoveToUnavailable(Position *move_pos)
{
    for(unsigned i = 0; i < available_moves.size(); i++)
    {
        if(*available_moves[i] == *move_pos)
        {
	    delete available_moves[i];
            available_moves.erase(available_moves.begin() + i);
            break;
        }
    }
}
void Node::setMoveToUnavailable(int row, int col)
{
    Position *pos = new Position(row, col);
    setMoveToUnavailable(pos);
    delete pos;
}
