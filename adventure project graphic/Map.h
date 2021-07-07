#pragma once
#ifndef Play_h
#define Play_h
#include "includes.h"

class Map {
	int *M;	//zbi�r warto�ci textur na mapie
	int x, y;	//rozmiar mapy
	int *Collide;	//zbi�r blok�w kt�re kooliduj�
	int CollideSize;
	sf::Sprite *map;	//tablica mapy
	sf::Texture *textures;	//tablica zawieraj�ca textury
	int texturessize;
	int texturesHeight;
	int texturesWidth;
	std::string MapName;

	void getXY(int &x, int &y, std::ifstream *file);	//metoda zliczaj�ca rozmiary mapy na podstawie macierzy mapy w pliku txt
	void getX(int &x, std::ifstream *file);
	void getY(int &y, std::ifstream *file);
public:
	Map();
	~Map();
	int load(std::string _MapName, bool firstLoad);
	void Draw(sf::RenderWindow *window);	
	bool collision(sf::Sprite npc);	//sprawdz kolizj� z granicami mapy (obiektami ustalonymi w metodzie)
	bool collision(sf::Sprite npc, int object);	//sprawdz kolizj� z danym obiektem na mapie
	void ChangeSprite(int x, int y, int texturenumber);	//zmie� texture sprita na mapie

	sf::Vector2f getBottomLeftCornerPosition();	//nie mam pomys�u na nazw�, ale zwraca wsp�rz�dne dolnego prawego rogu
	std::string getMapName();
	sf::Vector2f getRespawn();
};

#endif // !Play_h
