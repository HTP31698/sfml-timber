#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime> // 
#include <cstdlib> // srand rand


enum class Side { LEFT, RIGHT, NONE };

void updateBranches(Side* branches, int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		branches[i] = branches[i - 1];
	}
	int r = rand() % 3;
	switch (r)
	{
	case 0:
		branches[0] = Side::LEFT;
		break;
	case 1:
		branches[0] = Side::RIGHT;
		break;
	case 2:
		branches[0] = Side::NONE;
		break;
	}

}



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

	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");

	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");

	//폰트 불러오기

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//사운드 불러오기

	sf::SoundBuffer bufferChop;
	bufferChop.loadFromFile("sound/chop.wav");
	sf::SoundBuffer bufferDeath;
	bufferDeath.loadFromFile("sound/death.wav");
	sf::SoundBuffer bufferOut_of_time;
	bufferOut_of_time.loadFromFile("sound/out_of_time.wav");



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
	spritePlayer.setOrigin(textureTree.getSize().x * 0.5f, texturePlayer.getSize().y);
	Side sidePlayer = Side::LEFT;


	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setOrigin(texturePlayer.getSize().x, texturePlayer.getSize().y);
	Side sideAxe = Side::NONE;


	const int NUM_BRANCHES = 6;
	sf::Sprite spriteBranch[NUM_BRANCHES];
	Side sideBranch[NUM_BRANCHES];
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		spriteBranch[i].setTexture(textureBranch);
		spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);
		spriteBranch[i].setPosition(1920 * 0.5f, i * 150.f);

		int r = rand() % 3;
		switch (r)
		{
		case 0:
			sideBranch[i] = Side::LEFT;
			break;
		case 1:
			sideBranch[i] = Side::RIGHT;
			break;
		case 2:
			sideBranch[i] = Side::NONE;
			break;
		}
		if (sideBranch[NUM_BRANCHES - 1] == sidePlayer)
		{
			sideBranch[NUM_BRANCHES - 1] = Side::NONE;
		}

	}
	const int NUM_LOG = 6;
	bool isActiveTestLog[NUM_LOG];
	sf::Sprite testLog[NUM_LOG]; //
	sf::Vector2f testLogDir[NUM_LOG]; //
	sf::Vector2f gravity[NUM_LOG]; //
	float testLogSpeed[NUM_LOG]; //
	sf::Vector2f testLogVelocity[NUM_LOG]; //
	for (int i = 0; i < NUM_LOG; i++)
	{

		testLog[i].setTexture(textureLog);
		testLog[i].setOrigin(textureLog.getSize().x * 0.5f, textureLog.getSize().y);
		testLog[i].setPosition(spriteTree.getPosition().x, textureTree.getSize().y);
		isActiveTestLog[i] = false;
		testLogSpeed[i] = rand() / 100 + 1000;
		testLogDir[i] = { 1.f,-1.f };
		gravity[i] = { 0, 3000.f };
		testLogVelocity[i] = testLogDir[i] * testLogSpeed[i];

	}
	int currentLogIndex = 0;

	//UI
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString("SCORE: 0");
	textScore.setCharacterSize(70);
	textScore.setFillColor(sf::Color::Cyan);
	textScore.setPosition(20, 20);

	sf::Text textStart;
	textStart.setFont(font);
	textStart.setString("");
	textStart.setCharacterSize(100);
	textStart.setFillColor(sf::Color::Yellow);
	textStart.setPosition(1920 * 0.2f, 1080 * 0.4f);
	sf::Vector2f textStartOrigin;
	textStartOrigin.x = textStart.getLocalBounds().width * 0.5f;


	sf::Text textRestart;
	textRestart.setFont(font);
	textRestart.setString("");
	textRestart.setCharacterSize(100);
	textRestart.setFillColor(sf::Color::Yellow);
	textRestart.setPosition(1920 * 0.2f, 1080 * 0.4f);

	sf::Text textStop;
	textStop.setFont(font);
	textStop.setString("");
	textStop.setCharacterSize(100);
	textStop.setFillColor(sf::Color::Yellow);
	textStop.setPosition(1920 * 0.2f, 1080 * 0.4f);

	sf::RectangleShape timeBar;
	float timeBarWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize({ timeBarWidth, timeBarHeight });
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition(1920 * 0.5f - timeBarWidth * 0.5f, 1080.f - 100.f);

	//sound
	sf::Sound soundChop;
	soundChop.setBuffer(bufferChop);
	sf::Sound soundDeath;
	soundDeath.setBuffer(bufferDeath);
	sf::Sound soundOut_of_time;
	soundOut_of_time.setBuffer(bufferOut_of_time);





	// 게임 데이터
	int score = 0;
	float remaingTime = 5.f;
	float timeBarSpeed = timeBarWidth / 5.f;

	//스탑워치
	sf::Clock clock;


	bool isLeft = false; //키 입력 확인
	bool isRight = false;
	bool crash = true;
	bool retry = false;
	while (window.isOpen()) //윈도우 창에 띄우기
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();


		//이벤트 루프 //키 입력
		sf::Event event;
		bool isLeftDown = false; //키 입력 확인
		bool isRightDown = false;
		bool isLeftUp = false;
		bool isRightUp = false;

		//메인 루프

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					if (!isLeft)
					{
						isLeftDown = true;
					}
					isLeft = true;
					break;
				case sf::Keyboard::Right:
					if (!isRight)
					{
						isRightDown = true;
					}
					isRight = true;
					break;
				case sf::Keyboard::Enter:
					textStart.setString("");
					if (crash == true)
					{
						textRestart.setString("");
						textStop.setString("");
					}
					else
					{
						if (remaingTime == 0.f || sidePlayer == sideBranch[NUM_BRANCHES - 1])
						{
							score = 0;
							textScore.setString("SCORE: " + std::to_string(score));
							remaingTime = 5.f;
							timeBar.setSize({ timeBarWidth, timeBarHeight });
							updateBranches(sideBranch, NUM_BRANCHES);
							updateBranches(sideBranch, NUM_BRANCHES);
							updateBranches(sideBranch, NUM_BRANCHES);
							updateBranches(sideBranch, NUM_BRANCHES);
							updateBranches(sideBranch, NUM_BRANCHES);
							updateBranches(sideBranch, NUM_BRANCHES);
							sideBranch[NUM_BRANCHES - 1] = Side::NONE;
						}
					}
					crash = true;
					retry = true;
					break;
				case sf::Keyboard::Escape:
					textStop.setString("Press Enter to resume!");
					textRestart.setString("");
					crash = false;
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					isLeft = false;
					isLeftUp = true;
					break;
				case sf::Keyboard::Right:
					isRight = false;
					isRightUp = true;
					break;
				}
			}
		}




		
		// 업데이트
		if (crash == true)
		{

			if (retry == false)
			{
				textStart.setString("Press Enter to start!");
				crash = false;
			}


			remaingTime -= deltaTime;
			if (remaingTime < 0.f)
			{
				soundOut_of_time.play();
				remaingTime = 0.f;
				textRestart.setString("Press Enter to restart");
				textStop.setString("");
				crash = false;
			}
			timeBar.setSize({ timeBarSpeed * remaingTime,timeBarHeight });

			if (isRightDown || isLeftDown)
			{
				if (isLeftDown)
				{
					sidePlayer = Side::LEFT;
					sideAxe = Side::LEFT;
					for (int i = 0; i < NUM_LOG; i++)
					{
						testLogDir[i] = {1.f,-1.f};
					}
				}
				if (isRightDown)
				{
					sidePlayer = Side::RIGHT;
					sideAxe = Side::RIGHT;
					for (int i = 0; i < NUM_LOG; i++)
					{
						testLogDir[i] = { -1.f,-1.f };
					}

				}
				updateBranches(sideBranch, NUM_BRANCHES);
				if (sidePlayer == sideBranch[NUM_BRANCHES - 1])
				{
					soundDeath.play();
					textRestart.setString("Press Enter to restart");
					textStop.setString("");
					crash = false;
				}
				else
				{
					soundChop.play();
					score += 10;
					remaingTime += 0.2;
					textScore.setString("SCORE: " + std::to_string(score));

					isActiveTestLog[currentLogIndex] = true;
					testLog[currentLogIndex].setPosition(spriteTree.getPosition().x, textureTree.getSize().y);
					testLogVelocity[currentLogIndex] = testLogDir[currentLogIndex] * testLogSpeed[currentLogIndex];
					++currentLogIndex;
					if (currentLogIndex == NUM_LOG)
					{
						currentLogIndex = 0;
					}
					
				}

			}

			if (crash == false)
			{
				for (int i = 0; i < NUM_LOG; i++)
				{
					isActiveTestLog[i] = false;
				}
			}


			if (isRightUp || isLeftUp)
			{
				if (isRightUp)
				{
					sideAxe = Side::NONE;
				}
				if (isLeftUp)
				{
					sideAxe = Side::NONE;
				}
			}




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
					spriteBranch[i].setScale(-1.f, 1.f);
					break;
				case Side::RIGHT:
					spriteBranch[i].setScale(1.f, 1.f);
					break;
				}
			}


			switch (sidePlayer)
			{
			case Side::LEFT:
				spritePlayer.setScale(-1.f, 1.f);
				spritePlayer.setPosition(spriteTree.getPosition().x - 400.f, 900.f);
				spriteAxe.setScale(-1.f, 1.f);
				spriteAxe.setPosition(spritePlayer.getPosition().x + 120, 1000.f);
				break;

			case Side::RIGHT:
				spritePlayer.setScale(1.f, 1.f);
				spritePlayer.setPosition(spriteTree.getPosition().x + 400.f, 900.f);
				spriteAxe.setScale(1.f, 1.f);
				spriteAxe.setPosition(spritePlayer.getPosition().x - 120, 1000.f);
				break;
			}
			sf::Vector2f position[NUM_LOG];

			for (int i = 0; i < NUM_LOG; i++)
			{
				if (isActiveTestLog[i] == true)
				{
					testLogVelocity[i] += gravity[i] * deltaTime;
					position[i] = testLog[i].getPosition();
					position[i] += testLogVelocity[i] * deltaTime;
					testLog[i].setPosition(position[i]);
				}
			}
		}







		//그리기
		window.clear();

		window.draw(textStart);

		//WORLD
		window.draw(spriteBackground);

		for (int i = 0; i < 3; i++)
		{
			window.draw(spriteElement[i]);
		}

		window.draw(spriteTree);
		for (int i = 0; i < NUM_LOG; i++)
		{
			if (isActiveTestLog[i] != false)
			{
				window.draw(testLog[i]);
			}
		}

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

		if (sideAxe != Side::NONE)
		{
			window.draw(spriteAxe);
		}

		//UI
		window.draw(textScore);

		window.draw(textStart);

		if (crash == false)
		{

			window.draw(textRestart);

			window.draw(textStop);
		}



		window.draw(timeBar);

		window.display();

	}


	return 0;
}