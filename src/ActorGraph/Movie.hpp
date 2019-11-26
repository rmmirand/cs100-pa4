#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <vector>
#include <iostream>

#include "ActorGraph.hpp"
#include "Actor.hpp"

class Actor;

using namespace std;

class Movie {
	public:
		string movTit;
		Actor* prev;
		int year;
		vector<Actor*> actList;
	Movie(string movTit,int year, Actor* prev = 0) : movTit(movTit), year(year), prev(prev) {}

};
#endif //MOVIE_HPP
