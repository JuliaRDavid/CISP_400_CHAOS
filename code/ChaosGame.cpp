// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    sf::Font font;
    if (!font.loadFromFile("ARCADECLASSIC.TTF")) 
    {
        //error code if failure to load
        std::cout << "ERROR: Text not loaded." << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Click  on  3  locations  to  form  a  triangle");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        text.setString("Click  on  another  location");
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        text.setString("Watch  the  magic  happen!");
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            int index = rand() % 3;
            size_t lastPoint = points.size() - 1;
            size_t midX = (points[lastPoint].x + vertices[index].x) / 2;
            size_t midY = (points[lastPoint].y + vertices[index].y) / 2;
            points.push_back(Vector2f(midX, midY));
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        window.draw(text);
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        window.display();
    }
}