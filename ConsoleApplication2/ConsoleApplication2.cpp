#include <iostream>
#include<conio.h>
#include<Windows.h>
#include<ctime>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup()
{
	srand(time(0));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % (width);
	fruitY = rand() % (height);
	score = 0;

}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 1; i++)
	{
		std::cout << "#";

	}
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				std::cout << "#";
			if (i == y && j == x)
				std::cout << "0";
			else if (i == fruitY && j == fruitX)
				std::cout << "*";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << 'o';

					}
						
				}

				if (!print)
					std::cout << " ";

			}
				

		}
		std::cout << std::endl;

		
	}


	for (int i = 0; i < width + 1; i++)
	{
		std::cout << "#";

	}
	std::cout << std::endl;

	std::cout << "Score = " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[1];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	switch (dir)
	{
	case LEFT:
		x -= 1;
		break;
	case RIGHT:
		x += 1;
		break;
	case UP:
		y -= 1;
		break;
	case DOWN:
		y += 1;
		break;
	}
	if (x > width || x < 0)
		gameOver = true;
	if (y > height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 1;

		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail += 1;

	}

}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(500);
	}


	return 0;
}