#include"InputGetter.h"

int AnimationTask::getId(){
	return id;
}

std::string AnimationTask::getExtra(std::string key){
	return this->extras[key];
}

AnimationTask::AnimationTask(int id){
	this->id = id;
}

void AnimationTask::addExtra(std::string key, std::string value){
	this->extras[key] = value;
}
