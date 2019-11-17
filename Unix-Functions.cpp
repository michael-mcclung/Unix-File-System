/*
Michael McClung
CS 2413-501
05/09/2018
*/

// includes and stds
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <cstring>
#include "UFS.h"
using namespace std;

// default node constructor
Node::Node() {
	this->label = label;
	this->parent = NULL;
}

// node deconstructor
Node::~Node() {
}

// set label function
void Node::setLabel(string label) {
	this->label = label;
}

// get label function
string Node::getLabel() {
	return this->label;
}

// set directory state function
void Node::setDirState(bool state) {
	this->isDir = state;
}

// is directory function
bool Node::isDirectory() {
	return this->isDir;
}

// set parent function
void Node::setParent(Node * node) {
	this->parent = node;
}

// get parent function
Node * Node::getParent() {
	return this->parent;
}

// add child function
void Node::addChild(Node * node) {
	this->children.push_back(node);
}

//get children function
vector<Node*> Node::getChildren() {
	return this->children;
}

// folder system default constructor
FolderSystem::FolderSystem() {
	this->root = NULL;
	this->cwd = NULL;
}

// folder system constructor
FolderSystem::FolderSystem(Node* root) {
	this->root = root;
}

// folder system deconstructor
FolderSystem::~FolderSystem() {
}

// set root function
void FolderSystem::setRoot(Node * node) {
	this->root = node;
}

// get root function
Node * FolderSystem::getRoot() {
	return this->root;
}

// set current working directory function
void FolderSystem::setCwd(Node * newDirectory) {
	this->cwd = newDirectory;
}

// get current working directory function
Node * FolderSystem::getCwd() {
	return this->cwd;
}

// get current working directory string function
string FolderSystem::getCwdStr() {

	// start of root printout and get 
	// current working directory as a node pointer
	string dir = "";
	Node * cwd = this->getCwd();

	// gets root '~/'(stareting point of command prompt) 
	// and other current working directories if 
	// any follow after the root '~/'
	while (cwd != NULL) {
		dir = cwd->getLabel() + "/" + dir;
		cwd = cwd->getParent();
	}

	// return current working directory
	return dir;
}

// get children of directory
void FolderSystem::getDirChildren(Node* dir) {
	vector<Node*> children = dir->getChildren();

	// length of children size
	int len = children.size();

	// iterate through all directories or files
	// until all are found to be printed to screen
	for (int i = 0; i < len; i++) {
		cout << children[i]->getLabel() << endl;
	}
}

// mkdir function - make new directory in current directory
Node * FolderSystem::mkdir(string label) {
	// create new node to be entered
	Node* newNode = new Node();

	// set user input as new node
	newNode->setLabel(label);

	// set directory state true
	newNode->setDirState(true);

	// set parent as cureent working directory
	newNode->setParent(this->getCwd());

	// add a child of the new directory to current working directory
	this->getCwd()->addChild(newNode);

	// return newNode
	return newNode;
}

// touch function - create new file in current directory
Node* FolderSystem::mkfile(string label) {
	// create new node to be inserted
	Node* newNode = new Node();

	// set file as the new node 
	newNode->setLabel(label);

	// it will not go in as a new directory and set this to false
	newNode->setDirState(false);

	// set parent as curent working directory
	newNode->setParent(this->getCwd());

	// add a child of the new file to current working directory
	this->getCwd()->addChild(newNode);

	// return new node
	return newNode;
}

Node* FolderSystem::cd(string dir) {

	// initializing variables used in this function
	int numStepUps = 0;
	smatch sm;
	string temp = dir;

	// parse the string, . for current directory, .. for parent
	// then get string names of each folder, scan for step up directory characters
	regex stepUp("(\.\.\/)");
	string::const_iterator searchStart(dir.cbegin());
	regex_search(dir, sm, stepUp);

	// search for the length and position of the string
	while (regex_search(searchStart, dir.cend(), sm, stepUp)) {
		numStepUps++;
		searchStart += sm.position() + sm.length();
		temp = regex_replace(dir, stepUp, "");
	}
	dir = temp;

	// step up directories first, if needed
	Node * cwd = this->getCwd();
	if (numStepUps > 0) {
		while (numStepUps > 0 && cwd->getParent() != nullptr) {
			cwd = cwd->getParent();
			numStepUps--;
		}
	}

	// now step down into dir folders
	if (dir == "" || dir == " ") {
		return cwd;
	}
	regex folderChar("\/");
	vector<string> result{
		sregex_token_iterator(dir.begin(), dir.end(), folderChar, -1),{}
	};

	// iterator, if fails, we never changed real directory
	Node * tempCwd = cwd;
	bool foundOneDir = false;
	int len = result.size();

	// iterate through dir folders
	for (int i = 0; i < len; i++) {
		vector<Node*> children = cwd->getChildren();
		int lenJ = children.size();

		// iterate through children of cwd, and see if dir[i] matches at least one child folder
		for (int j = 0; j < lenJ; j++) {

			// does the current searched folder exist in children list
			if (children[j]->getLabel() == result[i]) {
				foundOneDir = true;
				tempCwd = children[j];
				break;
			}
		}

		// failed once, step out
		if (foundOneDir == false) {

			// did not find that directory
			return nullptr; 
		}
		foundOneDir = false;
	}
	// cwd is what dir wanted to get to
	return tempCwd;
}

// ls function - show path of current directory
void FolderSystem::ls(string dir) {
	// create new path directory
	Node * lsDir;

	// ls + dir typed, use cd to find temp dir
	if (dir != "" && dir != " ") {
		lsDir = this->cd(dir);
	}

	// only ls typed, give cwd 
	else {
		lsDir = this->getCwd();
	}

	// list folders here
	this->getDirChildren(lsDir);	
}

// show list of commands functions
void FolderSystem::helpInfo() {
	cout << "****************LIST OF COMMANDS AND THEIR MEANINGS****************************" << endl;
	cout << "\nmkdir--------MAKE A NEW DIRECTORY WITHIN CURRENT DIRECTORY" << endl;
	cout << "touch--------MAKE A NEW FILE WITHIN CURRENT DIRECTORY" << endl;
	cout << "cd-----------CHANGE TO A DIFFERENT DIRECTORY" << endl;
	cout << "ls-----------SHOW THE PATH OF ALL CURRENT DIRECTORIES/FILES IN CURRENT DIRECTORY" << endl;
	cout << "help---------SHOWS COMMAND LIST AND MEANINGS\n" << endl;
}
