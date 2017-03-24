#include<bits/stdc++.h>
#include<iostream>
using namespace std;
class memory;
class process{
	public:
		int process_no;
		int size;
		memory* best;
		memory* worst;
		memory* first;
		process(int process_no, int size){
			this->process_no = process_no;
			this->size = size;
			best = NULL;
			best = NULL;
			best = NULL;
		}
};
class memory{
	public:
		int size;
		int block_no;
		bool occupied;
		int process_no;
	memory(int block_no, int size){
		this->block_no = block_no;
		this->size = size;
		occupied = false;
	}
	void allocate(process p){
		occupied = true;
		this->process_no = p.process_no; 
	}
	void free(process p){
		occupied = false;
	}
};

void first(memory* m[],process* p,int size){
	for(int i=0;i<size;i++){
		if(m[i]->size >= p->size){
			p->first = m[i];
			return;
		}
	}
}

void worst(memory* m[],process* p,int size){
	memory* mx = m[0];
	for(int i=0;i<size;i++){
		if(m[i]->size > mx->size){
			mx = m[i];
		}
	}
	p->worst = mx;
}

void best(memory* m[],process* p,int size){
	int d = 1000000;
	for(int i=0;i<size;i++){
		if(m[i]->size >= p->size && m[i]->size - p->size <d){
			p->best = m[i];
			d = m[i]->size - p->size;
		}
	}
}

int main(){
	int n,l;
	cout<<"enter no of memory blocks: ";
	cin>>n;
	memory* m[n];
	for(int i=0;i<n;i++)
	{
		int a,b;
		cout<<"enter block_no and size:" ;
		cin>>a>>b;
		m[i] = new memory(a,b);
	}
	cout<<"enter no of processes:";
	cin>>l;
	process* p[l];
	for(int i=0;i<l;i++)
	{
		int a,b;
		cout<<"enter process no and size: ";
		cin>>a>>b;
		p[i] = new process(a,b);
		first(m,p[i],n);
		best(m,p[i],n);
		worst(m,p[i],n);
	}
	cout<<endl<<endl;
	cout<<"\t* process\tfirst\tbest\tworst *"<<endl<<endl;
	for(int i=0;i<l;i++){
		cout<<"\t* "<<p[i]->process_no<<"\t\t"<<p[i]->first->block_no<<"\t"<<p[i]->best->block_no<<"\t"<<p[i]->worst->block_no<<" *"<<endl<<endl;
	}	
	return 0;
}
