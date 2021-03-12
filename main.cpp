#include <SFML/Graphics.hpp>

using namespace sf;




int ground = 700;
class Player
{
public:
    float dx, dy; // скорость 
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    Player(Texture& image);

    ~Player();

    void update(float time);
private:

};

Player::Player(Texture& image)
{
    sprite.setTexture(image);
    rect = FloatRect(0,0,183,176);
    sprite.setTextureRect(IntRect(0,0,183,162));
    dx = dy = 0;
    currentFrame = 0;

}

Player::~Player()
{
}

void Player::update(float time) // гравитация 
{
    rect.left += dx * time;

    if (!onGround) dy = dy + 0.0015*time;
    
        rect.top += dy * time;
        onGround = false;

        if (rect.top > ground) {    
            rect.top = ground;
            dy = 0;
            onGround = true;
        }
        

            currentFrame += 0.015 * time;
            if (currentFrame > 2) currentFrame -= 2;


            
      /*  int    x1 =0;
        int    x2 = 182;
        int y1 = 20;
            int y2 = 167;
            if(dy>0)
            sprite.setTextureRect(IntRect(x1, y1, x2, y2));*/



          if (dx > 0)  sprite.setTextureRect(IntRect(182 * int(currentFrame), 0, 182, 167)); // сдвиг картинки на 182 - анимация
    
           if (dx < 0)  sprite.setTextureRect(IntRect(182 * int(currentFrame)+182, 0, -182, 167)); // сдвиг картинки на 182 - анимация

         
            
      
        

        sprite.setPosition(rect.left, rect.top);
        dx = 0;
    

}







int main()
{
    RenderWindow window(sf::VideoMode(1000, 1000), "casper game"); // создание окна 
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);



    Texture t; 

    t.loadFromFile("myhero.png"); // загрузка картинки
    //t.setTextureRect(IntRect(0,0, 183, 167));
    float currentFrame = 0; // скорость анимации



    Player p(t);


    //Sprite s; 
    //s.setTexture(t); // sprite = texture + rect
    //s.setTextureRect(IntRect(359,0,182,167)); // устанавливаем координаты анимации
    //s.setPosition(50, 100);



    Clock clock;

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); // запись времени для гладкой отрисовки картинки
        clock.restart();

        time = time / 1500;




        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (Keyboard:: isKeyPressed(Keyboard::Left)) 
        {


           p.dx = -0.5;



            //s.move(-0.5 * time, 0);
            //currentFrame += 0.015 * time; 
            //if (currentFrame > 2)currentFrame -= 2;
            //{
            //    s.setTextureRect(IntRect(182 * int(currentFrame)+182, 0, -182, 167)); // отзеркаливание картинки для левого перемещения
            //}
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {


            p.dx = 0.5;


            //s.move(0.5 * time, 0);
            //currentFrame += 0.015 * time;
            //if (currentFrame > 2)currentFrame -= 2;
            //{
            //    s.setTextureRect(IntRect(182*int(currentFrame), 0, 182, 167)); // сдвиг картинки на 182 - анимация
            //}
        }

         if (Keyboard::isKeyPressed(Keyboard::Up))
        {


             if (p.onGround)
             {
                 p.dy = -0.90;
                 p.onGround = false;
                 //fs
             }
           // s.move(0, -0.5 * time);
        }



       /*  if (Keyboard::isKeyPressed(Keyboard::Down))
         {
             s.move(0, 0.5 * time);
         }*/


         p.update(time);


        window.clear(Color::White);


    //  window.draw(s); // рисование sprite

        window.draw(p.sprite); // рисование sprite
        window.display();
    }

    return 0;
}