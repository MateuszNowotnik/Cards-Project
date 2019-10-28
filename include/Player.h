#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
    public:
        Player();
        virtual ~Player();

        void playScreen();
        void gameDraw(sf::RenderWindow &window);
        void generateCard(double, double);
        void betButton();
        void logOutButton();
        void passButton();
        void animate();
        void whatUser(std::string);

        int randP1;
        sf::Font font;
        sf::Sprite sP1Card, sGameBg;
        sf::Texture tP1Card, tGameBg;
        sf::RectangleShape betBtn, logOutBtn, passBtn;

    private:
        sf::Text betTxt, logOutTxt, passTxt, whatUserTxt, usernameTxt;
};

#endif // PLAYER_H
