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
        spriteCloud[i].setPosition((float)(rand() % 1200)*i, (float)(rand() % 250)*i);
    }
    sf::Vector2f spriteDir = {1.f,0.f};
    float CloudSpeed1 = rand() % 100 + 100;
    float random = rand() / RAND_MAX;
    for (int i = 0; i < 3; i++)
    {
        if (random < 0.5f)
        {
            spriteDir.x = 1;
            spriteCloud[i].setScale(-1.f, 1.f);
        }
        else
        {
            spriteDir.x = -1;
            spriteCloud[i].setScale(1.f, 1.f);
        }
    }

    sf::Sprite spriteBee;
    

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

       


        //그리기
        window.clear();
        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloud[i]);
        }
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }

    return 0;
}