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


char* FileParser::readFromFile(const char *filename){
	FILE *file = fopen(filename, "r");
	int basicBlockSize = 1024;
	char *buf = (char*)malloc(sizeof(char) * basicBlockSize);
	char *head = buf;
	
	char c;
	int i = 0;
	int numBufs = 1;
	while((c = fgetc(file) ) != EOF){
		*buf = c;
		buf++;
		i++;
		if(i == 1024){
			buf = head;
			numBufs++;
			buf = (char*)realloc(buf, sizeof(char) * (numBufs * basicBlockSize));
			head = buf;
			buf += (numBufs -1) * basicBlockSize;
			i=0;
		}
	}
	
	*buf = '\0';
	buf = head;
	return buf;
}



std::string FileParser::getInput(){
	std::string allCommands(this->readFromFile(this->filename.c_str()));
	
}


FileParser::FileParser(std::string filename){
	this->filename = filename;
}
