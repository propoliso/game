#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#pragma once

using namespace sf;

void menu(RenderWindow& window) {

    Music music;//создаем объект музыки
    music.openFromFile("musicchild.ogg");//загружаем файл
    music.play();//воспроизводим музыку

    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("menu.png");
    menuTexture2.loadFromFile("menu.png");
    menuTexture3.loadFromFile("menu.png");
    aboutTexture.loadFromFile("about.png");
    menuBackground.loadFromFile("back.png");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menuBg.setPosition(0, 0);

    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {

        if (IntRect(346, 150, 259, 105).contains(Mouse::getPosition(window))) { menu1.setColor(Color::White); menuNum = 1; }
        if (IntRect(347, 263, 261, 80).contains(Mouse::getPosition(window))) { menu2.setColor(Color::White); menuNum = 2; }
        if (IntRect(350, 350, 254, 88).contains(Mouse::getPosition(window))) { menu3.setColor(Color::White); menuNum = 3; }


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
            if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
}