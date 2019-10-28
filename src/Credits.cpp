#include "Credits.h"

Credits::Credits()
{
    if(!fontMVP.loadFromFile("fonts/arial.ttf"))
        throw "Couldn't load the font!";
}

Credits::~Credits()
{

}

void Credits::creditsBet(int amount, int currentPasses)
{
    if(amount < 0)
    {
        betAmount += amount;

        if((betAmount < 0) || ((currentPasses >= 2) && (betAmount < (creditsAmount / 2))))
            betAmount -= amount;
    }

    if(amount > 0)
    {
        betAmount += amount;

        if(betAmount > creditsAmount)
            betAmount -= amount;
    }

    amountShow();
}

void Credits::tokenCreate()
{
    tokenCircle1.setRadius(55);
    tokenCircle1.setOutlineColor(sf::Color::Black);
    tokenCircle1.setOutlineThickness(2);
    tokenCircle1.setFillColor(sf::Color(40, 20, 0));
    tokenCircle1.setPosition(750, 920);

    tokenTxt1.setPosition(780, 955);
    tokenTxt1.setFont(fontMVP);
    tokenTxt1.setString("- 1 +");

    tokenCircle10.setRadius(55);
    tokenCircle10.setOutlineColor(sf::Color::Black);
    tokenCircle10.setOutlineThickness(2);
    tokenCircle10.setFillColor(sf::Color(40, 20, 0));
    tokenCircle10.setPosition(900, 920);

    tokenTxt10.setPosition(920, 955);
    tokenTxt10.setFont(fontMVP);
    tokenTxt10.setString("- 10 +");

    tokenCircle100.setRadius(55);
    tokenCircle100.setOutlineColor(sf::Color::Black);
    tokenCircle100.setOutlineThickness(2);
    tokenCircle100.setFillColor(sf::Color(40, 20, 0));
    tokenCircle100.setPosition(1050, 920);

    tokenTxt100.setPosition(1060, 955);
    tokenTxt100.setFont(fontMVP);
    tokenTxt100.setString("- 100 +");
}

void Credits::amountShow()
{
    creditsAmountTxt1.setPosition(1300, 50);
    creditsAmountTxt1.setFont(font);
    creditsAmountTxt1.setString("Available Credits: ");

    creditsAmountTxt2.setPosition(1555, 50);
    creditsAmountTxt2.setFont(font);
    creditsAmountTxt2.setString(std::to_string(creditsAmount));

    betAmountTxt1.setPosition(850, 50);
    betAmountTxt1.setFont(font);
    betAmountTxt1.setString("Betting: ");

    betAmountTxt2.setPosition(970, 50);
    betAmountTxt2.setFont(font);
    betAmountTxt2.setString(std::to_string(betAmount));
}

// save credits to file
void Credits::saveCredits(std::string userFile)
{
    filein.open("files/usersDB.txt"); //File to read from
    fileout.open("files/tempDB.txt"); //Temporary file
    if(!filein || !fileout)
        throw "Error opening files!";

    while(filein >> std::ws, getline(filein, strTempUser, ';'), getline(filein, strTempPasswd, ';'), getline(filein, strTempCredits, ';'))
    {
        if(strTempUser == userFile)
            strTempCredits = std::to_string(creditsAmount);

        fileout << strTempUser << ";" << strTempPasswd << ";" << strTempCredits << ";" << "\n";
    }

    filein.close();
    fileout.close();

    std::rename("files/usersDB.txt", "files/1.txt");
    std::rename("files/tempDB.txt", "files/usersDB.txt");
    std::rename("files/1.txt", "files/tempDB.txt");
}

void Credits::creditsDraw(sf::RenderWindow &window)
{
    window.draw(tokenCircle1);
    window.draw(tokenCircle10);
    window.draw(tokenCircle100);
    window.draw(tokenTxt1);
    window.draw(tokenTxt10);
    window.draw(tokenTxt100);

    window.draw(creditsAmountTxt1);
    window.draw(creditsAmountTxt2);
    window.draw(betAmountTxt1);
    window.draw(betAmountTxt2);
}
