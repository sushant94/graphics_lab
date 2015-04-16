// Contributor: Sunil Nayak

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <math.h>

void putp(float x1, float y1) {
    glBegin(GL_POINTS);
    glVertex2f(x1 / 800, y1 / 800);
    glEnd();
}

void bres(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float p = 2 * (dy - dx);
    float x = x1, y = y1;

    if (dx == 0) {
        for (y = y1; y != y2; y += (dy) / abs(dy))
            putp(x, y);
    }

    while (x != x2) {
        if (dy == 0)
            x += dx / abs(dx);

        else if (p < 0) {
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

void brescirc(int cx, int cy, int r) {
    int x = r;
    int y = 0;
    int p = 1 - x;

    while (x >= y) {
        putp(x + cx, y + cy);
        putp(-x + cx, y + cy);
        putp(x + cx, -y + cy);
        putp(-x + cx, -y + cy);
        putp(y + cx, x + cy);
        putp(-y + cx, x + cy);
        putp(y + cx, -x + cy);
        putp(-y + cx, -x + cy);

        y += 1;
        if (p <= 0) {

            p += 2 * y;
        } else {
            x--;
            p += 2 * (y - x);
        }
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    bres(0, -800, 0, 800);
    bres(-800, 0, 800, 0);
    bres(250, 100, 500, 400);
    bres(750, 100, 500, 400);
    bres(500, 350, 500, 625);
    bres(250, 500, 500, 625);
    bres(750, 500, 500, 625);
    int i;
    for (i = 0; i <= 75; i++) {
        brescirc(500, 700, i);
        glColor3f((float)i / 75.0, (float)i / 75.0, (float)i / 75.0);
    }

    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Endsem Practice");
    glutDisplayFunc(render);
    glutMainLoop();
}
