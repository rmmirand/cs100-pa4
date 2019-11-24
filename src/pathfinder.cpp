/*header */
#include <iostream>
#include <queue>
#include <string.h>
#include "ActorGraph.cpp"
#define ARGS_VAL 5
using namespace std;

void unweightedPath(string inFile, string outFile){
   ifstream in;
   ofstream out;

   in.open(inFile, ios::binary);
   out.open(outFile, ios::trunc);

   if(in.peek() == ifstream::traits_type::eof()) {
	cout << "Empty Input File" << endl;
   }
   if(!out.good()){
	fstream file(outFile, ios::out);
	out.close();
	out.open(outFile, ios::trunc);
   }

   priority_queue<Actor*, vector<Actor*>, valComp> path;
   string firstActor;
   string secondActor;
   getline(in, firstActor);
   while(in.peek() != ifstream::traits_type::eof()){
	getline(in, firstActor, '\t');
	getline(in, secondActor, '\n');
	//path helper;
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
  
  if(strcmp(arg[2], "u") == 0){
  	graph->loadFromFile(arg[1], arg[2]);
	unweightedPath(arg[3], arg[4]);
  }
  delete graph;
  return 0;
}
