/*
Michael McClung
CS 2413-501
4/14/2018
*/

// ifndef and define header file
#ifndef UFS_H
#define UFS_H

// includes and stds
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class node
class Node {

private:
	// private node variables 
	string label;
	vector<Node*> children;
	Node* parent;
	bool isDir;

public:
	// node deconstructor and constructor
	Node();
	~Node();

	// label functions
	void setLabel(string);
	string getLabel();

	// directory functions
	void setDirState(bool state);
	bool isDirectory();

	// parent functions
	void setParent(Node*);
	Node* getParent();

	// children functions
	void addChild(Node*);
	vector<Node*> getChildren();
};

// class foldersystem
class FolderSystem {

private:
	// private folder system variables
	Node *root, *cwd;

public:
	// folder system deconstructor and constructors
	FolderSystem();
	FolderSystem(Node*);
	~FolderSystem();

	// root functions
	void setRoot(Node*);
	Node* getRoot();

	// current working directory functions
	void setCwd(Node*);
	Node* getCwd();
	string getCwdStr();

	// children functions
	void getDirChildren(Node*);

	// main user functions
	Node* mkdir(string);
	Node* mkfile(string);
	Node* cd(string);
	void ls(string);
	void helpInfo();
};
// end of header file
#endif