#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "body.hpp"
#include "BigNum.hpp"

const float window_width = 1400;
const float window_height = 900;

struct VerletObject {
	sf::Vector2f position_current;
	sf::Vector2f position_old;
	sf::Vector2f acceleration;

	void update(float dt) {
		applyConstraints();
		updatePosition(dt);
	}


	void updatePosition(float dt) {
		sf::Vector2f velocity = position_current - position_old;
		//save current pos
		position_old = position_current;
		//Verlet Integration
		position_current = position_current + velocity + acceleration * dt * dt;
		//Reset acceleration
		acceleration = {};
	}

	void accelerate(sf::Vector2f acc) {
		acceleration += acc;
	}

	void applyConstraints() {
		const sf::Vector2f position{ window_width / 2, window_height / 2 };
		const float radius = 200.0f;

		const sf::Vector2f to_obj = position_current - position;
		const float dist = sqrt(to_obj.x * to_obj.x + to_obj.y * to_obj.y);
		if (dist > radius - 25.f) {
			const sf::Vector2f n = to_obj / dist;
			position_current = position + n * (radius - 25.f);
		}

	}
};



int main() {

	char smth[5] = { '1', '2', '3', '4', '5' };
	bignum big(smth, 5);
	big.printNum();

	float circleRadius = 25.f;
	//create window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Test Window", sf::Style::Default, settings);


	//Draw Constraint
	sf::CircleShape constraint(200.0f, 1000.f);
	constraint.setFillColor(sf::Color::Transparent);
	constraint.setOutlineThickness(3);
	constraint.setOutlineColor(sf::Color::White);
	constraint.setPosition({window_width / 2 - (200.0f - 25.f), window_height / 2 - (200.0f - 25.f)});

	//Shapes Verlet Object
	VerletObject verletShape;
	verletShape.position_current = {window_width/2 - circleRadius, window_height/2 - circleRadius};
	verletShape.position_old = verletShape.position_current;
	verletShape.acceleration = {};

	//Draw Shape
	sf::CircleShape shape(circleRadius, 1000);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(0);
	shape.setOutlineColor(sf::Color::White);
	shape.setPosition(verletShape.position_current);


	//Start Clock for delta time
	sf::Clock deltaClock;

	//run while window is open
	while (window.isOpen()) {
	
		sf::Time dt = deltaClock.restart();
		//check all triggered events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//clear window with black color
		window.clear(sf::Color::Black);
		
		verletShape.accelerate({0.f, 1000.0f});
		verletShape.update(dt.asSeconds());
		shape.setPosition(verletShape.position_current);
		
		//draw everything with window.draw()
		window.draw(shape);
		window.draw(constraint);

		//end frame
		window.display();
	}
	

	return 0;
}