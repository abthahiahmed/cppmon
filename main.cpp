#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

using namespace std;

int main(int argc, char *argv[]){
	
	if (argc == 3){
		std::string compiler = argv[1];
		std::string filename = argv[2];
		
		
		string tmp = compiler + " " + filename + " -o output && ./output";
		const char* command = tmp.c_str();
		
		bool isMonitoring = true;
		
		auto mod_time = 0, prev_mod_time = 0;
		
		cout<<"Welcome to CPPMon 1.0"<<endl;
		cout<<"---------------------"<<endl;
		cout<<"Created by Abthahi Ahmed Rifat :D"<<endl;
		cout<<endl;
		while (isMonitoring){
			
			struct stat result;
			if(stat(filename.c_str(), &result) == 0)
			{
				prev_mod_time = mod_time;
				mod_time = result.st_mtime;
				if (mod_time != 0 &&  mod_time > prev_mod_time){
					cout<<"[cppmon] Starting... "<<" " <<command<<endl;
					cout<<"[cppmon] Compiling..."<<endl;
					cout<<endl;
					system(command);
					cout<<endl;
					cout<<"[cppmon] Waiting for file changes..."<<endl;
				}
			}else{
				cout<<"[cppmon] Cannot get file informations"<<endl;
				break;
			}
		}
	}else{
		cout<<"[cppmon] Wrong command!"<<endl;
		cout<<"Syntax : cppmon [g++/gcc] main.cpp"<<endl;
	}
	return 0;
}

