#include <SFML/Graphics.hpp>
#include <time.h>


int main()
{
	//criacao da janela
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake c++");
	sf::Clock clock;

	//gera semente aleatoria para o rand
	srand(time(NULL));

	//define o tamanho e inicializa a cobrinha(vetor de ciruclos)
	int length = 1;
	std::vector<sf::CircleShape> snake(100);

	//define o raio e a cor da cobrinha
	snake[0] = sf::CircleShape(16);
	snake[0].setFillColor(sf::Color::Magenta);

	//define a direcao inicial da cabeça
	sf::Vector2f dir(0, 32);

	//inicializa a comida em uma posição aleatória dentro do grid (32x32 * 26)
	sf::CircleShape food(10);
	food.setFillColor(sf::Color::Green);
	food.setPosition(sf::Vector2f(32 * (1 + rand() % 20), 32 * (1 + rand() % 20)));

	
	// bloco principal do jogo - renderização
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			//fecha o jogo se o usuario clicou em fechar
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			//em cada frame, limpa a tela aplicando o fundo preto
			window.clear(sf::Color::Black);

			//bloco dos inputs do teclado para direcao da cobrinha
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				dir = sf::Vector2f(-32, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				dir = sf::Vector2f(32, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				dir = sf::Vector2f(0, -32);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				dir = sf::Vector2f(0, 32);
			}
			//fim do bloco de inputs do teclado

			//se a posicao da cabeça da cobrinha for a mesma da comida, cria uma nova comida em uma posicao aleatoria
			if (snake[0].getPosition() == food.getPosition())
			{
				food.setPosition(sf::Vector2f(32 * (1 + rand() % 20), 32 * (1 + rand() % 20)));

				//inicializa um novo componente da cobra e o posiciona temporariamente fora da tela
				snake[length] = sf::CircleShape(12);
				snake[length].setFillColor(sf::Color::Magenta);
				snake[length].setPosition(sf::Vector2f(-32, -32));
				length++;
			}

			//define a taxa de atualização de quadros (clock)
			if (clock.getElapsedTime().asSeconds() > 0.1f)
			{
				//repassa cada um dos componentes da cobra de trás para frente
				for (int i = length - 1; i > 0; i--)
				{
					//caso a cobra encoste em algum componente, acaba o jogo
					if (snake[0].getPosition() == snake[i].getPosition() && i != 0)
					{
						window.close();
					}
						
					//cria uma espécie de recursão -> o último componente vai para a posição do antepenúltimo e assim vai
					snake[i].setPosition(snake[i - 1].getPosition());
				}

				//aplica a movimentação e reinicia o relógio
				snake[0].move(dir);
				clock.restart();
			}

			window.draw(food);

			//desenha na tela os componentes da cobra
			for (int i = 0; i < length; i++)
			{
				window.draw(snake[i]);
			}

			window.display();
		}
	}

}