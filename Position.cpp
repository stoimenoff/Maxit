#include"Position.h"
Position::Position()
{
    row_ = -1;
    col_ = -1;
}
Position::Position(int r, int c)
{
    row_ = r;
    col_ = c;
}
Position::~Position() {}
void Position::reset()
{
    row_ = -1;
    col_ = -1;
}
void Position::setTo(Position *pos)
{
    row_ = pos->row();
    col_ = pos->column();
}
bool Position::operator == (const Position& other) {
    if(this->row_ != other.row_)
    {
        return false;
    }
    if(this->col_ != other.col_)
    {
        return false;
    }
    return true;
}
