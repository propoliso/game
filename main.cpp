


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include "./Header.h"
#include <sstream>


using namespace sf;


int ground = 295;
float offsetX = 0, offsetY = 0;
double torch = 1;
const int H = 18;
const int W = 150;

String TileMap[H] = {


"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                   0",
"0                                                                                                                                                   0",
"0       s                                                                                                                                           0",
"0                                                                                                                                                   0",
"0F                                                                                                                                                  0",
"000                                                                                                                                                 0",
"0                  0              g 0                                         222                     22       2     2     2222222                  0",
"0                                                    0000                    2   2     2      2      2  2      2     2    2      2                  0",
"0                                                                     0      2       22222  22222   2    2     2     2    2 222222       d          0",
"0                                                                    00      2         2      2    22222222    2222222     2     2                  0",
"0                                                                   0000     2   2                2        2   2     2    2      2                  0",
"0                                                                  000000     222                2          2  2     2   2       2                  0",
"0                                                                 00000000                                                                          0",
"0                       FF                                       0000000000               O                                                         0",
"0                                                             00000000000000                                                                        0",
"0                                                           000000000000000000000                                                                   0",
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",


};







class Player
{
public:
    float dx, dy; // скорость 
    FloatRect rect;
    bool onGround;
    bool life;
    Sprite sprite;
    float currentFrame;

    Player(Texture& image);
    ~Player();
    void update(float time);

    void Collision(int temp);

    


};

Player::Player(Texture& image)
{
    sprite.setTexture(image);
    rect = FloatRect(7 * 32, 9 * 32, 70, 70);
    sprite.setTextureRect(IntRect(10,0,70,70)); // начальная отрисовка
    dx = dy = 0.1;
    currentFrame = 0;

}

Player::~Player()
{
}


void Player::update(float time) // гравитация 
{
    rect.left += dx * time;//движение dx
    if (!onGround) dy = dy + 0.0005*time;
    Collision(0);

        rect.top += dy * time;
        onGround = false;
        Collision(1);

       /* if (rect.top > ground) {    
            rect.top = ground;
            dy = 0;
            onGround = true;
        }*/
        

            currentFrame += 0.005 * time;
            if (currentFrame > 2) currentFrame -= 2;


            
      /*  int    x1 =0;
        int    x2 = 182;
        int y1 = 20;
            int y2 = 167;
            if(dy>0)
            sprite.setTextureRect(IntRect(x1, y1, x2, y2));*/


            if (!life)sprite.setTextureRect(IntRect(174, 0, 85, 70));
            if (dx > 0) sprite.setTextureRect(IntRect(85 * int(currentFrame), 0, 85, 70)); // замена картинки пр движении
            if (dx < 0) sprite.setTextureRect(IntRect(85 * int(currentFrame) + 85, 0, -85, 70));
        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
        dx = 0;
   
}


