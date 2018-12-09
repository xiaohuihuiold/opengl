#include <iostream>
#include <GL/glut.h>

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const int WIDTH = 1200;
static const int HEIGHT = 720;

static const char *TITLE = "OpenGL";

/**
 * 渲染
 */
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.4, 0.2);

    glBegin(GL_POLYGON);
    glVertex2i(180, 15);
    glVertex2i(10, 145);
    glVertex2i(1, 0);
    glEnd();

    glFlush();
}

/**
 * 错误检查
 * @param line 当前行
 * @return 错误code
 */
GLenum errorCheck(int line) {
    GLenum code;
    const GLubyte *message;

    code = glGetError();
    if (code != GL_NO_ERROR) {
        message = gluErrorString(code);
        fprintf(stderr, "OpenGL error: %s \n", message);
    }
    return code;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0, HEIGHT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((SCREEN_WIDTH - WIDTH) / 2, (SCREEN_HEIGHT - HEIGHT) / 2);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(TITLE);

    init();

    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}