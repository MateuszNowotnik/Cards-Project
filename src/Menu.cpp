#include "Menu.h"

Menu::Menu(double width, double height)
{
    if(!font.loadFromFile("fonts/Casino.ttf"))
        throw "Couldn't load the font!";

    tMenuBg.loadFromFile("images/menu_bg.jpg");
    sMenuBg.setTexture(tMenuBg);

    textMenu[0].setFont(font);
    textMenu[0].setColor(sf::Color(36, 28, 36));
    textMenu[0].setString("Login");
    textMenu[0].setCharacterSize(72);
    textMenu[0].setPosition(sf::Vector2f((width / 2) + (width * 0.2), height * 0.3));

    textMenu[1].setFont(font);
    textMenu[1].setColor(sf::Color::White);
    textMenu[1].setString("Register");
    textMenu[1].setCharacterSize(72);
    textMenu[1].setPosition(sf::Vector2f((width / 2) + (width * 0.2), height * 0.45));

    textMenu[2].setFont(font);
    textMenu[2].setColor(sf::Color::White);
    textMenu[2].setString("Exit");
    textMenu[2].setCharacterSize(72);
    textMenu[2].setPosition(sf::Vector2f((width / 2) + (width * 0.2), height * 0.6));

    selectedItemIndex = 0;
}

Menu::~Menu()
{

}

void Menu::moveUp()
{
    textMenu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex--;
    if(selectedItemIndex < 0) {selectedItemIndex = 2;}
    textMenu[selectedItemIndex].setColor(sf::Color(36, 28, 36));
}

void Menu::moveDown()
{
    textMenu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex++;
    if(selectedItemIndex > 2) {selectedItemIndex = 0;}
    textMenu[selectedItemIndex].setColor(sf::Color(36, 28, 36));
}

int Menu::selectMenu()
{
    return selectedItemIndex;
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(sMenuBg);
    for(int i = 0; i < 3; i++)
    {
        window.draw(textMenu[i]);
    }
}
