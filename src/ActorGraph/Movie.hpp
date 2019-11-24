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
		int year;
		vector<Actor*> actList;
	Movie(string movTit,int year) : movTit(movTit), year(year) {}

};
#endif //MOVIE_HPP
