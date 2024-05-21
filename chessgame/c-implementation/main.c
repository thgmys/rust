#include <stdio.h>
#include <string.h>

// Define constants for the dimensions of the chessboard
#define BOARD_SIZE 8

// Define enums for the pieces and colors
typedef enum
{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} Piece;

typedef enum
{
    NO_COLOR,
    WHITE,
    BLACK
} Color;

// Define a struct to represent a square on the chessboard
typedef struct
{
    Piece piece;
    Color color;
} Square;

// Define the chessboard as a 2D array of squares
Square board[BOARD_SIZE][BOARD_SIZE];

// Function to initialize the chessboard from a FEN string
void initialize_board_from_fen(const char *fen)
{
    // Initialize all squares to be empty
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            board[row][col].piece = EMPTY;
            board[row][col].color = NO_COLOR;
        }
    }

    int row = 0, col = 0;
    while (*fen && row < BOARD_SIZE)
    {
        if (*fen == '/')
        {
            row++;
            col = 0;
        }
        else if (*fen >= '1' && *fen <= '8')
        {
            col += *fen - '0';
        }
        else
        {
            Color color = (*fen >= 'a' && *fen <= 'z') ? BLACK : WHITE;
            Piece piece;
            switch (*fen)
            {
            case 'p':
            case 'P':
                piece = PAWN;
                break;
            case 'n':
            case 'N':
                piece = KNIGHT;
                break;
            case 'b':
            case 'B':
                piece = BISHOP;
                break;
            case 'r':
            case 'R':
                piece = ROOK;
                break;
            case 'q':
            case 'Q':
                piece = QUEEN;
                break;
            case 'k':
            case 'K':
                piece = KING;
                break;
            default:
                piece = EMPTY;
            }
            board[row][col].piece = piece;
            board[row][col].color = color;
            col++;
        }
        fen++;
    }
}

// Function to print the chessboard
void print_board()
{
    printf("  a b c d e f g h\n");
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        printf("%d ", BOARD_SIZE - row); // Print row numbers
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            char c;
            switch (board[row][col].piece)
            {
            case EMPTY:
                c = '.';
                break;
            case PAWN:
                c = 'P';
                break;
            case KNIGHT:
                c = 'N';
                break;
            case BISHOP:
                c = 'B';
                break;
            case ROOK:
                c = 'R';
                break;
            case QUEEN:
                c = 'Q';
                break;
            case KING:
                c = 'K';
                break;
            }
            if (board[row][col].color == BLACK)
            {
                c += 'a' - 'A'; // Convert to lowercase for black pieces
            }
            printf("%c ", c);
        }
        printf("%d\n", BOARD_SIZE - row); // Print row numbers
    }
    printf("  a b c d e f g h\n");
}

int main()
{
    const char *fen = "8/8/8/4p1K1/2k1P3/8/8/8";
    initialize_board_from_fen(fen);
    print_board();
    return 0;
}
