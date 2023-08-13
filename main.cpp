#include<iostream>
#include<string.h>
#include<vector>
#include<map>
#include<queue>
#include<fstream>
#include <sstream>

using namespace std;

class PassengerDetails
{
    public:
        string name;
        int age;
        string destination;
        bool inQueue = true;
};

int NO_PARENT = -1;
map<string,string> route;
 
// Function to print shortest path
// from source to currentVertex
// using parents array
void printPath(int currentVertex, vector<int> parents)
{
 
    // Base case : Source node has
    // been processed
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout <<char(currentVertex+'A') << " ";
    // return char(currentVertex+'A');
}

// A utility function to print
// the constructed distances
// array and shortest paths
void printSolution(int startVertex, vector<int> distances,
                   vector<int> parents)
{
    int nVertices = distances.size();
    cout << "Vertex\t Distance\tPath";
 
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        if (vertexIndex != startVertex) {
            cout << "\n" << char(startVertex+'A') << " -> ";
            cout << char(vertexIndex+'A') << " \t\t ";
            cout << distances[vertexIndex] << "\t\t";
            // route.insert(pair<string,string>(char(vertexIndex+'A'),printPath(vertexIndex, parents)));
            printPath(vertexIndex, parents);
        }
    }
}
 
// Function that implements Dijkstra's
// single source shortest path
// algorithm for a graph represented
// using adjacency matrix
// representation
 
void dijkstra(vector<vector<int> > adjacencyMatrix,
              int startVertex)
{
    int nVertices = adjacencyMatrix[0].size();
 
    // shortestDistances[i] will hold the
    // shortest distance from src to i
    vector<int> shortestDistances(nVertices);
 
    // added[i] will true if vertex i is
    // included / in shortest path tree
    // or shortest distance from src to
    // i is finalized
    vector<bool> added(nVertices);
 
    // Initialize all distances as
    // INFINITE and added[] as false
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
 
    // Distance of source vertex from
    // itself is always 0
    shortestDistances[startVertex] = 0;
 
    // Parent array to store shortest
    // path tree
    vector<int> parents(nVertices);
 
    // The starting vertex does not
    // have a parent
    parents[startVertex] = NO_PARENT;
 
    // Find shortest path for all
    // vertices
    for (int i = 1; i < nVertices; i++) {
 
        // Pick the minimum distance vertex
        // from the set of vertices not yet
        // processed. nearestVertex is
        // always equal to startNode in
        // first iteration.
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
 
        // Mark the picked vertex as
        // processed
        added[nearestVertex] = true;
 
        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
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

void init(int N,string startStation)
{
    vector<vector<int>> matrix(N, vector<int>(N));
    cout<<"Enter the path in form of matrix here: "<<endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> matrix[i][j];
               
    // vector<vector<int> > matrix
    //     = { {0,3,7,0,0},
    //     {0,0,2,2,5},
    //     {0,0,0,0,1},
    //     {0,0,0,0,3},
    //     {0,0,0,0,0}};

    dijkstra(matrix, 0);
}

class compare
{
    public:
        bool operator()(PassengerDetails a,PassengerDetails b)
        {
            return a.age < b.age;
        }
};

void addPassenger(string passengerName,int age,string destination)
{
    queue<PassengerDetails> passengersQueue;
    priority_queue<PassengerDetails,vector<PassengerDetails>,compare> passengersAgeQueue;

    PassengerDetails p;
    p.name = passengerName;
    p.age = age;
    p.destination = destination;
    
    passengersQueue.push(p);
    passengersAgeQueue.push(p);
        
    cout<<"Printing Details from Heap:"<<passengersAgeQueue.top().name<<" "<<passengersAgeQueue.top().age<<" "<<passengersAgeQueue.top().destination<<" "<<passengersAgeQueue.top().inQueue<<endl;
    cout<<endl<<"Printing Queue size: "<<passengersQueue.size();
}

int main()
{
    cout<<"WELCOME TO HYPERLOOP PASSENGER BOOKING!!"<<endl;
    
    ifstream inputFile ("input.txt");
    string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        cout<<"Line: "<<line<<endl;
        string command;
        iss >> command;
        cout<<"Command: "<<command<<endl;
        if (command == "INIT") {
            int lineCount;
            string source;
            iss >> lineCount >> source;
            cout<<"Printing INIT: "<<lineCount<<" "<<source<<endl;
            //Call the init function here and pass count and source
        } else if (command == "ADD_PASSENGER") {
            int passengerCount;
            iss >> passengerCount;
            cout<<"Printing PassengerCount: "<<passengerCount<<endl;
            for (int i = 0; i < passengerCount; ++i) {
                string passengerName;
                int age;
                string destination;
                iss>>passengerName >> age >> destination;
                cout<<"Printing Add Passenger: "<<passengerName<<" "<<age<<" "<<destination<<endl;
                //Call addPassenger function here
                // addPassenger(passengerName,age,destination);
            }
        } else if (command == "START_POD") {
            int podNumber;
            iss>>podNumber;
            cout<<"Printing POD count: "<<podNumber<<endl;
            // Process START_POD command
        } else if (command == "PRINT_Q") {
            // Print passenger queue if needed
            //Print no of element and all the element 
        }
    }
    inputFile.close();

    return 0;
}