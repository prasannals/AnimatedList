#include"CommonIncludes.h"
#include"PositionManager.h"
#include"InputGetter.h"
#include"ListElementViews.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

std::vector<AnimationTask> tasks;

int numElements;

////////////BAD INITIALIZATION. DO SOMETHING ABOUT IT LATER/////////////
LinearPositionManager pManager(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, numElements);

int calcNumElements(std::vector<AnimationTask> &t){
	int numAdditions = 0, numDeletions = 0;

	for(AnimationTask &task : t){
		int id = task.getId();

		if(id == ADD_ID){
			numAdditions++;
		} else if (id == DELETE_ID) {
			numDeletions++;
		}
	}

	////////////// ADD SOME EXTRA LOGIC LIKE min(numAdd- numDel, 0) ////////////
	return (numAdditions - numDeletions);
}

std::vector<BoxListElementView> views;

void redrawViews(int index){
	for(int i = index; i < views.size(); i++){
		std::vector<int> pos;
		pManager.getCoordinates(i, pos);

		BoxListElementView &v = views.at(i);

		v.setCoordinates(pos.at(0), pos.at(1));
		v.setSpan(pos.at(2), pos.at(3));

		v.draw();
	}
}

void display(void){
	for(AnimationTask &task: tasks){
		int id = task.getId();

		std::cout << "task id : " << id << std::endl;

		if(id == ADD_ID){
			std::cout << "Adding" << std::endl;
			std::vector<int> pos;
			pManager.getCoordinates(views.size(), pos);
			BoxListElementView v(pos.at(0), pos.at(1), pos.at(2), pos.at(3), task.getExtra(ELEMENT_EXTRA));
			v.popIn();
			views.push_back(v);
		}else if (id == DELETE_ID) {
			std::string str = task.getExtra(INDEX_EXTRA);
			int index = atoi(str.c_str());
			std::cout << "Deleting " << index << std::endl;
			views.at(index).popOut();
			views.erase(views.begin() + index);
			redrawViews(index);
		}else if (id == SWAP_ID) {
			std::cout << "swap\n";
		}else if (id == SET_ID) {
			std::cout << "set\n";
		}else if (id == HIGHLIGHT_ID) {
			std::cout << "highlight\n";
			views.at(index).highlight();
		}else{
			std::cout << "Something isn't right in display func\n";
		}

	}
}

int main(int argc, char **argv){
	if(argc <= 1){
		std::cout << "Insufficient arguments. Please provide the input filename." << std::endl;
		return 1;
	}

	std::string filename(argv[1]);
	FileParser parser(filename);

	parser.getTasks(tasks);

	numElements = calcNumElements(tasks);

	LinearPositionManager lp(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, numElements);

	pManager = lp;

	Open2D open2d(&argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, "Animated List");

	open2d.display(display);


	return 0;
}
