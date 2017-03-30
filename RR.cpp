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
	public:
		process(){}
		process(int process_no, int burst, int arrival = 0){
			this->process_no = process_no;
			this->burst = burst;
			this->arrival = arrival;
			this->remBurst = burst;
			this->waitTime = 0;
			this->finish = false;
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
	return p1.getArrival() < p2.getArrival();
}
bool comp2(process p1, process p2){
	return p1.getProcessNo() < p2.getProcessNo();   //if true then no swapping
}
int main(){
	int n,k;
	cout<<"enter no of process and time quantum: ";
	cin>>n;
	cin>>k;
	process p[n];
	for(int i=0;i<n;i++){
		int a,b,c;
		cout<<"enter pno burst and arrival: ";
		cin>>a>>b>>c;
		p[i] = process(a,b,c);
	}
	//sort(p,p+n,comp);
	
	
	
	int totalTime = 0;
	for(int i=0;i<n;i++){
		totalTime = totalTime + p[i].getBurst();
	}
	int current = 0;
	int c = 0;
	for(int i=0;i<totalTime;i++){
		//process
		if(p[current].getFinish() == true || p[current].getArrival() > i){
			current = (current+1)%n;
			i--;
			c = 0;
			continue;
		}else{
			p[current].execute();
			for(int j=0;j<n;j++){
				if(p[j].getFinish() == false && j != current){
					p[j].wait();
				}
			}
			c++;
		}
		if(c >= k){
			current = (current+1)%n;
			c = 0;
		}
	}
	
	
	int totalWait = 0;
	for(int i=0;i<n;i++){
		totalWait = totalWait + p[i].getWaitTime();
	}
	
	//sort(p,p+n,comp2);  if required
	cout<<"\tprocess no\tburst\tarrival\twait time"<<endl;
	for(int i =0;i<n;i++){
		cout<<"\t\t"<<p[i].getProcessNo()<<"\t"<<p[i].getBurst()<<"\t"<<p[i].getArrival()<<"\t"<<p[i].getWaitTime()+/*to add arrival of process or start of execution of programs*/p[0].getArrival()<<endl;
	}
	cout<<endl<<"Avarage wait time = "<<(float)totalWait/(float)n<<"\tper Process"<<endl;
	cout<<"Throughput        = "<<(float)n/(float)totalTime<<"\tper Time"<<endl; 
	return 0;
}
