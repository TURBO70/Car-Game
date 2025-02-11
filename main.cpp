#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <sstream>

GLuint enemyCarTexture;

float xx = -2.0f;
const float width = 0.1f;
const float height = 0.1f;
 float lineSpeed = 0.0005f;
float carX = 0.0f, carY = -0.8f;
GLuint carTexture;
float carWidth, carHeight;
int score=0;

float enemyCar1X = -0.5f, enemyCar1Y = 1.0f;
float enemyCar2X = 0.5f, enemyCar2Y = 1.5f;
float enemyCarWidth, enemyCarHeight;
 float enemyCarSpeed = 0.0003f;

bool gameOver = false;


GLuint loadTexture(const char* filePath, float& texWidth, float& texHeight) {
    int width, height, channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);
    if (!data) {
        printf("Failed to load image: %s\n", filePath);
        exit(1);
    }

    texWidth = (float)width;
    texHeight = (float)height;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
}

static void fillRect(float x, float y, float width, float height) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void fillRect2(float x, float y, float width, float height) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

bool checkCollision() {
    float carWidth = 0.2f;
    float carHeight = 0.4f;
    float enemyCarWidth = 0.2f;
    float enemyCarHeight = 0.2f;

     if ((carX < enemyCar1X + enemyCarWidth) && (carX + carWidth > enemyCar1X) &&
        (carY < enemyCar1Y + enemyCarHeight - 0.005f) && (carY + carHeight > enemyCar1Y + 0.005f)) {
        return true;
    }

    if ((carX < enemyCar2X + enemyCarWidth) && (carX + carWidth > enemyCar2X) &&
        (carY < enemyCar2Y + enemyCarHeight - 0.005f) && (carY + carHeight > enemyCar2Y + 0.005f)) {
        return true;
    }
    return false;
}


void drawGame() {
    glColor3f(1.0f, 1.0f, 1.0f);  
    glRasterPos2f(-0.9f, 0.9f);  

    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;  
    const std::string scoreMessage = scoreStream.str();
    for (size_t i = 0; i < scoreMessage.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreMessage[i]);
    }
    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.2f, 0.0f);  
        const char* message = "Game Over!";
        while (*message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        }
        
        glColor3f(1.0f, 1.0f, 1.0f);  
        glRasterPos2f(-0.2f, -0.1f);  
        std::ostringstream scoreStream;
        scoreStream << "Score: " << score;  
        const std::string scoreMessage = scoreStream.str();
        for (size_t i = 0; i < scoreMessage.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreMessage[i]);  
        }
        return;
    }

    float aspectRatio = carWidth / carHeight;
    float carQuadWidth = 0.2f * aspectRatio;
    float carQuadHeight = 0.2f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, carTexture);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(carX - carQuadWidth, carY - carQuadHeight);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(carX + carQuadWidth, carY - carQuadHeight);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(carX + carQuadWidth, carY + carQuadHeight);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(carX - carQuadWidth, carY + carQuadHeight);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}



void drawRoadLines() {
    int numLines = 200;
    float dashWidth = 0.02f;
    float dashHeight = 0.1f;

    float leftLineX = -0.3f;
    float rightLineX = 0.3f;

    for (int i = 0; i < numLines; i++) {
        float yPos = xx - 0.2f * i;
        fillRect2(leftLineX, yPos, dashWidth, dashHeight);
        fillRect2(rightLineX, yPos, dashWidth, dashHeight);
    }

    if (xx < 1.0f) {
        xx += 2.5f;
    }
    xx -= lineSpeed;
}

void drawRoad() {
    float windowWidth = 800.0f / 600.0f;
    float leftX = -windowWidth / 1.34f;
    float rightX = windowWidth / 1.5f;

    for (int i = 0; i < 1000; i++) {
        float yPos = xx - 0.2f * (i + 1);
        fillRect(leftX, yPos, width, height);
        fillRect(rightX, yPos, width, height);
    }
    if (xx < -5.0f) {
        xx = 10.0f;
    }
    xx -= lineSpeed;
}


void drawEnemyCar(float x, float y) {
    float aspectRatio = enemyCarWidth / enemyCarHeight;
    float enemyCarQuadWidth = 0.2f * aspectRatio;
    float enemyCarQuadHeight = 0.2f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, enemyCarTexture);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - enemyCarQuadWidth, y - enemyCarQuadHeight); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + enemyCarQuadWidth, y - enemyCarQuadHeight); // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + enemyCarQuadWidth, y + enemyCarQuadHeight); // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - enemyCarQuadWidth, y + enemyCarQuadHeight); // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void updateEnemyCars() {
    if (gameOver) return;

    enemyCar1Y -= enemyCarSpeed;
    enemyCar2Y -= enemyCarSpeed;

    if (enemyCar1Y < -1.0f) {
        enemyCar1Y = 1.0f;
        enemyCar1X = (rand() % 3 - 1) * 0.5f;
        score++;
        lineSpeed+=0.0001;
        enemyCarSpeed+=0.0001;
    }
    if (enemyCar2Y < -1.0f) {
        enemyCar2Y = 1.0f;
        enemyCar2X = (rand() % 3 - 1) * 0.5f;
        score++;
        lineSpeed+=0.0001;
        enemyCarSpeed+=0.0001;

    }
}

void init() {
    srand(time(0));
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    carTexture = loadTexture("E:\\sixth_Car 1.png", carWidth, carHeight);
    enemyCarTexture = loadTexture("E:\\second_Car.jpg", enemyCarWidth, enemyCarHeight);
}

void normalKey(unsigned char key, int x, int y) {
    if (gameOver && (key == 'r' || key == 'R')) {

        carX = 0.0f;
        carY = -0.8f;
        enemyCar1X = -0.5f;
        enemyCar1Y = 1.0f;
        enemyCar2X = 0.5f;
        enemyCar2Y = 1.5f;
        score = 0;
        gameOver = false;
    }
    glutPostRedisplay();
}



void keyboard(int key, int x, int y) {
    float moveSpeed = 0.05f;

    switch (key) {
        case GLUT_KEY_LEFT:
            carX -= moveSpeed;
            if (carX < -0.7f) carX = -0.7f;
            break;
        case GLUT_KEY_RIGHT:
            carX += moveSpeed;
            if (carX > 0.7f) carX = 0.7f;
            break;
        case GLUT_KEY_UP:
            carY += moveSpeed;
            if (carY > 0.3f) carY = 0.3f;
            break;
        case GLUT_KEY_DOWN:
            carY -= moveSpeed;
            if (carY < -0.9f) carY = -0.9f;
            break;
    }
    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRoad();
    drawRoadLines();
    drawGame();

    drawEnemyCar(enemyCar1X, enemyCar1Y);
    drawEnemyCar(enemyCar2X, enemyCar2Y);

    if (checkCollision()) {
        gameOver = true;
    }

    if (gameOver) {
        drawGame();
    } else {
        updateEnemyCars();
    }

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 560);
    glutCreateWindow("Moving Car");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normalKey);
    glutMainLoop();
    return 0;
}
