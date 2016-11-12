#include <string>														
#include <iostream>														
#include <unordered_map>												// To save previous states, in order to prevent making repetative states
#include <queue>														// To implement BFS
#include <stack>

using namespace std;

// Global Variables
std::unordered_map<string,int> visited;									// Indicates the visited nodes and actions that led to them
std::unordered_map<string,int>::iterator it;							// Iterator to iterate through all visited nodes

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

string BFS (string root){												// Takes root and executes BFS on Tree as it goes and returns the Goal Node
    
    queue<string> expandQueue;											// Create Expanding Queue
    queue<string> tempQueue;											// Create Temp Queue
    
    expandQueue.push(root);												// Push Root into the Expanding Queue
    visited[root] = 0;													// No Action made the root
    
   // int level = 0;
    while ( !expandQueue.empty() ){										// While expanding Queue is not Empty
        
        while ( !expandQueue.empty() ){									// Copy Expanding Queue to Temp Queue and Emptying the Expanding Queue
            string node = expandQueue.front();
           // cout << node << " " << level << endl;
            expandQueue.pop();
            tempQueue.push(node);
        }
       // level++;
        
        while ( !tempQueue.empty() ){									// For each node in the temporary queue
            
            string node = tempQueue.front();							// Dequeue Front Element from the Temp Queue
            tempQueue.pop();
            
            if (checkForGoal(node))										// If it is Goal State, return Node 
                return node;

            else {														// Insert all the non visited children of the dequeued element into the expanding queue
                string child = Action1(node);
                if (!isVisited(child)) {
                    expandQueue.push(child);
                    visited[child] = 1;									// Add that Node to Visited List (Unordered_map)
                }
              //  cout << child << "===" << node << endl;

                child = Action2(node);
                if (!isVisited(child)){
                    expandQueue.push(child);
                    visited[child] = 2;									// Add that Node to Visited List (Unordered_map)
                }
               // cout << child << "===" << node << endl;
                
                child = Action3(node);
                if (!isVisited(child)){
                    expandQueue.push(child);
                    visited[child] = 3;									// Add that Node to Visited List (Unordered_map)
                }
               // cout << child << "===" << node << endl;
                
                child = Action4(node);
                if (!isVisited(child)){
                    expandQueue.push(child);
                    visited[child] = 4;									// Add that Node to Visited List (Unordered_map)
                }
                //cout << child << "===" << node << endl;
                
                child = Action5(node);
                if (!isVisited(child)){
                    expandQueue.push(child);
                    visited[child] = 5;									// Add that Node to Visited List (Unordered_map)
                }
                //cout << child << "===" << node << endl;
            }
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

    clock_t INIT = clock();                                         // Start Clock

    string result = BFS (initState);
    printResult (result);

    printf("Elapsed Time: %lfms\n", 1000*(double) (clock() - INIT)/ CLOCKS_PER_SEC );

    cout << visited.size();
    
    return 0;
}