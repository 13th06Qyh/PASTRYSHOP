#include <GL/glut.h>

#define MAX 100

typedef struct
{
    int x, y, z;
} Point3D;

typedef struct
{
    int nFace;
    int indexFace[MAX];
} FaceType;

typedef struct
{
    int numVertex, numFace;
    Point3D vertex[MAX];
    FaceType face[MAX];
} FaceModel;

FaceModel cube;

void initCube()
{
    cube.numVertex = 8;
    cube.numFace = 6;

    cube.vertex[0] = {-1, -1, -1};
    cube.vertex[1] = {1, -1, -1};
    cube.vertex[2] = {1, 1, -1};
    cube.vertex[3] = {-1, 1, -1};
    cube.vertex[4] = {-1, -1, 1};
    cube.vertex[5] = {1, -1, 1};
    cube.vertex[6] = {1, 1, 1};
    cube.vertex[7] = {-1, 1, 1};

    cube.face[0] = {4, {0, 1, 2, 3}};
    cube.face[1] = {4, {4, 5, 6, 7}};
    cube.face[2] = {4, {0, 1, 5, 4}};
    cube.face[3] = {4, {2, 3, 7, 6}};
    cube.face[4] = {4, {0, 3, 7, 4}};
    cube.face[5] = {4, {1, 2, 6, 5}};
}

float theta = 0.0;
float phi = 0.0;
float scale = 1.0;
float cameraX = 0.0, cameraY = 0.0, cameraZ = 5.0;
bool perspective = true;

void drawModel(FaceModel &model)
{
    for (int i = 0; i < model.numFace; i++)
    {
        glBegin(GL_POLYGON);
        for (int j = 0; j < model.face[i].nFace; j++)
        {
            int vertexIndex = model.face[i].indexFace[j];
            Point3D v = model.vertex[vertexIndex];
            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (perspective)
    {
        gluPerspective(45.0, 1.0, 0.1, 50.0);
    }
    else
    {
        glOrtho(-5, 5, -5, 5, -10, 10);
    }

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    glScalef(scale, scale, scale);
    glRotatef(phi, 1.0, 0.0, 0.0);
    glRotatef(theta, 0.0, 1.0, 0.0);

    drawModel(cube);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        perspective = !perspective;
        break;
    case '+':
        scale += 0.1;
        break;
    case '-':
        scale -= 0.1;
        break;
    case 'w':
        phi += 5;
        break;
    case 's':
        phi -= 5;
        break;
    case 'a':
        theta -= 5;
        break;
    case 'd':
        theta += 5;
        break;
    case 'i':
        cameraZ -= 0.5;
        break;
    case 'o':
        cameraZ += 0.5;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Polygon Mesh Model");
    glEnable(GL_DEPTH_TEST);
    initCube();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
