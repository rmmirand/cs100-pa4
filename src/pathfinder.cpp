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

   out << "(Actor)--[movie#@year]-->(actor)--..." << endl;
   string firstActor;
   string secondActor;
   string total;
   getline(in, firstActor);
   while(in.peek() != ifstream::traits_type::eof()){

	getline(in, firstActor, '\t');
	getline(in, secondActor, '\n');

	cout << "Computing path for (" << firstActor << ") -> (" << secondActor << ")" << endl;

	unordered_map<string, Actor*>::const_iterator actStart = ((graph->getactMap()).find(firstActor));
	unordered_map<string, Actor*>::const_iterator actEnd = ((graph->getactMap()).find(secondActor));
        total = "";
	if(actStart == (graph->getactMap()).end()){
		cout << "Failed to locate node '" << firstActor << "'" << endl;
		out << endl;
        }else if(actEnd == (graph->getactMap()).end()){
		cout << "Failed to locate node '" << secondActor << "'" << endl;
		out << endl;
	}else{
		Actor* firstAct = (*((graph->getactMap()).find(firstActor))).second;
		Actor* secondAct = (*((graph->getactMap()).find(secondActor))).second;
		firstAct = graph->pathHelper(firstAct, secondActor);
		Movie* prevMov;
		if(firstAct->prev){
			prevMov = firstAct->prev;
		}
		out << "(" << firstActor << ")" ;
		while(firstAct->actName != firstActor && firstAct->prev){
			total = "--["+prevMov->movTit+"#@"+ to_string(prevMov->year) +"]-->("+firstAct->actName+")" + total;
			firstAct = prevMov->prev;
			if(firstAct->prev){
				prevMov = firstAct->prev;
			}
		}
		out << total << endl;
	}
	//Resets the graph for the next set of actor
	unordered_map<string, Actor*>::iterator resetA = ((graph->getactMap()).begin());
	unordered_map<string, Movie*>::iterator resetM = ((graph->getmovMap()).begin());
	for(auto resetA: (graph->getactMap())){
		((resetA).second)->dist = INT_MAX;
		((resetA).second)->prev = 0;
		((resetA).second)->visited = false;
	}
	for(auto resetM: (graph->getmovMap())){
		((resetM).second)->prev = 0;
	}
   }
      
   in.close();
   out.close();
}
void weightedPath(string inFile, string outFile, ActorGraph* graph){
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

   out << "(Actor)--[movie#@year]-->(actor)--..." << endl;
   string firstActor;
   string secondActor;
   string total;
   getline(in, firstActor);
   while(in.peek() != ifstream::traits_type::eof()){

	getline(in, firstActor, '\t');
	getline(in, secondActor, '\n');

	cout << "Computing path for (" << firstActor << ") -> (" << secondActor << ")" << endl;

	unordered_map<string, Actor*>::const_iterator actStart = ((graph->getactMap()).find(firstActor));
	unordered_map<string, Actor*>::const_iterator actEnd = ((graph->getactMap()).find(secondActor));
        total = "";
	if(actStart == (graph->getactMap()).end()){
		cout << "Failed to locate node '" << firstActor << "'" << endl;
		out << endl;
        }else if(actEnd == (graph->getactMap()).end()){
		cout << "Failed to locate node '" << secondActor << "'" << endl;
		out << endl;
	}else{
		Actor* firstAct = (*((graph->getactMap()).find(firstActor))).second;
		Actor* secondAct = (*((graph->getactMap()).find(secondActor))).second;
		firstAct = graph->pathHelperWeight(firstAct, secondActor);
		Movie* prevMov;
		if(firstAct->prev){
			prevMov = firstAct->prev;
		}
		out << "(" << firstActor << ")" ;
		while(firstAct->actName != firstActor && firstAct->prev){
			total = "--["+prevMov->movTit+"#@"+ to_string(prevMov->year) +"]-->("+firstAct->actName+")" + total;
			firstAct = prevMov->prev;
			if(firstAct->prev){
				prevMov = firstAct->prev;
			}
		}
		out << total << endl;
	}
	//Resets the graph for the next set of actor
	unordered_map<string, Actor*>::iterator resetA = ((graph->getactMap()).begin());
	unordered_map<string, Movie*>::iterator resetM = ((graph->getmovMap()).begin());
	for(auto resetA: (graph->getactMap())){
		((resetA).second)->dist = INT_MAX;
		((resetA).second)->prev = 0;
		((resetA).second)->visited = false;
	}
	for(auto resetM: (graph->getmovMap())){
		((resetM).second)->prev = 0;
	}
   }
      
   in.close();
   out.close();
}

int main(int argc, char* arg[]){

  if(argc != ARGS_VAL){
	cout << "Invalid Number of Arguements. " << endl;
        return 1; 
  }

  ActorGraph* graph = new ActorGraph();
  cout << "Reading " << arg[3] << " ..." << endl; 
  if(strcmp(arg[2], "u") == 0){
  	graph->loadFromFile(arg[1], arg[2]);
	cout << "done" << endl;
	unweightedPath(arg[3], arg[4], graph);
  }else{
  	graph->loadFromFile(arg[1], arg[2]);
	cout << "done" << endl;
	weightedPath(arg[3], arg[4], graph);
  }
  delete graph;
  return 0;
}
