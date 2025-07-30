#include <iostream>
using namespace std;

class Game {
protected:
    int movesCount;
public:
    Game() : movesCount(0) {}
    virtual void displayBoard() = 0;
    virtual bool makeMove(int position, int player) = 0;
    virtual bool checkWin(int player) = 0;
    virtual bool isDraw() = 0;
};

class TicTacToe : public Game {
private:
    int board[3][3];
    char player1Symbol;
    char player2Symbol;
public:
    TicTacToe() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = 0;
            }
        }
        player1Symbol = 'X';
        player2Symbol = 'O';
    }
    void displayBoard() override {
        cout << "\nCurrent Board:\n\n";
        cout << "  11 \t| \t12 \t| \t13\n";
        cout << "--------------------------------\n";
        cout << "  21 \t| \t22 \t| \t23\n";
        cout << "--------------------------------\n";
        cout << "  31 \t| \t32 \t| \t33\n\n";
        cout << "Game Status:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char symbol = ' ';
                if (board[i][j] == 1) symbol = player1Symbol;
                else if (board[i][j] == 2) symbol = player2Symbol;
                cout << "  " << symbol << "  ";
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "-----------------\n";
        }
        cout << "\n";
    }
    bool makeMove(int position, int player) override {
        int row = (position / 10) - 1;
        int col = (position % 10) - 1;
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid coordinates! Use numbers between 11-33.\n";
            return false;
        }
        if (board[row][col] != 0) {
            cout << "Position already taken! Choose another.\n";
            return false;
        }
        board[row][col] = player;
        movesCount++;
        return true;
    }
    bool checkWin(int player) override {
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
        }
        return false;
    }
    bool isDraw() override {
        return movesCount >= 9;
    }
};

int main() {
    TicTacToe game;
    int move;
    int currentPlayer = 1;
    cout << "Welcome to Coordinate Input Tic-Tac-Toe!\n";
    cout << "Player 1 (X) vs Player 2 (O)\n";
    cout << "Enter moves as coordinates (11-33)\n\n";
    cout << "Reference Board:\n";
    cout << "11 | 12 | 13\n";
    cout << "-----------\n";
    cout << "21 | 22 | 23\n";
    cout << "-----------\n";
    cout << "31 | 32 | 33\n\n";
    while (true) {
        game.displayBoard();
        cout << "Player " << currentPlayer << " (" << (currentPlayer == 1 ? 'X' : 'O') << "), enter your move: ";
        cin >> move;
        while (!game.makeMove(move, currentPlayer)) {
            cout << "Try again: ";
            cin >> move;
        }
        if (game.checkWin(currentPlayer)) {
            game.displayBoard();
            cout << "\nPlayer " << currentPlayer << " wins!\n";
            break;
        }
        if (game.isDraw()) {
            game.displayBoard();
            cout << "\nGame ended in a draw!\n";
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    cout << "\nGame over!\n";
    return 0;
}