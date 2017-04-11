#ifndef INPUT_GETTER_H
#define INPUT_GETTER_H

#include<map>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

class AnimationTask{
private:
	int id;
	std::map<std::string, std::string> extras;
public:
	AnimationTask(int id);
	int getId();
	std::string getExtra(std::string key);
	void addExtra(std::string key, std::string value);
};


class InputParser{
protected:
	void split(std::string str, char *delimiter, std::vector<std::string> &vec);
public:
	virtual std::string getInput() = 0;
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
