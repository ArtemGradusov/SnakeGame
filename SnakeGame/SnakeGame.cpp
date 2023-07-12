#include <iostream>
#include <conio.h>
#include <ctime>

#pragma warning(disable:4996)
using namespace std;

class Game
{
public:
	int mapwidth = 20;
	int mapheight = 20;
    int size = mapwidth * mapheight;

	int headxpos;
	int headypos;
	int direction;
	int food = 3;
	int map[400];
	bool running;

	Game()
	{
		memset(map, 0, sizeof(map));
	}

	void start()
	{
		// поле
		generateMap();
		running = true;
		while (running) 
		{
			// если клавиша нажата
			if (kbhit()) 
			{
				// меняем направление в зависимости от клавиши
				changeDirection(getch());
			}
			// обновляем карту
			mapUpdate();

			// очистка поля
			clearScreen();

			// рисуем карту
			printMap();

			// скорость
			_sleep(1500/food);
		}

		// конец игры
		cout << "\t\tИгра окончена !!!" << endl << "\t\tВы набрали: " << food -3 << " очков !";

		// чтоб консоль не закрывалась
		cin.ignore();
	}

	char getMapValue(int value)
	{
		// рисуем тело змеи
		if (value > 0) return 'o';

		switch (value)
		{
			// рисуем стену
		case -1: return '#';
			// рисуем еду
		case -2: return '*';
		}

		return ' ';
	}

	void printMap()
	{
		for (int x = 0; x < mapwidth; ++x) 
		{
			for (int y = 0; y < mapheight; ++y)
			{
				// рисуем поле
				cout << getMapValue(map[x + y * mapwidth]);
			}
			// переход на след. строку для отрисовки
			cout << endl;
		}
	}

	void generateMap()
	{
		// размещение змейки по центру поля
		headxpos = mapwidth / 2;
		headypos = mapheight / 2;
		map[headxpos + headypos * mapwidth] = 1;

		// верхняя и нижняя стены
		for (int x = 0; x < mapwidth; ++x) 
		{
			map[x] = -1;
			map[x + (mapheight - 1) * mapwidth] = -1;
		}

		// левая и правая стены
		for (int y = 0; y < mapheight; y++) 
		{
			map[0 + y * mapwidth] = -1;
			map[(mapwidth - 1) + y * mapwidth] = -1;
		}

		// генерируем "еду"
		generateFood();
	}

	void move(int dx, int dy)
	{
		// новое положение головы змеи
		int newx = headxpos + dx;
		int newy = headypos + dy;

		// проверка, есть ли "еда" на поле
		if (map[newx + newy * mapwidth] == -2) 
		{
			// увеличиваем длину змеи
			food++;

			// генерируем новую "еду"
			generateFood();
		}

		// если поле пустое
		else if (map[newx + newy * mapwidth] != 0) 
		{
			running = false;
		}

		// перемещаем голову змеи на новую позицию
		headxpos = newx;
		headypos = newy;
		map[headxpos + headypos * mapwidth] = food + 1;
	}

	void mapUpdate()
	{
		// направление движения змеи
		switch (direction) 
		{
		case 0: move(-1, 0);
			break;
		case 1: move(0, 1);
			break;
		case 2: move(1, 0);
			break;
		case 3: move(0, -1);
			break;
		}

		// уменьшаем длину змеи на поле для корректного отображения змеи
		for (int i = 0; i < size; i++) 
		{
			if (map[i] > 0) 
				map[i]--;
		}
	}

	void changeDirection(char key)
	{
		/*
	  W
	A + D
	  S
	*/
		switch (key) 
		{
		case 'w':
			if (direction != 2) direction = 0;
			break;
		case 'd':
			if (direction != 3) direction = 1;
			break;
		case 's':
			if (direction != 4) direction = 2;
			break;
		case 'a':
			if (direction != 5) direction = 3;
			break;
		}
	}

	void clearScreen()
	{
		// очистка консоли
		system("cls");
	}

	void generateFood()
	{
		int x = 0;
		int y = 0;
		do 
		{
			// генерируем координаты "еды"
			x = rand() % (mapwidth - 2) + 1;
			y = rand() % (mapheight - 2) + 1;

			// если координаты заняты пробуем еще
		}
		while (map[x + y * mapwidth] != 0);

		// располагаем "еду" в координатах
		map[x + y * mapwidth] = -2;
	}
};

int main()
{
	setlocale(LC_ALL,"Rus");
	srand(time(NULL));

	Game game;
	game.start();

	return 0;
}