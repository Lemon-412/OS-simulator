#ifndef _Lemon_PCB
#define _Lemon_PCB
#include "Process.h"

// PCB: Process Controller Block
class PCB{
public:
    PCB(){}
    ~PCB(){}
    Process* process;
    int in_time,out_time;
    double priority;
    string status; // ready, finished, running
    void Initiate(Process* process,double priority,int CurrentTime){
        this->process=process;
        this->priority=priority;
        in_time=CurrentTime;
        status="ready";
    }
    void Distroy(){
        process->Distroy();
        status="finished";
    }
};


#endif // _Lemon_PCB

