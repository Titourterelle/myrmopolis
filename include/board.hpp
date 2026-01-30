#ifndef __BOARD__
#define __BOARD__

class Board
{
    public:
        Board(const int row, const int column) noexcept;

    private:
        int row;
        int column;
};

#endif