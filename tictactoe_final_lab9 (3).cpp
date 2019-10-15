//TIC-TAC-TOE [game]
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;
 typedef string* StrPtr; // creating a typedef for string*
void displayBoard(StrPtr b[SIZE]); // changed string*to StrPtr for all methods
bool userFirst();
bool currentPlayerWon(StrPtr b[SIZE], string symbol);
void generateComputerMove (StrPtr board[SIZE], int &row, int &col);
int main() {
	//construct board
	StrPtr * board = new StrPtr[SIZE]; // creating an array of pointers
	for (int x =  0; x < SIZE; x++){ // creating a rows for the 2d array
		board[x] = new string [SIZE];
	}
	for (int x = 0; x < SIZE; x++){ // nested for loop to set 2d indexies to ""
		for(int y = 0; y< SIZE; y++){
					board[x][y] = "";
		}
	}
	int position_id = 1;
	for (int i=0; i< SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			board[i][j] = to_string(position_id);
			/*  stringstream ss;
			   ss << position_id;
			   board[i][j] = ss.str();
			 */position_id++;
		}
	}
	//Initial game output
	cout << "Welcome to Tic-Tac-Toe" << endl;
	bool userTurn = userFirst();
	if (userTurn == true) {
		cout << "Player goes first!\n" << endl;
	} else {
		cout << "Computer goes first!\n" << endl;
	}
	//Loop for turn taking in game
	int positionsRemaining = SIZE * SIZE;
	bool userWon = false;
	bool computerWon = false;

	while ((positionsRemaining > 0)  && (!userWon) && (!computerWon)) {
		displayBoard(board);
		//User's turn
		if (userTurn) {
			bool validMove = false;
			while (!validMove) {
				int position_id;
				cout << "Enter a position: ";
				cin >> position_id;
				if ((position_id <= (SIZE*SIZE)) && (position_id > 0)) {
					int row = (position_id-1)/SIZE;
					int col = (position_id-1)%SIZE;
					//cout << "row = " << row << " col = " << col << endl;
					if ((board[row][col] != "X") && (board[row][col] != "O")) {
						board[row][col] = "X";
						validMove = true;
					} else {
						cout << "Position already used. Try again." << endl;
					}
				} else {
					cout << "Position invalid. Try again." << endl;
				}
			}
			positionsRemaining--;
			userWon = currentPlayerWon(board, "X");
			userTurn = false;
		}
		//Computer's turn
		else {
			int row,col;
			generateComputerMove(board,row,col);// added function
			board[row][col] = "O";// boards move
			positionsRemaining--;
			computerWon = currentPlayerWon(board, "O");
			userTurn = true;
		}
	}
	//Display game result
	 displayBoard(board);
	if (userWon) {
		cout << "Congratulations! You have won!" << endl;
	} else if (computerWon) {
		cout << "The computer has won. Try again." << endl;
	} else {
		cout << "Out of moves. Try again." << endl;
	}
	for(int x = 0; x < SIZE; x++){
		delete [] board[x]; // deleting rows in 2d array
	}
	delete [] board; //deleting rest of array in 2d array
	return 0;
}

