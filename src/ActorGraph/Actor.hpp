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
		string actName;
		Movie* prev;
		vector<Movie*> movies;
		bool visited;
		int dist;
		
	Actor(string actName,  Movie* prev = 0, bool visited = false, int dist = 0) : actName(actName), prev(prev), visited(visited), dist(dist) {
	}
};

#endif //ACTOR_HPP
