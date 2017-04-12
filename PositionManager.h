#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include<vector>
#include<iostream>

class PositionManager{
private:

protected:
	int x, y, width, height, numElements;
	
public:
	PositionManager(int x, int y, int width, int height, int numElements);
	
	void setNumElements(int numElements);
	
	void setWidth(int width);
	
	void setHeight(int height);
	
	void setX(int x);
	
	void setY(int y);
	
	virtual void getCoordinates(int index, std::vector<int> &vec) = 0;
};

class LinearPositionManager: public PositionManager{
private:

protected:
	int borderLeft, borderRight, borderTop, borderBottom, verticalSpacing, horizontalSpacing;
	
	int unitWidth, unitHeight;
	
	int rowCapacity, columnCapacity, maxElements;
	
	void calculateCapacity();

public:
	LinearPositionManager(int x, int y, int width, int height, int numElements);
	
	void getCoordinates(int index, std::vector<int> &vec);
};

#endif
