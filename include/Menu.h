#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <exception>

class Menu
{
    public:
        Menu(double width, double height);
        virtual ~Menu();

        void draw(sf::RenderWindow &window);
        void moveUp();
        void moveDown();
        int selectMenu();

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text textMenu[3];
        sf::RectangleShape shape;
        sf::Sprite sMenuBg;
        sf::Texture tMenuBg;
};

#endif // MENU_H
