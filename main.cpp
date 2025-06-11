#include <SFML/Graphics.hpp>
#include <ctime> // 
#include <cstdlib> // srand rand

int main()
{
    srand((int)time(0));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

    //그림 불러오기

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
  
    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");


    //그림 위치 출력하기

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    //spritetree.setPosition(1920*0.5-textureTree.getSize().x*0.5f,0);
    spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
    spriteTree.setPosition(1920 * 0.5f, 0.f);


    sf::Sprite spriteCloud[3];
    for (int i = 0; i < 3; i++)
    {
        spriteCloud[i].setTexture(textureCloud);
        spriteCloud[i].setPosition((float)(rand() % 1200), (float)(rand() % 250)* (i + 1));
    }
    sf::Vector2f cloudDir[3];
    float cloudSpeed[3];
    for (int i = 0; i < 3; i++)
    {
        cloudSpeed[i] = rand() / 100 + 100;\
        float random = float(rand()) / RAND_MAX;
        if (random < 0.5f)
        {
            cloudDir[i] = { 1.f,0.f };
            spriteCloud[i].setScale(-1.f, 1.f);
        }
        else
        {
            cloudDir[i] = { -1.f,0.f };
            spriteCloud[i].setScale(1.f, 1.f);
        }
    }

    sf::Sprite spriteBee[2];
    for (int i = 0; i < 2; i++)
    {
        spriteBee[i].setTexture(textureBee);
        spriteBee[i].setPosition((float)(rand() % 1200), (float)(rand() % 800) * (i + 1));
    }
    sf::Vector2f BeeDir[2];
    float BeeSpeed[2];
    for (int i = 0; i < 2; i++)
    {
        BeeSpeed[i] = rand() / 100 + 100; \
        float random = float(rand()) / RAND_MAX;
        if (random < 0.5f)
        {
            BeeDir[i] = { 1.f,0.f };
            spriteBee[i].setScale(-1.f, 1.f);
        }
        else
        {
            BeeDir[i] = { -1.f,0.f };
            spriteBee[i].setScale(1.f, 1.f);
        }
    }

    sf::Clock clock; //스탑워치


    while (window.isOpen()) //윈도우 창에 띄우기
    {
        sf::Time time = clock.restart();
        float deltaTime = time.asSeconds();


        //이벤트 루프
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 업데이트
        sf::Vector2f cloudPosition[3];
        for (int i = 0; i < 3; i++)
        {
            cloudPosition[i] = spriteCloud[i].getPosition();
            cloudPosition[i] += cloudDir[i] * cloudSpeed[i] * deltaTime;
            spriteCloud[i].setPosition(cloudPosition[i]);
        
            if (cloudPosition[i].x < -350 || cloudPosition[i].x>1920 + 350)
            {
                float random = float(rand()) / RAND_MAX;
                if (random < 0.5f)
                {
                    cloudDir[i] = { 1.f,0.f };
                    spriteCloud[i].setScale(-1.f, 1.f);
                    spriteCloud[i].setPosition(0-300, (float)(rand() % 250) * (i + 1));
                }
                else
                {
                    cloudDir[i] = { -1.f,0.f };
                    spriteCloud[i].setScale(1.f, 1.f);
                    spriteCloud[i].setPosition(1920 + 300, (float)(rand() % 250) * (i + 1));
                }
            }
        }

        sf::Vector2f BeePosition[2];
        for (int i = 0; i < 2; i++)
        {
            BeePosition[i] = spriteBee[i].getPosition();
            BeePosition[i] += BeeDir[i] * BeeSpeed[i] * deltaTime;
            spriteBee[i].setPosition(BeePosition[i]);

            if (BeePosition[i].x < -100 || BeePosition[i].x>1920 + 100)
            {
                float random = float(rand()) / RAND_MAX;
                if (random < 0.5f)
                {
                    BeeDir[i] = { 1.f,0.f };
                    spriteBee[i].setScale(-1.f, 1.f);
                    spriteBee[i].setPosition(0 - 60, (float)(rand() % 800)* (i+1));
                }
                else
                {
                    BeeDir[i] = { -1.f,0.f };
                    spriteBee[i].setScale(1.f, 1.f);
                    spriteBee[i].setPosition(1920 + 60, (float)(rand() % 800) * (i + 1));
                }
            }
        }


        //그리기
        window.clear();
        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloud[i]);
        }
        window.draw(spriteTree);
        for (int i = 0; i < 2; i++)
        {
            window.draw(spriteBee[i]);
        }
        window.display();
    }

    return 0;
}