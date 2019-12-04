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
#include <queue>
#include <unordered_map>
#include <algorithm>

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
		allMovies.push_back(newMovie);
		theMovie = newMovie;
		movMap.insert(make_pair(movie_title + to_string(year), newMovie));
	}else{
		theMovie = (*movNode).second;
		if(theMovie->year != year){
			Movie* newMovie = new Movie(movie_title, year);
			allMovies.push_back(newMovie);
			theMovie = newMovie;
			movMap.insert(make_pair(movie_title + to_string(year), newMovie));
		}
	}
	if(actNode == actMap.end()){
		Actor* newActor = new Actor(actor);
		allActors.push_back(newActor);
		theActor = newActor;
		actMap.insert(make_pair(actor, newActor));
	}else{
		theActor = (*actNode).second;
	}
	for(unsigned int i = 0; i < theMovie->actList.size(); i++){
		if( actor == theMovie->actList[i]->actName){
			here = true;
			break;
		}
	}
	if(!here){
		theMovie->actList.push_back(theActor);
	}
	here = false;
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

    return true;

}
Actor* ActorGraph::pathHelper(Actor* currA, string target){
	Movie* currM;
	int d = 0;
	int tempd;
	priority_queue<Actor*, vector<Actor*>, valComp> pq;
	currA->dist = 0;
	pq.push(currA);
	while(!pq.empty()){
		d = (pq.top())->dist;
		currA = pq.top();
		pq.pop();
		if(!currA->visited){
			currA->visited = true;
			for(unsigned int i = 0; i < currA->movies.size(); i++){
				currM = currA->movies[i];
				if(currA->prev != currM){
					currM->prev = currA;
				}
				for(unsigned int j = 0; j < currM->actList.size(); j++){
					if(!currM->actList[j]->visited){
						tempd = d + 1;
						if(tempd < currM->actList[j]->dist){
							currM->actList[j]->prev = currM;
							currM->actList[j]->dist = tempd;
							pq.push(currM->actList[j]);
							if(currM->actList[j]->actName == target){
								return currM->actList[j];
							}
						}
					}			
				}
			}
		}
	}
	currA = (*(actMap.find(target))).second;
	return currA;

}
Actor* ActorGraph::pathHelperWeight(Actor* currA, string target){
	Movie* currM;
	int weight = 0;
	int tempd = 0;
	priority_queue<Actor*, vector<Actor*>, valComp> pq;
	currA->dist = 0;
	pq.push(currA);
	while(!pq.empty()){
		currA = pq.top();
		pq.pop();
		if(!currA->visited){
			currA->visited = true;
			for(unsigned int i = 0; i < currA->movies.size(); i++){
				currM = currA->movies[i];
				for(unsigned int j = 0; j < currM->actList.size(); j++){
					if(!currM->actList[j]->visited){
						weight = (1+(2019 - currM->year));
						tempd = currA->dist + weight;
						if(tempd < currM->actList[j]->dist){
							currM->actList[j]->prev = currM;
							currM->actList[j]->dist = tempd;
							pq.push(currM->actList[j]);
							if(currA->prev != currM){
								currM->prev = currA;
							}
						}
					}			
				}
			}
		}
	}
	currA = (*(actMap.find(target))).second;
	return currA;
}