void Player::Collision(int temp) {
    {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
            {
               


                if (TileMap[i][j] == '0')
                {
                    if ((dx > 0) && (temp == 0)) rect.left = j * 32 - rect.width;
                    if ((dx < 0) && (temp == 0)) rect.left = j * 32 + 32;
                    if ((dy > 0) && (temp == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
                    if ((dy < 0) && (temp == 1)) { rect.top = i * 32 + 32;   dy = 0; }
                }
            

                  


                if (TileMap[i][j] == 'F')
                {
                    TileMap[i][j] = ' ';
                    torch+=0.50;

                }


            }

    }
}


















class Enemy
{
public:
    float dx, dy; // скорость 
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;

    Enemy();
    ~Enemy();
    void set(Texture& image, int x, int y);
    void Collision();
    void update(float time);
    void  update(float time, Enemy& monsters);
};

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::set( Texture& image, int x, int y)
{
    sprite.setTexture(image);
    rect = FloatRect(x, y, 32, 32);
  //  sprite.setTextureRect(IntRect(55, 0, 85, 71)); // начальная отрисовка

    dx = 0.05;
    currentFrame = 0;
    life = true;




}

void Enemy::update(float time)
{
    rect.left += dx * time;

    Collision();


    currentFrame += time * 0.005;
    if (currentFrame > 2) currentFrame -= 2;
    sprite.setTextureRect(IntRect(80 * int(currentFrame), 0, 80, 70)); // замена картинки пр движении
    if (!life) sprite.setTextureRect(IntRect(165, 0, 80, 70));
    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);


}
void Enemy::update(float time, Enemy&monsters)
{
    rect.left += dx * time;

    Collision();


    currentFrame += time * 0.005;
    if (currentFrame > 2) currentFrame -= 2;
    monsters. sprite.setTextureRect(IntRect(125 * int(currentFrame), 0, 121,70 )); // замена картинки пр движении
    if (!life) sprite.setTextureRect(IntRect(165, 0, 80, 70));
    monsters. sprite.setPosition(rect.left - offsetX, rect.top - offsetY);


}



void Enemy :: Collision()
{

    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
            if (TileMap[i][j] == '0')
            {
                if (dx > 0)
                {
                    rect.left = j * 32 - rect.width; dx *= -1;
                }
                else if (dx < 0)
                {
                    rect.left = j * 32 + 32;  dx *= -1;
                }

            }
}






void fight(Player& player, Enemy& monster) {
 
    if (player.life)
    {
        if (player.rect.intersects(monster.rect))
        {
            if (monster.life) {
                if (player.dy > 0) {
                    monster.dx = 0;
                    player.dy = -0.2;
                    monster.life = false;
                }
                else
                {
                  

                        torch -= 0.01;
                        if (torch < 0)
                        {
                            player.life = false;
                            torch = 0;
                        }
                    
                }
            }
        }
    }
}

















int main()
{
    RenderWindow window(sf::VideoMode(1000, 800), "scribble game"); // создание окна 
    menu(window);
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    

    Texture tileSet;
    tileSet.loadFromFile("v1.png");


    Texture tileSet2;
    tileSet2.loadFromFile("monsters.png");


    Texture tileSet3;
    tileSet3.loadFromFile("warior.png");


    Texture t; 
    t.loadFromFile("casper.png"); // загрузка картинки
   // t.setTextureRect(IntRect(0,0, 183, 167));
    float currentFrame = 0; // скорость анимации


    Music music;//создаем объект музыки
    music.openFromFile("music.ogg");//загружаем файл
    music.play();//воспроизводим музыку


    //Sprite s; 
    //s.setTexture(t); // sprite = texture + rect
    //s.setTextureRect(IntRect(359,0,182,167)); // устанавливаем координаты анимации
    //s.setPosition(50, 100);

    Enemy monsters;
    monsters.set(tileSet2, 30 * 32, 15 * 32);
    Enemy monsters2;
    monsters2.set(tileSet2, 32 * 32, 12 * 32);
    Enemy monsters3;
    monsters3.set(tileSet3, 5 * 32, 5 * 32);


    Player p(t);
    Clock clock;
   // RectangleShape rectangle(Vector2f(32, 32));

    Sprite tile(tileSet);













            Font font;
            	font.loadFromFile("sansation.ttf");
            
            	Text mytext("Hello!", font, 50);
            	mytext.setFillColor(sf::Color::Red);
            	mytext.setPosition(10, 10);
            
                


    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); // запись времени для гладкой отрисовки картинки
        clock.restart();

        time = time / 400;




        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (p.life)
        {



            if (Keyboard::isKeyPressed(Keyboard::A))
            {

                p.dx = -0.1;

                if (Keyboard::isKeyPressed(Keyboard::RShift))
                {
                    p.dx = -0.5;


                }

                //s.move(-0.5 * time, 0);
                //currentFrame += 0.015 * time; 
                //if (currentFrame > 2)currentFrame -= 2;
                //{
                //    s.setTextureRect(IntRect(182 * int(currentFrame)+182, 0, -182, 167)); // отзеркаливание картинки для левого перемещения
                //}
            }


            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                p.dx = 0.1;
                if (Keyboard::isKeyPressed(Keyboard::LShift))
                {
                    p.dx = 0.5;


                }

                //s.move(0.5 * time, 0);
                //currentFrame += 0.015 * time;
                //if (currentFrame > 2)currentFrame -= 2;
                //{
                //    s.setTextureRect(IntRect(182*int(currentFrame), 0, 182, 167)); // сдвиг картинки на 182 - анимация
                //}
            }







            if (Keyboard::isKeyPressed(Keyboard::W))
            {

                if (p.onGround)
                {
                    p.dy = -0.35;
                    p.onGround = false;
                    //fs
                }
                // s.move(0, -0.5 * time);
             //}  if (Keyboard::isKeyPressed(Keyboard::Up))
             //{

             //    if (p.onGround)
             //    {
             //        p.dy = -0.35;
             //        p.onGround = false;
             //        //fs
             //    }
             //    // s.move(0, -0.5 * time);
             //}
            }
        }


       /*  if (Keyboard::isKeyPressed(Keyboard::Down))
         {
             s.move(0, 0.5 * time);
         }*/


         p.update(time);
         monsters.update(time);
         monsters2.update(time);
         monsters3.update(time, monsters3);




         offsetX = p.rect.left - 1000/2; // привязка камеры 
         offsetY = p.rect.top- 800 /2;


        // window.clear(Color(128, 128, 128));
         window.clear(Color::White);




        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
            {
                if (TileMap[i][j] == '0')  tile.setTextureRect(IntRect(0, 0, 32, 32));

                if (TileMap[i][j] == 'F')  tile.setTextureRect(IntRect(38, 2, 9, 32));

                if (TileMap[i][j] == '2')  tile.setTextureRect(IntRect(58, 0, 32, 32));

                if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(15, 68, 251, 148));

                if (TileMap[i][j] == 's')  tile.setTextureRect(IntRect(254, 216, 364, 264));

                if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(287, 0, 353, 230));

                if (TileMap[i][j] == 'O')  tile.setTextureRect(IntRect(61, 228, 70, 114));








                if (TileMap[i][j] == ' ') continue;

              //  if (TileMap[i][j] == '1')  rectangle.setFillColor(Color::Green);

              //  if (TileMap[i][j] == ' ') continue;

                

                tile.setPosition(j * 32 - offsetX , i * 32 - offsetY );
                window.draw(tile);





                

              
            }
        }



        fight(p,monsters);
      
        fight(p, monsters2);

        fight(p, monsters3);


         //window.draw(s); // рисование sprite

        Text mytext("Hello!", font, 50);
        mytext.setFillColor(sf::Color::Black);
        mytext.setPosition(10, 10);
        std::ostringstream ss;    // #include <sstream>
        ss << torch;
        mytext.setString(ss.str());
        window.draw(mytext);

        window.draw(p.sprite); // рисование sprite
        window.draw(monsters.sprite);      
        window.draw(monsters2.sprite);
        window.draw(monsters3.sprite);




        window.display();
    }

    return 0;
}