#include <iostream>
#include <string>
#include <cctype>

//---------------------------------Board class definition and implementation
class Board{
    private:
        char board[3][3];
    public:
        Board();
        void fillBoard(int cell, char symbol);
        bool checkForWinner(char sym);
        void printBoard();
};

Board::Board(){
    for(size_t i=0; i<3; i++){
        for(size_t j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

// Function to fill the board with the player's symbol based on the cell number they choose
void Board:: fillBoard(int cell, char symbol){
    // Map the cell number to the corresponding row and column 
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    board[row][col] = symbol;
}

// Function to print the current state of the board
void Board::printBoard(){
    for(size_t i=0; i<3; i++){
        for(size_t j=0; j<3; j++){
            std::cout << board[i][j];
            if(j < 2){
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if(i < 2){
            std::cout << "---------\n";
        }
    }
}

// Function to check if the current player has won by checking all possible winning combinations (rows, columns, diagonals)
bool Board:: checkForWinner(char sym){
    //check rows
    for(size_t i=0; i<3; i++){
        if(board[i][0] == sym && board[i][1] == sym && board[i][2] == sym){
            return true;
        }
    }
    //check for columns
    for(size_t i=0; i<3; i++){
        if(board[0][i] == sym && board[1][i] == sym && board[2][i] == sym){
            return true;
        }
    }
    //check for diagonals
    if(board[0][0] == sym && board[1][1] == sym && board[2][2] == sym){
        return true;
    } else if(board[0][2] == sym && board[1][1] == sym && board[2][0] == sym){
        return true;
    }
    return false;
}

//-------------------------Player class definition and implementation
class Player{
    private:
        std::string name;
        char symbol;
    public:
        Player(std::string name, char symbol);
        std::string getName();
        char getSymbol();
};

//Player class constructor 
Player::Player(std::string name, char symbol){
    this->name = name;
    this->symbol = symbol;
}
//Getters for player name and symbol
std::string Player::getName(){
    return name;
}
//Getters for player name and symbol
char Player::getSymbol(){
    return symbol;
}

// -------------------------Function to check if a cell has already been used
bool cellChecker(int cell, int used_cells[]){
    for (size_t i=0; i<9; i++){ 
        if (used_cells[i] == cell) {
            return true;
        }
    }
    return false;
}

//----------------------------Game class definition and implementation
class Game{
    protected:
        Board board;
        Player player1;
        Player player2;
    public:
        Game(std::string name1, char symbol1, std::string name2, char symbol2);
        void gamePlay();
};

Game::Game(std::string name1, char symbol1, std::string name2, char symbol2) : player1(name1, symbol1), player2(name2, symbol2)
{
}

// Function to manage the flow of the game, alternating turns between players, updating the board, and checking for a winner or draw after each move
void Game::gamePlay(){
    // Print welcome message and player information and instructions
    std::cout << "Welcome to Tic Tac Toe!\n" << std::endl;
    std::cout << "Player 1: " << player1.getName() << " (" << player1.getSymbol() << ")" << std::endl;
    std::cout << "Player 2: " << player2.getName() << " (" << player2.getSymbol() << ")" << std::endl;
    
    std::cout << "Here is the board layout:\n" << std::endl;
    std::cout << "1 2 3 \n4 5 6 \n7 8 9 \n" << std::endl;
    std::cout << "Player 1 goes first. Please enter the number corresponding to the cell where you want to place your symbol.\n" << std::endl;

    // Variable to keep track of the last player and an array to keep track of used cells
    int last_player = 2;
    int used_cells[9] = {0};

    // Loop through the maximum number of moves (9) and alternate between players
    for(size_t i=0; i<9; i++){
        int cell;
        char sym;      

        // Determine which player's turn it is and get the cell input
        if (last_player == 2){
            sym = player1.getSymbol();
            std::cout << player1.getName() << " enter your cell number: ";
            std::cin >> cell;
            while (cell < 1 || cell > 9 || cellChecker(cell, used_cells)){
                std::cout << "Invalid input. Please enter a number between 1 and 9 that has not been used: ";
                std::cin >> cell;
            };
            
        } else {
            sym = player2.getSymbol();
            std::cout << player2.getName() << " enter your cell number: ";
            std::cin >> cell;
            while (cell < 1 || cell > 9 || cellChecker(cell, used_cells)){
                std::cout << "Invalid input. Please enter a number between 1 and 9 that has not been used: ";
                std::cin >> cell;
            };
        }

        // Update the board and used cells
        board.fillBoard(cell, sym);
        used_cells[i] = cell;

        // Print the updated board
        std::cout << "\nCurrent board:\n" << std::endl;
        board.printBoard();

        // Check for a winner after the 5th move (the earliest a player can win)
        if(i >=4){
            if(board.checkForWinner(sym)){
                std::cout << "Congratulations " << (last_player == 2 ? player1.getName() : player2.getName()) << "! You won !!!\n" << std::endl;
                return;
            } else if(i == 8){                
                std::cout << "It's a draw! No winner this time.\n" << std::endl;
                return;
            }  
        }  

        // Switch the last player
        last_player = (last_player == 2 ? 1 : 2);
    }
}

int main(){
    std::string name1, name2;
    char symbol1, symbol2;

    // Get player1 names and symbol
    std::cout << "Player 1, please enter your name: ";
    std::getline(std::cin, name1);

    do{
        std::cout << name1 << ", please choose your symbol (X or O): ";
        std::cin >> symbol1;
        symbol1 = toupper(symbol1);
    } while (symbol1 != 'X' && symbol1 != 'O');

    // Get player2 names and symbol
    std::cin.ignore(); // Clear the input buffer before getting the next line of input
    std::cout << "Player 2, please enter your name: ";    
    std::getline(std::cin, name2);
    symbol2 = (symbol1 == 'X'? 'O' : 'X');
    std::cout << "Your symbol autmatically becomes " << symbol2 << " .\n" << std::endl;

    Game game(name1, symbol1, name2, symbol2);
    game.gamePlay();

    return 0;
}