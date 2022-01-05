# Auto-Store
Auto-Save helps you save/retrieve variables (and data structures) to/from file with minimal effort. 
For example, you only need to overload the << and >> operator(s) for ostream to serialize/deserialize a struct.

# Examples
Simple Example:
```c++
au::auto_store<unsigned int> game_score{0, "game_score.txt"};
std::cout << "Current Game Score: " << game_score << std::endl;
std::cout << "Enter New Game Score: ";
std::cin >> game_score;
```
Detailed Example:
```c++
struct Game {
	int score;
	int health;
	friend std::ostream& operator<<(std::ostream& out, const Game& g) {
		out << g.score << ',' << g.health;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Game& g) {
		char nop{ NULL };
		in >> g.score >> nop >> g.health;
		return in;
	}
	// It is optional to define operator=(), but you can do it if you want to use the '=' operator.
	// Example use:
	// au::auto_save<Game> current_game{Game(), "game.txt"};
	// current_game = Game();
	
	// If you don't define '=' operator, you can always use '*' to get the object stored inside auto_save
	// Example use of '*':
	// au::auto_save<Game> current_game{Game(), "game.txt"};
	// (*current_game).score++;
	// (*current_game).health++;
	void operator=(const Game& g) {
		score = g.score;
		health = g.health;
	}
	void operator=(Game&& g) noexcept = delete; // typically used for efficiency
};

void serialize_struct_example() {
	au::auto_store<Game> g{ Game(), "game.txt" };
	(*g).health++;
	(*g).score++;
}
```
More examples can be found in ```main.cpp```.

# Compiling
To compile autostore.hpp (as an individual file), you need C++20.

# Notes
- Cannot save pointers to file