void displayBoard(StrPtr b[SIZE]) {
	cout << "Tic-tac-toe board:" << endl << endl;
	for (int i=0; i< SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			cout << b[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

bool userFirst() {
	//set seed for random number generation
	srand(time(NULL));
	//generate a random number
	//0 for computer
	//1 for user
	int num = rand()%2;
	if (num == 0) {
		return false;
	}
	return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(StrPtr b[SIZE], string symbol) {
	//Horizontal case
	//Loop through each row
	for (int i=0; i < SIZE; i++) {
		bool rowWinDetected = true;
		//Check all positions in row and see if they are the same symbol
		for (int j = 0; j < SIZE; j++) {
			if (b[i][j] != symbol) {
				rowWinDetected = false;
			}
		}
		if (rowWinDetected) {
			return true;
		}
	}

	//Vertical case
	//Loop through each column
	for (int i=0; i < SIZE; i++) {
		bool colWinDetected = true;
		//Check all positions in column and see if they are the same symbol
		for (int j = 0; j < SIZE; j++) {
			if (b[j][i] != symbol) {
				colWinDetected = false;
			}
		}
		if (colWinDetected) {
			return true;
		}
	}

	//Diagonal case #1
	bool diagonal1WinDetected = true;
	for (int i=0; i < SIZE; i++) {
		if (b[i][i] != symbol) {
			diagonal1WinDetected = false;
		}
	}
	if (diagonal1WinDetected) {
		return true;
	}

	//Diagonal case #2
	bool diagonal2WinDetected = true;
	for (int i=0; i < SIZE; i++) {
		if (b[(SIZE-1)-i][i] != symbol) {
			diagonal2WinDetected = false;
		}
	}
	if (diagonal2WinDetected) {
		return true;
	}

	//otherwise win not diagonal2WinDetected
	return false;

}

void generateComputerMove(StrPtr board[SIZE], int &row, int&col){ // function called generatecomputer move to play strategicaly
	// Frede Emnetu 100704524
	col = 0; // resetting value of row and col
	row = 0;
	int player1 = 0; // this variable checks to see how many x's are on the board
	int computer = 0; // checks how many O's there are
	int row_index; // this varibale is used as a replacement for the row index
	int col_index; // this varibale is used as a replacement for the col index
	int options;  // used to hold either a 0 or 1 to make a random move if cant win or block
	bool tf; // same thing as options
	for(int r = 0; r < SIZE;  r++){ /// for loop to see how many x's and O's to see who went first and if computer needs to block
		for(int c = 0; c < SIZE; c++){
			if(board[r][c] == "X" ){
				player1++; // increments by 1 each time it finds an x
			}else if (board[r][c] == "O"){
				computer++; // increments by 1 each time it finds an o
			}
		}
	}
	if(player1 == 1 && computer == 0){ // if theres one x and no O's than computer can go anywhere
		while(true){ // while loop to find an index which doesnt contain a x
		row_index = rand()%3;
		col_index = rand()%3;
		if(board[row_index][col_index] != "X"){ // check to see if board index contains an x
			row = row_index; // setting board indexs
			col = col_index;
			return; // return statement
			}
		}
	}else if (player1 == 1 && computer == 1){ // if computer == 1 and player == 1 than computer went first and must now look for
		for(int r = 0; r < SIZE; r++){          // an optimium move
			for(int c = 0; c < SIZE; c++){ // for loop to go through different case in which the computer went first
				if(board[r][c] == "O"){
					if((r == 0 && c == 0) || (r == 0 && c == 2)){ // check to see if O is in the top corners and assigns a row and column
						if(board[1][1] == "5"){ // if middle box is empty take it()
							row = 1; // setting row and col
							col = 1;
							return;
						}else if (c == 2 && board[2][0] == "7"){ // if o is in top right take the bottom left spot to make a diagonal
							row = 2;
							col = 0;
							return;
						}else if(c == 0 && board[2][2] == "9"){ // if o is in top left spot take bottom right spot to make a diagonal
						row = 2;
						col = 2;
						return;
						}else // otherwise take the side edge or top middle edge
						options = rand()%2;
						if(options == 0){
							row = r + 1;
							col = c;
							return;
						}else
							row = 0;
							col = c + 1;
							return;
						}else if (( r == 2 && ( c == 0 || c == 2))){ // check to see if o is in bottom corners of the board
							if(board[1][1] == "5"){ /// if middle spot is open take it
								row = 1;
								col = 1;
								return;
						}else  if (c == 2 && board[0][0] == "1"){ // if o is in bottom right take top left
							row = 0;
							col = 0;
							return;
						}else if(c == 0 && board[0][2] == "3"){ // if o is in bottom left take top right
							row = 0;
							col = 2;
							return;
				 	}else // other wise either go up on or take an edge
					 options = rand()%2;
					 if(options == 0){
						 row = r + 1; // go up one
						 col = c;
						 return;
					 	}else
						 row = 0;
						 col = c + 1; // take an edge
						 return;
					 	}else if (  r == 1 && c == 1){// checks to see if o is in the middle in which case an spot is a good choice
						 for(int x = 0; x < 9; x++){
							 row_index = rand()%3;
							 col_index = rand()%3;
							 if (board[row_index][col_index] != "X" || board[row_index][col_index] != "O"){ // making sure spot isnt taken
								 row = row_index;
								 col = col_index;
								 return;
							  }
						  }
					 	}else if (r == 1 && (c == 0 || c == 2)){ // checks to see if o is in the middle side edges
						 options = rand()%2;
						 if(board[1][1] == "5"){ /// if center is free take it
 							row = 1;
 							col = 1;
 							return;
 					  }else if(options == 0){
						 tf = rand()%2;
						 if(tf == 0){ // other wise go to a bottom corner  or top corner
							row = r  - 1;
							col = c;
							return;
							}else if (tf == 1){
								row =  r + 1;
								col = c;
								return;
							}
						}
					}else if(c == 1 && (r == 0 || r == 2)){ // checks to see if o is in bottom center or top center
						if(board[1][1] == "5"){ // if center free take it
 							row = 1;
 							col = 1;
 							return;
						}else if(r == 0 && board[2][1] == "8"){ // if in top middle take bottom middle and vice versa for bottom middle
							 row = 2;
							 col = 1;
							 return;
					 	}else if (r == 2 && board[0][1] == "2" ){
							 row = 0;
							 col = 1;
							 return;
					 	}else // other wise make a move one colum left or right
						 	options = rand()%2;
 					    if(options == 0){
						 		tf = rand()%2;
					 			if(tf == 0){
									row = r;
									col = c - 1;
									return;
								}else if (tf == 1){
									row =  r;
									col = c + 1;
									return;
							 }
						 }
					 }
					}
				}
			}
		}else if((player1 == 2 && computer == 1)){ // if thers two x's on the board computer must check to block
		// row block
			for(int r = 0; r < 3; r++){
				if(board[r][0] == "X" && board[r][1] == "X"){ // if first row contains two x's together block
					row = r;
					col = 2;
					return;
				}else if (board[r][0] == "X" && board[r][2] == "X"){ // if x's are apart by one
					row = r;
					col = 1;
					return;
				}else if(board[r][1] == "X" && board[r][2] == "X"){ // if two x's are together but on the opposite side of case 1
					row = r;
					col = 0;
					return;
				}
			}
			// column block
			for (int c = 0; c < 3; c++){ // loop through colums to block
				if(board[0][c] == "X" && board[1][c] == "X"){ // if x's are vertically aligned together block
					row = 2;
					col = c;
					return;
				}else if (board[1][c] == "X" && board[2][c] == "X"){ // if x's are vertically aligned but seperated by a box
					row = 0;
					col = c;
					return;
				}else if(board[0][c] == "X" && board[2][c] == "X"){
					row = 1;
					col = c;
					return;
				}
			}

			// diagonal test 1 from top left to bottom right
			if (board[0][0] == "X" && board[1][1]  == "X" ){ // two o's together diagonally
				row = 2;
				col = 2;
				return;
			}else if ( board[0][0] == "X" && board[2][2] == "X"){ // two o's together seperated by one box diagonally
				row = 1;
				col = 1;
				return;
			}else if (board[1][1] == "X" && board[2][2] == "X"){
				row = 0;
				col = 0;
				return;
			}
			//diagonal test 2 for top right to bottom left
			if (board[0][2] == "X" && board[1][1] == "X" ){ // same as lines 347 - 358 but from top right to bottom left
				row = 2;
				col = 0;
				return;
			}else if ( board[0][2] == "X" && board[2][0] == "X"){
				row = 1;
				col = 1;
				return;
			}else if (board[2][0] == "X" && board[1][1] == "X"){
				row = 0;
				col = 2;
				return;
			}
			// if computer does not need to make a block make a random move
			for(int x = 0; x < 9; x++){
				row_index = rand()%3;
				col_index = rand()%3;
				if(board[row_index][col_index] != "X" && board[row_index][col_index] != "O"){
					row = row_index;
					col = col_index;
					return;
				}

			}
		}else	if (player1 >=2 && computer >= 2){ // if there are more than or equal to  two x's and o's
			/// the computer looks for a move to win
			// row win test
			for(int r = 0; r < 3; r++){
				if(board[r][0] == "O" && board[r][1] == "O" && board[r][2] != "X"){ // looks for two o's in a row to win and makes sure an x isnt there
					row = r;
					col = 2;
					return;
				}else if (board[r][0] == "O" && board[r][2] == "O" && board[r][1] != "X"){ // two o's in a row seperated by a box
					row = r;
					col = 1;
					return;
				}else if(board[r][1] == "O" && board[r][2] == "O" && board[r][0] != "X"){
					row = r;
					col = 0;
					return;
				}
			}
			// column win tests
			for (int c = 0; c < 3; c++){ // looks for a colum win
				if(board[0][c] == "O" && board[1][c] == "O" && board[2][c] != "X"){ // checks for two o's vertically aligned together
					row = 2;
					col = c;
					return;
				}else if (board[1][c] == "O" && board[2][c] == "O" && board[0][c] != "X"){ // looks for two o's vertically together aligned on the oppositeside of case 1
					row = 0;
					col = c;
					return;
				}else if(board[0][c] == "O" && board[2][c] == "O" && board[1][c] != "X"){ // two o's speratd by one box
					row = 1;
					col = c;
					return;
				}
			}
			// diagonal win test 1 from top left to bottom right
			if (board[0][0] == "O" && board[1][1]  == "O" && board[2][2] != "X"){ // looks for a diagonal win from top left two bottom right with two o's together
				row = 2;
				col = 2;
				return;
			}else if ( board[0][0] == "O" && board[2][2] == "O" && board [1][1] != "X"){ // tow o's diagonal seperated by one box
				row = 1;
				col = 1;
				return;
			}else if (board[1][1] == "O" && board[2][2] == "O" && board[0][0] != "X"){
				row = 0;
				col = 0;
				return;
			}
			//diagonal win test 2 for top right to bottom left
			if (board[0][2] == "O" && board[1][1] == "O" && board[2][0] != "X"){ // lines 439 - 452 do the same thing as lines 424 to 436 but from top right to bottom left
				row = 2;
				col = 0;
				return;
			}else if ( board[0][2] == "O" && board[2][0] == "O" && board[1][1] != "X"){
				row = 1;
				col = 1;
				return;
			}else if (board[2][0] == "O" && board[1][1] == "O" && board[0][2] != "X"){
				row = 0;
				col = 2;
				return;
			}
			// blocks
			// row blocks
			for(int r = 0; r < 3; r++){ // looks for a row block if cant win lines same as top row blocks
				if(board[r][0] == "X" && board[r][1] == "X" && board[r][2] != "O"){
					row = r;
					col = 2;
					return;
				}else if (board[r][0] == "X" && board[r][2] == "X" && board[r][1] != "O"){
					row = r;
					col = 1;
					return;
				}else if(board[r][1] == "X" && board[r][2] == "X" && board[r][0] != "O"){
					row = r;
					col = 0;
					return;
				}
			}
			// column block
			for (int c = 0; c < 3; c++){ // looks for colum block same as colum blocs on top
				if(board[0][c] == "X" && board[1][c] == "X" && board[2][c] != "O"){
					row = 2;
					col = c;
					return;
				}else if (board[1][c] == "X" && board[2][c] == "X" && board[0][c] != "O"){
					row = 0;
					col = c;
					return;
				}else if(board[0][c] == "X" && board[2][c] == "X" && board[1][c] != "O"){
					row = 1;
					col = c;
					return;
				}
			}
			// diagonal block test 1 from top left to bottom right
			if (board[0][0] == "X" && board[1][1]  == "X" && board[2][2] != "O"){
				row = 2;
				col = 2;
				return;
			}else if ( board[0][0] == "X" && board[2][2] == "X" && board[1][1] != "O"){
				row = 1;
				col = 1;
				return;
			}else if (board[1][1] == "X" && board[2][2] == "X" && board[0][0] != "O"){
				row = 0;
				col = 0;
				return;
			}
			//diagonal block test 2 for top right to bottom left
			if (board[0][2] == "X" && board[1][1] == "X" && board[2][0] != "O" ){
				row = 2;
				col = 0;
				return;
			}else if ( board[0][2] == "X" && board[2][0] == "X" && board[1][1] != "O"){
				row = 1;
				col = 1;
				return;
			}else if (board[2][0] == "X" && board[1][1] == "X" && board[0][2] != "O"){
				row = 0;
				col = 2;
				return;
			}
			for(int r = 0; r < 3; r++){ // if the computer cant block and cant win it makes a random move
				for(int c = 0; c < 3; c++){
					if(board[r][c] != "X" && board[r][c] != "O"){
						row = r;
						col = c;
						return;
					}
				}
			}
		}
	}
