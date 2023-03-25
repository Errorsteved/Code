#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct PCB{
    char name[8];
    int arrival_time;
    int service_time;
    int start_time;
    int finish_time;
    int turn_around_time;
    float Weighted_turnaround_time;
    bool finishornot;
};

struct Process {
    string name; // 进程名
    int arrival_time_rr; // 到达时间
    int burst_time_rr; // CPU执行时间
    int remaining_time_rr; // 剩余执行时间
    int completion_time_rr; // 完成时间
    int turnaround_time_rr; // 周转时间
    float weighted_turnaround_time_rr; // 带权周转时间
};

float sum_turn_around_time=0.0;
float sum_Weighted_turnaround_time=0.0;
struct PCB pcb[4],tem,con_pcb[4],rr[4];
void input();
void sort();
void output();
void fcfsoutput();
void init();
void SJF();
void HRRF();
void round_robin_scheduling(vector<Process> processes, int quantum);

bool compare_arrival_time(Process a, Process b) {
    return a.arrival_time_rr < b.arrival_time_rr;
}

int main(){
    cout<<"fcfs: "<<endl;
    input();
    init();
    sort();
    fcfsoutput();

    cout<<"sjf: "<<endl;
    init();
    SJF();
    output();
    
    cout<<"hrrf: "<<endl;
    init();
    sort();
    HRRF();
    output();

    cout<<"rr: "<<endl;
    init();
    vector<Process> processes = {{pcb[0].name, pcb[0].arrival_time, pcb[0].service_time, pcb[0].service_time}, {pcb[1].name, pcb[1].arrival_time, pcb[1].service_time, pcb[1].service_time}, {pcb[2].name, pcb[2].arrival_time, pcb[2].service_time, pcb[2].service_time},{pcb[3].name, pcb[3].arrival_time, pcb[3].service_time, pcb[3].service_time}};
    int quantum = 1;
    round_robin_scheduling(processes, quantum);

    return 0;
}

void init(){
    sum_turn_around_time=0.0;
    sum_Weighted_turnaround_time=0.0;
    for(int i=0;i<4;i++){
        pcb[i]=con_pcb[i];
    }
    
}

