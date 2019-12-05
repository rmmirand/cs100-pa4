/* Rosa Miranda rmmirand@ucsd.edu
 * December 4th, 2019
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <climits>
#include <iostream>
#include <vector>
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
    int triangles;

    Actor(string actName, Movie* prev = 0, bool visited = false,
          int dist = INT_MAX, int triangles = 0)
        : actName(actName),
          prev(prev),
          visited(visited),
          dist(dist),
          triangles(triangles) {}
};

#endif  // ACTOR_HPP
