#include <iostream> 
#include <string.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct V2 {
	signed int x = 0;
	signed int y = 0;
};
struct Player {
	V2 position = { 0,0 };
	V2 targetPosition{ -1,-1 };
	V2 lastPosition{ -1,-1 };
	int life = 1;
	int moves = 0;
};
void GenerateFixedMap(signed int**& _array)
{
	_array[0][0] = 1;
	_array[0][1] = -1;
	_array[0][2] = -3;
	_array[0][3] = 4;
	_array[1][0] = -4;
	_array[1][1] = 3;
	_array[1][2] = -2;
	_array[1][3] = 1;
	_array[2][0] = 1;
	_array[2][1] = -5;
	_array[2][2] = -2;
	_array[2][3] = 0;
	_array[3][0] = 2;
	_array[3][1] = 3;
	_array[3][2] = 1;
	_array[3][3] = 2;
}
void DisplayMap(signed int**& _array, int& sizeX, int& sizeY, Player _player) {
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			if (_player.position.x == x && _player.position.y == y) {
				std::cout << "[]";
			}
			else {
				if (_array[x][y] >= 0) {
					std::cout << " ";
				}
				std::cout << _array[x][y];
			}
			if (x != sizeX - 1)
			{
				std::cout << "|";
			}
		}
		std::cout << std::endl;
	}
}
bool MovePlayer(signed int**& _array, Player& _player, int sizeX, int sizeY) {
	signed int distX = _player.targetPosition.x - _player.position.x;
	signed int distY = _player.targetPosition.y - _player.position.y;
	_player.life += _array[_player.position.x][_player.position.y];
	bool cUp{ true }, cDown{ true }, cLeft{ true }, cRight{ true };
	if (distX == 0 && distY == 0) {
		return true;
	}
	if (distX > 1) {
		cLeft = false;
	}
	if (distX < -1) {
		cRight = false;
	}
	if (distY > 1) {
		cUp = false;
	}
	if (distY < -1) {
		cDown = false;
	}
	if (_player.position.x == 0) {
		cLeft = false;
	}
	if (_player.position.x == sizeX - 1) {
		cRight = false;
	}
	if (_player.position.y == 0) {
		cUp = false;
	}
	if (_player.position.y == sizeY - 1) {
		cDown = false;
	}
	signed int up{ 0 }, down{ 0 }, left{ 0 }, right{ 0 };
	if (cLeft) {
		left = _array[_player.position.x - 1][_player.position.y] + _player.life;
		if (left < 1 || (_player.position.x - 1) == _player.lastPosition.x) {
			cLeft = false;
		}
	}
	if (cRight) {
		right = _array[_player.position.x + 1][_player.position.y] + _player.life;
		if (right < 1 || (_player.position.x + 1) == _player.lastPosition.x) {
			cRight = false;
		}
	}
	if (cUp) {
		up = _array[_player.position.x][_player.position.y - 1] + _player.life;
		if (up < 1 || (_player.position.y - 1) == _player.lastPosition.y) {
			cUp = false;
		}
	}
	if (cDown) {
		down = _array[_player.position.x][_player.position.y + 1] + _player.life;
		if (down < 1 || (_player.position.y + 1) == _player.lastPosition.y) {
			cDown = false;
		}
	}


	std::cout << "No " << _player.moves << "|| " << "UP:" << up << "(" << cUp << ")" << "," << "DOWN:" << down << "(" << cDown << ")" << "," << "LEFT:" << left << "(" << cLeft << ")" << "," << "RIGHT:" << right << "(" << cRight << ")" << endl;
	_player.lastPosition = _player.position;
	if (cUp) {
		_player.position.y--;
		return false;
	}
	if (cDown) {
		_player.position.y++;
		return false;
	}
	if (cRight) {
		_player.position.x++;
		return false;
	}
	if (cLeft) {
		_player.position.x--;
		return false;
	}
}

int main()
{
	int eSizeX = 4;
	int eSizeY = 4;
	signed int** pMapArray = new signed int* [eSizeX];
	for (int i = 0; i < eSizeX; ++i) {
		pMapArray[i] = new signed int[eSizeY];
	}
	GenerateFixedMap(pMapArray);
	V2 sPos{ 0,0 };
	V2 ePos{ 3,1 };

	Player player;
	player.position = sPos;
	player.targetPosition = ePos;
	bool gameEnd = false;
	while (!gameEnd) {
		DisplayMap(pMapArray, eSizeX, eSizeY, player);
		cin.get();
		system("CLS");
		cout << flush;
		player.moves++;
		gameEnd = MovePlayer(pMapArray, player, eSizeX, eSizeY);
	}
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
