#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <math.h>

struct point
{
	float x;
	float y;
}p[5];



int visited[800][800];

void sort(float x[],int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=1;j<size;j++)
		{
			if(x[i]>=x[j])
			{
				float tmp = x[i];
				x[i] = x[j];
				x[j] = tmp;
			}
		}
	}
}

void slfill()
{	
	
	float x[10];
	int count=0;
	float y = 1;
	while(y>=-1)
	{
		for(int i=0;i<5;i++)
		{
			if( ( (p[i].y-y)>0 && (p[(i+1)%5].y-y)<0 )||  ( (p[i].y-y)<0 && (p[(i+1)%5].y-y)>0 ) )
			{
				float m = (p[(i+1)%5].y - p[i].y)/(p[(i+1)%5].x - p[i].x);
				float c = p[i].y - m*p[i].x;
				float x1 = (y - c)/m;
				x[count++]=x1;
			}
			else
			{
				;
			}
		}
		sort(x,count);
		if(count>0)
		{
			glColor3f(1.0,0.0,0.0);
			glBegin(GL_LINES);
			for(int i=0;i<count;i+=2)
			{
				glVertex2f(x[i],y);
				glVertex2f(x[i+1],y);
			}
			glEnd();
		}
		y-=0.001;
		count=0;
	}

}

int isWhite(int x,int y)
{
	GLubyte pix[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pix);
	if(pix[0]>=250 && pix[1]>=250 && pix[2]>=250)
	{	
		//printf("%d,%d IS White!\n",x,y);
		return 1;

	}
	//printf("%d,%d is not White!\n",x,y);
	return 0;
}

int isBlack(int x,int y)
{
	GLubyte pix[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pix);
	if(pix[0]==0 && pix[1]==0 && pix[2]==0)
	{	
		//printf("%d,%d IS Black!\n",x,y);
		return 1;

	}

	return 0;
}


void setp(int x, int y)
{
	float x1 = (float)(x-400)/400.0;
	float y1 = (float)(y-300)/300.0;
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
	glVertex2f(x1,y1);
	glEnd();
	glFlush();
}

void floodfill(int x, int y)
{

	
	if(x>=800 || y>=600)
		return;
	if(x<=0 || y<=0)
		return;

	if(visited[x][y] == 1)
		return;
	
	p[0].x = 0.0; p[0].y = 0.0;
	p[1].x = 0.0; p[1].y = 0.25;
	p[2].x = 0.25; p[2].y = 0.25;
	p[3].x = 0.375; p[3].y = 0.125;
	p[4].x = 0.25; p[4].y = 0.0;
	
	int i;
	
	glColor3f(1.0,1.0,1.0);	
	glBegin(GL_LINE_LOOP);
	for(i=0;i<5;i++)
		glVertex2f(p[i].x,p[i].y);
	glEnd();
	glFlush();
	
	visited[x][y] = 1;

	
	if(!isWhite(x,y) && (!isWhite(x,y-1) && !isWhite(x+1,y)))
	{
	
		setp(x,y);
		floodfill(x+1,y);
		floodfill(x,y+1);
		floodfill(x-1,y);
		floodfill(x,y-1);

	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	int i;
	p[0].x = 0.0; p[0].y = 0.0;
	p[1].x = 0.0; p[1].y = 0.25;
	p[2].x = 0.25; p[2].y = 0.25;
	p[3].x = 0.375; p[3].y = 0.125;
	p[4].x = 0.25; p[4].y = 0.0;
	glBegin(GL_LINE_LOOP);
	for(i=0;i<5;i++)
		glVertex2f(p[i].x,p[i].y);
	glEnd();
	
	
	floodfill(500,305);
	glFlush();
	slfill();
	glFlush();
	
}

int main(int argc, char *argv[])
{
	for(int i = 0; i< 800; i++) 
	{
		for(int j = 0; j< 800; j++) 
		{
			visited[i][j] = 0;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Scan Line Fill");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}