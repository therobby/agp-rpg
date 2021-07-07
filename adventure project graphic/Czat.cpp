#include "Czat.h"
#include "Settings.h"

Czat::Czat() {
	Settings S;
	active = false;
	fontLoaded = false;
	input = "";
	tmp = '\0';

	if (font.loadFromFile(S.getFont())) {
		text.setFont(font);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(26);
		text.setPosition(1, 1);
		fontLoaded = true;
	}
	else
		std::cout << "Error loading czat font!\n";

}

bool Czat::isActive() {
	if (fontLoaded)
		return active;
	else
		return false;
}

int Czat::inputComponent(sf::Event *event) {
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Return) {
		commandProcessor();
		input = "";
		return -1;
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Escape) {
		return -1;
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::BackSpace) {
		if (input.size() > 0) {
			input[input.size() - 1] = '\0';
			input.resize(input.size() - 1);
		}
		else
			return -1;
	}
	else {
		if (event->type == sf::Event::TextEntered) {
			if (event->text.unicode < 128) 
				tmp = static_cast<char>(event->text.unicode);
		}
		if (event->type == sf::Event::KeyReleased && tmp != '\0') {
			input += tmp;
			tmp = '\0';
		}
		return 0;
	}
}

int Czat::commandProcessor() {
	if (input == "/reloadmap")
		return -2;
		//m.load(MapName, false);
		/*else if (command.find("zoom ") == 0) {
		int newZoom = 0, tmp = 1;
		for (int i = command.size(); i > 5; i--) {
		newZoom += (int)command[i] * tmp;
		tmp *= 10;
		}
		newZoom = 1 / newZoom;

		view.zoom(newZoom);
		}*/
}

void Czat::enable() {
	active = true;
}

void Czat::disable() {
	active = false;
}

void Czat::draw(sf::RenderWindow *window, sf::View *view) {
	text.setString(">" + input);

	text.setPosition(sf::Vector2f(view->getCenter().x - (window->getSize().x / 5 + 1), view->getCenter().y - (window->getSize().y / 5 - 5)));
	window->draw(text);
}