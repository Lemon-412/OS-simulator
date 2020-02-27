#ifndef _Lemon_scheduling
#define _Lemon_scheduling
#include "PCBcontrol.h"

// process scheduling algorithm: first come first serve.
// FCFS selects the process that comes earlier.
namespace FCFS{
    PCB* select_next_process(vector<PCB*>& PCB_List,PCB* cur){
        if (cur) return cur;
        PCB* ret=NULL;
        int best_in=0x3f3f3f3f;
        for(auto pcb:PCB_List){
            if (pcb->in_time<best_in){
                best_in=pcb->in_time;
                ret=pcb;
            }
        }
        return ret;
    }
}

// process scheduling algorithm: shortest job first.
// SJF selects the process that has the lowest runtime (priority).
namespace SJF{
    PCB* select_next_process(vector<PCB*>& PCB_List,PCB* cur){
        PCB* ret=NULL;
        double best_priority=1e10;
        for (auto pcb:PCB_List){
            if (pcb->priority<best_priority){
                best_priority=pcb->priority;
                ret=pcb;
            }
        }
        if (ret){
            ret->priority+=1.0;
        }
        return ret;
    }
}

// process scheduling algorithm: round robin
// RR selects the next process of current process.
namespace RR{
    PCB* select_next_process(vector<PCB*>& PCB_List,PCB* cur){
        if (PCB_List.size()==0) return NULL;
        if (cur==NULL) return PCB_List[0];
        vector<PCB*>::iterator it;
        for (it=PCB_List.begin();it!=PCB_List.end();++it){
            if (*it==cur) break;
        }
        assert(it!=PCB_List.end());
        ++it;
        if (it==PCB_List.end()) return PCB_List[0];
        return *it;
    }
}

#endif // _Lemon_scheduling

