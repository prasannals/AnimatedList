#ifndef INPUT_GETTER_H
#define INPUT_GETTER_H


#define ADD_ID 0
#define DELETE_ID 1
#define SET_ID 3
#define HIGHLIGHT_ID 4
#define SWAP_ID 5
#define ELEMENT_EXTRA "element"
#define INDEX_EXTRA "index"
#define INDEX_ONE_EXTRA "index1"
#define INDEX_TWO_EXTRA "index2"

#include<map>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<vector>

class AnimationTask{
private:
	int id;
	std::map<std::string, std::string> extras;
public:
	AnimationTask();
	AnimationTask(int id);
	int getId();
	void setId(int id);
	std::string getExtra(std::string key);
	void putExtra(std::string key, std::string value);
};


class InputParser{
protected:
	void split(std::string str, const char *delimiter, std::vector<std::string> &vec);
public:
	virtual std::string getInput() = 0;
	void getTasks(std::vector<AnimationTask> &tasks);
};

class FileParser: public InputParser{
private:
	std::string filename;
	char* readFromFile(const char *filename);
public:
	FileParser(std::string filename);

	std::string getInput();
};

#endif
