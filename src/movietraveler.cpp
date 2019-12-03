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
  delete graph;
  return 0;
}
