#ifndef OPEN_2D_H
#define OPEN_2D_H

#include<GL/glut.h>



void reshape(int w, int h)
{
  /* save new screen dimensions */
  int width = (GLdouble) w;
  int height = (GLdouble) h;

  /* tell OpenGL to use the whole window for drawing */
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  /* do an orthographic parallel projection with the coordinate
     system set to first quadrant, limited by screen/window size */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, 0.0, height, -1.f, 1.f);

  return;
}


class Open2D{
	
	
public:	

	Open2D(int *argc, char **argv, int width, int height, const char* title){
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutCreateWindow(title);
		glutReshapeFunc(reshape);
		glClearColor(0,0,0,0);
	}

	void display(void (*disp)(void)){
		glClear(GL_COLOR_BUFFER_BIT);
		glutDisplayFunc(disp);
		glutMainLoop();
	}

};

#endif
