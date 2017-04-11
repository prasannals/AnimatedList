#define X_OFFSET 5
#define Y_OFFSET 8
#define FONT GLUT_BITMAP_TIMES_ROMAN_24

#include"CommonIncludes.h"
#include"Open2D.h"

class AbstractListElementView{
protected:
	int x, y, width, height;
	Color highlightColor;
	float colorRatio;
	std::string text;

	
	void drawText(Color color){	
		glColor3f(colorRatio * color.r, colorRatio * color.g,
					colorRatio * color.b);
		
		
		int x_centre = x + (width/2);
		int y_centre = y + (height/2);
		
		int x_pos = x_centre - (width / X_OFFSET);
		int y_pos = y_centre - (height / Y_OFFSET);;
		
		renderText(x_pos, y_pos, FONT, text.c_str());
		printf("drawing text\n");
		glColor3f(1, 1,1);
		
		glFlush();
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
		
		this->highlightColor.r = 50;
		this->highlightColor.g = 180;
		this->highlightColor.b = 80;
		this->colorRatio = (1/255.0);
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
	
	
	void setCoordinates(int x, int y){
		this->x = x;
		this->y = y;
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

BoxListElementView bView(100, 100, 100, 100, "122" ), bv2(250, 100, 100, 100, "22"),
	bv3(400, 200, 100, 100, "333");

void display(void){
	printf("in display func\n");
	bView.draw();	
	
	bv3.draw();
	bv2.draw();
	Color color;
	color.r = 255;
	color.g = 22;
	color.b = 99;
	bv2.highlight(color);
}

int main(int argc, char **argv){
	Open2D op(&argc, argv, 800, 600, "Animated List");
	op.display(display);
}
