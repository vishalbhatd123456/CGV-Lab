// !!! While compiling add -lm to include math.h

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat triangle[3][3]={
    {100.0,250.0,175.0},
    {100.0,100.0,300.0},
    {1.0,1.0,1.0}
};

GLfloat rotateMat[3][3]={{0},{0},{0}};
GLfloat result[3][3]={{0},{0},{0}};
GLfloat arbitrary_x = 0;
GLfloat arbitrary_y = 0;
float rotation_angle;

void multiply()
{
    int i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            result[i][j] = 0;
            for(k=0;k<3;k++)
                result[i][j] += rotateMat[i][k] * triangle[k][j];
        }
}

/* Rotate Matrix matrix:

   | cos(𝛩) -sin(𝛩)  m |
   | sin(𝛩) cos(𝛩)   n |
   | 0      0        1  |

    m = x(1-cos(𝛩)) + ysin(𝛩)
    n = y(1-cos(𝛩)) - xsin(𝛩) */


void rotate()
{
    GLfloat m,n;
    rotation_angle = (rotation_angle*3.14)/180;
    m = (arbitrary_x*(1-cos(rotation_angle)))+(arbitrary_y*sin(rotation_angle));
    n = (arbitrary_y*(1-cos(rotation_angle)))-(arbitrary_x*sin(rotation_angle));
    rotateMat[0][0] = cos(rotation_angle);
    rotateMat[0][1] = -sin(rotation_angle);
    rotateMat[0][2] = m;
    rotateMat[1][0] = sin(rotation_angle);
    rotateMat[1][1] = cos(rotation_angle);
    rotateMat[1][2] = n;
    rotateMat[2][0] = 0;
    rotateMat[2][1] = 0;
    rotateMat[2][2] = 1;
    multiply();
}

void displayTriangle()
{
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle[0][0],triangle[1][0]);
    glVertex2f(triangle[0][1],triangle[1][1]);
    glVertex2f(triangle[0][2],triangle[1][2]);
    glEnd();
}

void displayRotatedTriangle()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(result[0][0],result[1][0]);
    glVertex2f(result[0][1],result[1][1]);
    glVertex2f(result[0][2],result[1][2]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayTriangle();
    displayRotatedTriangle();
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0,1.0,1.0,1.0);
    glLineWidth(3.0);
}

int main(int argc, char** argv)
{
    int ch;
    printf("Enter your choice:\n1)Rotate about origin\n2)Rotate about fixed point\nYour Choice:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: printf("\n Enter the Angle of rotation:");
                scanf("%f",&rotation_angle);
                rotate();
                break;
        case 2: printf("\n Enter the Fixed point of rotation xr yr:");
                scanf("%f%f",&arbitrary_x,&arbitrary_y);
               printf("\n Enter the Angle of rotation:");
                scanf("%f",&rotation_angle);
                rotate();
                break;
        default: printf("Invalid Choice");
                 exit(-1);
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Triangle Rotation");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
