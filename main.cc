#include "game.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

int main(int argc, char** argv) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if (argc > 1) {
		seed = stoi(string{argv[1]});
	}
	Game straights = Game();
	straights.start(seed);
}
