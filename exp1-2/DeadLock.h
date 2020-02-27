#ifndef _Lemon_DeadLock
#define _Lemon_DeadLock

// no deadlock protection
namespace NoProtection{
    vector<int> apply_for_allocation(int resource_n,vector<int>& own,vector<int>& apply){
        vector<int> release(resource_n,0);
        return release;
    }

    bool check_allocation(int resource_n,vector<int>& requirements,vector<int>& available){
        return true;
    }
}

// deadlock protection: prevention
// wreck the condition of circular wait: [textbook p109, 3.6.3]
// 1. set priority for resources.
// 2. If a process applies for resources of lower priority,
//    it should release all the resources of higher priority.
namespace DeadLockPrevention{
    vector<int> apply_for_allocation(int resource_n,vector<int>& own,vector<int>& apply){
        vector<int> release(resource_n);
        int split=resource_n;
        for (int i=0;i<resource_n;++i){
            if (apply[i]!=0){
                split=i;
                break;
            }
        }
        for (int i=0;i<resource_n;++i){
            release[i]=(i>=split?0:own[i]);
        }
        return release;
    }

    bool check_allocation(int resource_n,vector<int>& requirements,vector<int>& available){
        for (int i=0;i<resource_n;++i){
            if (requirements[i]>available[i]){
                return false;
            }
        }
        return true;
    }
}

#endif // _Lemon_DeadLock
