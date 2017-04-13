#include"InputGetter.h"

int AnimationTask::getId(){
	return id;
}

std::string AnimationTask::getExtra(std::string key){
	return this->extras[key];
}

AnimationTask::AnimationTask(){

}

void AnimationTask::setId(int id){
	this->id = id;
}

AnimationTask::AnimationTask(int id){
	this->setId(id);
}

void AnimationTask::putExtra(std::string key, std::string value){
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

void InputParser::split(std::string str, const char *delimiter, std::vector<std::string> &vec){
	char *token = strtok((char*)str.c_str(), delimiter);

	while(token != NULL){
		std::string s(token);
		vec.push_back(s);
		token = strtok(NULL, delimiter);
	}
}

std::string FileParser::getInput(){
	std::string allCommands(this->readFromFile(this->filename.c_str()));

	return allCommands;
}

void InputParser::getTasks(std::vector<AnimationTask> &tasks){
	std::string allCommands = this->getInput();

	std::vector<std::string> lines;
	this->split(allCommands, "\n", lines);

	for(int i = 0; i < lines.size(); i++){
		std::string line = lines.at(i);

		std::vector<std::string> tokens;
		this->split(line, " ", tokens);

		AnimationTask task;


		///////////// NOTE : MORE VALIDATION NEEDED LATER ///////////////////
		switch(tokens.size()){
		case 2:
			if(strcmp(tokens.at(0).c_str(), "add") == 0 ){
				//std::cout << "add\n";
				task.setId(ADD_ID);
				task.putExtra(ELEMENT_EXTRA, tokens.at(1));
			}else if(strcmp(tokens.at(0).c_str(), "delete") == 0){
				//std::cout << "delete\n";
				task.setId(DELETE_ID);
				task.putExtra(INDEX_EXTRA, tokens.at(1));
			}else if(strcmp(tokens.at(0).c_str(), "set") == 0){
				//std::cout << "set\n";
				task.setId(SET_ID);
				std::vector<std::string> sp;
				this->split(tokens.at(1), "," , sp);

				task.putExtra(INDEX_EXTRA, sp.at(0));
				task.putExtra(ELEMENT_EXTRA, sp.at(1));
			}else if(strcmp(tokens.at(0).c_str(), "highlight") == 0){
				//std::cout << "highlight\n";
				task.setId(HIGHLIGHT_ID);

				task.putExtra(INDEX_EXTRA, tokens.at(1));
			}else if(strcmp(tokens.at(0).c_str(), "swap") == 0){
				//std::cout << "swap\n";
				task.setId(SWAP_ID);
				std::vector<std::string> sp;
				this->split(tokens.at(1), "," , sp);

				task.putExtra(INDEX_ONE_EXTRA, sp.at(0));
				task.putExtra(INDEX_TWO_EXTRA, sp.at(1));
			}else{
				//std::cout << "something else\n";
			}

			tasks.push_back(task);

			break;
		default:
			break;
		}
	}

}

FileParser::FileParser(std::string filename){
	this->filename = filename;
}


// int main(int argc, char **argv){
// 	std::string filename(argv[1]);
// 	FileParser fp(argv[1]);
//
// 	std::vector<AnimationTask> tasks;
// 	fp.getTasks(tasks);
//
//
// 	for(int i =0 ; i < tasks.size(); i++){
// 		AnimationTask current = tasks.at(i);
// 		switch(current.getId()){
// 			case ADD_ID:
//
// 				std::cout << "add : " << current.getExtra(ELEMENT_EXTRA) << std::endl;
// 				break;
// 			case DELETE_ID:
// 				std::cout << "delete : " << current.getExtra(INDEX_EXTRA) << std::endl;
// 				break;
// 			case SET_ID:
// 				std::cout << "set : " << current.getExtra(INDEX_EXTRA) << " :: " << current.getExtra(ELEMENT_EXTRA) << std::endl;
// 				break;
// 			case SWAP_ID:
// 				std::cout << "swap : " << current.getExtra(INDEX_ONE_EXTRA) << " :: " << current.getExtra(INDEX_TWO_EXTRA) << std::endl;
// 				break;
// 			case HIGHLIGHT_ID:
// 				std::cout << "highlight : " << current.getExtra(INDEX_EXTRA) << std::endl;
// 				break;
// 			default:
// 				std::cout << "new encounter...." << std::endl;
// 		}
// 	}
//
// return 0;
// }
