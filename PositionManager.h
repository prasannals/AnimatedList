#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

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
	
	virtual vector<int> getCoordinates(int index) = 0;
};

class LinearPositionManager: public PositionManager{
private:

public:
	LinearPositionManager(int x, int y, int width, int height, int numElements);
	
	vector<int> getCoordinates(int index);
}

#endif
