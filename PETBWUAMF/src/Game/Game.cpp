#include "Game.h"


void Game::init (const nlohmann::json & settingFile)
{
}

Game::Game()
{
	canv = new Canvas();
	canv->setPosition(500, 0);

	canv2 = new Canvas();
	canv2->setPosition(500, 768);

	sf::Image i;

	TextArea * a = new TextArea{};
	a->setText("testtest\n testt\nerfwefwefwe\nwefwefwe\nwefwefwak bardzo test\n jak\n widaæ\n ten\n tekst \n mo¿na skro\nll\nowaæ\n\n\n\n\n\n\n :D");
	sf::Font *f = new sf::Font;
	f->loadFromFile("data/fonts/arial.ttf");
	a->setFont(f);
	a->setAlaign(TextArea::Alaign::Center);
	a->setFontColor(sf::Color::Black);

	TextArea * a2 = new TextArea{};
	a2->setText("Pierwsza opcja");
	a2->setFont(f);
	a2->setFontColor(sf::Color::Black);

	TextArea * a3 = new TextArea{};
	a3->setText("Testowa opcja 2");
	a3->setFont(f);
	a3->setFontColor(sf::Color::Black);

	TextArea * a4 = new TextArea{};
	a4->setText("Testowa opcja 3");
	a4->setFont(f);
	a4->setFontColor(sf::Color::Black);

	TextArea * a5 = new TextArea{};
	a5->setText("Najlepsza opcja");
	a5->setFont(f);
	a5->setFontColor(sf::Color::Black);


	i.loadFromFile("data/graphix/testImages/storyArea/arrowBot.bmp");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * t1 = new sf::Texture;
	t1->loadFromImage(i);
	i.loadFromFile("data/graphix/testImages/storyArea/arrowTop.bmp");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * t2 = new sf::Texture;
	t2->loadFromImage(i);
	i.loadFromFile("data/graphix/testImages/storyArea/scrbut.bmp");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * t3 = new sf::Texture;
	t3->loadFromImage(i);
	i.loadFromFile("data/graphix/testImages/storyArea/scrbck.bmp");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * t4 = new sf::Texture;
	t4->loadFromImage(i);

	Scroller scr;
	scr.init(t2, t1, t3, { 32, 600 }, t4);
	scr.setHoverColor({ 200,200,200,255 });
	scr.setClickedColor({ 150,150,150,255 });

	ScrollArea * c = new ScrollArea(scr);

	ScrollArea * c2 = new ScrollArea(scr);

	i.loadFromFile("data/graphix/testImages/storyArea/background.png");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * B1 = new sf::Texture;
	B1->loadFromImage(i);
	i.loadFromFile("data/graphix/testImages/DecisionArea/background.png");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * B12 = new sf::Texture;
	B12->loadFromImage(i);
	i.loadFromFile("data/graphix/testImages/storyArea/smok.png");
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	sf::Texture * T1 = new sf::Texture;
	T1->loadFromImage(i);


	ImageWidget * BB = new ImageWidget();
	BB->setTexture(B1);

	ImageWidget * BB2 = new ImageWidget();
	BB2->setTexture(B12);

	ImageWidget * TT = new ImageWidget();
	TT->setTexture(T1);

	StoryArea * test = new StoryArea();
	test->init(canv, BB, c, a, TT);

	DecisionArea * test2 = new DecisionArea();
	test2->init(canv2, BB2, c2, { a2,a3,a4 });
	test2->setOnChoosenOption([test2](size_t o) {if (o == 3)test2->setSize({ 300, 500 }); });
}


void Game::saveGame(const std::string & path)
{
}

void Game::update(unsigned int deltaTime)
{
	_ticks += deltaTime;
	canv->update(deltaTime);
	canv2->update(deltaTime);
}

void Game::render(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(*canv, states);
	target.draw(*canv2, states);
}

void Game::input(const sf::Event & e)
{
	canv->input(e);
	canv2->input(e);
}
