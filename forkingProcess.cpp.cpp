#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;


int main(void)
{
	int forkNumber = 1;
	cout << "Main Process ID : " << getpid() << "\n\n";

	int pid = fork();
	//cout << "pid: " << pid << endl;

	if(pid == 0){	// Child
		forkNumber++;
		int pid1 = fork();
		//cout << "pid1: " << pid1 << endl;

		if(pid1 == 0){
			// Child
			forkNumber++;
			int pid3 = fork();
			//cout << "pid3: " << pid3 << endl;

			if(pid3 > 0){
				//	Parent
				cout << "Fork " << forkNumber << ". I'm the child " << pid3;
				cout << ", my parent is " << getpid() << ".\n";	
				
				wait(NULL);
			}
			exit(123);
		}
		else{
			// Parent
			cout << "Fork " << forkNumber << ". I'm the child " << pid1;
			cout << ", my parent is " << getpid() << ".\n";

			int pid2 = fork();
			//cout << "pid2: " << pid2 << endl;

			if(pid2 > 0){
				// Parent
				cout << "Fork " << forkNumber << ". I'm the child " << pid2;
				cout << ", my parent is " << getpid() << ".\n";

				wait(NULL);
			}
			else{
				forkNumber++;
				int pid4 = fork();
				//cout << "pid4: " << pid4 << endl;

				if(pid4 > 0){
					// Parent
					cout << "Fork " << forkNumber << ". I'm the child " << pid4;
					cout << ", my parent is " << getpid() << ".\n";
					
					wait(NULL);
				}
				exit(0);
			}
			wait(NULL);
		}
		exit(0);
	}
	else{	// Parent
		cout << "Fork " << forkNumber << ". I'm the child " << pid;
		cout << ", my parent is " << getpid() << ".\n";

		wait(NULL);
	}

	//system("ps aux | grep 'Z'");
	return 0;
}
