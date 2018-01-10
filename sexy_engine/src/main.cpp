#include "ecs/Core.hpp"
#include "ecs/ASystem.hpp"
#include "Graphical/GraphicalSystem.hpp"
#include "Graphical/SFML/SFMLLib.hpp"

/*
int			main()
{
	Sex::Core core;

	core.emplaceSystem<Graphical::GraphicalSystem>();
	auto graphicalSystem = core.getSystem<Graphical::GraphicalSystem>();
	while (graphicalSystem.IsOpen());
}
*/

void        print() {
    std::cout << "Bonjour Madame" << std::endl;
}

int			main()
{
	Graphical::SFMLLib		Lib;

	auto		Window = Lib.CreateWindow(Graphical::Vector2D(1920, 1080), "RType");
	auto		Sprite = Lib.CreateSprite("Asset/Attack1.png", Graphical::Vector2D(0, 0), Graphical::Vector2D(200, 200), 1, 4);
	auto		Font1 = Lib.GetFont("DigitalDesolation");
	auto		Font2 = Lib.GetFont("Neogrey");
	auto		Text = Lib.CreateText(Font1, "WALLAH", Graphical::Vector2D(0, 0), 20);
	auto		Background = Lib.CreateSprite("Asset/Background.png",
											Graphical::Vector2D(0, 0),
											Graphical::Vector2D(1920, 1080),
											1, 3000);
    auto        Button = Lib.CreateButton(Graphical::Vector2D(800, 100), 5,
                                          Graphical::Color(255, 25, 255), "toto", print);
	Background->SetAnimationSprite(Graphical::Vector2D(1920, 1080));
	Background->SetAnimationSpeed(5);
	while (Window->IsOpen())
	{
		Graphical::Event event;

		while (Window->GetEvent(event))
		{
			if (event.type == Graphical::Event::KEYPRESSED)
			{
				if (event.key == Graphical::Event::ESexKey::DOWN)
					Text->SetFont(Font2);
				else if (event.key == Graphical::Event::ESexKey::UP)
					Text->SetFont(Font1);
			}

		}

		Window->Draw(*Background);
		Window->Draw(*Sprite);
        Window->Draw(*Button);
		Window->Draw(*Text);
		Window->Display();
	}
	return (0);
}