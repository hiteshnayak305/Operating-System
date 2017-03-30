#include<iostream>
#include<algorithm>
using namespace std;
class process{
		int process_no;
		int burst;
		int arrival;
		int remBurst;
		int waitTime;
		bool finish;
		int priority;
	public:
		process(){}
		process(int process_no, int burst, int priority, int arrival = 0){
			this->process_no = process_no;
			this->burst = burst;
			this->arrival = arrival;
			this->remBurst = burst;
			this->waitTime = 0;
			this->finish = false;
			this->priority = priority;
		}
		
		int getProcessNo(){
			return process_no;
		}
		int getBurst(){
			return burst;
		}
		int getWaitTime(){
			return waitTime - arrival;
		}
		bool getFinish(){
			return finish;
		}
		int getArrival(){
			return arrival;
		}
		int getPriority(){
			return priority;
		}
		
		void execute(){
			remBurst--;
			if(remBurst <= 0)
				finish = true;
		}
		void wait(){
			waitTime++;
		}
};
bool comp(process p1, process p2){
	if(p1.getPriority() == p2.getPriority())
		return p1.getArrival() < p2.getArrival();
	else
		return p1.getPriority() < p2.getPriority();
}

bool comp2(process p1, process p2){
	return p1.getProcessNo() < p2.getProcessNo();   //if true then no swapping
}
int main(){
	int n,k;
	cout<<"enter no of process :";
	cin>>n;
	process p[n];
	for(int i=0;i<n;i++){
		int a,b,c,d;
		cout<<"enter pno burst priority and arrival: ";
		cin>>a>>b>>c>>d;
		p[i] = process(a,b,c,d);
	}
	sort(p,p+n,comp);
	
	int totalTime = 0;
	for(int i=0;i<n;i++){
		totalTime = totalTime + p[i].getBurst();
	}
	int current = 0;
	for(int i=0;i<totalTime;i++){
		//process
		p[current].execute();
		for(int j=current+1;j<n;j++){
			p[j].wait();
		}
		if(p[current].getFinish() == true){
			current++;
		}	
	}
	
	
	int totalWait = 0;
	for(int i=0;i<n;i++){
		totalWait = totalWait + p[i].getWaitTime();
	}
	
	sort(p,p+n,comp2);  //if required
	cout<<"\tprocess no\tburst\tpriority\tarrival\twait time"<<endl;
	for(int i =0;i<n;i++){
		cout<<"\t\t"<<p[i].getProcessNo()<<"\t"<<p[i].getBurst()<<"\t"<<p[i].getPriority()<<"\t"<<p[i].getArrival()<<"\t"<<p[i].getWaitTime()+/*to add arrival of process or start of execution of programs*/p[0].getArrival()<<endl;
	}
	cout<<endl<<"Avarage wait time = "<<(float)totalWait/(float)n<<"\tper Process"<<endl;
	cout<<"Throughput        = "<<(float)n/(float)totalTime<<"\tper Time"<<endl; 
	return 0;
}