vector<Actor*> ActorGraph::linkCollab(Actor* actor){
	triangleComp tricomp;
	vector<Actor*> collabs; 
	//initializes vector of directly linked actors to query actor 
	for(unsigned int i = 0; i < actor->movies.size(); i++){
		for(unsigned int j = 0; j < actor->movies[i]->actList.size(); j++){
			if(actor->actName != actor->movies[i]->actList[j]->actName){
				if(!actor->movies[i]->actList[j]->visited){
					actor->movies[i]->actList[j]->visited = true;
					collabs.push_back(actor->movies[i]->actList[j]);
				}
			}
		}
	}
	//begins counter for links
	for(unsigned int i = 0; i < collabs.size(); i++){
		for(unsigned int j = 0; j < collabs[i]->movies.size() ; j++){
			for(unsigned int k = 0; k < collabs[i]->movies[j]->actList.size(); k++){
				if(collabs[i]->movies[j]->actList[k]->actName != actor->actName){
					for(unsigned int l = 0; l < collabs.size(); l++){
						if(collabs[l]->actName != collabs[i]->actName && collabs[i]->movies[j]->actList[k]->actName  == collabs[l]->actName){
							if(!collabs[i]->movies[j]->actList[k]->visited){
								collabs[i]->movies[j]->actList[k]->visited = true;
								collabs[i]->triangles = collabs[i]->triangles + 1;
							}
						}
					}
				}
			}
		}
		for(unsigned int m = 0; m < collabs.size(); m++){
			collabs[m]->visited = false;
		}
	}
	sort(collabs.begin(), collabs.end(), tricomp);
	return collabs;
}
vector<Actor*> ActorGraph::linkUncollab(Actor* actor){
	triangleComp tricomp;
	vector<Actor*> uncollabs;
	vector<Actor*> undesirables;
	bool here = false;

	for(unsigned int i = 0; i < actor->movies.size(); i++){
		for(unsigned int j = 0; j < actor->movies[i]->actList.size(); j++){
			if(actor->actName != actor->movies[i]->actList[j]->actName){
				if(!actor->movies[i]->actList[j]->visited){
					actor->movies[i]->actList[j]->visited = true;
					undesirables.push_back(actor->movies[i]->actList[j]);
				}
			}
		}
	}
	for(unsigned int i = 0; i < undesirables.size(); i++){
		for(unsigned int j = 0; j < undesirables[i]->movies.size() ; j++){
			for(unsigned int k = 0; k < undesirables[i]->movies[j]->actList.size(); k++){
				if(undesirables[i]->movies[j]->actList[k]->actName == actor->actName){
					undesirables[i]->triangles = undesirables[i]->triangles + 1;
				}else{
					if(undesirables[i]->movies[j]->actList[k]->actName != undesirables[i]->actName){
						for(unsigned int m =0; m < undesirables.size(); m++){
							if(undesirables[m]->actName == undesirables[i]->movies[j]->actList[k]->actName){
								here = true;
							}
						}
						if(!here){
							here = false;
							for(unsigned int n =0; n < uncollabs.size(); n++){
								if(uncollabs[n]->actName == undesirables[i]->movies[j]->actList[k]->actName){
									here = true;
								}
							}
							if(!here){
								uncollabs.push_back(undesirables[i]->movies[j]->actList[k]);
							}
						}
						here = false;
					}
				}
			}
		}
	}
	for(unsigned int i = 0; i < uncollabs.size(); i++){
		for(unsigned int j =0; j < uncollabs[i]->movies.size(); j++){
			for(unsigned int k =0; k < uncollabs[i]->movies[j]->actList.size(); k++){
				for(unsigned int m = 0; m < undesirables.size() ; m++){
					if(uncollabs[i]->movies[j]->actList[k]->actName == undesirables[m]->actName){
						if(!undesirables[m]->visited){
							uncollabs[i]->triangles = uncollabs[i]->triangles + undesirables[m]->triangles;
							undesirables[m]->visited = true;
						}else{
							uncollabs[i]->triangles = uncollabs[i]->triangles + 1;
						}
						
					}
				}
			}
		}
		for(unsigned int n = 0; n < undesirables.size(); n++){
			undesirables[n]->visited = false;
		}
	}
	sort(uncollabs.begin(), uncollabs.end(), tricomp);
	return uncollabs;
}
void ActorGraph::travelMovies(ostream& out){
	int edges = 0;
	int vertices = 1;
	int totWeight = 0;

	weightComp comp;
	sort(allMovies.begin(), allMovies.end(), comp);
	
	for(unsigned int i = 0; i < allMovies.size(); i++){
		for(unsigned int j = 0; j < allMovies[i]->actList.size(); j++){
			if(!allMovies[i]->actList[j]->visited){
				if(j+1 < allMovies[i]->actList.size()){
					totWeight += allMovies[i]->weight;
					edges++;
					vertices++;
					allMovies[i]->actList[j]->visited = true;
					//allMovies[i]->actList[j+1]->visited = true;
					out << allMovies[i]->actList[j]->actName << "<--[" << allMovies[i]->movTit << "#@" << allMovies[i]->year << "]-->" << allMovies[i]->actList[j+1]->actName << endl;
				}else{
					if(j-1 >= 0 && !allMovies[i]->actList[j-1]->visited ){
						totWeight += allMovies[i]->weight;
						edges++;
						vertices++;
						allMovies[i]->actList[j]->visited = true;
					//	allMovies[i]->actList[j-1]->visited = true;
						out << allMovies[i]->actList[j]->actName << "<--[" << allMovies[i]->movTit << "#@" << allMovies[i]->year << "]-->" << allMovies[i]->actList[j-1]->actName << endl;
					}
				}
			}
		}
	}
	out << "#NODE CONNECTED: " << vertices << endl;
        out << "#EDGE CHOSEN: " << edges << endl;
	out << "TOTAL EDGE WEIGHTS: " << totWeight << endl;	
}
ActorGraph::~ActorGraph(){
	unordered_map<string, Actor*>::iterator resetA = ((getactMap()).begin());
	unordered_map<string, Movie*>::iterator resetM = ((getmovMap()).begin());
	for(auto resetA: (getactMap())){
		delete ((resetA).second);
	}
	for(auto resetM: (getmovMap())){
		delete ((resetM).second);
	}

}
