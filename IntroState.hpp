#include "State.hpp"

class IntroState : public State {
	public:
		IntroState(Context& context);

		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();

	private:
		sf::Font font;
		sf::Text text;
		sf::Text helpText;
};

