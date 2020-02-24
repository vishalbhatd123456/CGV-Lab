#include<stdio.h>
#include<GL/glut.h>
typedef GLfloat point[2];
point v[]={{-1.0,-0.5},{1.0,-0.5},{0.0,1.15}};
int n;
void triangles(point a,point b,point c)
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glEnd();
}
void divideTriangle(point a,point b,point c,int m)
{
	point v0,v1,v2;
	int j;
	if(m>0)
	{
		for(j=0;j<2;j++)
			v0[j]=(a[j]+b[j])/2.0;
		for(j=0;j<2;j++)
			v1[j]=(c[j]+b[j])/2.0;
		for(j=0;j<2;j++)
			v2[j]=(a[j]+c[j])/2.0;
		
		divideTriangle(a,v0,v2,m-1);
		divideTriangle(v0,b,v1,m-1);
		divideTriangle(v2,v1,c,m-1);
	}
	else
		triangles(a,b,c);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	divideTriangle(v[0],v[1],v[2],n);
	glFlush();
}
void Init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0,2.0,-2.0,2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
}
void main(int argc,char** argv)
{
	printf("No. of subdivisions:");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("2d Serpinski Gasket");
	glutDisplayFunc(display);
	Init();
	glutMainLoop();
}
