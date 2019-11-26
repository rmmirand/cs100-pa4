/** Rosa Miranda
 *  rmmirand@ucsd.edu
 *
 *  INT_MAX usage taken from cplusplus.com
 *
 *  Pathfinder finds the shorted distance between the two given actors, if the search is unweighted it searches for the path with the least amount of vertices, if weighted, it outputs the path with the shortest weightest total distance.
 */
#include <iostream>
#include <queue>
#include <string.h>
#include <climits>
#include "ActorGraph.cpp"

#define ARGS_VAL 5
using namespace std;

void unweightedPath(string inFile, string outFile, ActorGraph* graph){
   ifstream in;
   ofstream out;

   in.open(inFile, ios::binary);
   out.open(outFile, ios::trunc);
   
   //checks if infile is empty;
   if(in.peek() == ifstream::traits_type::eof()) {
	cout << "Empty Input File" << endl;
   }
   //checks if outfile exists, if not creates one
   if(!out.good()){
	fstream file(outFile, ios::out);
	out.close();
	out.open(outFile, ios::trunc);
   }

   out << "(Actor)--[movie#@year]-->(actor)...." << endl;
// priority_queue<Actor*, vector<Actor*>, valComp> path;
   string firstActor;
   string secondActor;
   getline(in, firstActor);
   while(in.peek() != ifstream::traits_type::eof()){
	getline(in, firstActor, '\t');
	getline(in, secondActor, '\n');
	Actor* actStart = (*((graph->getactMap()).find(firstActor))).second;
        out << actStart->actName << endl;
	actStart = graph->pathHelper(actStart, secondActor);
	while(actStart->actName != firstActor){
		out << actStart->prev;
	}
	out << endl;
	//Resets the graph for the next set of actor
/*	for(auto it = (graph->getactMap()).begin(); it != (graph->getactMap()).end(); it++){
		Actor* actCurr = (*it).second;
		actCurr->dist = INT_MAX;
		actCurr->prev = nullptr;
		actCurr->visited = false;
	}
	for(auto it = (graph->getmovMap()).begin(); it != (graph->getmovMap()).end(); it++){
		Movie* movCurr = (*it).second;
		movCurr->prev = nullptr;

	}*/
   }   
   in.close();
   out.close();
}
void pathHelper(Actor* curr){	
   int step = 0;
   priority_queue<Actor*, vector<Actor*>, valComp> path;
   path.push(curr);
//   while(!path.empty()){


  // }
   
}
int main(int argc, char* arg[]){

  if(argc != ARGS_VAL){
	cout << "Invalid Number of Arguements. " << endl;
        return 1; 
  }

  ActorGraph* graph = new ActorGraph();
   
  if(strcmp(arg[2], "u") == 0){
  	graph->loadFromFile(arg[1], arg[2]);
	unweightedPath(arg[3], arg[4], graph);
  }
  delete graph;
  return 0;
}
