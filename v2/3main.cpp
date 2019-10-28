#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <string>
#include <iostream>
#include "Menu.h"
#include "Player.h"
#include "Dealer.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1920,1080), "Goal Game", Style::Fullscreen);
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    //ContextSettings settings; // comment
    //settings.antialiasingLevel = 16; // comment

    Menu menu(window.getSize().x, window.getSize().y);

    Player player;

    /*
    @Font font;
    @font.loadFromFile("fonts/casino_2/Casino.ttf");


    RectangleShape playBtn(Vector2f(160, 80));
    playBtn.setPosition(860,940);
    playBtn.setFillColor(Color(40, 20, 0));

    Text playTxt("PLAY", font);
    playTxt.setPosition(905,960);


    @RectangleShape betBtn(Vector2f(160, 80));
    @betBtn.setPosition(1050,940);
    @betBtn.setFillColor(Color(40, 20, 0));

    @Text betTxt("BET", font);
    @betTxt.setPosition(1100,960);


    Text amountTxt("Amount:", font);
    amountTxt.setPosition(850,80);

    Text countTxt("1000", font);
    countTxt.setPosition(970,80);


    srand(time(NULL));

    int temp1, temp2 = 0; // kolejnosc kart uzywajac przyciskow
    int amount = 1000;
    -@int randD1, randD2, randP1; //randomly generated cards for the dealer and player
    int phD1, phD2; //place holders for cards dealt by the dealer for sorting
    -@Sprite sD1Card, sD2Card, sP1Card, sBG;
    -@Texture tD1Card, tD2Card, tP1Card, tBG;
    -@Vector2f sD1CurrentPos, sD2CurrentPos, sP1CurrentPos;

    // Scaling Cards
    sD1Card.scale(0.2, 0.2);
    sD2Card.scale(0.2, 0.2);
    @sP1Card.scale(0.2, 0.2);

    // Setting a background
    @tBG.loadFromFile("images/background.png");
    @sBG.setTexture(tBG);

    */
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            // events
            switch(event.type)
            {
            case Event::KeyReleased:
                // when a key is pressed (*released)
                switch(event.key.code)
                {
                case Keyboard::Return:
                    switch(menu.selectMenu())
                    {
                    case 0:
                        player.startGame();
                        break;

                    case 1:
                        // dataBase.registerPlayer();
                        cout << "Register" << endl;
                        break;

                    case 2:
                        window.close();
                        break;
                    }
                    break;

                case Keyboard::Up:
                    menu.moveUp();
                    break;

                case Keyboard::Left:
                    menu.draw(window);
                    break;

                case Keyboard::Down:
                    menu.moveDown();
                    break;

                case Keyboard::Escape:
                    window.close();
                    break;
                }
                break;

            case Event::MouseButtonPressed:
                // when a mouse is clicked
                if((event.mouseButton.button == Mouse::Left) && (event.mouseButton.x >= 1050 && event.mouseButton.x <= 1210) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                {
                    player.generateCard(window.getSize().x, window.getSize().y);
                }

                if((event.mouseButton.button == Mouse::Left) && (event.mouseButton.x >= 860 && event.mouseButton.x <= 1020) && (event.mouseButton.y >= 940 && event.mouseButton.y >= 120))
                {
                    //dealer.generateCard(window.getSize().x, window.getSize().y);
                }
                break;

            case Event::Closed:
                window.close();
                break;
            }

            /*
            if(event.type == Event::MouseButtonPressed)
            {
                // Dealer
                if((temp2 == 0) && (event.mouseButton.button == Mouse::Left) && (event.mouseButton.x >= 860 && event.mouseButton.x <= 1020) && (event.mouseButton.y >= 940 && event.mouseButton.y >= 120))
                {
                    temp1 = 1;
                    temp2 = 1;

                    randD1 = rand() % 13 + 2;
                    randD2 = rand() % 13 + 2;

                    phD1 = min(randD1, randD2);
                    phD2 = max(randD1, randD2);

                    tD1Card.loadFromFile("images/" + to_string(phD1) + ".png");
                    tD2Card.loadFromFile("images/" + to_string(phD2) + ".png");

                    sD1Card.setTexture(tD1Card);
                    sD2Card.setTexture(tD2Card);

                    sD1Card.setPosition(600, -250);
                    sD2Card.setPosition(1100, -250);

                    sP1Card.setPosition(-1000, 0);
                }

                -@// Player
                @if((temp1 == 1) && (event.mouseButton.button == Mouse::Left) && (event.mouseButton.x >= 1050 && event.mouseButton.x <= 1210) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                @{
                    temp2 = 0;

                    amount -= 100;

                    @randP1 = rand() % 13 + 2;

                    @tP1Card.loadFromFile("images/" + to_string(randP1) + ".png");

                    @sP1Card.setTexture(tP1Card);

                    @sP1Card.setPosition(850, -250);

                    if(randP1 >= phD1 && randP1 <= phD2)
                        amount += 200;

                    countTxt.setString(to_string(amount));

                    temp1 = 0;
                @}
            }
            */

        }

        /*
        // animations of cards
        if(sD1CurrentPos.y <= 400 && sD2CurrentPos.y <= 400)
        {
            sD1Card.move(0.f, 16.f);
            sD2Card.move(0.f, 16.f);
        }

        @if(sP1CurrentPos.y <= 400)
            @sP1Card.move(0.f, 16.f);


        sD1CurrentPos = sD1Card.getPosition();
        sD2CurrentPos = sD2Card.getPosition();
        @sP1CurrentPos = sP1Card.getPosition();

        */

        player.animate();

        window.clear();
        menu.draw(window);
        player.field(window);
        /*
        @window.draw(sBG);
        window.draw(sD1Card);
        window.draw(sD2Card);
        @window.draw(sP1Card);
        window.draw(playBtn);
        @window.draw(betBtn);
        window.draw(playTxt);
        @window.draw(betTxt);
        window.draw(amountTxt);
        window.draw(countTxt);
        */
        window.display();
    }

    return 0;
}
