#include <vector>
#include "CPU.h"

int main(){
    vector<JOB> JOBS={
        JOB(
            "Process A",
            3,9,0.0,
            {
                Event("Input",1,5,{}),
                Event("Output",7,3,{}),
                Event("Require res",2,2,{2,0,1}),
                Event("Require res",4,2,{0,1,0})
            }
        ),
        JOB(
            "Process B",
            12,15,0.0,
            {
                Event("Require res",10,5,{0,2,0}),
                Event("Require res",13,5,{1,0,1})
            }
        ),
        JOB(
            "Process C",
            15,6,0.0,
            {
                Event("Printer",3,3,{})
            }
        )
    };
    CPU cpu(
        "First Come First Serve",
        "Deadlock Prevention",
        {2,2,5},
        JOBS
    );
    cpu.run();
    return 0;
}
