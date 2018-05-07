#include <SFML/Graphics.hpp>
#include <iostream>

#define LOG(x) std::cout<<x<<std::endl

//----------------------------------CONSTANTES DEL MAPA--------------------------------//
const int WIDTH= 600;
const int HEIGHT = 500;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 16;
const int CANTIDAD_BLOQUES = 100;

//--------------------------------COLISIONES--------------------------------//

bool DetectarColision(sf::Sprite spr1, sf::Sprite spr2 )
{
	return spr1.getGlobalBounds().intersects( spr2.getGlobalBounds() );//compara cood de bola y el bloque
}

//---------------------------ENDGAME-----------------------//
void DibujarTexto(sf::RenderWindow& v, sf::Text& endtext, sf::Font& font, const char* message, int size, int x, int y)
{
	endtext.setFont(font);
	endtext.setString(message);
	endtext.setCharacterSize(size);
	endtext.setFillColor(sf::Color::White);
	endtext.setPosition(x,y);
	v.draw(endtext);
}

int main()
{
	//-------------------------------CREAR VENTANA--------------------------------------//
	sf::RenderWindow ventana(sf::VideoMode(WIDTH, HEIGHT),"Just BreakOut!", sf::Style::Default);
	ventana.setFramerateLimit(60);
	srand(time(0));														//generar un seed random
	//----------------------------------------RECURSOS------------------------------------//
	sf::Text endGameText, exitText, victoryText;
	sf::Font font;
	font.loadFromFile("images/neuropol x rg.ttf");
	

	sf::Texture blocks, ball, paddle, background;
	blocks.loadFromFile("images/tileset_bloques.png");
	ball.loadFromFile("images/tileset_bloques.png");
	paddle.loadFromFile("images/paddle.png");
	background.loadFromFile("images/grid_bg.png");
	
	sf::Sprite bloques[CANTIDAD_BLOQUES], tabla(paddle), bola(ball), bg(background);

	bola.setTextureRect( sf::IntRect(TILE_WIDTH * 3, TILE_HEIGHT * 3, 8, 8) );
	bola.setScale( 1.5,1.5 );
	bola.setPosition( sf::Vector2f(WIDTH / 2, HEIGHT / 2) );

	tabla.setTextureRect( sf::IntRect(0, TILE_HEIGHT * 9, TILE_WIDTH * 2 + 10, TILE_HEIGHT * 2 - 5) );
	tabla.setPosition( sf::Vector2f(WIDTH / 2 - 50, HEIGHT - 50) );

	int n = 0;														//Recorrer el mapa y el array
	for (int i = 1; i <= CANTIDAD_BLOQUES / 10; i++)
	{
		for (int j = 1; j <= CANTIDAD_BLOQUES / 10; j++)
		{
			bloques[n].setTexture(blocks);
			bloques[n].setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
			bloques[n].setPosition(sf::Vector2f((float)i * TILE_WIDTH + 100, (float)j * TILE_HEIGHT + 25));
			n++;
		}
	}

																			//movimiento de bola
	float bolaDx = 3;
	float bolaDy = 2.5;
																			//mov de tabla
	float tablaDx = 4.5;

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
		bola.rotate(2);														//rotacion
		bola.move(-bolaDx, 0);												//mov de la bola en mapa
		

																			//detecta si hay colision con bloques
		for (int i = 0; i < n; i++)
		{
			if (DetectarColision(bola, bloques[i]))
			{
				bloques[i].setColor(sf::Color::Transparent);				//las 'desaparece' del mapa
				bolaDx = -bolaDx;
			}
		}
		bola.move(0, -bolaDy);
		
		for (int i = 0; i < n; i++)
		{
			if (DetectarColision(bola, bloques[i]))
			{
				bloques[i].setColor(sf::Color::Transparent);			//las 'desaparece' del mapa
				bolaDy = -bolaDy;
			}
		}

		sf::Vector2f bolaCoordenadas = bola.getPosition();						//Colision con el borde del mapa
		if (bolaCoordenadas.x >= WIDTH || bolaCoordenadas.x <= 0) bolaDx = -bolaDx;	//rebote con el borde
		if (bolaCoordenadas.y <= 0)	bolaDy = -bolaDy;

		
		//-----------------------------MOVIMIENTO TABLA------------------------------//
		sf::Vector2f tablaCoordenadas = tabla.getPosition();					//coord de tabla
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && tablaCoordenadas.x < WIDTH -100) tabla.move(tablaDx,0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && tablaCoordenadas.x > 10) tabla.move(-tablaDx,0);
		
		if ( DetectarColision(bola, tabla ) )
		{
			bolaDy = -( rand()%5+1 );	//valor negativo lo manda arriba
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
		//--------------------------------CHEKEAR GAMEOVER---------------------------//
		if (bolaCoordenadas.y >= HEIGHT)										//si bola toca el suelo
		{
			DibujarTexto(ventana, endGameText, font, "GameOver", 24, 200, 220);
			DibujarTexto(ventana, exitText,font , "Press ESC to exit", 12, 215, 260);
		}

		//--------------------------------CHEKEAR VICTORY----------------------------//
		for (int i = 0; i < n; i++)
		{
			if (bloques[n].getColor() == sf::Color::Transparent)
			{
				DibujarTexto(ventana, victoryText, font, "Victory", 24, 200,220);
				LOG("ENDGAME");
			}
		}
		//------------------------------MOSTRAR CAMBIOS------------------------------------//
		ventana.display();
	}//ventana.isOpen()


	

	return 0;
}