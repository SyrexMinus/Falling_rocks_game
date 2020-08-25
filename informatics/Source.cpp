#include <iostream>
#include <math.h>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;

//map settings
const int _size = 20 + 1;
char map[_size+1][_size+1];
//player settings
bool life = true;
int x = 10, y = 19;
long int score = 0;
char key;
//bounty settings
int xbounty, ybounty;
//bomb settings
int xbomb, ybomb,timebomb;
//textures
char TexturePlayer = '&', TextureBounty = '$', TextureBomb = '@', TextureExplosion = '#', TextureField = ' ', TextureBorder = '-';

void SpawnBounty()
{
	xbounty = x;
	ybounty = y;
	while (xbounty == x || xbounty == xbomb)
	{
		xbounty = rand() % (_size-1) + 1;
	}
	while (ybounty == y || ybounty == ybomb)
	{
		ybounty = rand() % (_size - 1) + 1;
	}
	map[xbounty][ybounty] = TextureBounty;
}

void SpawnBomb()
{
	xbomb = x;
	ybomb = y;
	while (xbomb == x || xbomb == xbounty || xbomb<=0 ||xbomb>=_size)
	{
		xbomb = x-4+rand()%9;
	}
	while (ybomb == y || ybomb == ybounty || ybomb <= 0 || ybomb >= _size)
	{
		ybomb = y - 4 + rand() % 9;
	}
	map[xbomb][ybomb] = TextureBomb;
	timebomb = 1;
}

void ExplosionBomb()
{
	for (int i = ybomb - 1; i <= ybomb + 1; i++)
	{
		for (int k = xbomb - 1; k <= xbomb + 1; k++)
		{
			if (map[k][i] == TextureField || map[k][i] == TexturePlayer || map[k][i]==TextureBomb)
			{
				map[k][i] = TextureExplosion;
			}
		}
	}
	if (abs(x - xbomb) <= 1 && abs(y - ybomb) <= 1)
	{
		life = false;
	}
}

void TickBomb()
{
	if (timebomb >= 0) 
	{
		timebomb--;
	}
	if (timebomb == 0)
	{
		ExplosionBomb();
	}
	else if (timebomb == -1)
	{
		for (int i = ybomb - 1; i <= ybomb + 1; i++)
		{
			for (int k = xbomb - 1; k <= xbomb + 1; k++)
			{
				if (map[k][i] == TextureExplosion)
				{
					map[k][i] = TextureField;
				}
			}
		}
		SpawnBomb();
	}
}

void GenerateMap()
{
	//field
	for (int i = 0; i <= _size; i++)
	{
		for (int k = 0; k <= _size; k++)
		{
			if (k != 0 && k != _size && i != 0 && i != _size) {
				map[i][k] = TextureField;
			}
			else {
				map[i][k] = TextureBorder;
			}
		}
	}
	//player
	map[x][y] = TexturePlayer;
	SpawnBounty();
}

void DrawMap()
{
	system("cls");
	cout << "Score: " << score << endl;
	for (int i = 0; i <= _size; i++)
	{
		for (int k = 0; k <= _size; k++)
		{
			cout << map[k][i];
		}
		cout << endl;
	}
	cout << "|----------|----------|" << endl;
	cout << "|  w - up  | a - left |" << endl;
	cout << "|----------|----------|" << endl;
	cout << "| s - down | d - right|" << endl;
	cout << "|----------|----------|" << endl;
	cout << "| p - death|----------|" << endl;
	cout << "|----------|----------|";
}

void Captions()
{
	system("cls");
	cout << "Creator: Shevchenko Makar Ilyich, 2019" << endl;
	cout << "Version: 1.0.0" << endl << endl;
	cout << "|----------|----------|" << endl;
	cout << "| 1 - menu |----------|" << endl;
	cout << "|----------|----------|" << endl;
	key = _getch();
	switch (key)
	{
	case '1':
		break;
	default:
		Captions();
		break;
	}
}

void TopMenu()
{
	system("cls");
	ifstream FileTop;
	ofstream _FileTop;
	FileTop.open("Top.txt");
	char FileName[10];
	int num = 1,FileScore;
	cout << "         Records" << endl<<endl;
	cout << "Position Name       Score" << endl;
	if (!FileTop.is_open())
	{
		_FileTop.open("Top.txt");
		_FileTop.close();
		FileTop.open("Top.txt");
	}
	while (FileTop >> FileName >> FileScore)
	{
		cout.width(8);
		cout << num;
		cout.width(0);
		cout << " ";
		cout.width(10);
		cout << FileName;
		cout.width(0);
		cout << " " << FileScore << endl;
		num++;
	}
	FileTop.close();
	cout << "|----------|----------|" << endl;
	cout << "| 1 - menu |----------|" << endl;
	cout << "|----------|----------|" << endl;
	key = _getch();
	switch (key)
	{
	case '1':
		break;
	default:
		TopMenu();
		break;
	}
}

