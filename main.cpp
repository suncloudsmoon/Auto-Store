/*
 * Copyright (c) 2022, suncloudsmoon and the Auto-Store contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <climits>

#include "autostore.hpp"

void game_score_example();
void random_num_example();
void serialize_struct_example();

int main() {
	// game_score_example();
	// random_num_example();
	serialize_struct_example();
}

void game_score_example() {
	au::auto_store<unsigned int> game_score{ 0, "game_score.txt" };
	std::cout << "Game score: " << game_score << std::endl;
	std::cout << "Enter a random number: ";
	std::cin >> game_score;
}

void random_num_example() {
	std::function<unsigned long()> rand_func = [&]() -> unsigned long {
		// LCG -> (a*X + c) % m
		static unsigned long a = 1103515245, x = 100, c = 12345, m = INT_MAX;
		x = (a * x + c) % m;
		return x;
	};
	au::auto_store<unsigned int> something{ 0, rand_func };
	(*something)++;
}

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
