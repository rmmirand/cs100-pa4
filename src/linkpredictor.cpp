/** Rosa Miranda
 *  rmmirand@ucsd.edu
 *
 *  INT_MAX usage taken from cplusplus.com
 *
 *  LinkPredictor predicts the 4 most likely candidates to work with the queried
 * Actor from both the set of actors with which he has collaborated in the past
 * and the set of actors which he has not collaborated with before.
 */
#include <string.h>
#include <climits>
#include <iostream>
#include <queue>
#include "ActorGraph.cpp"

#define ARGS_VAL 5
using namespace std;

// finds collaborated actors and uncollaborated at the same time
void findLinks(string inFile, string out1File, string out2File,
               ActorGraph* graph) {
    ifstream in;
    ofstream collab;
    ofstream uncollab;

    in.open(inFile, ios::binary);
    collab.open(out1File, ios::trunc);
    uncollab.open(out2File, ios::trunc);
    // checks if infile is empty;
    if (in.peek() == ifstream::traits_type::eof()) {
        cout << "Empty Input File" << endl;
    }
    // checks that both out files exist, if not creates missing ones
    if (!collab.good()) {
        fstream file(out1File, ios::out);
        collab.close();
        collab.open(out1File, ios::trunc);
    }
    if (!uncollab.good()) {
        fstream file(out2File, ios::out);
        uncollab.close();
        uncollab.open(out2File, ios::trunc);
    }

    collab << "Actor1,Actor2,Actor3,Actor4" << endl;
    uncollab << "Actor1,Actor2,Actor3,Actor4" << endl;

    vector<Actor*> listCollabs;
    vector<Actor*> listUnColl;
    string queryAct;
    getline(in, queryAct);
    Actor* theActor;
    while (in.peek() != ifstream::traits_type::eof()) {
        getline(in, queryAct);
        unordered_map<string, Actor*>::const_iterator queryPoint =
            (graph->getactMap()).find(queryAct);
        theActor = (*queryPoint).second;
        cout << "Computing predictions for (" << queryAct << ")" << endl;
        if (queryPoint == (graph->getactMap()).end()) {
            cout << "Failed to locate node '" << queryAct << "'" << endl;
            collab << endl;
        }

        listCollabs = graph->linkCollab(theActor);
        for (unsigned int i = 0; i < listCollabs.size(); i++) {
            listCollabs[i]->visited = false;
            listCollabs[i]->triangles = 0;
        }
        collab << listCollabs[0]->actName;
        for (unsigned int i = 1; i < listCollabs.size(); i++) {
            if (i == 4) {
                break;
            }
            collab << '\t' << listCollabs[i]->actName;
        }
        collab << endl;
        listUnColl = graph->linkUncollab(theActor);
        if (listUnColl.size() > 0) {
            uncollab << listUnColl[0]->actName;
        }
        for (unsigned int i = 1; i < listUnColl.size(); i++) {
            if (i == 4) {
                break;
            }
            uncollab << '\t' << listUnColl[i]->actName;
        }
        for (unsigned int i = 0; i < listUnColl.size(); i++) {
            listUnColl[i]->visited = false;
            listUnColl[i]->triangles = 0;
        }
        uncollab << endl;
    }

    in.close();
    collab.close();
    uncollab.close();
}
int main(int argc, char* arg[]) {
    if (argc != ARGS_VAL) {
        cout << "Invalid Number of Arguements. " << endl;
        return 1;
    }

    ActorGraph* graph = new ActorGraph();
    cout << "Reading " << arg[2] << " ..." << endl;
    graph->loadFromFile(arg[1], false);
    cout << "done" << endl;
    findLinks(arg[2], arg[3], arg[4], graph);
    delete graph;
    return 0;
}
