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
	glClearColor(0,0,0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i = index; i < views.size(); i++){
		std::vector<int> pos;
		pManager.getCoordinates(i, pos);

		BoxListElementView &v = views.at(i);

		v.setCoordinates(pos.at(0), pos.at(1));
		v.setSpan(pos.at(2), pos.at(3));

		v.draw();
	}
}

bool displayed = false;


float circleY(float x, float radius){
	return sqrt(fabs((radius * radius ) - (x * x)));
}


void display(void){

	if(!displayed){

		for(AnimationTask &task: tasks){
			int id = task.getId();


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
				redrawViews(0);
			}else if (id == SWAP_ID) {

				int fromIndex = atoi(task.getExtra(INDEX_ONE_EXTRA).c_str());
				int toIndex = atoi(task.getExtra(INDEX_TWO_EXTRA).c_str());

				std::cout << "swap from " << fromIndex << " to " << toIndex << std::endl;

				std::vector<int> fromPos, toPos;
				views.at(fromIndex).getPosition(fromPos);
				views.at(toIndex).getPosition(toPos);

				int distance = abs(fromPos.at(0) - toPos.at(0) );
				//centre of the circle whose circumference will define the animation
				int xCentre = fromPos.at(0) + round(distance/2.0);
				int yCentre = fromPos.at(1);

				std::vector<float> xVals;

				int fps = 30;
				int numSec = 2;
				int numFrames = fps * numSec;
				linSpace(fromPos.at(0), toPos.at(0), numFrames, xVals);

				int delay = (int)(1000000 * (1.0/fps));
				std::cout << "Loop Start"<<std::endl;
				//move the INDEX_ONE to INDEX_TWO

				int curX = fromPos.at(0);
				int curY = fromPos.at(1);
				for(int i = 0; i < numFrames; i++){
					views.at(fromIndex).clear(curX,curY, fromPos.at(2), fromPos.at(3));
					curX = xVals.at(i);
					curY = -circleY(curX - xCentre, distance/2.0) + yCentre;

					views.at(fromIndex).setCoordinates(curX, curY);
					views.at(fromIndex).draw();

					usleep(delay);
				}


				curX = toPos.at(0);
				curY = toPos.at(1);
				for(int i = numFrames - 1; i >= 0; i--){
					views.at(toIndex).clear(curX,curY, toPos.at(2), toPos.at(3));
					curX = xVals.at(i);
					curY = -circleY(curX - xCentre, distance/2.0) + yCentre;

					views.at(toIndex).setCoordinates(curX, curY);
					views.at(toIndex).draw();
					views.at(fromIndex).draw();
					usleep(delay);
				}

				auto temp = views.at(fromIndex);
				views.at(fromIndex) = views.at(toIndex);
				views.at(toIndex) = temp;

			}else if (id == SET_ID) {
				std::cout << "set\n";
				std::string str = task.getExtra(INDEX_EXTRA);
				int index = atoi(str.c_str());

				std::string eleStr = task.getExtra(ELEMENT_EXTRA);
				views.at(index).setText(eleStr);
				views.at(index).draw();
			}else if (id == HIGHLIGHT_ID) {
				std::string str = task.getExtra(INDEX_EXTRA);
				int index = atoi(str.c_str());

				std::cout << "highlight\n";
				std::cout << "index : " << index << std::endl;
				views.at(index).highlight();
				views.at(index).draw();
			}else{
				std::cout << "Something isn't right in display func\n";
			}

		}
		displayed = true;
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
