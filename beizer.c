#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int count = 0;
int newclick = 0;
int drawing = 1;

struct pt
{
    float x;
    float y;
} p[100];




unsigned long int ncr(int n, int r)
{
    if (r > n/2)
        r = n-r;

    int i = n;
    unsigned long int res = 1;

    for (i = n; i > n - r; i--)
        res *= i;
    for (i = r; i > 1; i--)
        res /= i; 

    return res;
}


void bez()
{   
    if (count == 0)
        return;

    int i;
    double t = 0, x, y;

    glBegin (GL_POINTS);
    for (; t<1; t += 0.001)
    {
        unsigned long int nci = ncr (count, i);

        x = 0;
        y = 0;
        for (i = 0; i < count; i++)        
        {
            double term = pow (1-t, count-i-1);
            double tpi = pow (t,i);
            x += nci * term * tpi * p[i].x;
            y += nci * term * tpi * p[i].y;
        }

        glVertex2f(x,y);
    }
    glEnd();
}


void mouseHandler(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_UP)
            {

                p[count].x = (float)(x-250)/250.0;
                p[count].y = (float)(250-y)/250.0;
                printf("%d %d\n",x,y);
                count++;
                glutPostRedisplay();
                return;

            }

            break;
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    int i=0;
    glBegin(GL_LINE_LOOP);
    while(i<count)
    {
        glVertex2f(p[i].x,p[i].y);
        i++;
    }
    glEnd();
    glColor3f(1.0,0.0,0.0);
    bez();
    glColor3f(1.0,1.0,1.0);
    glFlush();

}


int main( int argc, char **argv )
{  
    p[0].x = 0;
    p[0].y = 0;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - BEZIER");
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutMainLoop();
    return 0;
}
