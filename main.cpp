#include<iostream>
#include<string.h>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;
bool INIT_DONE = false;
int NO_PARENT = -1;
map<int,string> index_stations;
map<string,int> stations_index;
map<string,string> route;
string source_Station;

class PassengerDetails
{
	public:
        string name;
        int age;
        string destination;
        bool inQueue;
        PassengerDetails(string name, string destination, int age){
        	this->name = name;
        	this->destination = destination;
        	this->age = age;
        	this->inQueue = true;
		}
} ;

class compare
{
    public:
        bool operator()(PassengerDetails *a,PassengerDetails *b)
        {
            return a->age < b->age;
        }
};

queue<PassengerDetails*> passengersQueue;
priority_queue<PassengerDetails*,vector<PassengerDetails*>,compare> passengersAgeQueue;

void addPassenger(string passengerName,int age,string destination)
{

    PassengerDetails *p = new PassengerDetails(passengerName, destination, age);
    
    passengersQueue.push(p);
    passengersAgeQueue.push(p);
}
void printPath(int currentVertex, vector<int> parents, string &path)
{
 
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents, path);
    path += index_stations[currentVertex] +" ";
}

void printSolution(int startVertex, vector<int> distances,
                   vector<int> parents)
{
    int nVertices = distances.size();
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        if (vertexIndex != startVertex) {
            string path;
            printPath(vertexIndex, parents, path);
            route[index_stations[vertexIndex]] = path;
        }
    }
}
 
 
void dijkstra(vector<vector<int> > adjacencyMatrix,
              int startVertex) {
    int nVertices = adjacencyMatrix[0].size();
 
    vector<int> shortestDistances(nVertices);
 
    vector<bool> added(nVertices);
 
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
 
    shortestDistances[startVertex] = 0;
 
    vector<int> parents(nVertices);
 
    parents[startVertex] = NO_PARENT;
 
    for (int i = 1; i < nVertices; i++) {
 
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices;
             vertexIndex++) {
            if (!added[vertexIndex]
                && shortestDistances[vertexIndex]
                       < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance
                    = shortestDistances[vertexIndex];
            }
        }
 
        added[nearestVertex] = true;
 
        for (int vertexIndex = 0; vertexIndex < nVertices;
             vertexIndex++) {
            int edgeDistance
                = adjacencyMatrix[nearestVertex]
                                 [vertexIndex];
 
            if (edgeDistance > 0
                && ((shortestDistance + edgeDistance)
                    < shortestDistances[vertexIndex])) {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex]
                    = shortestDistance + edgeDistance;
            }
        }
    }
    printSolution(startVertex, shortestDistances, parents);
}


void init(int N,string startStation, ifstream &ifs) {
    int k = 0;
    string a, b;
    int dis;
    vector<vector<int> > input;

    stations_index[startStation] = k++;
	index_stations[k] = startStation;
    for (int i = 0; i < N; ++i) {
    	string in;
    	vector<string> input1;
        getline(ifs, in);
        istringstream iss(in);
    	iss>>a;
    	iss>>b;
    	iss>>dis;
    	if(stations_index.find(a) == stations_index.end()){
    		stations_index[a] = k;
		    index_stations[k++] = a;
		}
		if(stations_index.find(b) == stations_index.end()){
    		stations_index[b] = k;
		    index_stations[k++] = b;
		}
		vector<int> temp(3);
		temp[0] = stations_index[a];
		temp[1] = stations_index[b];
		temp[2] = dis;
        input.push_back(temp);
	}

    vector<vector<int> > matrix(k, vector<int>(k));
    for (int i = 0; i < input.size(); i++) {
        matrix[input[i][0]][input[i][1]] = input[i][2];
	}

    dijkstra(matrix, 0);
}

void startPOD(int np){
	if(passengersAgeQueue.size() < np)
		return;
	while(np--){
		PassengerDetails* p = passengersAgeQueue.top();
		passengersAgeQueue.pop();
		cout<<p->name<<" "<<source_Station<<route[p->destination]<<endl;
		p->inQueue = false;
	}
}

void printQ(void){
	int size_q = passengersQueue.size();
	int size_q2 = passengersAgeQueue.size();
	cout<<size_q2<<endl;
	while(size_q--){
		PassengerDetails* p = passengersQueue.front();
		passengersQueue.pop();
		if(p->inQueue){
			cout<<p->name<<" "<<p->age<<endl;
			passengersQueue.push(p);
		}
		else
			delete p;
	}
}

int main()
{
    cout<<"WELCOME TO HYPERLOOP PASSENGER BOOKING!!"<<endl;
    
    ifstream inputFile ("input.txt");
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (command == "INIT") {
            int lineCount;
            iss >> lineCount >> source_Station;
                route[source_Station] = source_Station;
            init(lineCount, source_Station, inputFile);
            INIT_DONE = true;
        } else if (command == "ADD_PASSENGER") {
        	if(!INIT_DONE)
        		cout<<"INIT not done"<<endl;
            int passengerCount;
            iss >> passengerCount;
            for (int i = 0; i < passengerCount; ++i) {
            	string line_add;
            	getline(inputFile, line_add);
        		istringstream iss2(line_add);

                string passengerName;
                int age;
                string destination;
                iss2>>passengerName >> age >> destination;
                
                addPassenger(passengerName,age,destination);
            }
        } else if (command == "START_POD") {
        	if(!INIT_DONE)
        		cout<<"INIT not done"<<endl;
            int podNumber;
            iss>>podNumber;
            startPOD(podNumber);
        } else if (command == "PRINT_Q") {
        	if(!INIT_DONE)
        		cout<<"INIT not done"<<endl;
            int queueNumber;
            iss>>queueNumber;
            printQ();
        }
    }
    inputFile.close();

    return 0;
}
