/* Rosa Miranda rmmirand@ucsd.edu
 * December 4th, 2019
 */
#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <iostream>
#include <vector>

#include "Actor.hpp"
#include "ActorGraph.hpp"

class Actor;

using namespace std;

class Movie {
  public:
    string movTit;
    Actor* prev;
    int year;
    int weight;
    vector<Actor*> actList;
    Movie(string movTit, int year, Actor* prev = 0)
        : movTit(movTit), year(year), prev(prev) {
        weight = 1 + (2019 - year);
    }
};
#endif  // MOVIE_HPP
