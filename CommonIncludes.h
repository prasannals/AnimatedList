#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H
#include<stdio.h>
#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<vector>

typedef struct color{
	int r, g, b;
}Color;

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

#endif
