#include <string>														
#include <iostream>														
#include <unordered_map>												// To save previous states, in order to prevent making repetative states
#include <queue>														// To implement visited map
#include <stack>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Global Variables:
std::unordered_map<string,int> visited;									// Indicates the visited nodes and actions that led to them
std::unordered_map<string,int>::iterator it;							// Iterator to iterate through all visited nodes

char Goal [4][4] = {{'A','B','C','D'},{'L','N','N','E'},{'K','N','N','F'},{'J','I','H','G'}};

// Classes:
class Prioritize {
public:
     int operator() ( const pair <int, pair <int, string> > &pair1, const pair <int, pair <int, string> > &pair2 ) {
         return pair1.first > pair2.first;
     }
};

// Functions
bool checkForGoal (string array){
    
    if ( array[0] == 'A' &&
         array[1] == 'B' &&
         array[2] == 'C' &&
         array[3] == 'D' &&
         array[4] == 'L' &&
         array[5] == 'N' &&
         array[6] == 'N' &&
         array[7] == 'E' &&
         array[8] == 'K' &&
         array[9] == 'N' &&
         array[10] == 'N' &&
         array[11] == 'F' &&
         array[12] == 'J' &&
         array[13] == 'I' &&
         array[14] == 'H' &&
         array[15] == 'G' )  

        return true;
    
    return false;
}

void string_to_arr (string state, char answer[4][4]){

    int k = 0;

    for ( int i = 0; i < 4; i++ ){
        for ( int j = 0; j < 4; j++ ){
            answer[i][j] = state[k];
            k++;
        }
    }
}

int h (string input){                                                    // The heuristic function used to set priority queue is Manhattan Distance 
    
    char state[4][4];
    string_to_arr(input,state);
    int sum = 0;                                                        // Sum of Manhattan Distances of Each cell with it's goal place

    for ( int i = 0; i < 4; i++ ){
        for ( int j = 0; j < 4; j++ ){
            for ( int k = 0; k < 4; k++ ){
                for ( int p = 0; p < 4; p++ ){
                    if ( state[i][j] == Goal[k][p] ){
                    	if ( state[i][j] == 'N' ) {
                			if ( (i == 0 && j == 1) || (i == 0 && j == 2) || (i == 1 && j == 0) || (i == 1 && j == 3) 
                				 || (i == 2 && j == 0) || (i == 2 && j == 3) || (i == 3 && j == 1) || (i == 3 && j == 2) )
                				sum += 1;
                			if ( (i == 1 && j == 1) || (i == 2 && j == 2) || (i == 1 && j == 2) || (i == 2 && j == 1) )
                				sum += 0;
                			if ( (i == 0 && j == 0) || (i == 3 && j == 3) || (i == 3 && j == 0) || (i == 3 && j == 0) )
                				sum += 2;
                		}
                        else 
                            sum += abs(k-i) + abs(p-j);
                    }
                }
            }
        }
    }

    return sum;
}

bool isVisited (string state){

    if ( visited.find(state) != visited.end() )
    	return true;

    return false;
}

string Action1 (string state){
	
    swap (state[1], state[5]);
    swap (state[0], state[1]);
    swap (state[0], state[4]);
    
    return state;
}

string Action2 (string state){
	
    swap (state[3], state[7]);
    swap (state[2], state[3]);
    swap (state[2], state[6]);
    
    return state;
}

string Action3 (string state){
    
    swap (state[9], state[13]);
    swap (state[8], state[9]);
    swap (state[8], state[12]);
    
    return state;
}

string Action4 (string state) {
    
    swap (state[11], state[15]);
    swap (state[10], state[11]);
    swap (state[10], state[14]);
    
    return state;
}

string Action5 (string state){
    
    swap (state[6], state[10]);
    swap (state[5], state[6]);
    swap (state[5], state[9]);
 
    return state;
}

