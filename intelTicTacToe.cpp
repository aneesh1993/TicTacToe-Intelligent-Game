#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Move
{
	int x, y;
	int score;
	char currentPlayerSymbol;
	string currentPlayerName;
}a;

struct IntelAgent
{
	char Symbol = 'K';
	string Name = "THOR";
}intel;

void clearBoard(char board[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = ' ';
}

void printBoard(char board[3][3])
{
	std::cout << endl;
	std::cout << "  | 1 | 2 | 3 |\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "  -------------\n";
		std::cout << " " << i + 1 << "| " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " | \n";
	}
	std::cout << "  -------------\n\n";

}


int getXCoordinate()
{
	int x;
	bool correct = false;

	while (correct == false)
	{
		std::cout << "Please Enter X Coordinate of the location you want to place your Marker : ";
		std::cin >> x;

		if (x > 3 || x < 1)
		{
			std::cout << "Coordinate out of bound" << endl;
			correct = false;
		}
		else
			correct = true;
	}

	return x - 1;

}


int getYCoordinate()
{
	int y;
	bool correct = false;

	while (correct == false)
	{
		std::cout << "Now Enter the Y Coordinate : ";
		std::cin >> y;

		if (y > 3 || y < 1)
		{
			std::cout << "Coordinate out of bound" << endl;
			correct = false;
		}
		else
			correct = true;
	}

	return y - 1;

}


bool checkAndPlace(char board[3][3], int x, int y, char currentPlayer)
{
	if (board[y][x] != ' ')
		return false;

	board[y][x] = currentPlayer;
	return true;

}


bool checkVictory(char board[3][3], char currentPlayer)
{
	for (int i = 0; i < 3; i++)
	{
		if ((currentPlayer == board[i][0]) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
			return true;
	}

	for (int i = 0; i < 3; i++)
	{
		if ((currentPlayer == board[0][i]) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
			return true;
	}

	if ((currentPlayer == board[0][0]) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
		return true;

	if ((currentPlayer == board[0][2]) && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
		return true;

	return false;
}

struct Move bestMove(char board[3][3], char currentPlayer, char player1)
{
	Move newMove;
	//newMove.currentPlayerSymbol = currentPlayer;

	vector<Move> movesVector;

	int count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != ' ')
				count++;
		}
	if (count == 9)
	{
		if (checkVictory(board, currentPlayer))
		{
			if (currentPlayer == intel.Symbol)
			{
				newMove.score = 10;
				return newMove;
			}
			else
			{
				newMove.score = -10;
				return newMove;
			}
		}
		else
		{
			newMove.score = 0;
			return newMove;
		}
	}

	if (checkVictory(board, currentPlayer))
	{
		if (currentPlayer == intel.Symbol)
		{
			newMove.score = 10;
			return newMove;
		}
		else
		{
			newMove.score = -10;
			return newMove;
		}
	}


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[j][i] == ' ')
			{
				newMove.y = i;
				newMove.x = j;
				board[j][i] = currentPlayer;

				if (currentPlayer == intel.Symbol)
					newMove.score = bestMove(board, player1, player1).score;
				else
					newMove.score = bestMove(board, intel.Symbol, player1).score;

				movesVector.push_back(newMove);

				board[j][i] = ' ';
			}
		}
	}


	int bestMoveIndex = 0;
	if (currentPlayer == intel.Symbol)
	{
		int bestScore = -10000000;
		for (int i = 0; i < movesVector.size(); i++)
		{
			if (movesVector[i].score > bestScore)
			{
				bestMoveIndex = i;
				bestScore = movesVector[i].score;
			}
		}
	}
	else
	{
		int bestScore = 10000000;
		for (int i = 0; i < movesVector.size(); i++)
		{
			if (movesVector[i].score < bestScore)
			{
				bestMoveIndex = i;
				bestScore = movesVector[i].score;
			}
		}
	}
	return movesVector[bestMoveIndex];
}


void playGame(char board[3][3])
{
	clearBoard(board);

	char player1;
	char player2;
	player2 = intel.Symbol;

	string player1Name, player2Name;
	player2Name = intel.Name;

	std::cout << "----- Welcome to Tic Tac Toe! -----\n\n";

	std::cout << "What's the Name of Player 1? ";
	std::cin >> player1Name;
	std::cout << endl;

	std::cout << "Hi " << player1Name << "! please enter your symbol (Except K): ";
	std::cin >> player1;
	std::cout << endl;

	std::cout << "My Name is THOR and I a bet you cant defeat me at this game!!\n\n";
	/*std::cout << "What's the Name of Player 2? ";
	std::cin >> player2Name;										// Player2 is AI
	std::cout << endl;

	std::cout << "Hi " << player2Name << "! please enter your symbol: ";
	std::cin >> player2;
	std::cout << endl;*/
	std::cout << "Bring It ON!!! \n" << endl;

	char currentPlayer = player1;

	bool isDone = false;
	int x, y;
	int tieCount = 0;

	while (isDone == false)
	{
		printBoard(board);

		if (currentPlayer == player1)
			std::cout << player1Name;
		else
			std::cout << player2Name;
		std::cout << " to play ...\n";

		if (currentPlayer == player2)
		{
			cout << "Thinking . . . \n\n";

			Move temp;
			temp = bestMove(board, currentPlayer, player1);
			int x1 = temp.x;
			int y1 = temp.y;

			tieCount++;
			if (tieCount != 9)
			{
				board[x1][y1] = player2;
			}

			if (checkVictory(board, currentPlayer))
			{
				printBoard(board);
				if (currentPlayer == player1)
					std::cout << "\n" << player1Name;
				else
					std::cout << "\n" << player2Name;
				std::cout << " has won!" << endl;
				isDone = true;
			}

			currentPlayer = player1;
		}
		else
		{
			x = getXCoordinate();
			y = getYCoordinate();

			if (checkAndPlace(board, x, y, currentPlayer) == false)
			{
				std::cout << "Position already taken by ";
				if (board[x][y] == player1)
					std::cout << player1Name << endl;
				else
					std::cout << player2Name << endl;
			}
			else
			{
				tieCount++;
				//printBoard(board);
				if (checkVictory(board, currentPlayer))
				{
					printBoard(board);
					if (currentPlayer == player1)
						std::cout << "\n" << player1Name;
					else
						std::cout << "\n" << player2Name;
					std::cout << " has won!" << endl;
					isDone = true;
				}
				if (tieCount == 9)
				{
					printBoard(board);
					std::cout << "The Game has Tied!" << endl;
					isDone = true;
				}

				if (currentPlayer == player1)
					currentPlayer = player2;
				else
					currentPlayer = player1;
			}
		}
	}
}




int main()
{
	char playAgain;
	bool isDone = false;
	char board[3][3];

	a.score = 0;

	while (isDone == false)
	{
		playGame(board);
		std::cout << "Do you want to continue? (Y/N) : ";
		std::cin >> playAgain;

		if (playAgain == 'n' || playAgain == 'N')
		{
			std::cout << "\nGoodbye!" << " Have a nice day..." << endl;
			isDone = true;
		}

		system("CLS");
	}


	system("pause");
	return 0;
}