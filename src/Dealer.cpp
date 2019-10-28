#include "Dealer.h"

Dealer::Dealer()
{
    sD1Card.scale(0.2, 0.2);
    sD2Card.scale(0.2, 0.2);
}

Dealer::~Dealer()
{

}

template<typename T>
int Dealer::getMax(T a, T b) {
    return (a>b?a:b);
}

void Dealer::generateCard(double width, double height)
{
    do{
    randD1 = rand() % 13 + 2;
    randD2 = rand() % 13 + 2;
    }while((randD1 == randD2) || ((randD1 == randD2 - 1) || (randD1 == randD2 + 1)));

    phD1 = std::min(randD1, randD2);
    phD2 = getMax<int>(randD1, randD2);

    tD1Card.loadFromFile("images/" + std::to_string(phD1) + ".png");
    tD2Card.loadFromFile("images/" + std::to_string(phD2) + ".png");

    sD1Card.setTexture(tD1Card);
    sD2Card.setTexture(tD2Card);

    sD1Card.setPosition(600, -250);
    sD2Card.setPosition(1100, -250);

    sP1Card.setPosition(850, -250);
}

void Dealer::playButton()
{
    playBtn.setSize(sf::Vector2f(160, 80));
    playBtn.setPosition(510,940);
    playBtn.setFillColor(sf::Color(70, 20, 0));

    playTxt.setString("PLAY");
    playTxt.setFont(font);
    playTxt.setPosition(560,960);
}

void Dealer::animate()
{
    sD1Card.setPosition(600, 400);
    sD2Card.setPosition(1100, 400);
    /*
    if(sD1Card.getPosition().y <= 400 && sD2Card.getPosition().y <= 400)
        {
            sD1Card.move(0.f, 16.f);
            sD2Card.move(0.f, 16.f);
        }
    */
}

void Dealer::dealerDraw(sf::RenderWindow &window)
{
    window.draw(sD1Card);
    window.draw(sD2Card);
    window.draw(playBtn);
    window.draw(playTxt);
}
