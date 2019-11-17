/*
Michael McClung
CS 2413-501
05/09/2018

Description:
User can enter any of the following functions: mkdir, touch, 
cd, ls, exit, or help. By typing help, a list of the commands
and their meanings will be provided to the user. mkdir - make a
new directory and only 1 directory name created at a time. touch - 
make a new file and only 1 file name created at a time. cd - by 
typing '../' directory will go back by parent directories as many
times possible either until user is back at the root or user 
only wants to go back 1 or a # of times. ls - will show the current 
directories and files user is currently in. exit - will exit 
program and help - will show commands and meaning. Examples are 
given of each function in next paragraph.

Examples:
mkdir folder1 
touch file1 
cd folder1 (to change to next directory/folder)
				or 
cd ../../ (to change to previous/parent directories/folders)
ls (nothing else)
help (nothing else)
exit (nothing else)

*/

// includes and stds
#include <iostream>
#include <string>
#include "UFS.h"
using namespace std;

// main
int main() {

	// create a new graph
	FolderSystem* key = new FolderSystem();

	// directory entered as a string
	// get command and input given by user
	string dirEnt;
	string cmdGiven, restGiven;

	// config ~ as a string 
	// create a new root node/start of com prompt
	string label = "~";
	Node* root = new Node();

	// labl is set to root
	// parent is set to null
	root->setLabel(label);
	root->setParent(NULL);

	//FolderSystem sys = FolderSystem(root);
	key->setCwd(root);

	// always running unless user exits program
	while (true) {

		// getting current working directory '~' 
		// and adding '>' to it
		cout << key->getCwdStr() + "> ";

		// get command and/or name of dir/folder 
		// given by user, then erase to start over
		cin >> cmdGiven;
		getline(cin, restGiven);
		restGiven.erase(0, 1);

		// make directory function call
		if (cmdGiven == "mkdir") {
			key->mkdir(restGiven);
		}

		// make file function call
		else if (cmdGiven == "touch") {
			key->mkfile(restGiven);
		}

		// change directory function call
		else if (cmdGiven == "cd") {
			Node * cdDir = key->cd(restGiven);
			key->setCwd(cdDir);
		}

		// show path function call
		else if (cmdGiven == "ls") {
			key->ls(restGiven);
		}

		// shows command list
		else if (cmdGiven == "help") {
			key->helpInfo();
		}

		// exit program
		else if (cmdGiven == "exit") {
			exit(0);
		}

		// error, function not available
		else {
			cout << "Error: " << cmdGiven << " function does not exist" << endl;
		}
	}
}
