#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <fstream>
#include "Player.h"

class Credits : public Player
{
    public:
        Credits();
        virtual ~Credits();

        void tokenCreate();
        void creditsBet(int, int);
        void amountShow();
        void saveCredits(std::string userFile);
        void creditsDraw(sf::RenderWindow &window);

        int creditsAmount = 0;
        int betAmount = 0;

    private:
        sf::Font fontMVP, fontCr;
        sf::Text creditsAmountTxt1, creditsAmountTxt2, betAmountTxt1, betAmountTxt2;
        sf::Text tokenTxt1, tokenTxt10, tokenTxt100;
        sf::CircleShape tokenCircle1, tokenCircle10, tokenCircle100;

        std::string strTempUser, strTempPasswd, strTempCredits;
        std::ofstream fileout;
        std::ifstream filein;
};

#endif // CREDITS_H
