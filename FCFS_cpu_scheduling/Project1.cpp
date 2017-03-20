// Project1.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "myscheduler.h"
//#include "scheduler.h"
#include "myscheduler.cpp"
using namespace std;

int main(int argc, char* argv[])
{
	
   /*    
    printf("scheduler is created\n");
    
    s.CreateThread(0, 5, 0, 1);
    s.CreateThread(2, 2, 1, 2);
    s.CreateThread(4, 1, 2, 3);
    s.CreateThread(8, 4, 3, 4);
    
    printf("create thread is called\n");
*/

	cout<<"=================================================================\n";
        printf("--------------------WELCOME TO THE TESTBENCH--------------------\n");
	MyScheduler s = MyScheduler(FCFS,2);

	cout<<"===========This is for PBS==============="<<endl;
	// Test #1 CPU:1 ThreadCount:1 arr:0     
	cout<<"=Test#1=======CPU:1 Thread:1 arr:0 rem:2 prio:1 id:1"<<endl;
	s.CreateThread(0,3,1,1);
	// Test #2 CPU:2 Threads: 2 Works for n CPUs with n>=x threads	
	cout<<"=Test#2=======CPU:2 Thread:2 arr:2 rem:2 prio:1 id:2 "<<endl;
	s.CreateThread(1,4,1,2);
	// Test #3 CPU:2 Threads:3 for n CPUS with n<x threads
	s.CreateThread(3,5,1,3);
	
	s.Go();
    
	return 0;
}

