#include<bits/stdc++.h>
using namespace std;
class Graph{
    vector<int> resources;
    vector<int> processes;
    vector<pair<pair<int,int>,int> > relations;
    vector<list<pair<int,int> > > graph;
public:

    Graph(){}
    Graph(vector<int> resources, vector<int> processes, vector<pair<pair<int,int>,int> > relations){
        this->resources = resources;
        this->processes = processes;
        this->relations = relations;
    }
    void plotGraph(){
        for(int i=0;i<processes.size();i++){
            list<pair<int,int> > lst;
            for(int j=0;j<relations.size();j++){
                if(relations[j].first.first == processes[i]){
                    lst.push_back(make_pair(relations[j].first.second,relations[j].second));
                }
            }
            graph.push_back(lst);
        }
    }

    void display(){
        for(int i=0;i<graph.size();i++){
            cout<<processes[i]<<" -> ";
            list<pair<int,int> >::iterator it = graph[i].begin();
            for(;it!=graph[i].end();it++){
                cout<<"("<<(*it).first<<","<<(*it).second<<") ";
            }
            cout<<endl;
        }
    }
};
int main(){
    vector<int> resource;
    vector<int> processe;
    vector<pair<pair<int,int>,int> > relation;
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
        int k,l,m;
        cout<<"enter relation as p->r: and no of instance";
        //relations as p->r request r->p allocated
        cin>>k>>l>>m;
        relation.push_back(make_pair(make_pair(k,l),m));
    }
    Graph g = Graph(resource,processe,relation);
    g.plotGraph();
    g.display();
    return 0;
}
