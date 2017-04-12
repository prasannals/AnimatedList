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

}
	
vector<int> LinearPositionManager::getCoordinates(int index){
	
}
