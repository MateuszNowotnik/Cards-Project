#ifndef DEALER_H
#define DEALER_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Player.h"

class Dealer: public Player
{
    public:
        Dealer();
        virtual ~Dealer();

        template<typename T>
        int getMax(T, T);
        void dealerDraw(sf::RenderWindow &window);
        void generateCard(double, double);
        void playButton();
        void animate();

        int phD1, phD2;
        sf::Sprite sD1Card, sD2Card;
        sf::Texture tD1Card, tD2Card;
        sf::RectangleShape playBtn;

    private:
        int randD1, randD2;
        sf::Text playTxt;
};

#endif // DEALER_H
