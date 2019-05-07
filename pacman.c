#include <iostream>
#include <Windows.h>
using namespace std;

struct Player 
{
	int x, y;
	Player()
	{
		x = -1;
		y = -1;
	}
};

struct Ghost
{
	int x, y, direction;
	Ghost()
	{
		x = -1;
		y = -1;
		direction = 1;
	}
};

const char SYMBOL_EMPTY = ' ';
const char SYMBOL_PLAYER = '@';
const char SYMBOL_GHOST = 'G';
const char SYMBOL_WALL = '#';
const int MapDx = 10;
const int MapDy = 20;
const int GameSpeed = 100;
const int LEFT = 1;
const int RIGHT = 2;
const int UP = 3;
const int DOWN = 4;
int direction = RIGHT;

char map[10][20] = 
{
	"###################",
	"#                 #",
	"#                 #",
	"#                 #",
	"#                 #",
	"#                 #",
	"#                 #",
	"#                 #",
	"###################"
};

bool isValidPos(int x, int y) 
{ 
	return (x >= 0 && x < MapDx && y >= 0 && y < MapDy);
}

bool movePlayer(Player &player, int x, int y)
{
	if (!isValidPos(x, y)) 
	{ 
		return false;
	}
	
	char ch = map[x][y];
	
	if(ch != SYMBOL_EMPTY) 
	{
		return false;
	}
	
	if (isValidPos(player.x, player.y)) 
	{ 
		map[player.x][player.y] = SYMBOL_EMPTY;
	}
	player.x = x; player.y = y;
	map[player.x][player.y] = SYMBOL_PLAYER;
	return true;
}

bool moveGhost(Ghost &ghost, int x, int y)
{
	if (!isValidPos(x, y))
	{
		return false;
	}

	char ch = map[x][y];

	if (ch != SYMBOL_EMPTY)
	{
		return false;
	}

	if (isValidPos(ghost.x, ghost.y))
	{
		map[ghost.x][ghost.y] = SYMBOL_EMPTY;
	}
	ghost.x = x; ghost.y = y;
	map[ghost.x][ghost.y] = SYMBOL_GHOST;
	return true;
}

void GhostAI(Ghost &ghost, Player &player)
{
	double a = sqrt((pow((double) (ghost.x - 1) - player.x, 2)) + pow((double) ghost.y - player.y, 2)); //UP
	double b = sqrt((pow((double) (ghost.x + 1) - player.x, 2)) + pow((double) ghost.y - player.y, 2)); //DOWN
	double c = sqrt((pow((double) (ghost.y - 1) - player.x, 2)) + pow((double) ghost.x - player.y, 2)); //RIGHT
	double d = sqrt((pow((double) (ghost.y + 1) - player.x, 2)) + pow((double) ghost.x - player.y, 2)); //LEFT
	if(a < b && a <= c && a <= d && ghost.direction != DOWN) ghost.direction = UP;
	else if(b <= c && b <= d && ghost.direction != UP) ghost.direction = DOWN;
	else if(c < d && ghost.direction != LEFT) ghost.direction = RIGHT;
	else if(ghost.direction != RIGHT) ghost.direction = LEFT;
}

void showMap() 
{
	for (int x = 0; x < MapDx; x++) 
	{
		cout << map[x] << endl;
	}
}

void showPlayer(Player &player)
{
	cout << "\nPlayerX: " << player.x << endl;
	cout << "PlayerY: " << player.y << endl;
}

void gameLoop() 
{
	Player player;
	Ghost ghosts[3];
	movePlayer(player, 1, 2);
	moveGhost(ghosts[0], 5, 2);
	moveGhost(ghosts[1], 5, 5);
	moveGhost(ghosts[2], 5, 8);
	while (true) 
	{
		system("cls");
		showMap();
		showPlayer(player);
		if (GetAsyncKeyState(VK_UP)) 
		{
			direction = UP;
		} 
		else if (GetAsyncKeyState(VK_DOWN)) 
		{
			direction = DOWN;
		} 
		else if (GetAsyncKeyState(VK_LEFT)) 
		{
			direction = LEFT;
		} 
		else if (GetAsyncKeyState(VK_RIGHT)) 
		{
			direction = RIGHT;
		}
		switch (direction)
		{
		case UP:
			movePlayer(player, player.x-1, player.y);
			break;
		case DOWN:
			movePlayer(player, player.x+1, player.y);
			break;
		case LEFT:
			movePlayer(player, player.x, player.y-1);
			break;
		case RIGHT:
			movePlayer(player, player.x, player.y+1);
			break;
		}
		for (int ghost = 0; ghost < 3; ghost++)
		{
			GhostAI(ghosts[ghost], player);
			switch (ghosts[ghost].direction)
			{
			case UP:
				moveGhost(ghosts[ghost], ghosts[ghost].x-1, ghosts[ghost].y);
				break;
			case DOWN:
				moveGhost(ghosts[ghost], ghosts[ghost].x+1, ghosts[ghost].y);
				break;
			case LEFT:
				moveGhost(ghosts[ghost], ghosts[ghost].x, ghosts[ghost].y-1);
				break;
			case RIGHT:
				moveGhost(ghosts[ghost], ghosts[ghost].x, ghosts[ghost].y+1);
				break;
			}
		}
		Sleep(GameSpeed);
	}
}


int main() 
{
	gameLoop();
	return 0;
}

