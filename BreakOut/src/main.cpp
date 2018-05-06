#include <SFML/Graphics.hpp>
#include <iostream>
#define LOG(x) std::cout<<x<<std::endl

const int WIDTH= 600;
const int HEIGHT = 500;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 16;

int main()
{
	//-------------------------------CREAR VENTANA--------------------------------------//
	sf::RenderWindow ventana(sf::VideoMode(WIDTH, HEIGHT),"Just BreakOut!", sf::Style::Default);
	ventana.setFramerateLimit(60);

	//----------------------------------------RECURSOS------------------------------------//
	sf::Texture blocks, ball, paddle, background;
	blocks.loadFromFile("images/tileset_bloques.png");
	ball.loadFromFile("images/tileset_bloques.png");
	paddle.loadFromFile("images/paddle.png");
	background.loadFromFile("images/grid_bg.png");
	
	sf::Sprite bloques[100], tabla(paddle), bola(ball), bg(background);

	bola.setTextureRect( sf::IntRect(TILE_WIDTH * 3, TILE_HEIGHT * 3, 8, 8) );
	bola.setScale( 2,2 );
	bola.setPosition( sf::Vector2f(WIDTH / 2, HEIGHT / 2) );
	
	tabla.setTextureRect( sf::IntRect(0, TILE_HEIGHT * 9, TILE_WIDTH * 2 + 10, TILE_HEIGHT * 2 - 5) );
	tabla.setPosition( sf::Vector2f(WIDTH / 2 - 50, HEIGHT - 200) );

	int n = 0;														//Recorrer el mapa y el array
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			bloques[n].setTexture(blocks);
			bloques[n].setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
			bloques[n].setPosition(sf::Vector2f((float)i * TILE_WIDTH + 100, (float)j * TILE_HEIGHT + 25));
			n++;
		}
	}

	while ( ventana.isOpen() )
	{
		//--------------------------------MANAGER DE EVENTOS-----------------------------//
		sf::Event evt;

		while ( ventana.pollEvent(evt) )
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				ventana.close();
				break;

			case sf::Event::Resized:
				LOG(evt.size.width);
				LOG(evt.size.width);
				break;

			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ventana.close();
				break;
			}
		}

		//------------------------------LIMPIAR PANTALLA---------------------------------//
		ventana.clear(sf::Color::White);

		//------------------------------DIBUJAR EN PANTALLA-------------------------------//
		ventana.draw(bg);														//dibujar bg
		ventana.draw(tabla);													//dibujar tabla
		ventana.draw(bola);														//dibujar bola

		for (int i = 0; i < n; i++)												//Dibujar bloques
		{
			ventana.draw(bloques[i]);
		}
		//------------------------------MOSTRAR CAMBIOS------------------------------------//
		ventana.display();
		
	}//ventana.isOpen()


	

	return 0;
}