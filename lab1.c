#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

typedef GLfloat point[3];

point v[]={{-1.0,-0.5,0.0},
	   {1.0,-0.5,0.0},
	   {0.0,1.0,0.0},
	   {0.0,0.0,1.0}};
	   
GLfloat colors[4][3]={{1.0,0.0,0.0},
		      {0.0,1.0,0.0},
		      {0.0,0.0,1.0},
		      {1.0,1.0,0.0}};
	   
int n;
void triangle(point a,point b,point c)
{
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void tetra(point a,point b,point c,point d)
{
	glColor3fv(colors[0]);
	triangle(a,b,c);
	glColor3fv(colors[1]);
	triangle(a,c,d);
	glColor3fv(colors[2]);
	triangle(a,d,b);
	glColor3fv(colors[3]);
	triangle(b,d,c);
}
void divideTetra(point a,point b,point c,point d,int m)
{
	point mid[6];
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
		{
			mid[0][j]=(a[j]+b[j])/2.0;
			mid[1][j]=(a[j]+c[j])/2.0;
			mid[2][j]=(a[j]+d[j])/2.0;
			mid[3][j]=(c[j]+b[j])/2.0;
			mid[4][j]=(c[j]+d[j])/2.0;
			mid[5][j]=(b[j]+d[j])/2.0;
			
		}
		divideTetra(a,mid[0],mid[1],mid[2],m-1);
		divideTetra(mid[0],b,mid[3],mid[5],m-1);
		divideTetra(mid[1],mid[3],c,mid[4],m-1);
		divideTetra(mid[2],mid[5],mid[4],d,m-1);
	}
	else
		tetra(a,b,c,d);
}
void drawtext(float x,float y,char* s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	divideTetra(v[0],v[1],v[2],v[3],n);
	drawtext(0.5,0.8,"3D Gasket");
	drawtext(0.5,0.7,"1BI17CS015");
	drawtext(0.5,0.6,"Anandteerth");
	drawtext(0.5,0.5,"No. Of Divisions=2");
	glFlush();
}

void Reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-1.0,1.0,-1.0*((GLfloat)h/(GLfloat)w),1.0*((GLfloat)h/(GLfloat)w),-1.0,1.0);
	else
		glOrtho(-1.0*((GLfloat)w/(GLfloat)h),1.0*((GLfloat)h/(GLfloat)w),-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void main(int argc,char** argv)
{
	printf("No. of subdivisions:");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("3d Gasket");
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
