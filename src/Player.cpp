#include "Player.h"

Player::Player()
{
    if(!font.loadFromFile("fonts/Casino.ttf"))
        throw "Couldn't load the font!";

    sP1Card.scale(0.2, 0.2);
}

Player::~Player()
{
    //dtor
}

void Player::playScreen()
{
    tGameBg.loadFromFile("images/game_bg.png");
    sGameBg.setTexture(tGameBg);

    betButton();
    logOutButton();
    passButton();
}

void Player::generateCard(double width, double height)
{
    randP1 = rand() % 13 + 2;

    tP1Card.loadFromFile("images/" + std::to_string(randP1) + ".png");

    sP1Card.setTexture(tP1Card);

    sP1Card.setPosition(850, -250);
}

void Player::betButton()
{
    betBtn.setPosition(1240, 940);
    betBtn.setFillColor(sf::Color(40, 20, 0));
    betBtn.setSize(sf::Vector2f(160, 80));

    betTxt.setFont(font);
    betTxt.setString("BET");
    betTxt.setPosition(1295, 960);
}

void Player::logOutButton()
{
    logOutBtn.setPosition(50, 30);
    logOutBtn.setFillColor(sf::Color(40, 20, 0));
    logOutBtn.setSize(sf::Vector2f(160, 80));

    logOutTxt.setPosition(85, 50);
    logOutTxt.setFont(font);
    logOutTxt.setString("LOGOUT");
}

void Player::passButton()
{
    passBtn.setPosition(1470, 940);
    passBtn.setFillColor(sf::Color(40, 20, 0));
    passBtn.setSize(sf::Vector2f(160, 80));

    passTxt.setPosition(1520, 960);
    passTxt.setFont(font);
    passTxt.setString("PASS");
}

void Player::animate()
{
    sP1Card.setPosition(850, 400);
    //if(sP1Card.getPosition().y <= 400)
        //sP1Card.move(0.f, 16.f);
}

void Player::whatUser(std::string username)
{
    whatUserTxt.setPosition(300, 50);
    whatUserTxt.setFont(font);
    whatUserTxt.setString("User: ");

    usernameTxt.setPosition(385, 50);
    usernameTxt.setFont(font);
    usernameTxt.setString(username);
}

void Player::gameDraw(sf::RenderWindow &window)
{
    window.draw(sGameBg);
    window.draw(sP1Card);
    window.draw(betBtn);
    window.draw(betTxt);
    window.draw(logOutBtn);
    window.draw(logOutTxt);
    window.draw(passBtn);
    window.draw(passTxt);
    window.draw(whatUserTxt);
    window.draw(usernameTxt);
}
