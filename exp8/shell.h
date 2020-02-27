#ifndef _Lemon_Shell
#define _Lemon_Shell

#include "command.h"

DWORD USERNAME_MAXSIZE=256;
DWORD COMPUTERNAME_MAXSIZE=256;

class Shell{
protected:
    HANDLE hout;
    Command command;
    char path[PATH_MAXSIZE];
    char username[256];
    char computername[256];

public:

    Shell(){
        hout=GetStdHandle(STD_OUTPUT_HANDLE);
        getcwd(path,PATH_MAXSIZE);
        GetUserName(username,&USERNAME_MAXSIZE);
        GetComputerName(computername,&COMPUTERNAME_MAXSIZE);
    }

    ~Shell(){}

    void run(){
        while (true){
            SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_GREEN);
            printf("%s@%s ",username,computername);
            SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
            printf("%s\n",path);
            SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
            printf("$ ");

            try{
                command.read();
                SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                command.run(path);
            }
            catch(int err){
                SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED);
                switch(err){
                    case -1:printf("Bash: Unknown Command \n");break;
                    case -2:printf("Bash: Missing Parameters After \n");break;
                }
                putchar('\n');
                continue;
            }
            catch(const char* err){
                SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED);
                printf("Bash: %s\n", err);
                putchar('\n');
                continue;
            }

            command.output();
            putchar('\n');
        }
    }
};


#endif // _Lemon_Shell
