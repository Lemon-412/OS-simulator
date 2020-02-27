#ifndef _Lemon_cmds
#define _Lemon_cmds

#include <dirent.h>
#include <windows.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

static const unsigned int PATH_MAXSIZE=1000;

void Echo(int& p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret=cmds[p+1];
    p+=2;
}

void Clear(int &p,vector<string>& cmds,string& ret){
    system("CLS");
    ret.clear();
    ++p;
}

void Ls(int &p,vector<string>& cmds,string& ret){
    DIR* dir=opendir(".");
    struct dirent* cur;
    ret.clear();
    while (cur=readdir(dir)){
        ret+=cur->d_name;
        ret+="\n";
    }
    ++p;
}

void Cd(int &p,vector<string>& cmds,string& ret,char path[]){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    if (cmds[p+1][1]==':'){
        SetCurrentDirectoryA(cmds[p+1].c_str());
        getcwd(path,PATH_MAXSIZE);
        p+=2;
        return;
    }
    if (cmds[p+1].back()!='\\'){
        cmds[p+1]+='\\';
    }
    if (cmds[p+1][0]!='.'){
        cmds[p+1].insert(0,"\\");
    }
    int cur=0,length=strlen(path);
    if (cmds[p+1][0]=='.'&&cmds[p+1][1]=='\\'){
        cur=1;
    }
    while (cur!=(int)cmds[p+1].length()){
        char c=cmds[p+1][cur];
        if (c=='.'){
            if (cur+1==(int)cmds[p+1].length()){
                throw("Unexpected \".\" in address");
            }
            if (cmds[p+1][cur+1]=='\\'){
                cur+=2;
                continue;
            }
            if (cmds[p+1][cur+1]!='.'){
                throw("Unexpected \".\" in address");
            }
            if (path[length-1]=='\\'){
                path[--length]='\0';
            }
            while (path[length-1]!='\\'){
                path[--length]='\0';
            }
            path[--length]='\0';
            cur+=2;
        }
        else{
            path[length++]=c;
            path[length]='\0';
            ++cur;
        }
    }
    if (length!=3){
        path[--length]='\0';
    }
    SetCurrentDirectoryA(path);
    getcwd(path,PATH_MAXSIZE);
    p+=2;
}

void Cat(int &p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    char buffer[1024];
    FILE* fp=fopen(cmds[p+1].c_str(),"r");
    while (fgets(buffer,1024,fp)){
        ret+=buffer;
    }
    fclose(fp);
    p+=2;
}

void Mkdir(int &p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    _mkdir(cmds[p+1].c_str());
    p+=2;
}

void Rmdir(int &p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    _rmdir(cmds[p+1].c_str());
    p+=2;
}

void Touch(int &p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    FILE* fp=fopen(cmds[p+1].c_str(),"w");
    fclose(fp);
    p+=2;
}

void Rm(int &p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    ret.clear();
    DeleteFile(cmds[p+1].c_str());
    p+=2;
}

void Redirect(int& p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    FILE* fp=fopen(cmds[p+1].c_str(),"w");
    fputs(ret.c_str(),fp);
    fclose(fp);
    ret.clear();
    p+=2;
}

void RedirectAdd(int& p,vector<string>& cmds,string& ret){
    if (p+1==(int)cmds.size()) throw -2;
    FILE* fp=fopen(cmds[p+1].c_str(),"a");
    fputs(ret.c_str(),fp);
    fclose(fp);
    ret.clear();
    p+=2;
}

void GetContent(int &p,vector<string>& cmds,string& ret){
    if (cmds[p].length()>=4&&cmds[p][cmds[p].length()-1]=='e'&&cmds[p][cmds[p].length()-2]=='x'&&cmds[p][cmds[p].length()-3]=='e'&&cmds[p][cmds[p].length()-4]=='.'){
        system("CLS");
        system(cmds[p].c_str());
        system("CLS");
        ++p;
        return;
    }
    FILE* fp=fopen(cmds[p].c_str(),"r");
    if (!fp) throw(-1);
    ret.clear();
    char buffer[1024];
    while (fgets(buffer,1024,fp)){
        ret+=buffer;
    }
    fclose(fp);
    ++p;
}

#endif // _Lemon_cmds
