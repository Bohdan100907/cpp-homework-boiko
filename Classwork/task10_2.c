#include <stdio.h>

typedef struct
{
    char file;
    int rank;
} ChessSquare;

int inputChessSquare(ChessSquare *square)
{
    printf("Enter chess square (for example, a5): ");
    if (scanf(" %c%d", &square->file, &square->rank) != 2)
    {
        return 0;
    }

    if (square->file >= 'A' && square->file <= 'H')
    {
        square->file = (char)(square->file - 'A' + 'a');
    }

    return square->file >= 'a' && square->file <= 'h' &&
           square->rank >= 1 && square->rank <= 8;
}

int knightCanMove(const ChessSquare *from, const ChessSquare *to)
{
    int fileDistance = from->file - to->file;
    int rankDistance = from->rank - to->rank;

    if (fileDistance < 0)
    {
        fileDistance = -fileDistance;
    }
    if (rankDistance < 0)
    {
        rankDistance = -rankDistance;
    }

    return (fileDistance == 1 && rankDistance == 2) ||
           (fileDistance == 2 && rankDistance == 1);
}

int main(void)
{
    ChessSquare first;
    ChessSquare second;

    if (!inputChessSquare(&first))
    {
        printf("Invalid first square.\n");
        return 1;
    }

    if (!inputChessSquare(&second))
    {
        printf("Invalid second square.\n");
        return 1;
    }

    if (knightCanMove(&first, &second))
    {
        printf("Yes, a knight can move from %c%d to %c%d.\n",
               first.file, first.rank, second.file, second.rank);
    }
    else
    {
        printf("No, a knight cannot move from %c%d to %c%d.\n",
               first.file, first.rank, second.file, second.rank);
    }

    return 0;
}