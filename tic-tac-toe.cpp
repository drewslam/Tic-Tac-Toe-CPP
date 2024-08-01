#include <iostream>

class Player {
private:
    char id;

public:
    Player(char id) { this->id = id; }
    char getID() const { return id; }
};

class Game {
private:
    char gameBoard[3][3];

public:
    Game() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                gameBoard[i][j] = ' ';
            }
        }
    }

    void displayGameBoard() {
        std::cout << "  A   B   C\n";
        std::cout << "1[" << gameBoard[0][0] << "] [" << gameBoard[0][1] << "] [" << gameBoard[0][2] << "]\n";
        std::cout << "2[" << gameBoard[1][0] << "] [" << gameBoard[1][1] << "] [" << gameBoard[1][2] << "]\n";
        std::cout << "3[" << gameBoard[2][0] << "] [" << gameBoard[2][1] << "] [" << gameBoard[2][2] << "]\n";
    }

    void selectPosition(Player* player, char col, int row) {
        int coli;
        if (col == 'A') {
            coli = 0;
        } else if (col == 'B') {
            coli = 1;
        } else if (col == 'C') {
            coli = 2;
        } else {
            std::cerr << "Invalid input\n";
            return;
        }

        if (gameBoard[row - 1][coli] == ' ') {
            gameBoard[row - 1][coli] = player->getID();
        } else {
            std::cerr << "Invalid input\n";
            return;
        }

        displayGameBoard();
    }

    bool gameWon(Player* player) {
        char id = player->getID();
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (gameBoard[i][0] == id && gameBoard[i][1] == id && gameBoard[i][2] == id) {
                std::cout << "\n" << player->getID() << " Wins!\n";
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (gameBoard[0][i] == id && gameBoard[1][i] == id && gameBoard[2][i] == id) {
                std::cout << "\n" << player->getID() << " Wins!\n";
                return true;
            }
        }

        // Check diagonals
        if (gameBoard[0][0] == id && gameBoard[1][1] == id && gameBoard[2][2] == id) {
            std::cout << "\n" << player->getID() << " Wins!\n";
            return true;
        }
        if (gameBoard[0][2] == id && gameBoard[1][1] == id && gameBoard[2][0] == id) {
            std::cout << "\n" << player->getID() << " Wins!\n";
            return true;
        }

        return false;
    }

    bool isDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gameBoard[i][j] == ' ') {
                    return false;
                }
            }
        }
        std::cout << "The game is a draw!\n";
        return true;
    }
};

int main() {
    char id1, id2;

    std::cout << "Player 1, enter your character ID: ";
    std::cin >> id1;
    do {
        std::cout << "Player 2, enter your unique character ID: ";
        std::cin >> id2;
        if (id2 == id1) {
            std::cerr << "Character ID must be unique.\n";
        }
    } while (id2 == id1);

    Player* player1 = new Player(id1);
    Player* player2 = new Player(id2);
    Player* currentPlayer = player2;
    Game* currentGame = new Game();
    bool gameOver = false;

    currentGame->displayGameBoard();

    std::cout << "Input \"Column Row\" (A 1, B 2, C 3)\n";

    while (!gameOver) {
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }

        std::cout << "\nInput " << currentPlayer->getID() << ": ";
        char col;
        int row;
        std::cin >> col >> row;
        currentGame->selectPosition(currentPlayer, col, row);
        if (currentGame->gameWon(currentPlayer)) {
            gameOver = true;
        } else if (currentGame->isDraw()) {
            gameOver = true;
        }
    }

    delete currentGame;
    delete player1;
    delete player2;

    return 0;
}

