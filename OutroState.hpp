#include "State.hpp"

class OutroState : public State {
	public:
		OutroState(Context& context);

		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();

	private:
		sf::Font font;
		sf::Text text;
		sf::Text helpText;
};

