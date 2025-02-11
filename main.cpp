#include <GL/glut.h>


void DrawShape() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 1);
    glPointSize(10);


    GLfloat points[16][2] = {
            {50, 50}, {150, 50}, {250, 50},   // Bottom row
            {50, 150}, {100, 150}, {250, 150}, // Middle row
            {50, 250}, {150, 250}, {250, 250}, // Top row
            {100, 100}, {200, 100},           // Bottom side of inner square
            {200, 200}, {100, 200},           // Top side of inner square
            {150, 100}, {200, 150}, {150, 200} // Midpoints of the inner square sides
    };

    // Draw points
    glBegin(GL_POINTS);
    for (int i = 0; i < 16; ++i) {
        glVertex2f(points[i][0], points[i][1]);
    }

    glEnd();

    // Draw lines connecting the points
    glColor3f(0, 1, 1);  // Set line color to cyan
    glBegin(GL_LINES);

    // Outer square lines
    glVertex2f(points[0][0], points[0][1]); glVertex2f(points[1][0], points[1][1]);
    glVertex2f(points[1][0], points[1][1]); glVertex2f(points[2][0], points[2][1]);
    glVertex2f(points[2][0], points[2][1]); glVertex2f(points[5][0], points[5][1]);
    glVertex2f(points[5][0], points[5][1]); glVertex2f(points[8][0], points[8][1]);
    glVertex2f(points[8][0], points[8][1]); glVertex2f(points[7][0], points[7][1]);
    glVertex2f(points[7][0], points[7][1]); glVertex2f(points[6][0], points[6][1]);
    glVertex2f(points[6][0], points[6][1]); glVertex2f(points[3][0], points[3][1]);
    glVertex2f(points[3][0], points[3][1]); glVertex2f(points[0][0], points[0][1]);

    // Inner square lines
    glVertex2f(points[9][0], points[9][1]); glVertex2f(points[10][0], points[10][1]);
    glVertex2f(points[11][0], points[11][1]); glVertex2f(points[10][0], points[10][1]);
    glVertex2f(points[12][0], points[12][1]); glVertex2f(points[11][0], points[11][1]);
    glVertex2f(points[9][0], points[9][1]); glVertex2f(points[12][0], points[12][1]);

    // Diagonal lines connecting the outer square to the inner square
    glVertex2f(points[7][0], points[7][1]); glVertex2f(points[11][0], points[11][1]);

    glVertex2f(points[5][0], points[5][1]); glVertex2f(points[11][0], points[11][1]);

    glVertex2f(points[7][0], points[7][1]); glVertex2f(points[12][0], points[12][1]);

    glVertex2f(points[3][0], points[3][1]); glVertex2f(points[12][0], points[12][1]);

    //glVertex2f(points[5][0], points[5][1]); glVertex2f(points[12][0], points[12][1]);

    glVertex2f(points[5][0], points[5][1]); glVertex2f(points[10][0], points[10][1]);

    glVertex2f(points[1][0], points[1][1]); glVertex2f(points[10][0], points[10][1]);

    glVertex2f(points[3][0], points[3][1]); glVertex2f(points[9][0], points[9][1]);

    glVertex2f(points[1][0], points[1][1]); glVertex2f(points[9][0], points[9][1]);

    glVertex2f(points[15][0], points[15][1]); glVertex2f(points[14][0], points[14][1]);


    glVertex2f(points[13][0], points[13][1]); glVertex2f(points[14][0], points[14][1]);
    glVertex2f(points[4][0], points[4][1]); glVertex2f(points[13][0], points[13][1]);
    glVertex2f(points[4][0], points[4][1]); glVertex2f(points[15][0], points[15][1]);
    glVertex2f(points[14][0], points[14][1]); glVertex2f(points[4][0], points[4][1]);
    glEnd();  // End drawing lines

    glFlush();  // Force drawing to screen
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Shape Drawing");

    gluOrtho2D(0, 300, 0, 300);

    glutDisplayFunc(DrawShape);
    glutMainLoop();
}
