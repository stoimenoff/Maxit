class Position
{
private:
    int row_;
    int col_;
public:
    Position();
    Position(int r, int c);

    int column() {return col_;}
    int row() {return row_;}

    void reset();
    void setTo(Position *pos);

    bool operator==(const Position& other);
};
