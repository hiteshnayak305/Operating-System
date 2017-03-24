#include<iostream>
#include<algorithm>
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
			worst = NULL;
			first = NULL;
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
		this->occupied = false;
		this->process_no = -1;
	}
	void allocate(process p){
		this->occupied = true;
		this->process_no = p.process_no; 
	}
	void free(){
		this->occupied = false;
		this->process_no = -1;
	}
};

int cond(memory* m){
	memory* mt = m;
	if(mt == NULL)
		return -1;
	else
		return mt->block_no;
}

void sort1(memory* m[],int n){
	for(int i =0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(m[i]->size > m[j]->size)
			{
				memory* temp = m[i];
				m[i] = m[j];
				m[j] = temp;
			}
		}
	}
}


void reset(memory* m[],int n){
	for(int i =0;i<n;i++){
		m[i]->free();
	}
}
void first(memory* m[],process* p,int size){
	for(int i=0;i<size;i++){
		if(m[i]->size >= p->size && m[i]->occupied == false){
			p->first = m[i];
			m[i]->allocate(*p);
			return;
		}
	}
}

void worst(memory* m[],process* p,int size){
	for(int i=size-1;i>=0;i--){
		if(m[i]->size >= p->size && m[i]->occupied == false){
			p->worst = m[i];
			m[i]->allocate(*p);
			return;
		}
	}
}

void best(memory* m[],process* p,int size){
	for(int i=0;i<size;i++){
		if(m[i]->size >= p->size && m[i]->occupied == false){
			p->best = m[i];
			m[i]->allocate(*p);
			return;
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
	}
	for(int i =0;i<l;i++){
		first(m,p[i],n);
	}
	reset(m,n);
	//sort memory block
		sort1(m,n);
	for(int i =0;i<l;i++){			
		best(m,p[i],n);
	}
	reset(m,n);
	for(int i =0;i<l;i++){
		worst(m,p[i],n);
	}
	reset(m,n);
	cout<<endl<<endl;
	cout<<"\t* process\tfirst\tbest\tworst *"<<endl<<endl;
	for(int i=0;i<l;i++){
		cout<<"\t* "<<p[i]->process_no<<"\t\t"<<cond(p[i]->first)<<"\t"<<cond(p[i]->best)<<"\t"<<cond(p[i]->worst)<<" \t*"<<endl<<endl;
	}	
	return 0;
}
