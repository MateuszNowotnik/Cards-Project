#ifndef DATABASE_H
#define DATABASE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Dealer.h"


class Database : public Player, public Dealer
{
    public:
        Database();
        virtual ~Database();

        void backButton();
        void sendButton(bool, bool);

        void loginDraw(sf::RenderWindow &window);
        void registerDraw(sf::RenderWindow &window);

        void dbScreen(bool, bool);

        void formUsername(int unicode);
        void formPasswd(int unicode);

        void sendLogIn();
        void sendRegister();
        void resetField();
        void searchLogin();
        void textFieldReg();
        void textFieldLog();

        friend std::ostream& operator<<(std::ostream& output, const Database& obj);

        std::ofstream outFile;
        std::ifstream inFile;

        std::string usernmFromFile, passwdFromFile, creditsFromFile;
        bool isPasswd;
        bool isUsernm;
        sf::String usernameInput, passwdInput;
        sf::Text backTxt, sendTxt, usernameText, passwdText, creditsText, fieldText;

    private:
        sf::Font fontDb;
        sf::Sprite sLoginBg, sRegisterBg;
        sf::Texture tLoginBg, tRegisterBg;
        sf::RectangleShape backBtn, sendBtn, uField, pField;
};

#endif // DATABASE_H
