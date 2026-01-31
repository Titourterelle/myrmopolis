#ifndef __BOARD__
#define __BOARD__

class Board
{
    public:
        Board(const int row, const int column);

    private:
        void setDimensions(const int row, const int column);

        int row;
        int column;
};

#endif