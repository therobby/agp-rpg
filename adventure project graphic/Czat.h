#pragma once
#ifndef Czat_h
#define Czat_h
#include "includes.h"


class Czat {
	std::string input;
	bool active;
	char tmp;
	bool fontLoaded;
	sf::Font font;
	sf::Text text;

	int commandProcessor();

public:
	Czat();

	void draw(sf::RenderWindow *window, sf::View *view);

	bool isActive();

	void enable();
	void disable();

	int inputComponent(sf::Event *event);
};

#endif // !Czat_h
