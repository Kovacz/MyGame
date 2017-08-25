#ifndef __GAME_H__
#define __GAME_H__
///////////////////////////////////////////////////////////
#include <random> 
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cmath>
///////////////////////////////////////////////////////////
class Human;
using std::cout;
using std::endl;
///////////////////////////////////////////////////////////
class Game
{
private:
	std::mt19937 gen;
	std::uniform_real_distribution<> urd;
public:
	void Play();
	static Game &Instance();
	unsigned _randomize(unsigned from, unsigned to);
	double _randomize(std::uniform_real_distribution<> urd);
private:
	Game();
	Game(double from, double to);
	Game(Game const&) = delete;
	Game &operator=(Game const&) = delete;

};
#endif // __GAME_H__