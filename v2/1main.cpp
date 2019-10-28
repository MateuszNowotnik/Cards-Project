#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <string>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1920,1080), "Goal Game", Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ContextSettings settings;
    settings.antialiasingLevel = 16;


    RectangleShape rectangle(Vector2f(160, 80));
    rectangle.setPosition(860,940);
    rectangle.setFillColor(Color::Black);



    int randNum1, randNum2; //randomly generated cards for the dealer
    int phD1, phD2; //place holders for cards dealt by the dealer
    Sprite sD1Card, sD2Card, sP1Card, sBG;
    Texture tD1Card, tD2Card, tP1Card, tBG;

    tBG.loadFromFile("images/background.png");
    sBG.setTexture(tBG);

    //((int)rand()*(14-2))/(int)RAND_MAX + 2;
    srand(time(NULL));
    randNum1 = rand() % 13 + 2;
    randNum2 = rand() % 13 + 2;

    phD1 = min(randNum1, randNum2);
    phD2 = max(randNum1, randNum2);

    tD1Card.loadFromFile("images/" + to_string(phD1) + ".png");
    tD2Card.loadFromFile("images/" + to_string(phD2) + ".png");

    sD1Card.setTexture(tD1Card);
    sD1Card.scale(0.2, 0.2);
    sD1Card.setPosition(600, -250);

    sD2Card.setTexture(tD2Card);
    sD2Card.scale(0.2, 0.2);
    sD2Card.setPosition(1100, -250);

    Vector2f sD1CurrentPos = sD1Card.getPosition();
    Vector2f sD2CurrentPos = sD2Card.getPosition();

    Vector2i mouseCurrentPos = Mouse::getPosition();


    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();

            if(Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        if((mouseCurrentPos.x >= 860 && mouseCurrentPos.x <= 1020) && (mouseCurrentPos.y >= 940 && mouseCurrentPos.y <= 1020))
        {
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                randNum1 = rand() % 13 + 2;
                randNum2 = rand() % 13 + 2;

                phD1 = min(randNum1, randNum2);
                phD2 = max(randNum1, randNum2);

                tD1Card.loadFromFile("images/" + to_string(phD1) + ".png");
                tD2Card.loadFromFile("images/" + to_string(phD2) + ".png");

                sD1Card.setTexture(tD1Card);
                sD2Card.setTexture(tD2Card);

                sD1Card.setPosition(600, -250);
                sD2Card.setPosition(1100, -250);
            }
        }
        mouseCurrentPos = Mouse::getPosition();

        if(sD1CurrentPos.y <= 400)
        {
            sD1Card.move(0.f, 16.f);
            sD1CurrentPos = sD1Card.getPosition();
        }

        if(sD2CurrentPos.y <= 400)
        {
            sD2Card.move(0.f, 16.f);
            sD2CurrentPos = sD2Card.getPosition();
        }
        sD1CurrentPos = sD1Card.getPosition();
        sD2CurrentPos = sD1Card.getPosition();


        window.clear();
        window.draw(sBG);
        window.draw(sD1Card);
        window.draw(sD2Card);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
