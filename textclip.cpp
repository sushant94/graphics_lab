#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <string.h>

void printw(float x, float y, float z, char *string)
{
	
	glRasterPos3f(x,y,z);
	for(int i=0;string[i]!='\0';i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	}
}

int isWhite(float x, float y)
{
	GLubyte pix[3];
	x= (x*400 + 400);
	y =(y*300 + 300);
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *) pix);
	if(pix[0]>=250 && pix[1]>=250 && pix[2]>=250)
		return 1;
	return 0;
}

int inWin(float x1,float y1,float x2, float y2, float x, float y)
{
	if(x<=x2 && x>=x1)
	{
		if(y<=y2 && y>=y1)
			return 1;
	}
	return 0;
}

void textclip(float xm, float ym, float xM, float yM)
{
	float y=1;
	float x=-1;
	while(y>-1)
	{
		for(x=-1;x<=1;x+=0.001)
		{
			if(!inWin(xm,ym,xM,yM,x,y))
			{
				if(isWhite(x,y))
				{	
					glColor3f(0.0,0.0,1.0);
					glBegin(GL_POINTS);
						glVertex2f(x,y);
					glEnd();
					glFlush();
				}
			}
		}

		y-=0.002;

	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	char *ch;
	ch = (char *) malloc(sizeof(char *));
	ch = strdup("THE CHAMBER OF SECRETS HAS BEEN OPENED");
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,0);
		glVertex2f(0,0.1);
		glVertex2f(0.3,0.1);
		glVertex2f(0.3,0);
	glEnd();
	printw(-0.5,0,0,ch);
	glFlush();
	

	textclip(0,0,0.3,0.1);
	glFlush();

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Text Clip");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}
