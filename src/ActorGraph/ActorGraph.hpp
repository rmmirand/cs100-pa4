/*
 * ActorGraph.hpp
 * Author: Rosa Miranda rmmirand@ucsd.edu
 * Date:  December 4th, 2019
 *
 *Contained the declarations of the methods and variables of the ActorGraph
 *class, along with the implementations of the comparators used.
 *
 * This file is meant to exist as a container for starter code that you can use
 *to read the input file format defined imdb_2019.tsv. Feel free to modify
 *any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "Actor.hpp"
#include "Movie.hpp"
// Maybe include some data structures here

using namespace std;

/* * TODO: add class header
 */
// compares distances for the pathfinder
struct valComp {
    bool operator()(Actor* a1, Actor* a2) const { return a1->dist > a2->dist; }
};
// compares distances for the link predictor
struct triangleComp {
    bool operator()(Actor* a1, Actor* a2) const {
        if (a1->triangles == a2->triangles) {
            return a1->actName < a2->actName;
        }
        return a1->triangles > a2->triangles;
    }
};
// compares weights for the movie traveler
struct weightComp {
    bool operator()(Movie* m1, Movie* m2) const {
        if (m1->weight == m2->weight) {
            return m1->movTit < m2->movTit;
        }
        return m1->weight < m2->weight;
    }
};
class ActorGraph {
  protected:
    // Maybe add class data structure(s) here
    unordered_map<string, Actor*> actMap;
    unordered_map<string, Movie*> movMap;
    vector<Movie*> allMovies;
    vector<Actor*> allActors;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    // Maybe add some more methods here

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    vector<Actor*> linkUncollab(Actor* actor);
    vector<Actor*> linkCollab(Actor* actor);
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    unordered_map<string, Actor*> getactMap() { return actMap; };
    unordered_map<string, Movie*> getmovMap() { return movMap; };
    Actor* pathHelper(Actor* currA, string target);
    Actor* pathHelperWeight(Actor* currA, string target);
    void travelMovies(ostream& out);
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
