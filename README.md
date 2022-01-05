# Auto-Store
Auto-Save helps you save/retrieve variables (and data structures) to/from file with minimal effort. 
For example, you only need to overload the << and >> operator(s) for ostream to serialize a struct to file.
```
struct Data {};
friend ostream& operator<<(ostream &o, const Data &s);
friend istream& operator>>(istream &o, Data &s);
```

# Examples
See main.cpp for a detailed example.
```
au::auto_store<unsigned int> game_score{0, "game_score.txt"};
std::cout << "Current Game Score: " << game_score << std::endl;
std::cout << "Enter New Game Score: ";
std::cin >> game_score;
```

# Compiling
To compile autostore.hpp (as an individual file), you need C++20.

# Notes
- Cannot save pointers to file
