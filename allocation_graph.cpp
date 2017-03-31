#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
class Graph{
    vector<int> resources;
    vector<int> processes;
    vector<pair<int,int> > relations;
public:

    Graph(){}
    Graph(vector<int> resources, vector<int> processes, vector<pair<int,int> > relations){
        this->resources = resources;
        this->processes = processes;
        this->relations = relations;
    }
    void plotGraph(){
        int matrixSize = resources.size() + processes.size();
        int graph[matrixSize][matrixSize];
        //make all zero
        for(int i=0;i<matrixSize;i++){
            for(int j=0;j<matrixSize;j++){
                graph[i][j] = 0;
            }
        }
        /*//first column and row
        for(int i=0;i<processes.size();i++){
            graph[i][0] = processes[i];
            graph[0][i] = processes[i];
        }
        for(int i=processes.size();i<matrixSize;i++){
            graph[i][0] = resources[i];
            graph[0][i] = resources[i];
        }*/
        //p-p no relation
        for(int i =0;i<processes.size();i++){
            for(int j =0;j<processes.size();j++){
                graph[i][j] = -1;
            }
        }
        //r-r no relations
        for(int i =processes.size();i<matrixSize;i++){
            for(int j =processes.size();j<matrixSize;j++){
                graph[i][j] = -1;
            }
        }
        //relations
        for(int i=0;i<relations.size();i++){
            graph[relations[i].first-1][relations[i].second-1] = 1;
        }
        for(int i=0;i<matrixSize;i++){
            for(int j=0;j<matrixSize;j++){
                cout<<graph[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
};
int main(){
    vector<int> resource;
    vector<int> processe;
    vector<pair<int,int> > relation;
    int r,p,rel;
    cout<<"enter no of resources, processes, relations: ";
    cin>>r>>p>>rel;
    for(int i =0;i<p;i++){
        int k;
        cout<<"process no: ";
        cin>>k;
        processe.push_back(k);
    }
    for(int i =0;i<r;i++){
        int k;
        cout<<"resource no: ";
        cin>>k;
        resource.push_back(k);
    }
    for(int i =0;i<rel;i++){
        char c;
        cout<<"type of relation request->r or allocate ->a : ";
        cin>>c;
        switch(c){
            int k,l;
            case 'r':
                cout<<"enter relation as p->r: ";
                //relations as p->r request r->p allocated
                cin>>k>>l;
                relation.push_back(make_pair(k,l+p));
                break;
            case 'a':
                cout<<"enter relation as r->p: ";
                //relations as p->r request r->p allocated
                cin>>k>>l;
                relation.push_back(make_pair(k+p,l));
                break;
        }
    }
    Graph g = Graph(resource,processe,relation);
    g.plotGraph();
    return 0;
}
