#ifndef Lemon_PCB_Control
#define Lemon_PCB_Control
#include <cassert>
#include "PCB.h"

// A PCB Queue
class PCBControl{
public:
    vector<PCB*> PCB_List;
    void initiate(){
        PCB_List.clear();
    }
    void insert_process(string name,int total_time,double priority,vector<Event> events,int CurrentTime,int resource_n){
        PCB *pcb=new PCB;
        Process *p=new Process;
        p->Initiate(total_time,name,events,resource_n);
        pcb->Initiate(p,priority,CurrentTime);
        PCB_List.push_back(pcb);
    }
    void insert_process(PCB *pcb){
        PCB_List.push_back(pcb);
    }
    void free_process(PCB* p){
        for (vector<PCB*>::iterator it=PCB_List.begin();it!=PCB_List.end();++it){
            if (*it==p){
                PCB_List.erase(it);
                return;
            }
        }
        assert(false);
    }
};

#endif // Lemon_PCB_Control

