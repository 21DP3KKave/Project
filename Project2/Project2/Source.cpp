#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
bool lose = false;
struct point
{
    int x, y;
};

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(400, 533), "Doodle Game!");
    window.setFramerateLimit(60);

    Texture texture1, texture2, texture3, texture4;
    texture1.loadFromFile("background.png");
    texture2.loadFromFile("platform.png");
    texture3.loadFromFile("doodle.png");
    texture4.loadFromFile("youlose.png");

    Sprite sBackground(texture1), sPlat(texture2), sPers(texture3), sLose(texture4);

    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

        dy += 0.2;
        y += dy;
        if (y > 500)  lose =true;

        if (y < h)
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
            }

        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

        sPers.setPosition(x, y);
        if (lose == true) {
            window.draw(sLose);
        }
        else {
            window.draw(sBackground);
            window.draw(sPers);
            for (int i = 0; i < 10; i++)
            {
                sPlat.setPosition(plat[i].x, plat[i].y);
                window.draw(sPlat);
            }
        }
        window.display();
    }

    return 0;
}