string Astar (string root){												// Takes root and executes Astar on Tree as it goes and returns the Goal Node
    
    // Create Expanding Queue < f(n), < g(n), string > >
    priority_queue <pair <int, pair <int, string> >, vector < pair <int, pair <int, string> > >, Prioritize > PQueue;

    PQueue.push(make_pair(0 + h(root), make_pair(0, root)));			// Push Root into the Expanding Queue
    visited[root] = 0;													// No Action made the root
    
    while ( !PQueue.empty() ){											// While PQueue is not Empty
                    
            auto node = PQueue.top();							    	// Dequeue Front Element
            PQueue.pop();
            
            if (checkForGoal(node.second.second))						// If it is Goal State, return node.second.second (goal string) 
                return node.second.second;

            else {														// Insert all the non visited children of the dequeued element into the PQueue
                string child = Action1(node.second.second);
                if (!isVisited(child)) {
                    PQueue.push(make_pair((node.second.first + 4) + h(child), make_pair((node.second.first + 4), child)));
                    visited[child] = 1;									// Add that Node to Visited List (Unordered_map)
                }
               // cout << child << "===" << node << endl;

                child = Action2(node.second.second);
                if (!isVisited(child)){
                    PQueue.push(make_pair((node.second.first + 4) + h(child), make_pair((node.second.first + 4), child)));
                    visited[child] = 2;									// Add that Node to Visited List (Unordered_map)
                }
                //cout << child << "===" << node << endl;
                
                child = Action3(node.second.second);
                if (!isVisited(child)){
                    PQueue.push(make_pair((node.second.first + 4) + h(child), make_pair((node.second.first + 4), child)));
                    visited[child] = 3;									// Add that Node to Visited List (Unordered_map)
                }
               // cout << child << "===" << node << endl;
                
                child = Action4(node.second.second);
                if (!isVisited(child)){
                    PQueue.push(make_pair((node.second.first + 4) + h(child), make_pair((node.second.first + 4), child)));
                    visited[child] = 4;									// Add that Node to Visited List (Unordered_map)
                }
              //  cout << child << "===" << node << endl;
                
                child = Action5(node.second.second);
                if (!isVisited(child)){
                    PQueue.push(make_pair((node.second.first + 4) + h(child), make_pair((node.second.first + 4), child)));
                    visited[child] = 5;									// Add that Node to Visited List (Unordered_map)
                }
              //  cout << child << "===" << node << endl;
            }
        }
      
    return root;
}

void printResult (string node){
    
    stack<int> myStack;
    int i;
    
    while ( visited[node] != 0 ){										// While the Node is not Root
        myStack.push(visited[node]);
        switch (visited[node]) {
            case 1: {
            	for ( i = 0; i < 3; i++ )
                	node = Action1(node);								// Results in counter action 1
                break;
            }
            case 2: {
            	for ( i = 0; i < 3; i++ )
                	node = Action2(node);								// Results in counter action 2
                break;
            }
            case 3: {
            	for ( i = 0; i < 3; i++ )
                	node = Action3(node);								// Results in counter action 3
                break;
            }
            case 4: {
            	for ( i = 0; i < 3; i++ )
                	node = Action4(node);								// Results in counter action 4
                break;
            }
            case 5: {
            	for ( i = 0; i < 3; i++ )
               		node = Action5(node);								// Results in counter action 5
                break;
            }
        }
    }

    cout << myStack.size() << endl;									// Prints the size of Stack (Number of Moves)
    
    while ( !myStack.empty() ){
        cout << myStack.top() << endl;								// Group Number of Rotating Tiles (Starting from Root)
        myStack.pop();
    }
}

int main(){
    
    string initState;
    cout << "Enter The Initial Order of Tiles: " << endl;
    cin >> initState;

    clock_t INIT = clock();											// Start Clock

    string result = Astar (initState);
    printResult (result);
    
    printf("Elapsed Time: %lfms\n", 1000*(double) (clock() - INIT)/ CLOCKS_PER_SEC );

    cout << visited.size() << endl;

    return 0;
}