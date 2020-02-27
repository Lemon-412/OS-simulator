#ifndef _Lemon_Command
#define _Lemon_Command

#include "cmds.h"

static const unsigned int COMMAND_MAXSIZE=1000;

class Command{
public:
    char command[COMMAND_MAXSIZE];
    int length;
    string result;
    vector<string> cmds;

    Command(){}

    ~Command(){}

    void read(){
        fgets(command,COMMAND_MAXSIZE,stdin);
        length=strlen(command);
        command[length-1]=' ';

        string cur;
        bool stat=false;
        cmds.clear();
        for (int i=0;i<length;++i){
            if (command[i]==' '){
                if (stat){
                    cur.push_back(' ');
                }
                else{
                    if (cur.empty()){
                        continue;
                    }
                    cmds.push_back(cur);
                    cur.clear();
                }
            }
            else if (command[i]=='\"'){
                if (stat){
                    stat=false;
                    cmds.push_back(cur);
                    cur.clear();
                }
                else{
                    if (!cur.empty()){
                        cmds.push_back(cur);
                        cur.clear();
                    }
                    stat=true;
                }
            }
            else{
                cur.push_back(command[i]);
            }
        }
        if (stat){
            throw("unexpected EOF while looking for matching \'\"\'");
        }
    }

    void run(char path[]){
        int p=0;
        result.clear();
        while (p!=(int)cmds.size()){
            try{
                if (cmds[p]=="exit") exit(0);
                else if (cmds[p]=="echo") Echo(p,cmds,result);
                else if (cmds[p]=="clear") Clear(p,cmds,result);
                else if (cmds[p]=="ls") Ls(p,cmds,result);
                else if (cmds[p]=="cd") Cd(p,cmds,result,path);
                else if (cmds[p]=="cat") Cat(p,cmds,result);
                else if (cmds[p]=="mkdir") Mkdir(p,cmds,result);
                else if (cmds[p]=="rmdir") Rmdir(p,cmds,result);
                else if (cmds[p]=="touch") Touch(p,cmds,result);
                else if (cmds[p]=="rm") Rm(p,cmds,result);
                else if (cmds[p]==">") Redirect(p,cmds,result);
                else if (cmds[p]==">>") RedirectAdd(p,cmds,result);
                else GetContent(p,cmds,result);
            }
            catch (int err){
                string cur="";
                switch(err){
                    case -1: cur+="Command not found: \""+cmds[p]+"\"";break;
                    case -2: cur+="Missing Parameters After "+cmds[p];break;
                }
                throw(cur.c_str());
            }
        }
    }

    void output(){
        printf("%s\n",result.c_str());
    }
};


#endif // _Lemon_Command