void output(){
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        cout<<setw(24)<<"进程名"<<setw(24)<<"到达时间"<<setw(24)<<"运行时间"<<setw(24)<<"完成时间"<<setw(24)<<"周转时间"<<setw(26)<<"带权周转时间"<<endl;
        for(int i=0;i<4;i++)
            {
               cout<<setw(20)<<pcb[i].name<<setw(20)<<pcb[i].arrival_time<<setw(20)<<pcb[i].service_time<<setw(20)<<pcb[i].finish_time<<setw(20)<<pcb[i].turn_around_time<<setw(20)<<pcb[i].Weighted_turnaround_time<<endl;

            }
        cout<<"平均周转时间:"<<fixed<<setprecision(0)<<sum_turn_around_time/4<<endl;
        cout<<"平均带权周转时间:"<<fixed<<setprecision(0)<<sum_Weighted_turnaround_time/4<<endl;
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void input(){
    cout<<"-------Enter data of four process--------"<<endl;
    for(int i=0;i<4;i++){
        cout<<"Please enter the process name: "<<endl;
        cin>>con_pcb[i].name;
        cout<<"Please enter the arrival time: "<<endl;
        cin>>con_pcb[i].arrival_time;
        cout<<"Please enter the service time: "<<endl;
        cin>>con_pcb[i].service_time;
        cout<<"Please enter the start time: "<<endl;
        cin>>con_pcb[i].start_time;
        //cout<<"Please enter the finish time: "<<endl;
        //cin>>con_pcb[i].finish_time;
        //cout<<"Please enter the turn around time: "<<endl;
        //cin>>pcb[i].turn_around_time;
    }
}

void sort(){
    for(int i=0;i<3;i++){
        for(int j=i+1;j<4;j++){
            if(pcb[i].arrival_time>pcb[j].arrival_time){
                tem=pcb[i];
                pcb[i]=pcb[j];
                pcb[j]=tem;
            }
        }
    }
}

void fcfsoutput(){
    pcb[0].finish_time=pcb[0].service_time+pcb[0].arrival_time;
    pcb[0].turn_around_time=pcb[0].finish_time-pcb[0].arrival_time;
	pcb[0].Weighted_turnaround_time=(float)pcb[0].turn_around_time/pcb[0].service_time;

    for(int i=1;i<4;i++)
        {	 
            if(pcb[i].arrival_time>pcb[i-1].finish_time)
            {
                pcb[i].finish_time=pcb[i].arrival_time+pcb[i].service_time;
                pcb[i].turn_around_time=pcb[i].service_time;
                pcb[i].Weighted_turnaround_time=(float)pcb[i].turn_around_time/pcb[i].service_time;
            }
            else
            {
                pcb[i].finish_time=pcb[i-1].finish_time+pcb[i].service_time;
                pcb[i].turn_around_time=pcb[i].finish_time-pcb[i].arrival_time;
                pcb[i].Weighted_turnaround_time=(float)pcb[i].turn_around_time/pcb[i].service_time;
            }
            
        }  

        for(int i=0;i<4;i++)
            {
                sum_turn_around_time+=pcb[i].turn_around_time;
                sum_Weighted_turnaround_time+=pcb[i].Weighted_turnaround_time;
            }

        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        cout<<setw(24)<<"进程名"<<setw(24)<<"到达时间"<<setw(24)<<"运行时间"<<setw(24)<<"完成时间"<<setw(24)<<"周转时间"<<setw(26)<<"带权周转时间"<<endl;
        for(int i=0;i<4;i++)
            {
               cout<<setw(20)<<pcb[i].name<<setw(20)<<pcb[i].arrival_time<<setw(20)<<pcb[i].service_time<<setw(20)<<pcb[i].finish_time<<setw(20)<<pcb[i].turn_around_time<<setw(20)<<pcb[i].Weighted_turnaround_time<<endl;

            }
        cout<<"平均周转时间:"<<fixed<<setprecision(0)<<sum_turn_around_time/4<<endl;
        cout<<"平均带权周转时间:"<<fixed<<setprecision(0)<<sum_Weighted_turnaround_time/4<<endl;
        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void SJF()
{  
	cout<<"SJF调度算法:"<<endl;
	int i,j,min_time,index;
    int last_finishedPCB_index;    //记录上一次已经运行的进程的数组下标
   
     // 运行第一个到达的进程  得到它的完成时间、周转时间等,并设置为已访问
    pcb[0].finish_time=pcb[0].arrival_time+pcb[0].service_time;
    pcb[0].turn_around_time=pcb[0].finish_time-pcb[0].arrival_time;
    pcb[0].Weighted_turnaround_time=(float)pcb[0].turn_around_time/pcb[0].service_time;
    pcb[0].finishornot=true;
    last_finishedPCB_index=0; 

     //下面在剩下的进程中循环找出运行时间最小的进程，
     //计算它的完成时间、周转时间等，并设置为已访问。 
	 //先找出没有访问过的运行时间最小的进程的下标
    for(i=0;i<4;i++)
    {     
	    index=-1;
	    min_time=100;
        for(j=0;j<4;j++)
		{
			if(min_time>pcb[j].service_time&&pcb[j].finishornot==false&&pcb[j].arrival_time<=pcb[last_finishedPCB_index].finish_time)
			{
				min_time=pcb[j].service_time;
				index=j;
			}
		}

		if(pcb[index].arrival_time<=pcb[last_finishedPCB_index].finish_time)
		{
			pcb[index].finish_time=pcb[last_finishedPCB_index].finish_time+pcb[index].service_time;
			pcb[index].turn_around_time=pcb[index].finish_time-pcb[index].arrival_time;
			pcb[index].Weighted_turnaround_time=(float)pcb[index].turn_around_time/pcb[index].service_time;
		}
		if(pcb[index].arrival_time>pcb[last_finishedPCB_index].finish_time)
		{
			pcb[index].finish_time=pcb[index].arrival_time+pcb[index].service_time;
			pcb[index].turn_around_time=pcb[index].service_time;
			pcb[index].Weighted_turnaround_time=(float)pcb[index].turn_around_time/pcb[index].service_time; 
		}
		pcb[index].finishornot =true;
		last_finishedPCB_index=index;
	}  

    for(i=0;i<4;i++)
		{
			sum_turn_around_time+=pcb[i].turn_around_time;
			sum_Weighted_turnaround_time+=pcb[i].Weighted_turnaround_time;
		}
}

void HRRF(){
    pcb[0].finish_time=pcb[0].arrival_time+pcb[0].service_time;
    pcb[0].turn_around_time=pcb[0].finish_time-pcb[0].arrival_time;
    pcb[0].Weighted_turnaround_time=(float)pcb[0].turn_around_time/pcb[0].service_time;
    int index=1;
    int last_finishedPCB_index=0;
    float response_ration[4];

    for(int i=1;i<4;i++){
        for(int j=1;j<4;j++){
            if(pcb[last_finishedPCB_index].finish_time>=pcb[j].arrival_time){
                response_ration[j]=1+(pcb[last_finishedPCB_index].finish_time-pcb[j].arrival_time)/pcb[j].service_time;
            }
            else{
                response_ration[j]=1;
            }
        }//按顺序计算剩余作业响应比

        for(int k=1;k<4;k++){
            for(int a=1;a<4;a++){
                if(response_ration[index]>response_ration[a]){
                    index=a;
                    break;
                }
            }
        }//找到剩余作业最高响应比

        //计算当前作业的完成时间，周转时间，带权周转时间
        if(pcb[index].arrival_time<=pcb[last_finishedPCB_index].finish_time)
		{
			pcb[index].finish_time=pcb[last_finishedPCB_index].finish_time+pcb[index].service_time;
			pcb[index].turn_around_time=pcb[index].finish_time-pcb[index].arrival_time;
			pcb[index].Weighted_turnaround_time=(float)pcb[index].turn_around_time/pcb[index].service_time;
		}
		if(pcb[index].arrival_time>pcb[last_finishedPCB_index].finish_time)
		{
			pcb[index].finish_time=pcb[index].arrival_time+pcb[index].service_time;
			pcb[index].turn_around_time=pcb[index].service_time;
			pcb[index].Weighted_turnaround_time=(float)pcb[index].turn_around_time/pcb[index].service_time; 
        }
        last_finishedPCB_index=index;
    }

        for(int j=0;j<4;j++)
		{
			sum_turn_around_time+=pcb[j].turn_around_time;
			sum_Weighted_turnaround_time+=pcb[j].Weighted_turnaround_time;
		}

}

void round_robin_scheduling(vector<Process> processes, int quantum) {
    sort(processes.begin(), processes.end(), compare_arrival_time);

    queue<Process> q;
    int current_time_rr = 0;
    int i = 0;
    float total_turnaround_time_rr = 0;
    float total_weighted_turnaround_time_rr = 0;
    int index_rr=0;

    while (i < processes.size() || !q.empty()) {
        if (q.empty()) {
            q.push(processes[i]);
            current_time_rr = processes[i].arrival_time_rr;
            i++;
        }

        Process current_process = q.front();
        q.pop();

        if (current_process.remaining_time_rr <= quantum) {
            current_time_rr += current_process.remaining_time_rr;
            current_process.completion_time_rr = current_time_rr;
            current_process.turnaround_time_rr = current_process.completion_time_rr - current_process.arrival_time_rr;
            current_process.weighted_turnaround_time_rr = (float)current_process.turnaround_time_rr / current_process.burst_time_rr;
            total_turnaround_time_rr += current_process.turnaround_time_rr;
            total_weighted_turnaround_time_rr += current_process.weighted_turnaround_time_rr;
        
            cout << "Process " << current_process.name << " finished at time " << current_process.completion_time_rr << endl;
            cout << "Turnaround time: " << current_process.turnaround_time_rr << endl;
            cout << "Weighted turnaround time: " << current_process.weighted_turnaround_time_rr << endl;

            while (i < processes.size() && processes[i].arrival_time_rr <= current_time_rr) {
                q.push(processes[i]);
                i++;
            }
        } else {
            current_process.remaining_time_rr -= quantum;
            current_time_rr += quantum;
            q.push(current_process);

            while (i < processes.size() && processes[i].arrival_time_rr <= current_time_rr) {
                q.push(processes[i]);
                i++;
            }
        }
    }

    cout << "Average turnaround time: " << total_turnaround_time_rr / processes.size() << endl;
    cout << "Average weighted turnaround time: " << total_weighted_turnaround_time_rr / processes.size() << endl;
}