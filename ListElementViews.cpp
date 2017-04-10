#define X_OFFSET 5
#define Y_OFFSET 8
#define FONT GLUT_BITMAP_TIMES_ROMAN_24

#include"CommonIncludes.h"
#include"Open2D.h"

class AbstractListElementView{
protected:
	int x, y, width, height;
	
	void drawText(){
		//calculate the centre 
		int x_centre = x + (width/2);
		int y_centre = y + (height/2);
		
		int x_pos = x_centre - (width / X_OFFSET);
		int y_pos = y_centre - (height / Y_OFFSET);;
		
		renderText(x_pos, y_pos, FONT, "1");	
	}
	
private:	
	void renderText(int w, int h, void *font, const char *string){
		glRasterPos2f(w,h);
	
		for(const char *c = string; *c != '\0'; c++){
			glutBitmapCharacter(font, (int)*c);
		}
	}	
	

public:
	AbstractListElementView(int x, int y, int width, int height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	virtual void draw() = 0;
	
	void setCoordinates(int x, int y){
		this->x = x;
		this->y = y;
	}	
};


class BoxListElementView: public AbstractListElementView{
private:

public:
	BoxListElementView(int x, int y, int width, int height)
	: AbstractListElementView(x, y, width, height){
		
	}
	
	void draw(){
		glBegin(GL_POLYGON);
			glVertex3f(x, y, 0);
			glVertex3f(x + width, y, 0);
			glVertex3f(x + width, y + height, 0);
			glVertex3f(x, y + height, 0);
		glEnd();
		float ratio = (1/255.0);
		
		glColor3f(ratio * 50, ratio * 50, ratio * 50);
		drawText();
		glColor3f(1,1,1);
		glFlush();
	}
};

BoxListElementView bView(100, 100, 100, 100), bv2(100, 400, 100, 100);

void display(void){
	bView.draw();	
	bv2.setCoordinates(500,400);
	bv2.draw();
}

int main(int argc, char **argv){
	Open2D op(&argc, argv, 800, 600, "Animated List");
	op.display(display);	
}
