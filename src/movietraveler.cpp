#include <iostream>
#include <queue>
#include <string.h>
#include <climits>
#include "ActorGraph.cpp"

#define ARGS_VAL 3
using namespace std;


int main(int argc, char* arg[]){

  if(argc != ARGS_VAL){
	cout << "Invalid Number of Arguements. " << endl;
        return 1; 
  }

  ActorGraph* graph = new ActorGraph();
  cout << "Reading " << arg[1] << " ..." << endl; 
  graph->loadFromFile(arg[1], false);
  cout << "done" << endl;
ofstream out;

out.open(arg[2], ios::trunc);

//checks if outfile exists, if not creates one
if(!out.good()){
     fstream file(arg[2], ios::out);
     out.close();
     out.open(arg[2], ios::trunc);
}
out << "(actor)<--[movie#@year]-->(actor)" << endl;

  graph->travelMovies(out);
  delete graph;
  return 0;
}
