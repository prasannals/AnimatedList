#include"PositionManager.h"

PositionManager::PositionManager(int x, int y, int width, int height, int numElements){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->numElements = numElements;
}
	
void PositionManager::setNumElements(int numElements){
	this->numElements = numElements;
}
	
void PositionManager::setWidth(int width){
	this->width = width;
}
	
void PositionManager::setHeight(int height){
	this->height = height;
}
	
void PositionManager::setX(int x){
	this->x = x;
}
	
void PositionManager::setY(int y){
	this->y = y;
}



LinearPositionManager::LinearPositionManager(int x, int y, int width, int height, int numElements): PositionManager(x, y, width, height, numElements) {
	this->borderLeft= 10;
	this->borderRight = 10;
	this->borderTop = 10;
	this->borderBottom = 10; 
	this->verticalSpacing = 10; 
	this->horizontalSpacing = 10;
	
	this->unitWidth = 100;
	this->unitHeight = 100;
	
	this->calculateCapacity();
}
	
void LinearPositionManager::calculateCapacity(){
	this->rowCapacity = (width - (borderLeft + borderRight) ) / (unitWidth + horizontalSpacing);
	
	this->columnCapacity = (height - (borderTop + borderBottom) ) / (unitHeight + verticalSpacing);
	
	this->maxElements = this->rowCapacity * this->columnCapacity;
}

void LinearPositionManager::getCoordinates(int index, std::vector<int> &vec){
	if(index > maxElements || index < 0){
		return;
	}
	
	int column = index % rowCapacity;
	int row = index / rowCapacity;
	
	int x = this->x + borderLeft + ( column * (unitWidth + horizontalSpacing)) ;
	int yTop = y + height;
	int y = yTop - borderTop - ( (row + 1) * (unitHeight + verticalSpacing) );

	vec.push_back(x);
	vec.push_back(y);
	vec.push_back(unitWidth);
	vec.push_back(unitHeight);
}

//void printPosition(std::vector<int> &position){
//	std::cout << "X : " << position.at(0) << std::endl;
//	std::cout << "Y : " << position.at(1) << std::endl;
//	std::cout << "Width : " << position.at(2) << std::endl;
//	std::cout << "Height : " << position.at(3) << std::endl;
//}

//int main(int argc, char **argv){
//	LinearPositionManager posManager(0, 0, 800, 600, 20);
//	
//	std::vector<int> position;
//	
//	for(int i = 0; i < 20; i++){
//		posManager.getCoordinates(i, position);
//		
//		printPosition(position);
//		
//		position.clear();
//	}
//return 0;
//}
