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
	memory* m[4];
	m[0] = new memory(0,100);
	m[1] = new memory(1,50);
	m[2] = new memory(2,200);
	m[3] = new memory(3,250);
	int size = 4;
	process* p1 = new process(1,50);
	process* p2 = new process(2,202);
	process* p3 = new process(3,103);
	//first fit
	
	first(m,p1,4);
	first(m,p2,4);
	first(m,p3,4);
	
	worst(m,p1,4);
	worst(m,p2,4);
	worst(m,p3,4);
	
	best(m,p1,4);
	best(m,p2,4);
	best(m,p3,4);
	cout<<"\tprocess\tfirst\tbest\tworst"<<endl<<endl;
	cout<<"\t"<<p1->process_no<<"\t"<<p1->first->block_no<<"\t"<<p1->best->block_no<<"\t"<<p1->worst->block_no<<endl<<endl;
	cout<<"\t"<<p2->process_no<<"\t"<<p2->first->block_no<<"\t"<<p2->best->block_no<<"\t"<<p2->worst->block_no<<endl<<endl;
	cout<<"\t"<<p3->process_no<<"\t"<<p3->first->block_no<<"\t"<<p3->best->block_no<<"\t"<<p3->worst->block_no<<endl<<endl;	
	return 0;
}
