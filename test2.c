#include<stdio.h>
#include<GL/glut.h>

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat v[3][2]={0.0,0.0,25.0,50.0,50.0,0.0};
	int j,k;
	GLfloat p[]={7.5,5.0};
	glBegin(GL_POINTS);
	for(k=0;k<20000;k++)
	{
		j=rand()%3;
		p[0]=(p[0]+v[j][0])/2.0;
		p[1]=(p[1]+v[j][1])/2.0;
		glVertex2f(p[0],p[1]);
	}
	glEnd();
	glFlush();
}
void Init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,55.0,0.0,55.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
}
void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("2d Serpinski Gasket");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();
}
