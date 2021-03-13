#include <SFML/Graphics.hpp>

using namespace sf;


int ground = 295;


const int H = 12;
const int W = 40;


String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                   B   BBB",
"B                               BB     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB       BBBB           B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};





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

    void Collision(int temp);

};

Player::Player(Texture& image)
{
    sprite.setTexture(image);
    rect = FloatRect(7 * 32, 9 * 32, 50, 50);
    sprite.setTextureRect(IntRect(10,10,50,50)); // начальная отрисовка
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



            if (dx > 0) sprite.setTextureRect(IntRect(70 * int(currentFrame), 0, 70, 70)); // замена картинки пр движении
            if (dx < 0) sprite.setTextureRect(IntRect(70 * int(currentFrame) + 70, 0, -70, 70));
        sprite.setPosition(rect.left, rect.top);
        dx = 0;
   
}


void Player::Collision(int temp) {

    {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
            {
                if (TileMap[i][j] == 'B')
                {
                    if ((dx > 0) && (temp == 0)) rect.left = j * 32 - rect.width;
                    if ((dx < 0) && (temp == 0)) rect.left = j * 32 + 32;
                    if ((dy > 0) && (temp == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
                    if ((dy < 0) && (temp == 1)) { rect.top = i * 32 + 32;   dy = 0; }
                }
                    
                if (TileMap[i][j] == '0')
                {
                    TileMap[i][j] = ' ';
                }

            }

    }
}







int main()
{
    RenderWindow window(sf::VideoMode(1280, 400), "casper game"); // создание окна 
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);


    Texture t; 
    t.loadFromFile("myhero.png"); // загрузка картинки
    //t.setTextureRect(IntRect(0,0, 183, 167));
    float currentFrame = 0; // скорость анимации


    //Sprite s; 
    //s.setTexture(t); // sprite = texture + rect
    //s.setTextureRect(IntRect(359,0,182,167)); // устанавливаем координаты анимации
    //s.setPosition(50, 100);


    Player p(t);
    Clock clock;
    RectangleShape rectangle(Vector2f(32, 32));


    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); // запись времени для гладкой отрисовки картинки
        clock.restart();

        time = time / 700;




        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (Keyboard:: isKeyPressed(Keyboard::Left)) 
        {

           p.dx = -0.1;

            //s.move(-0.5 * time, 0);
            //currentFrame += 0.015 * time; 
            //if (currentFrame > 2)currentFrame -= 2;
            //{
            //    s.setTextureRect(IntRect(182 * int(currentFrame)+182, 0, -182, 167)); // отзеркаливание картинки для левого перемещения
            //}
        }


        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            p.dx = 0.1;

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
                 p.dy = -0.35;
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


        window.clear(Color::Magenta);




        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
            {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);

                if (TileMap[i][j] == '0')  rectangle.setFillColor(Color::Green);

                if (TileMap[i][j] == ' ') continue;

                rectangle.setPosition(j * 32 , i * 32 );
                window.draw(rectangle);

            }
        }

         //window.draw(s); // рисование sprite

        window.draw(p.sprite); // рисование sprite
        window.display();
    }

    return 0;
}