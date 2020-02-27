#ifndef _Lemon_Event
#define _Lemon_Event
#include <string>
using namespace std;

class Event{
public:
    string reason;
    int start_time;
    int total_time;
    vector<int> requirements;

    Event(string reason,int start_time,int total_time,vector<int> requirements):
        reason(reason),start_time(start_time),total_time(total_time),requirements(requirements){}

    void debug(){
        cout<<reason<<", "<<total_time<<"  ";
        if (reason=="Require res"){
            cout<<"[ ";
            for (auto x:requirements){
                cout<<x<<" ";
            }
            cout<<"]";
        }
        else assert(requirements.empty());
        cout<<endl;
    }
};

#endif // _Lemon_Event
