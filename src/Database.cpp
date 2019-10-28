#include "Database.h"

Database::Database()
{
    if(!fontDb.loadFromFile("fonts/Casino.ttf"))
        throw "Couldn't load the font!";
    isUsernm = false;
    isPasswd = false;
}

Database::~Database()
{

}

std::ostream& operator<<(std::ostream & output, const Database& obj)
{
    output << obj.usernameText.getString().toAnsiString() << ";" << obj.passwdText.getString().toAnsiString() << ";" << obj.creditsText.getString().toAnsiString() << ";" << "\n";
    return output;
}

/*
std::ostream& operator<<(std::ostream & output, const sf::Text txt)
{
    output << txt.getString().toAnsiString() << ";";
    output << "\n";
    return output;
}
*/

void Database::dbScreen(bool loginScreen, bool registerScreen)
{
    if(loginScreen == true)
    {
        tLoginBg.loadFromFile("images/login_bg.jpg");
        sLoginBg.setTexture(tLoginBg);
    }

    if(registerScreen == true)
    {
        tRegisterBg.loadFromFile("images/register_bg.jpg");
        sRegisterBg.setTexture(tRegisterBg);
    }

    uField.setPosition(1250, 350);
    uField.setFillColor(sf::Color::White);
    uField.setSize(sf::Vector2f(460, 80));

    pField.setPosition(1250, 500);
    pField.setFillColor(sf::Color::White);
    pField.setSize(sf::Vector2f(460, 80));

    backButton();
    sendButton(loginScreen, registerScreen);
}

void Database::formUsername(int unicode)
{
    if((((unicode >= 97) && (unicode <= 122)) || ((unicode >= 48) && (unicode <= 57))) && (usernameInput.getSize() <= 15))
        usernameInput += static_cast<char>(unicode);
    if(unicode == 8)
        usernameInput = usernameInput.substring(0, usernameInput.getSize() - 1);
    usernameText.setFont(fontDb);
    usernameText.setString(usernameInput);
    usernameText.setColor(sf::Color::Black);
    usernameText.setPosition(sf::Vector2f(1300, 370));
}

void Database::formPasswd(int unicode)
{
    if((((unicode >= 97) && (unicode <= 122)) || ((unicode >= 48) && (unicode <= 57))) && (passwdInput.getSize() <= 15))
        passwdInput += static_cast<char>(unicode);
    if(unicode == 8)
        passwdInput = passwdInput.substring(0, passwdInput.getSize() - 1);
    passwdText.setFont(fontDb);
    passwdText.setString(passwdInput);
    passwdText.setColor(sf::Color::Black);
    passwdText.setPosition(sf::Vector2f(1300, 520));
}

void Database::backButton()
{
    backBtn.setPosition(50, 940);
    backBtn.setFillColor(sf::Color(40, 20, 0));
    backBtn.setSize(sf::Vector2f(160, 80));

    backTxt.setPosition(100, 960);
    backTxt.setFont(fontDb);
    backTxt.setString("BACK");

    fieldText.setString("");
    resetField();
}

void Database::sendButton(bool loginScreen, bool registerScreen)
{
    sendBtn.setPosition(1530, 650);
    sendBtn.setFillColor(sf::Color(40, 20, 0));
    sendBtn.setSize(sf::Vector2f(180, 80));

    sendTxt.setFont(fontDb);
    if(loginScreen == true)
    {
        sendTxt.setString("LOGIN");
        sendTxt.setPosition(1585, 670);
    }

    if(registerScreen == true)
    {
        sendTxt.setString("REGISTER");
        sendTxt.setPosition(1560, 670);
    }
}

void Database::sendLogIn()
{
    isUsernm = false;
    isPasswd = false;
    searchLogin();
    passwdFromFile = "";
    textFieldLog();
    resetField();
}

void Database::sendRegister()
{
    searchLogin();

    if(isUsernm == false)
    {
        creditsText.setString("1000");

        outFile.open("files/usersDB.txt", std::fstream::app);
        Database db;

        db.usernameText = usernameText;
        db.passwdText = passwdText;
        db.creditsText = creditsText;

        outFile << db;
        outFile.close();
    }

    textFieldReg();
    resetField();

    isUsernm = false;
    isPasswd = false;
    //outFile << usernameText;
    //outFile << passwdText;

    //std::getline(outFile, usernameText.getString().toAnsiString());
}

void Database::searchLogin()
{
    inFile.open("files/usersDB.txt", std::ifstream::in);

    if (!inFile)
        throw "Error opening the file!";

    while(inFile >> std::ws, getline(inFile, usernmFromFile, ';'), getline(inFile, passwdFromFile, ';'), getline(inFile, creditsFromFile, ';'))
    {
        if(usernmFromFile == usernameText.getString().toAnsiString())
        {
            isUsernm = true;

            if(passwdFromFile == passwdText.getString().toAnsiString())
            {
                isPasswd = true;
                break;
            }
            else
                isPasswd = false;
        }
    }
    inFile.close();
}

void Database::resetField()
{
    usernameInput = usernameInput.substring(0, 0);
    passwdInput = passwdInput.substring(0, 0);
    usernameText.setString(usernameInput);
    passwdText.setString(passwdInput);
}

void Database::textFieldLog()
{
    fieldText.setFont(fontDb);
    fieldText.setPosition(1250, 600);
    fieldText.setCharacterSize(30);

    if(isUsernm == false)
    {
        fieldText.setColor(sf::Color::Red);
        fieldText.setString("There is no such username!");
    }

    if(isUsernm == true && isPasswd == false)
    {
        fieldText.setColor(sf::Color::Red);
        fieldText.setString("Wrong password!");
    }

    if(isUsernm == true && isPasswd == true)
    {
        fieldText.setColor(sf::Color(127,255,0));
        fieldText.setString("Success!");
    }
}

void Database::textFieldReg()
{
    fieldText.setFont(fontDb);
    fieldText.setPosition(1250, 600);
    fieldText.setCharacterSize(30);

    if(isUsernm == false)
    {
        fieldText.setColor(sf::Color(127,255,0));
        fieldText.setString("Success!");
    }

    if(isUsernm == true)
    {
        fieldText.setColor(sf::Color::Red);
        fieldText.setString("The username already exists!");
    }
}

void Database::loginDraw(sf::RenderWindow &window)
{
    window.draw(sLoginBg);
    window.draw(uField);
    window.draw(pField);
    window.draw(backBtn);
    window.draw(sendBtn);
    window.draw(backTxt);
    window.draw(sendTxt);
    window.draw(usernameText);
    window.draw(passwdText);
    window.draw(fieldText);
}

void Database::registerDraw(sf::RenderWindow &window)
{
    window.draw(sRegisterBg);
    window.draw(uField);
    window.draw(pField);
    window.draw(backBtn);
    window.draw(sendBtn);
    window.draw(backTxt);
    window.draw(sendTxt);
    window.draw(usernameText);
    window.draw(passwdText);
    window.draw(fieldText);
}
