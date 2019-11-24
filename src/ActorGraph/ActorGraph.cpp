/*
 * ActorGraph.cpp
 * Author: Rosa Miranda
 * Date:   November 17th, 2019
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in imdb_2019.tsv. Feel free to modify any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include "Actor.hpp"
#include "Movie.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * Constructor of the Actor graph
 */ 
ActorGraph::ActorGraph(void) {}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year),
 *                      otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);
        
        // TODO: we have an actor/movie relationship, now what?
	unordered_map<string, Actor*>::const_iterator actNode = actMap.find(actor);
	unordered_map<string, Movie*>::const_iterator movNode = movMap.find(movie_title+to_string(year));

	Actor* theActor;
	Movie* theMovie;
	bool here = false;

	if(movNode == movMap.end()){
		Movie* newMovie = new Movie(movie_title, year);
		theMovie = newMovie;
		movMap.insert(make_pair(movie_title + to_string(year), newMovie));
	}else{
		theMovie = (*movNode).second;
		if(theMovie->year != year){
			Movie* newMovie = new Movie(movie_title, year);
			theMovie = newMovie;
			movMap.insert(make_pair(movie_title + to_string(year), newMovie));
		}
	}
	if(actNode == actMap.end()){
		Actor* newActor = new Actor(actor);
		theActor = newActor;
		actMap.insert(make_pair(actor, newActor));
	}else{
		theActor = (*actNode).second;
	}
	for(unsigned int i = 0; i < theActor->movies.size(); i++){
		if( movie_title == theActor->movies[i]->movTit ){
			if(year == theActor->movies[i]->year){
				here = true;
				break;
			}
		}
	}
	if(!here){
		theActor->movies.push_back(theMovie);
	}
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    cout << "Actors: " << actMap.size() << " Movies: " <<movMap.size() << endl;

    return true;


}
