// Contributor: Sunil Nayak

#include "GL/freeglut.h"
#include "GL/glut.h"
#include <math.h>
#include <stdio.h>

void putp(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x / 2400.0, y / 2400.0);
    glEnd();
}

float verts[8][2] = { { 0, 0 },
                      { 0, 400 },
                      { 400, 400 },
                      { 400, 0 },
                      { 200, 200 },
                      { 200, 600 },
                      { 600, 600 },
                      { 600, 200 } };

void bres(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float p = 2 * (dy - dx);
    float x = x1, y = y1;

    if (dx == 0) {
        for (y = y1; y != y2; y += (dy) / abs(dy)) {
            putp(x, y);
        }
    }

    while (x != x2) {
        if (dy == 0) {
            x += dx / abs(dx);
        } else if (p < 0) {
            x += dx / abs(dx);
            y = y;
            p += 2 * abs(dy);
        } else {
            x += dx / abs(dx);
            y += dy / abs(dy);
            p += 2 * (abs(dy) - abs(dx));
        }
        putp(x, y);
    }
}

void brij(int i, int j) {
    bres(verts[i][0], verts[i][1], verts[j][0], verts[j][1]);
}

void dcube() {
    int i;
    for (i = 0; i <= 2; i++)
        brij(i, i + 1);
    brij(0, 3);
    for (i = 4; i <= 6; i++)
        brij(i, i + 1);
    brij(4, 7);
    for (i = 0; i < 4; i++)
        brij(i, i + 4);
}

float sinx, siny;

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    float sx = 0, sy = 0;
    dcube();
    while (sx <= sinx) {
        glClear(GL_COLOR_BUFFER_BIT);
        dcube();
        glFlush();
        glutSwapBuffers();
        sx += 1;
        verts[1][0] += 5;
        verts[2][0] += 5;
        verts[5][0] += 5;
        verts[6][0] += 5;
    }
    /*
    while(sy<=siny)
    {
            glClear(GL_COLOR_BUFFER_BIT);
            dcube();
            glFlush();
            sy+=1;
            verts[0][1]+=1;
            verts[3][1]+=1;
            verts[4][1]+=1;
            verts[7][1]+=1;
    }
    dcube(); */
    glFlush();
}

int main(int argc, char *argv[]) {
    sinx = (float)atoi(argv[1]);
    siny = (float)atoi(argv[2]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test");
    glutDisplayFunc(render);
    glutMainLoop();
}
