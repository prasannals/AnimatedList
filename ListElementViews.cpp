#define X_OFFSET 5
#define Y_OFFSET 8
#define FONT GLUT_BITMAP_TIMES_ROMAN_24

#include"CommonIncludes.h"
#include"Open2D.h"
#include"PositionManager.h"

class Drawable{
public:
	virtual void draw() = 0;
};


class AbstractListElementView: public Drawable{
protected:
	int x, y, width, height, fps;
	Color highlightColor;
	float colorRatio, speed;
	std::string text;


	void drawText(Color color){
		glColor3f(colorRatio * color.r, colorRatio * color.g,
					colorRatio * color.b);


		int x_centre = x + (width/2);
		int y_centre = y + (height/2);

		int x_pos = x_centre - (width / X_OFFSET);
		int y_pos = y_centre - (height / Y_OFFSET);;

		renderText(x_pos, y_pos, FONT, text.c_str());
		glColor3f(1, 1,1);

		glFlush();
	}


	void linSpace(float start, float end, int numDivisions, std::vector<float> &vec){
		float slope = fabs(end - start) / (numDivisions -1);
		for(int i = 0; i < numDivisions; i++){
			if(i == 0) {
				vec.push_back(start);
			} else if(i == numDivisions - 1) {
				vec.push_back(end);
			} else {
				vec.push_back( start + (i * slope) );
			}
		}
	}


private:
	void renderText(int w, int h, void *font, const char *string){
		glRasterPos2f(w,h);

		for(const char *c = string; *c != '\0'; c++){
			glutBitmapCharacter(font, (int)*c);
		}
	}

	virtual void drawShape() = 0;

public:
	AbstractListElementView(int x, int y, int width, int height, std::string text){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->text = text;

		this->fps = 30;
		this->speed = 1;
		this->highlightColor.r = 50;
		this->highlightColor.g = 180;
		this->highlightColor.b = 80;
		this->colorRatio = (1/255.0);
	}

	void popIn(){
		int xCentre = x + (width /2);
		int yCentre = y + (height /2);

		float delayInSec = ((2.0/speed)/fps);
		int delay = (int)(1000000 * delayInSec);

		int originalX = x, originalY =y, originalHeight = height, originalWidth = width;

		int minWidth = 10;
		int minHeight = 10;

		int minX = xCentre - (minWidth /2);
		int minY = yCentre - (minHeight/2);

		std::vector<float> xVec, yVec, wVec, hVec;

		linSpace(x, minX, fps, xVec);
		linSpace(y, minY, fps, yVec);
		linSpace(minWidth, width, fps, wVec);
		linSpace(minHeight, height, fps, hVec);



		for(int i = 0; i < fps; i++){
		//display frame and provide delay
			x = xVec.at((fps-1) - i);
			y = yVec.at((fps-1) - i);
			height = hVec.at(i);
			width = wVec.at(i);

			clear(originalX, originalY, originalWidth, originalHeight);
			if( i != fps -1){
				drawShape();
			}else{
				draw();
			}
			usleep(delay);
		}
	}

	void popOut(){
		int xCentre = x + (width /2);
		int yCentre = y + (height /2);

		float delayInSec = ((2.0/speed)/fps);
		int delay = (int)(1000000 * delayInSec);

		int originalX = x, originalY =y, originalHeight = height, originalWidth = width;

		int minWidth = 10;
		int minHeight = 10;

		int minX = xCentre - (minWidth /2);
		int minY = yCentre - (minHeight/2);

		std::vector<float> xVec, yVec, wVec, hVec;

		linSpace(x, minX, fps, xVec);
		linSpace(y, minY, fps, yVec);
		linSpace(minWidth, width, fps, wVec);
		linSpace(minHeight, height, fps, hVec);



		for(int i = 0; i < fps; i++){
		//display frame and provide delay
			x = xVec.at(i);
			y = yVec.at(i);
			height = hVec.at((fps-1) - i);
			width = wVec.at((fps-1) - i);

			clear(originalX, originalY, originalWidth, originalHeight);
			drawShape();
			usleep(delay);
		}
		clear(x, y, width, height);
		x = originalX;
		y = originalY;
		width = originalWidth;
		height = originalHeight;
	}

	void setSpeed(float speed){
		this->speed = speed;
	}

	void draw(){
		drawShape();
		Color color;
		color.r = 50;
		color.g = 50;
		color.b = 50;
		drawText(color);
	}

	void highlight(){
		glColor3f(colorRatio * highlightColor.r,
			colorRatio * highlightColor.g, colorRatio * highlightColor.b);
		draw();
	}

	void highlight(Color color){
		glColor3f(colorRatio * color.r,
			colorRatio * color.g, colorRatio * color.b);
		draw();
	}

	void removeHighlight(){
		glColor3f(1,1,1);
		draw();
	}

		void setText(std::string &text){
			this->text  = text;
		}

	void setCoordinates(int x, int y){
		this->x = x;
		this->y = y;
	}

	void setSpan(int width, int height){
		this->width = width;
		this->height = height;
	}

	void clear(int x, int y, int width, int height){
	////////// NOTE : Take in and restore previous color in later versions ////////
		glColor3f(0,0,0);
		glBegin(GL_POLYGON);
			glVertex3f(x, y, 0);
			glVertex3f(x + width, y, 0);
			glVertex3f(x + width, y + height, 0);
			glVertex3f(x, y + height, 0);
		glEnd();
		glFlush();
		glColor3f(1,1,1);
	}
};


class BoxListElementView: public AbstractListElementView{
private:


protected:
	void drawShape(){
		glBegin(GL_POLYGON);
			glVertex3f(x, y, 0);
			glVertex3f(x + width, y, 0);
			glVertex3f(x + width, y + height, 0);
			glVertex3f(x, y + height, 0);
		glEnd();
		glFlush();
	}

public:
	BoxListElementView(int x, int y, int width, int height, std::string text)
	: AbstractListElementView(x, y, width, height, text){

	}

};

//BoxListElementView bView(100, 100, 100, 100, "122" );
//
//LinearPositionManager pManager(0,0,800,600,20);
//
//void printPosition(std::vector<int> &position){
//	std::cout << "X : " << position.at(0) << std::endl;
//	std::cout << "Y : " << position.at(1) << std::endl;
//	std::cout << "Width : " << position.at(2) << std::endl;
//	std::cout << "Height : " << position.at(3) << std::endl;
//}

//void display(void){
//	std::vector<int> position;
//
//	for(int i = 0; i < 20; i++){
//		pManager.getCoordinates(i, position);
//
//		bView.setCoordinates(position.at(0), position.at(1));
//		bView.setSpan(position.at(2), position.at(3));
//
//		//printPosition(position);
//		position.clear();
//
//		bView.draw();
//		usleep(1000000);
//	}

//}



//int main(int argc, char **argv){
//	Open2D op(&argc, argv, 800, 600, "Animated List");
//	op.display(display);

//}
