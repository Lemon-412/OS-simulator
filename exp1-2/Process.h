#ifndef _Lemon_Process
#define _Lemon_Process
#include <iostream>
#include "Event.h"

class Process{
public:
    Process(){}
    ~Process(){}
    int total_time;
    int run_time;
    int stuck_time;
    string name;
    vector<Event> events;
    vector<int> resources;

    void Initiate(int total_time,string name,vector<Event> events,int resources_n){
        this->name=name;
        this->total_time=total_time;
        this->run_time=0;
        this->events=events;
        resources.clear();
        resources.resize(resources_n,0);
        stuck_time=0;
    }

    void Distroy(){
        name="";
        total_time=0;
        events.clear();
    }
};


#endif // _Lemon_Process

