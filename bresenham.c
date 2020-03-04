#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

int x1,x2,y1,y2;

void drawPixel(float x, float y)
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void drawLine(int x1,int y1, int x2, int y2)
{
    int dx,dy,inc1,inc2,incx,incy,x,y,i;
    int d;
    dx = x2-x1;
    dy = y2-y1;
    if(dx<0) dx = -dx;
    if(dy<0) dy = -dy;
    incx = 1;
    if(x2<x1) incx = -1;
    incy = 1;
    if(y2<y1) incy = -1;
    x = x1;
    y = y1;
    drawPixel(x,y);
    if(dx>dy)
    {
        d = 2*dy-dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for(i=0;i<dx;i++)
        {
            if(d>=0)
            {
                y += incy;
                d += inc1;
            }
            else
                d += inc2;
            x += incx;
            drawPixel(x,y);
        }
    }
    else
        {
        d = 2*dx-dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for(i=0;i<dy;i++)
        {
            if(d>=0)
            {
                x += incx;
                d += inc1;
            }
            else
                d += inc2;
            y += incy;
            drawPixel(x,y);
        }
    }
}

void drawText(float x, float y, char* s)
{
    int i;
    glRasterPos2f(x,y);
    for(i=0;s[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}

void display()
{
    char c1[10],c2[10];
    sprintf(c1,"(%d,%d)",x1,y1);
    sprintf(c2,"(%d,%d)",x2,y2);
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(x1,y1,x2,y2);
    drawText(x1,y1-10,c1);
    drawText(x2,y2-10,c2);
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
}

void main(int argc, char** argv)
{
    printf("Enter x1,y1 and x2,y2\n");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Line Drawing Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}