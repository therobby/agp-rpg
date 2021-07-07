#include "Map.h"

Map::Map() {
	M = Collide = NULL;
	x = y = CollideSize = texturessize = texturesHeight = texturesWidth = 0;
	map = NULL;
	textures = NULL;
	MapName = "";
}

Map::~Map() {
	delete[] M;
	delete[] map;
	delete[] Collide;
	delete[] textures;
}



int Map::load(std::string _MapName, bool firstLoad) {
	x = y = 0;
	MapName = _MapName;

	std::ifstream file;
	file.open("Data/" + MapName + "_textsize.txt");
	if (file.is_open()) {
		file >> texturesHeight;
		file >> texturesWidth;
	}
	else 
		return 10;

	file.close();

	if (!firstLoad) {
		delete[] M;
		delete[] map;
		delete[] Collide;
		delete[] textures;
	}

	file.open("Data/" + MapName + ".txt");

	if (file.is_open()) {	//jak plik mapy zosta³ uruchomiony
		std::string texturename;
		getXY(x, y, &file);	//pobierz wymiary

		M = new int[x*y];	//ustaw tablice w zale¿noœci od wymiarów
		map = new sf::Sprite[x*y];

		for (int i = 0; i < x; i++)
			for (int j = 0; j < y; j++)
				file >> M[j + (y * i)];	//wczytaj info na temat rozmieszczenia textur na mapie

		std::ifstream textfile;
		textfile.open("Data/" + MapName + "_Textures.txt");

		if (textfile.is_open()) {
			getY(texturessize, &textfile);
			textures = new sf::Texture[texturessize];

			for (int i = 0; i < texturessize; i++) {
				std::getline(textfile, texturename);
				if (!textures[i].loadFromFile("Textures/" + texturename))	//wczytaj textury
					return 21;
				textures[i].setSmooth(true);
			}
		}
		else 
			return 11;

		for (int j = 0; j < y; j++)
			for (int i = 0; i < x; i++) {
				if (M[i + (x * j)] >= texturessize) 
					return 30;

				map[i + (x * j)].setTexture(textures[M[i + (x * j)]]);	//przypisz textury
				map[i + (x * j)].setPosition(sf::Vector2f(texturesHeight * i, texturesWidth * j));	//i ustaw sprity
			}
	}
	else 
		return 12;
	
	file.close();

	file.open("Data/" + MapName + "_Collide.txt");
	if (file.is_open()) {
		getX(CollideSize, &file);

		Collide = new int[CollideSize];	//ustaw tablice w zale¿noœci od wymiarów

		for (int i = 0; i < CollideSize; i++)
			file >> Collide[i];	//wczytaj info na temat koliduj¹cych bloków
	}
	else 
		return 13;
	
	file.close();
	return 0;
}

void Map::Draw(sf::RenderWindow *window) {
	for (int i = 0; i < x*y; i++)
		window->draw(map[i]);
}

bool Map::collision(sf::Sprite npc) {
	for (int i = 0; i < x*y; i++)
		for(int j = 0; j < CollideSize; j++)
			if (map[i].getTexture() == &textures[Collide[j]]) {	//sprawdŸ czy npc kooliduje z tym spritem
				sf::FloatRect colide = map[i].getGlobalBounds();	//pobierz wymiary sprite na mapie
				sf::FloatRect n = npc.getGlobalBounds();	//pobierz wymiary npc
				if (colide.intersects(n))	//sprawdŸ czy npc zawiera siê w sprite
					return true;	//jak tak to zwróæ ¿e jest kolizja
			}
	return false;
}

bool Map::collision(sf::Sprite npc, int object) {
	for (int i = 0; i < x*y; i++)
		if (map[i].getTexture() == &textures[object]) {	//to samo co wy¿ej tylko szukasz danego elementu, a nie wszystkich z którymi mo¿esz koolidowaæ
			sf::FloatRect colide = map[i].getGlobalBounds();
			sf::FloatRect n = npc.getGlobalBounds();
			if (colide.intersects(n))
				return true;
		}
	return false;
}

void Map::getXY(int &x, int &y, std::ifstream *file) {
	std::string s;	//zmienna pomocnicza
	char k; //zmienna pomocnicza
	do
	{
		*file >> k;	//zlicz iloœæ elementów w pliku
		x++;
	} while (!file->eof());
	file->clear();	//cofnij wskaŸnik do pocz¹tku pliku
	file->seekg(0);
	do
	{
		std::getline(*file, s);	//zlicz iloœæ linijek w pliku
		y++;
	} while (!file->eof());

	file->clear();	//cofnij wskaŸnik do pocz¹tku pliku
	file->seekg(0);
	x--;	//udejmij znak (chyba) '\0'
	x /= y;	//podziel x przez y by uzyskaæ ilosæ elementów w jednej linijce
}

void Map::getX(int &x, std::ifstream *file) {
	char k; //zmienna pomocnicza
	do
	{
		*file >> k;	//zlicz iloœæ elementów w pliku
		x++;
	} while (!file->eof());

	file->clear();	//cofnij wskaŸnik do pocz¹tku pliku
	file->seekg(0);
	x--;	//udejmij znak (chyba) '\0'
}

void Map::getY(int &y, std::ifstream *file) {
	std::string s;	//zmienna pomocnicza
	do
	{
		std::getline(*file, s);	//zlicz iloœæ linijek w pliku
		y++;
	} while (!file->eof());
	file->clear();	//cofnij wskaŸnik do pocz¹tku pliku
	file->seekg(0);
}

void Map::ChangeSprite(int x, int y, int texturenumber) {
	map[x * y].setTexture(textures[texturenumber]);	//zmieñ sprite na taki z danym numerem
}

std::string Map::getMapName() {
	return MapName;
}

sf::Vector2f Map::getRespawn() {
	sf::Vector2f resp;

	std::ifstream file;
	file.open("Data/" + MapName + "_Respawn.txt");
	if (file.is_open()) {
		file >> resp.x;
		file >> resp.y;
	}
	else {
		std::cout << "Can't load " << "Data/" + MapName + "_Respawn.txt\n";
		resp.x = -14;
	}
	return resp;
}

sf::Vector2f Map::getBottomLeftCornerPosition() {
	sf::Vector2f pos(x*texturesHeight, y*texturesWidth);
	return pos;
}