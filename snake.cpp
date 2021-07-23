#include <iostream>
#include<conio.h>
#include<Windows.h>

bool GameOver{ false };
const int width = 20;
const int height = 20;
int SnakeX, SnakeY, FruitX, FruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection
{Stop=0,Left , Right , Up , Down };
eDirection dir;



//Setup function 
void Setup()
{
	GameOver = false;
	dir = Stop;
	SnakeX = height / 2;
	SnakeY = width / 2;
	FruitX = rand() % height;
	FruitY = rand() % width;
	score = 0;

}

//Draw function 
void Draw()
{
	system("cls");
	//The upper wall
	for (int i = 0; i < width+2; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)//Displayig the left wall
				std::cout << "#";
			if (i == SnakeX && j == SnakeY)
				std::cout << "O";//the snake head
			else if (i == FruitX && j == FruitY)
				std::cout << "*";//diaplaying the fruit 
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j)
					{
						std::cout << "o";//printing the tail 
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}
				
			if (j == width-1)//displaying the right wall 
				std::cout << "#";
		}
		std::cout << std::endl;
		 

	}
	
	//The bottom  wall
	for (int i = 0; i < height+2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score: "<<score << std::endl;

}

//Input function 
void Input()
{
	if (_kbhit())//_kbhit: c method to check if the keyboard was hit or not
	{
		switch (_getch())
		{
		case 'a':
		case 'A':
			dir = Left;
			break;
		case 'd':
		case 'D':
			dir = Right;
			break;
		case 'w':
		case 'W':
			dir = Up;
			break;
		case 's':
		case 'S':
			dir = Down;
			break;
		case 'x':
		case'X':
			GameOver = true;
			break;
		}

				
				

	}
}

//Logic function 
void Logic()
{	 
	//growing the tail
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X,  prev2Y;
	tailX[0] = SnakeX;
	tailY[0] = SnakeY;


	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//taking the input 
	switch (dir)
	{
	case Left:
		SnakeY--;//moving the snake left
		break;

	case Right:
		SnakeY++;//moving the snake right
		break;
	case Up:
		SnakeX--;//moving the snake up
		break;
	case Down:
		SnakeX++;//moving the snake down 
		break;
	default:
		break;
	}
	if (SnakeX > height || SnakeX<0 || SnakeY>width || SnakeY < 0)
		GameOver = true;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == SnakeX && tailY[i] == SnakeY)
			GameOver = true;
	}
	if (SnakeX ==FruitX && SnakeY == FruitY)
	{
		score += 1;
		FruitX = rand() % height;
		FruitY = rand() % width;
		nTail++;

	}
}

//Main
int main()
{
	Setup();
	while (GameOver != true)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	std::cin.get();
}