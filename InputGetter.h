#ifndef INPUT_GETTER_H
#define INPUT_GETTER_H

#include<map>
#include<iostream>

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



#endif
