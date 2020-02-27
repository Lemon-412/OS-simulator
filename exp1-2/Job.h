#ifndef _Lemon_Job
#define _Lemon_Job
#include <string>
#include <vector>
#include "Event.h"

class JOB{
public:
    string name;
    int declare_time,total_time;
    vector<Event> events;
    double priority;
    JOB(string name,int declare_time,int total_time,double priority,vector<Event>events):
        name(name),declare_time(declare_time),total_time(total_time),events(events),priority(priority){}
};

#endif // _Lemon_Job
