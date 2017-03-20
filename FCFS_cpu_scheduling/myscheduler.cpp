//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
// Galip Cagan

vector<ThreadDescriptorBlock> threads;
ThreadDescriptorBlock initCPU = {99,99,99,99};
vector<bookThreads> infoThreads;

int i = 0;
int threadCap;
int goner=0;
int freeCPU=-1;

int cpuFinder(ThreadDescriptorBlock **CPUs, int num_cpu){

	int find;
	for(int cindex=0; cindex<num_cpu; cindex++){
		if(CPUs[cindex] == NULL){
			cout<<"[CPUFINDER]===CPU: " <<cindex << " ; is empty"<<endl;
			find = cindex;
			break;
		}
	}
	return find;	
}

int waiterFinder(int timer){
	int waiting;
	for(int thindex = 0; thindex <threadCap;thindex++){
		if(infoThreads[thindex].cond == 1 && (infoThreads[thindex].arriving_time<=timer)) {
			waiting = thindex;
			cout<<"[waiterFinder]=== Waiting thread is: "<<infoThreads[thindex].tid<<endl;
			break;	
		}
	}

return (waiting);
}

bool cpuChecker(int index){ 
	if(index == 0){
		if(threads[index].remaining_time == 0){
			return false;
		}
		else
			return true;
	}
	else if(threads[index].remaining_time !=0){
		return true;
	}
	else
		cpuChecker((index)-1);

}

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
    
    threads.reserve(threads.capacity() + 1);
    
    ThreadDescriptorBlock threadTest;
    // store data in struct
    threadTest.tid = tid;
    threadTest.arriving_time = arriving_time;
    threadTest.remaining_time = remaining_time;
    threadTest.priority = priority;

    // copy to vector
    threads.push_back(threadTest);
    
   // cout<<"Id:"<<threads[i].tid<<endl;
    cout<<"[CREATETHREAD]~~~~~Creating thread id: "<< threads[i].tid<<endl;
    i++;
	//geting size
	threadCap =threads.capacity();


	//for free threads
	infoThreads.reserve(infoThreads.capacity() +1);

	bookThreads infoTest;

	infoTest.tid = tid;
	infoTest.arriving_time = arriving_time;
	infoTest.remaining_time = remaining_time;
	infoTest.priority = priority;
	infoTest.cond = 1;

	infoThreads.push_back(infoTest);
	
}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
    
   	 int cIndex;
	switch(policy)
	{
		case FCFS:	
		
		if(num_cpu>= threadCap){
		
			if(timer ==0){
				for(cIndex=0; cIndex <=threadCap ; cIndex++){
					CPUs[cIndex] = &initCPU;  //decided to make an initializer just to make cpus and not get segfaults
				}
			}

			// running threads into CPUS

			for(int thindex=0; thindex<threads.size(); thindex++){
				if(timer>= threads[thindex].arriving_time){
					CPUs[thindex] = &threads[thindex];
				}
			}
	
			// Checking Remaining Times
			for(int prindex=0 ; prindex<threads.size(); prindex++){
			cout<<"[FCFS]Thread Remaining tid: " <<threads[prindex].tid <<" time : "<<threads[prindex].remaining_time<<endl;
			//cout<<"[FCFS]Thread Rem_time 1: "<<threads[1].remaining_time<<endl;
			}
			// Remaining time is 0 for threads
			for(int rindex=0; rindex<threads.size(); rindex++){
				if(threads[rindex].remaining_time ==0){
					CPUs[rindex] = NULL;
				}		
			}
			
			//recursion function checks all threads have reaminig of 0 or not 
			if(((bool)(cpuChecker(threadCap))) == false ){
				cout<<"[FCFS]CPU is all 0 "<<endl;
				return false;
			}
		}

		else if(num_cpu < threadCap){////////////////////////////////////////the other case////////////////////////////////////////////
			if(timer ==0){
				for(cIndex=0; cIndex <=threadCap ; cIndex++){
				//	if(CPUs[cIndex].)
					CPUs[cIndex] = &initCPU;  //decided to make an initializer just to make cpus and not get segfaults
				}
				
			}
		// running threads into CPUS

			for(int thindex=0; thindex<num_cpu; thindex++){
				if(timer>= threads[thindex].arriving_time && (CPUs[thindex] == &initCPU || CPUs[thindex] == NULL)){
					CPUs[thindex] = &threads[thindex];
				//	infoCPU[thindex].free = 1;
					infoThreads[thindex].cond = 0;
				//	cout<<"infothread[ "<<thindex<<" ].cond: "<<infoThreads[thindex].cond << endl;
				}
			}

			
			//waiter finder
						
			// Checking Remaining Times
			for(int prindex=0 ; prindex<threads.size(); prindex++){
			cout<<"[FCFS2]Thread Remaining tid: " <<threads[prindex].tid <<" time : "<<threads[prindex].remaining_time
				<<" cpus0tid: "<< CPUs[0]->tid <<" cpus0rem: "<<CPUs[0]->remaining_time <<
					" cpus1.tid: "<<CPUs[1]->tid<< " cpus1.remtime: "<< CPUs[1]->remaining_time <<endl;
			}
	
			
			// Remaining time is 0 for threads
			for(int rindex=0; rindex<threads.size(); rindex++){
				if(threads[rindex].remaining_time ==0){
						CPUs[rindex] = NULL;
				}
			}

				if(waiterFinder(timer) !=-1 && CPUs[cpuFinder(CPUs, num_cpu)] == NULL){
				freeCPU = cpuFinder(CPUs, num_cpu);
				CPUs[freeCPU] = &threads[waiterFinder(timer)];
				}
		
			//recursion function checks all threads have reaminig of 0 or not 
			if(((bool)(cpuChecker(threadCap))) == false ){
				cout<<"[FCFS2]CPU is all 0 "<<endl;
				return false;
			}
			
		}
			break;

		case STRFwoP:	//Shortest Time Remaining First, without preemption

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption

			break;
		case PBS:		//Priority Based Scheduling, with preemption
						break;

//********************************************************************************************
		default:
			cout<<"Invalid policy!\n";
			throw 0;
	}
	return true;
}


