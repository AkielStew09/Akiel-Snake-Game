//Snake game project
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <thread>
#include <chrono>
bool gameOver;

const int mapWidth = 25;
const int mapHeight = 25; // internal space is 25x25

//positions and score
int snakePosX, snakePosY, 
fruitPosX, fruitPosY, score, 

tailPosX[50], tailPosY[50], tailSize; //tail info

void drawTail(int i, int j, bool& print) {
	for (int k = 0; k < tailSize; k++) {
		if (tailPosX[k] == j && tailPosY[k] == i) {
			std::cout << "o";
			print = true;
		}
	}
}

enum Edirection { STILL = 0, UP, DOWN, LEFT, RIGHT };
Edirection snakeDir;

void Setup() {
	
	gameOver = false;
	snakeDir = STILL;
	snakePosX = mapWidth/2+1;
	snakePosY = mapHeight/2+1;

	srand(time(0));
	fruitPosX = rand() % mapWidth +1;
	fruitPosY = rand() % mapHeight +1;
	tailSize = 0;
	score = 0;
}
void Draw() {
	system("cls");
	//add +2 when drawing the borders so the mapWidth and mapHeight variables 
	//can actually represent the inside map dimensions, not the dimensions including the border.


	for (int i = 0; i < mapHeight + 2; i++) {//i goes down (y-axis). j goes across (x-axis).
		
		   
		//for when 'i' is ceiling OR floor.
		if (i == 0 || i == mapHeight + 1)  
		{
		for (int j = 0; j < mapWidth + 2; j++) //all #'s for j. this creates the ceiling and floor
			std::cout << "#";

		std::cout << std::endl; //row separator
		}
		
		

		// if 'i' is between ceiling and floor, just '#' at the left end and right end (walls).
		else {
		
		for (int j = 0; j < mapWidth + 2; j++) {//tests if j is at left end OR right end. then prints #
			if (j == 0 || j == mapWidth + 1) 
			std::cout << "#";


			else { // inside the internal space of the map. 
					
				if (i == snakePosY && j == snakePosX) //print snake head
					std::cout << "O";

				else if (i == fruitPosY && j == fruitPosX) {//print fruit (X-shaped fruit)

					std::cout << "&";
				}
				else {
					bool print = false;
					drawTail(i, j, print);
					if(!print)
						std::cout << " "; //if there's no tail then print space
				}	
			}

		}
			std::cout << std::endl; //row separator
			
		}
		
	}	
	std::cout << "Score: " << score;
}
void Input() {

	if (_kbhit()) {
		switch (_getch())
		{
		case 'w':
			snakeDir = UP;
			break;
		case 's':
			snakeDir = DOWN;
			break;
		case 'a':
			snakeDir = LEFT;
			break;
		case 'd':
			snakeDir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}
void Logic() {
	//tail logic
	for (int i = tailSize; i > 0; --i) {
		tailPosX[i] = tailPosX[i - 1];
		tailPosY[i] = tailPosY[i - 1];
	}
	tailPosX[0] = snakePosX;
	tailPosY[0] = snakePosY;
	
	
	//Movement based on the snake direction snakeDir
	switch (snakeDir)
	{
	case UP:
		--snakePosY;
		break;
	case DOWN:
		++snakePosY;
		break;
	case LEFT:
		--snakePosX;
		break;
	case RIGHT:
		++snakePosX;
		break;
	default:
		break;
	}

	//hitting the wall
	if (snakePosY > mapHeight || snakePosY < 1 || snakePosX > mapWidth || snakePosX < 1)
		gameOver = true;
	//hitting own tail
	for (int i = 0; i < tailSize; i++) {
		if (tailPosX[i] == snakePosX && tailPosY[i] == snakePosY)
			gameOver = true;
	}


	//eating the fruit
	if (snakePosY == fruitPosY && snakePosX == fruitPosX){
		score += 100;
		tailSize++;
		fruitPosX = rand() % mapWidth +1;
		fruitPosY = rand() % mapHeight +1;
	}
	

}

int main() 
{
	char keepPlaying;
	do {
	Setup();



	while (!gameOver) {
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		// pause for tenth of a second
		
		Draw();
		Input();
		Logic();
	}

	std::cout << " Enter 'y' to continue. (anything else to quit): "; 
	std::cin >> keepPlaying;
	} while (keepPlaying == 'y');
	
	Draw();
	
	return 0;
}
