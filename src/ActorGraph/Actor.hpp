#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <iostream>

#include "ActorGraph.hpp"
#include "Movie.hpp"
using namespace std;

class Movie;
/** A class defining the vertices of the graph*/
class Actor {
	public: 
		string ActName;
		Actor* prev;
		vector<Movie*> movies;
		bool visited;
		int dist;
		
	Actor(string ActName,  Actor* prev = 0, bool visited = false, int dist = 0) : ActName(ActName), prev(prev), visited(visited), dist(dist) {
	}
};

#endif //ACTOR_HPP
