#include <SFML/Graphics.hpp>
#include <ctime> // 
#include <cstdlib> // srand rand

enum class Side {LEFT,RIGHT,NONE};

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

    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");

    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/Branch.png");


    //그림 위치 출력하기

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    //spritetree.setPosition(1920*0.5-textureTree.getSize().x*0.5f,0);
    spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0.f);
    spriteTree.setPosition(1920 * 0.5f, 0.f);

    sf::Sprite spriteElement[4];
    sf::Vector2f elementDir[4];
    float elementSpeed[4];
    int cloudCount = 3;
    for (int i = 0; i < 4; i++)
    {
        {
            if (i < cloudCount)
            {
                spriteElement[i].setTexture(textureCloud);
                spriteElement[i].setPosition((float)(rand() % 1200), (float)(rand() % 250) * (i + 1));
                elementSpeed[i] = rand() / 100 + 100;
                float random = float(rand()) / RAND_MAX;
                if (random < 0.5f)
                    {
                        elementDir[i] = { 1.f,0.f };
                        spriteElement[i].setScale(-1.f, 1.f);
                    }
                else
                    {
                        elementDir[i] = { -1.f,0.f };
                        spriteElement[i].setScale(1.f, 1.f);
                    }
            }
            else
            {     
                spriteElement[i].setTexture(textureBee);
                spriteElement[i].setPosition((float)(rand() % 1200), (float)(rand() % 800) * (i + 1));
                elementSpeed[i] = rand() / 100 + 100; \
                float random = float(rand()) / RAND_MAX;
                if (random < 0.5f)
                    {
                        elementDir[i] = { 1.f,0.f };
                        spriteElement[i].setScale(-1.f, 1.f);
                    }
                else
                    {
                        elementDir[i] = { -1.f,0.f };
                        spriteElement[i].setScale(1.f, 1.f);
                    }
            }
        }
    }

    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setOrigin(textureTree.getSize().x*0.5f, texturePlayer.getSize().y);
    Side sidePlayer = Side::LEFT;



    const int NUM_BRANCHES = 6;
    sf::Sprite spriteBranch[NUM_BRANCHES];
    Side sideBranch[NUM_BRANCHES] = { Side::LEFT,Side::RIGHT,Side::NONE,
        Side::LEFT,Side::RIGHT,Side::NONE };
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setOrigin(textureTree.getSize().x*-0.5f, 0.f);
        spriteBranch[i].setPosition(1920*0.5f, i*150.f);
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
        sf::Vector2f elmentPosition[4];
        for (int i = 0; i < 4; i++)
        {
            elmentPosition[i] = spriteElement[i].getPosition();
            elmentPosition[i] += elementDir[i] * elementSpeed[i] * deltaTime;
            spriteElement[i].setPosition(elmentPosition[i]);
            if (i < cloudCount)
            {
                if (elmentPosition[i].x < -350 || elmentPosition[i].x>1920 + 350)
                {
                    float random = float(rand()) / RAND_MAX;
                    if (random < 0.5f)
                    {
                        elementDir[i] = { 1.f,0.f };
                        spriteElement[i].setScale(-1.f, 1.f);
                        spriteElement[i].setPosition(0 - 300, (float)(rand() % 250) * (i + 1));
                    }
                    else
                    {
                        elementDir[i] = { -1.f,0.f };
                        spriteElement[i].setScale(1.f, 1.f);
                        spriteElement[i].setPosition(1920 + 300, (float)(rand() % 250) * (i + 1));
                    }
                }
            }
            else
            {
                if (elmentPosition[i].x < -100 || elmentPosition[i].x>1920 + 100)
                {
                    float random = float(rand()) / RAND_MAX;
                    if (random < 0.5f)
                    {
                        elementDir[i] = { 1.f,0.f };
                        spriteElement[i].setScale(-1.f, 1.f);
                        spriteElement[i].setPosition(0 - 60, (float)(rand() % 800) * (i + 1));
                    }
                    else
                    {
                        elementDir[i] = { -1.f,0.f };
                        spriteElement[i].setScale(1.f, 1.f);
                        spriteElement[i].setPosition(1920 + 60, (float)(rand() % 800) * (i + 1));
                    }
                }

            }
        }


        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            switch (sideBranch[i])
            {
                 case Side::LEFT:
                 {
                     spriteBranch[i].setScale(1.f, 1.f);
                     break;
                 }
                 case Side::RIGHT:
                 {
                     spriteBranch[i].setScale(-1.f, 1.f);
                     break;
                 }
            }
        }

        switch(sidePlayer)
        {
            case Side::LEFT:
            {
                spritePlayer.setScale(-1.f, 1.f);
                spritePlayer.setPosition(1920 * 0.3f, 900.f);
                break;
            }
            case Side::RIGHT:
            {
                spritePlayer.setScale(1.f, 1.f);
                spritePlayer.setPosition(1920 * 0.7f, 900.f);
                break;
            }
        }
        

        

        //그리기
        window.clear();
        window.draw(spriteBackground);

        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteElement[i]);
        }

        window.draw(spriteTree);

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            if (sideBranch[i] != Side::NONE)
            {
                window.draw(spriteBranch[i]);
            }
        }

        for (int i = 3; i < 4; i++)
        {
            window.draw(spriteElement[i]);
        }

        window.draw(spritePlayer);
  
        window.display();
       
    }

    return 0;
}