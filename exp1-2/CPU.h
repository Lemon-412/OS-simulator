#ifndef _Lemon_CPU
#define _Lemon_CPU

#include <iostream>
#include <iomanip>
#include <cassert>
#include "scheduling.h"
#include "Job.h"
#include "DeadLock.h"

class CPU{
protected:
    int CurrentTime,resource_n;
    PCBControl PCB_Ready;
    PCBControl PCB_Stuck;
    PCBControl PCB_Done;
    PCB* running_process;

public:
    string scheduling_logic;
    string deadlock_logic;
    vector<int> resources;
    vector<JOB> JOB_List;

    CPU(string scheduling_logic,string deadlock_logic,vector<int> resources,vector<JOB> JOB_List)
        :scheduling_logic(scheduling_logic),deadlock_logic(deadlock_logic),resources(resources),JOB_List(JOB_List){
        resource_n=resources.size();
    }

    void Display(){
        std::cout<<std::left<<"Inner Time:"<<std::setw(5)<<CurrentTime<<std::endl;
        std::cout<<"=========================== Process Ready ============================"<<std::endl;
        {
            std::cout<<std::setw(10)<<"NAME";
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"CPUTIME";
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->run_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"ALLTIME";
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->total_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"PRIORITY";
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<std::setprecision(3)<<std::fixed<<pcb->priority;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"STATE";
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<pcb->status;
            }
            std::cout<<std::endl;
        }
        std::cout<<"=========================== Process Stuck ============================"<<std::endl;
        {
            std::cout<<std::setw(10)<<"NAME";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"CPUTIME";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->run_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"ALLTIME";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->total_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"PRIORITY";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<std::setprecision(3)<<std::fixed<<pcb->priority;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"STATE";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->status;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"REMAIN";
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->stuck_time;
            }
            std::cout<<std::endl;
        }
        std::cout<<"============================ Process Done ============================"<<std::endl;
        {
            std::cout<<std::setw(10)<<"NAME";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"CPUTIME";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->run_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"ALLTIME";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->total_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"PRIORITY";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<std::setprecision(3)<<std::fixed<<pcb->priority;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"STATE";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->status;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"INTIME";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->in_time;
            }
            std::cout<<std::endl;
            std::cout<<std::setw(10)<<"OUTTIME";
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->out_time;
            }
            std::cout<<std::endl;
        }
        std::cout<<"========================== System Resources =========================="<<std::endl;
        {
            std::cout<<std::setw(12)<<"SYSTEM";
            for (auto res:resources){
                std::cout<<std::setw(4)<<res;
            }
            std::cout<<std::endl;
            for (auto pcb:PCB_Ready.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
                for (auto res:pcb->process->resources){
                    std::cout<<std::setw(4)<<res;
                }
                std::cout<<std::endl;
            }
            for (auto pcb:PCB_Stuck.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
                for (auto res:pcb->process->resources){
                    std::cout<<std::setw(4)<<res;
                }
                std::cout<<std::endl;
            }
            for (auto pcb:PCB_Done.PCB_List){
                std::cout<<std::setw(12)<<pcb->process->name;
                for (auto res:pcb->process->resources){
                    std::cout<<std::setw(4)<<res;
                }
                std::cout<<std::endl;
            }
        }
    }

    void initialize(){
        CurrentTime=0;
        running_process=NULL;
        PCB_Ready.initiate();
        PCB_Stuck.initiate();
        PCB_Done.initiate();
        system("CLS");
    }

    void run(){
        initialize();
        while (true){

            // add new jobs to ready list
            for(auto job:JOB_List){
                if (job.declare_time==CurrentTime){
                    PCB_Ready.insert_process(job.name,job.total_time,job.priority,job.events,CurrentTime,resource_n);
                }
            }

            // select next running process base on scheduling_logic.
            if (scheduling_logic=="Round Robin") running_process=RR::select_next_process(PCB_Ready.PCB_List,running_process);
            else if (scheduling_logic=="Shortest Job First") running_process=SJF::select_next_process(PCB_Ready.PCB_List,running_process);
            else if (scheduling_logic=="First Come First Serve") running_process=FCFS::select_next_process(PCB_Ready.PCB_List,running_process);
            else assert(false);
            if (running_process!=NULL){
                running_process->status="Running"; // ready->running
            }// else busy wait.

            // display the current situation.
            Display();

            // run the running process.
            if (running_process!=NULL){
                running_process->process->run_time+=1;
                running_process->status="Ready"; // running->ready
                if (running_process->process->run_time==running_process->process->total_time){
                    running_process->status="Finished"; // running->finished
                    for (int i=0;i<resource_n;++i){ // return res to sys.
                        assert(running_process->process->resources[i]>=0);
                        resources[i]+=running_process->process->resources[i];
                        running_process->process->resources[i]=0;
                    }
                    running_process->out_time=CurrentTime;
                    PCB_Ready.free_process(running_process);
                    PCB_Done.insert_process(running_process);
                    running_process=NULL;
                }
                else{
                    for (auto event:running_process->process->events){
                        if (running_process->process->run_time==event.start_time){
                            cout<<"***********************************************************"<<endl;
                            cout<<running_process->process->name<<": ";event.debug();
                            if (event.reason=="Require res"){
                                vector<int> release;
                                bool is_allocation;
                                // get the resources to be released.
                                if (deadlock_logic=="No Protection") release=NoProtection::apply_for_allocation(resource_n,running_process->process->resources,event.requirements);
                                else if (deadlock_logic=="Deadlock Prevention") release=DeadLockPrevention::apply_for_allocation(resource_n,running_process->process->resources,event.requirements);
                                else assert(false);
                                // release resources.
                                for (int i=0;i<resource_n;++i){
                                    running_process->process->resources[i]-=release[i];
                                    resources[i]+=release[i];
                                    event.requirements[i]+=release[i];
                                }
                                // check if allocate or not.
                                if (deadlock_logic=="No Protection") is_allocation=NoProtection::check_allocation(resource_n,event.requirements,resources);
                                else if (deadlock_logic=="Deadlock Prevention") is_allocation=DeadLockPrevention::check_allocation(resource_n,event.requirements,resources);
                                else assert(false);
                                if (is_allocation){
                                    // allocate resources to the process
                                    for (int i=0;i<resource_n;++i){
                                        assert(resources[i]>=event.requirements[i]);
                                        resources[i]-=event.requirements[i];
                                        running_process->process->resources[i]+=event.requirements[i];
                                    }
                                }
                                else{ // system denies resources requirement
                                    running_process->process->run_time-=1;
                                    running_process->status=event.reason;
                                    running_process->process->stuck_time=event.total_time;
                                    PCB_Ready.free_process(running_process);
                                    PCB_Stuck.insert_process(running_process);
                                    running_process=NULL;
                                }
                            }
                            else{ // event other than "require res"
                                running_process->status=event.reason;
                                running_process->process->stuck_time=event.total_time;
                                PCB_Ready.free_process(running_process);
                                PCB_Stuck.insert_process(running_process);
                                running_process=NULL;
                            }
                            break;
                        }
                    }
                }
            }

            // deal with stuck processes.
            for (auto pcb:PCB_Stuck.PCB_List){
                pcb->process->stuck_time-=1;
                if (pcb->process->stuck_time==0){
                    pcb->status="Ready"; // stuck->ready
                    PCB_Stuck.free_process(pcb);
                    PCB_Ready.insert_process(pcb);
                }
            }
            CurrentTime+=1;
            if (CurrentTime>=100) break;
            system("pause");
            system("CLS");
        }
    }

};


#endif // _Lemon_CPU
