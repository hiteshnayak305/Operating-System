#include<iostream>
#include<algorithm>
using namespace std;
class memory;
class process{
		int process_no;
		int size;
		memory* best;
		memory* worst;
		memory* first;
	public:
		process(int process_no, int size){
			this->process_no = process_no;
			this->size = size;
			best = NULL;
			worst = NULL;
			first = NULL;
		}
		void setFirst(memory* m){
			this->first = m;
		}
		void setBest(memory* m){
			this->best = m;
		}
		void setWorst(memory* m){
			this->worst = m;
		}
		
		int getProcessNo(){
			return process_no;
		}
		int getSize(){
			return size;
		}
		memory* getFirst(){
			return first;
		}
		memory* getBest(){
			return best;
		}
		memory* getWorst(){
			return worst;
		}
};
class memory{
		int size;
		int block_no;
		bool occupied;
		int process_no;
		int remSize;
	public:
		memory(int block_no, int size){
			this->block_no = block_no;
			this->size = size;
			this->remSize = size;
			this->occupied = false;
			this->process_no = -1;
		}
		
		int getSize(){
			return size;
		}
		int getBlockNo(){
			return block_no;
		}
		int getStatus(){
			return occupied;
		}
		int getProcessNo(){
			return process_no;
		}
		int getRemSize(){
			return remSize;
		}
		
		void allocate(process p){
			this->occupied = true;
			this->process_no = p.getProcessNo();
			this->remSize = this->size - p.getSize(); 
		}
		void free(){
			this->occupied = false;
			this->process_no = -1;
			this->remSize = this->size;
		}
};

int cond(memory* m){
	memory* mt = m;
	if(mt == NULL)
		return -1;
	else
		return mt->getBlockNo();
}

void sort1(memory* m[],int n){
	for(int i =0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(m[i]->getSize() > m[j]->getSize())
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
		if(m[i]->getSize() >= p->getSize() && m[i]->getStatus() == false){
			p->setFirst(m[i]);
			m[i]->allocate(*p);
			return;
		}
	}
}

void worst(memory* m[],process* p,int size){
	for(int i=size-1;i>=0;i--){
		if(m[i]->getSize() >= p->getSize() && m[i]->getStatus() == false){
			p->setWorst(m[i]);
			m[i]->allocate(*p);
			return;
		}
	}
}

void best(memory* m[],process* p,int size){
	for(int i=0;i<size;i++){
		if(m[i]->getSize() >= p->getSize() && m[i]->getStatus() == false){
			p->setBest(m[i]);
			m[i]->allocate(*p);
			return;
		}
	}
}

int main(){
	int n,l;
	int remFirst=0, remBest=0, remWorst=0;
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
	for(int i=0;i<n;i++){
		if(m[i]->getStatus() == true){
			remFirst = remFirst + m[i]->getRemSize();
		}
	}
	reset(m,n);
	//sort memory block
		sort1(m,n);
	for(int i =0;i<l;i++){			
		best(m,p[i],n);
	}
	for(int i=0;i<n;i++){
		if(m[i]->getStatus() == true){
			remBest = remBest + m[i]->getRemSize();
		}
	}
	reset(m,n);
	for(int i =0;i<l;i++){
		worst(m,p[i],n);
	}
	for(int i=0;i<n;i++){
		if(m[i]->getStatus() == true){
			remWorst = remWorst + m[i]->getRemSize();
		}
	}
	reset(m,n);
	cout<<endl<<endl;
	cout<<"\t* process\tfirst\tbest\tworst *"<<endl<<endl;
	for(int i=0;i<l;i++){
		cout<<"\t* "<<p[i]->getProcessNo()<<"\t\t"<<cond(p[i]->getFirst())<<"\t"<<cond(p[i]->getBest())<<"\t"<<cond(p[i]->getWorst())<<" \t*"<<endl<<endl;
	}
	cout<<"\t* "<<"total waste"<<"\t"<<remFirst<<"\t"<<remBest<<"\t"<<remWorst<<" \t*"<<endl<<endl;	
	return 0;
}
