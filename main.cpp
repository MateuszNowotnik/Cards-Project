#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <math.h>
#include <string>
#include "Menu.h"
#include "Player.h"
#include "Dealer.h"
#include "Database.h"
#include "Credits.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Goal Game", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    Menu menu(window.getSize().x, window.getSize().y);

    Player player;
    Dealer dealer;
    Database db;
    Credits credits;

    srand (time(NULL));

    bool menuScreen = true;
    bool loginScreen = false;
    bool registerScreen = false;
    bool gameScreen = false;

    bool usernameField = false;
    bool passwdField = false;
    bool animatePlayer = false;
    bool animateDealer = false;
    bool playOrBet = false;

    int currentPasses = 0;


    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // events
            switch(event.type)
            {
            case sf::Event::KeyReleased:
                // when a key is pressed (*released)
                switch(event.key.code)
                {
                case sf::Keyboard::Return:
                    switch(menu.selectMenu())
                    {
                    case 0:
                        loginScreen = true;
                        menuScreen = false;
                        db.dbScreen(loginScreen, registerScreen);
                        break;

                    case 1:
                        registerScreen = true;
                        menuScreen = false;
                        db.dbScreen(loginScreen, registerScreen);
                        break;

                    case 2:
                        window.close();
                        break;
                    }
                    break;

                case sf::Keyboard::Up:
                    if(menuScreen == true)
                        menu.moveUp();
                    break;

                case sf::Keyboard::Down:
                    if(menuScreen == true)
                        menu.moveDown();
                    break;
                }
                break;

            case sf::Event::MouseButtonPressed:
                // when the mouse is clicked

                // bet button
                if((credits.betAmount > 0) && (playOrBet == true) && (gameScreen == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1240 && event.mouseButton.x <= 1400) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                {
                    player.generateCard(window.getSize().x, window.getSize().y);
                    //animatePlayer = true;
                    player.animate();

                    if((player.randP1 >= dealer.phD1) && (player.randP1 <= dealer.phD2))
                    {
                        credits.creditsAmount += credits.betAmount;
                        credits.betAmount = 0;
                        credits.amountShow();
                    }
                    if((player.randP1 <= dealer.phD1) || (player.randP1 >= dealer.phD2))
                    {
                        credits.creditsAmount -= credits.betAmount;
                        credits.betAmount = 0;
                        credits.amountShow();
                    }
                    playOrBet = false;
                    currentPasses = 0;

                    dealer.playBtn.setFillColor(sf::Color(70, 20, 0));
                    player.betBtn.setFillColor(sf::Color(40, 20, 0));
                    player.passBtn.setFillColor(sf::Color(40, 20, 0));
                }

                //pass button
                if((gameScreen == true) && (playOrBet == true) && (currentPasses < 2) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1470 && event.mouseButton.x <= 1630) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                {
                    currentPasses++;
                    dealer.generateCard(window.getSize().x, window.getSize().y);

                    if(currentPasses == 2)
                    {
                        currentPasses++;
                        credits.betAmount = ((credits.creditsAmount) / 2);
                        credits.amountShow();

                        player.betBtn.setFillColor(sf::Color(70, 20, 0));
                        player.passBtn.setFillColor(sf::Color(40, 20, 0));
                        dealer.playBtn.setFillColor(sf::Color(40, 20, 0));
                    }
                    else
                    {
                        player.betBtn.setFillColor(sf::Color(70, 20, 0));
                        player.passBtn.setFillColor(sf::Color(70, 20, 0));
                        dealer.playBtn.setFillColor(sf::Color(40, 20, 0));
                    }

                    dealer.animate();
                    playOrBet = true;
                }

                //play button
                if((gameScreen == true) && (playOrBet == false) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 510 && event.mouseButton.x <= 670) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                {
                    dealer.generateCard(window.getSize().x, window.getSize().y);
                    //animateDealer = true;
                    dealer.animate();
                    playOrBet = true;

                    player.betBtn.setFillColor(sf::Color(70, 20, 0));
                    player.passBtn.setFillColor(sf::Color(70, 20, 0));
                    dealer.playBtn.setFillColor(sf::Color(40, 20, 0));
                }

                // back button
                if((event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 50 && event.mouseButton.x <= 210) && (event.mouseButton.y >= 940 && event.mouseButton.y <= 1020))
                {
                    if(loginScreen == true || registerScreen == true)
                    {
                        menuScreen = true;
                        loginScreen = false;
                        registerScreen = false;
                    }
                }

                // logout button  !reset cards, texts: credits, bet itd!
                if((event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 50 && event.mouseButton.x <= 210) && (event.mouseButton.y >= 30 && event.mouseButton.y <= 110))
                {
                    if(gameScreen == true)
                    {
                        //reset screen
                        menuScreen = true;
                        gameScreen = false;

                        //reset login
                        db.isUsernm = false;
                        db.isPasswd = false;

                        //reset cards
                        //animatePlayer = false;
                        //animateDealer = false;
                        player.sP1Card.setPosition(850, -250);
                        dealer.sD1Card.setPosition(600, -250);
                        dealer.sD2Card.setPosition(1100, -250);

                        //reset credits
                        credits.betAmount = 0;

                        //save credits to file
                        credits.saveCredits(db.usernmFromFile);
                    }
                }

                // token (- 1)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 750 && event.mouseButton.x <= 805) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(-1, currentPasses);

                // token (+ 1)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 806 && event.mouseButton.x <= 860) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(1, currentPasses);

                // token (- 10)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 900 && event.mouseButton.x <= 955) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(-10, currentPasses);

                // token (+ 10)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 956 && event.mouseButton.x <= 1010) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(10, currentPasses);

                // token (- 100)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1050 && event.mouseButton.x <= 1105) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(-100, currentPasses);

                // token (+ 100)
                if((gameScreen == true) && (playOrBet == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1106 && event.mouseButton.x <= 1160) && (event.mouseButton.y >= 920 && event.mouseButton.y <= 1030))
                    credits.creditsBet(100, currentPasses);

                // username field
                if((loginScreen == true || registerScreen == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1250 && event.mouseButton.x <= 1710) && (event.mouseButton.y >= 350 && event.mouseButton.y <= 430))
                {
                    usernameField = true;
                    passwdField = false;
                }

                // password field
                if((loginScreen == true || registerScreen == true) && (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1250 && event.mouseButton.x <= 1710) && (event.mouseButton.y >= 500 && event.mouseButton.y <= 580))
                {
                    passwdField = true;
                    usernameField = false;
                }

                // login/register button
                if((event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x >= 1530 && event.mouseButton.x <= 1710) && (event.mouseButton.y >= 650 && event.mouseButton.y <= 730))
                {
                    if(loginScreen == true)
                        if(db.usernameInput != "" && db.passwdInput != "")
                            db.sendLogIn();
                            if(db.isUsernm == true && db.isPasswd == true)
                            {
                                player.playScreen();
                                player.whatUser(db.usernmFromFile);
                                dealer.playButton();
                                credits.tokenCreate();
                                credits.creditsAmount = stoi(db.creditsFromFile);
                                credits.amountShow();

                                gameScreen = true;
                                loginScreen = false;
                            }
                    if(registerScreen == true)
                        if(db.usernameInput != "" && db.passwdInput != "")
                            db.sendRegister();
                }
                break;

            case sf::Event::TextEntered:
                if(loginScreen == true || registerScreen == true)
                {
                    if(usernameField == true)
                        db.formUsername(event.text.unicode);

                    if(passwdField == true)
                        db.formPasswd(event.text.unicode);
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;
            }

        }

        /*
        if(animatePlayer == true)
            player.animate();

        if(animateDealer == true)
            dealer.animate();
        */

        window.clear();

        if(menuScreen == true)
            menu.draw(window);

        if(loginScreen == true)
            db.loginDraw(window);

        if(registerScreen == true)
            db.registerDraw(window);

        if(gameScreen == true)
        {
            player.gameDraw(window);
            dealer.dealerDraw(window);
            credits.creditsDraw(window);
        }

        window.display();
    }

    return 0;
}
