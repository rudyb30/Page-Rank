#include <iostream>
#include <utility>
#include <set>
#include <vector>
#include <iomanip>
using namespace std;

class AdjList{
//this class will construct the graph through an adjacency list
public:
    vector<pair<string, vector<pair<string, float >>>> graph;
    pair<string, vector<pair<string, float >>> inner;
    vector<pair<string, float>> secondInner;
    pair <string, float> thirdInner;
    
   /* from top to bottom these variables represent the following structure: a variable to represent the graph in its entirety, a pair that holds a single total line of the adjacency list, a variable that represents the list of values a single vertex (webpage) is pointing to, the individual page being pointed to and 1/nth of the total page rank*/
    AdjList(vector<pair<string, string>> graphPair, set<string> pageList);
    set<string> webPageList;
    vector<pair<string, string>> pagePair;
    void computeRanks(int power);
    
private:
    void printOutput(vector<float> ranks);
    void initRank();
};


void AdjList:: computeRanks(int power){
  //this function handles the power iteration computations
    initRank();//helper function to initialize the rank values in the adjacency list
    float rankVal;
    vector<float> newRanks;

    for(int i =0; i <webPageList.size(); i++){
        newRanks.push_back((float)1/(float)webPageList.size());
    }
    
    for(int  p=0; p < power -1; p++){
        for(auto x: webPageList){
            //this outer loop iterates through each unqiue web page by string
            rankVal = 0;
            for(int i=0; i < webPageList.size(); i++){
                //for each unique string every web page is visited see if the web page is poining to that string
            
                for(int j = 0; j< graph[i].second.size(); j++){
                 //this loop goes through the webpages each page is pointing to
                    if(graph[i].second[j].first == x)
                    //if the value from the outer loop is the same as one of these connections the website is being pointed to
                    rankVal+= graph[i].second[j].second * newRanks[i];
                    //if the website is being pointed to the partial rank value is added to the total
              }
            }
            newRanks.push_back(rankVal);//adds the total rank value for a unqiue website to a vector
        }
        newRanks.erase(newRanks.begin(), newRanks.begin() + webPageList.size());
        //this deletes the previous power iteration values before the next iteration
   }
    printOutput(newRanks);//prints the rank values once all power iterations are complete
}


void AdjList::printOutput(vector<float> ranks){
//this function is used to display the proper output after all power iterations
    int rankCount =0;
    for(auto x: webPageList){
        cout<< x << " " << fixed <<setprecision(2) <<ranks[rankCount] << endl;
        rankCount++;
    }
    
}
void AdjList:: initRank(){
//this function initializes the initial rank values before power iterations
    
    for(int i =0; i < graph.size(); i++){
        
        for(int j =0; j < graph[i].second.size(); j++){
           
            graph[i].second[j].second = 1/(float)graph[i].second.size();
            
/*here this statement reflects that a piece of the rank is the split between all the vertices that
that one incoming vertex is pointing to*/
        }
        
    }
}

AdjList:: AdjList(vector<pair<string, string>> graphPair, set<string> pageList){
//this function constructs the initial adjacency list without rank values
    webPageList = pageList;//initialize a set variable for use in the power iteration calculation function
    pagePair = graphPair;
    bool firstInsert = true;
    bool multOutDegree;

      for(auto x : pageList){
          multOutDegree = false;
//the set is used to loop through each unique occurence of a web page and to keep alphabetical order
    for(int i =0; i < graphPair.size(); i++){
        
        if(!firstInsert)
         multOutDegree = true;
        
        if(graphPair[i].first == x && firstInsert){
//this code works to initialize one row of the adjacency list for a "from" variable not already present in the list
            inner.first = graphPair[i].first;
            thirdInner.first = graphPair[i].second;
            secondInner.push_back(thirdInner);
            firstInsert = false;
         
          }
        
        if(graphPair[i].first == x && multOutDegree){
//this code works to insert a new connection for a "from" variable already present in the adjacency list
            thirdInner.first = graphPair[i].second;
            secondInner.push_back(thirdInner);
           
          
              }
           }

     inner.second = secondInner;
     secondInner.clear();
     graph.push_back(inner);
     firstInsert = true;
          
   }
    
}

int main(){
    set<string> pageList;
    vector<pair<string, string>> graphPair;
    pair<string, string> lineSegment;
    int lines, power;
    string from, to;
    cin >> lines;
    cin >> power;
    //add cin >> power iterations
    
    for(int i= 0; i < lines; i++){
        cin >> from;
        cin >> to;
        
        pageList.insert(to);
        pageList.insert(from);
        lineSegment.first = from;
        lineSegment.second = to;
        graphPair.push_back(lineSegment);
    }
    AdjList adj = AdjList(graphPair, pageList);//construct adjaceny list
    adj.computeRanks(power);//compute the ranks for each page after all power iterations 
}