int MainMenu()
{
	system("cls");
	cout << "     FALLING ROCKS     " << endl;
	cout << endl;
	cout << "|----------|----------|" << endl;
	cout << "| 1 - start| 2 - top  |" << endl;
	cout << "|----------|----------|" << endl;
	cout << "| 3 - exit | 4 - crtor|" << endl;
	cout << "|----------|----------|" << endl;
	key = _getch();
	switch (key)
	{
	case '1':
		break;
	case '2':
		TopMenu();
		if (MainMenu() == 0) { return 0; }
		break;
	case '3':
		return 0;
		break;
	case '4':
		Captions();
		if (MainMenu() == 0) {return 0;}
		break;
	default:
		if (MainMenu() == 0) { return 0; }
		break;
	}
	return 1;
}

void GamePlay()
{
	bool change;
	while (life == true)
	{
		change = false;
		map[x][y] = ' ';
		key = _getch();
		//walking
		switch (key)
		{
		case 'w':
			if (y != 1) {
				y--;
				change = true;
			}
			break;
		case 'a':
			if (x != 1) {
				x--;
				change = true;
			}
			break;
		case 's':
			if (y != _size - 1) {
				y++;
				change = true;
			}
			break;
		case 'd':
			if (x != _size - 1) {
				x++;
				change = true;
			}
			break;
		case 'p':
			life = false;
			break;
		default:
			GamePlay();
			break;
		}
		if (change == true) {
			if (x == xbounty && y == ybounty)
			{
				score += 10;
				SpawnBounty();
			}
			map[x][y] = TexturePlayer;
			TickBomb();
			//print map
			DrawMap();
		}
	}
}

int EndMenu()
{
	//reading record
	ifstream FileTop;
	ofstream _FileTop;
	char name[10];
	string FileName[6];
	int num, FileScore[6], pos;
	bool isfind = false;
	FileTop.open("Top.txt");
	if (!FileTop.is_open())
	{
		_FileTop.open("Top.txt");
		_FileTop.close();
		FileTop.open("Top.txt");
	}
	FileScore[0] = -1;
	FileTop >> FileName[0] >> FileScore[0];
	FileTop.close();
	//menu
	system("cls");
	cout << "       Game over!" << endl;
	if (score > FileScore[0])
	{
		cout << "      New record: "<<score << endl;
	}
	else
	{
		cout << "      Your score: " << score << endl;
		cout << "        Record: " << FileScore[0] << endl;;
	}
	cout << "|----------|----------|" << endl;
	cout << "| 1 - menu | 2 - exit |" << endl;
	cout << "|----------|----------|" << endl;
	cout << "| 3 - rmmbr|----------|" << endl;
	cout << "|----------|----------|" << endl;

	key = _getch();
	switch (key)
	{
	case '1':
		break;
	case '2':
		return 0;
		break;
	case '3':
		num = 0;

		system("cls");
		cout << "Enter you name: ";
		cin >> name;

		//add score to top list
		FileTop.open("Top.txt");
		
		while (FileTop >> FileName[num] >> FileScore[num])
		{
			if (score > FileScore[num]&&!isfind)
			{
				pos = num;
				isfind = true;
			}
			num++;
		}
		FileTop.close();
		if (isfind)
		{
			for (int i = num; i > pos; i--)
			{
				FileName[i] = FileName[i - 1];
				FileScore[i] = FileScore[i - 1];
			}
			FileName[pos] = name;
			FileScore[pos] = score;
			if (num < 4)
			{
				num++;
			}
		}
		else if (num < 5)
		{
			FileName[num] = name;
			FileScore[num] = score;
			num++;
		}
		_FileTop.open("Top.txt");
		for (int i = 0; i < num; i++)
		{
			if (i != 0)
			{
				cout << endl;
			}
			_FileTop << FileName[i] << " " << FileScore[i]<<endl;
		}
		_FileTop.close();
		break;
	default:
		if (EndMenu() == 0) { return 0; }
		break;
	}
	return 1;
}

int main()
{
	//menu
	if (MainMenu() == 0) { return 0; }
	else
	{

		//player revive
		life = true;
		x = 10, y = 19;
		score = 0;

		//generation map
		GenerateMap();

		//load map
		DrawMap();

		//control
		GamePlay();
		//end menu
		if (EndMenu() == 0)
		{
			return 0;
		}
		else
		{
			main();
			return 0;
		}
	}
	return 0;
}

//Shevchenko Makar Ilyich (C) 2019