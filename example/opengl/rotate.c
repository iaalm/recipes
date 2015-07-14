#include <GL/glut.h>

GLfloat X = 10.0f;
GLfloat Y = 1.0f;
GLfloat Z = 5.0f;

void myDisplay(void)
{
	GLfloat diffuse[] = {0.7,0.7,0.0,1.0};
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	/*绘制立方体*/
	glPushMatrix();
	glRotatef(X,1.0,0.0,0.0);
	//glRotatef(Y,0.0,1.0,0.0);
	//glRotatef(Z,0.0,0.0,1.0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	//glutSolidCube(1.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);

	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	//glVertex3f(0.0,0.0,1.0);
	//glVertex3f(1.0,1.0,0.0);
	//glVertex3f(0.0,1.0,1.0);
	//glVertex3f(1.0,0.0,1.0);
	//glVertex3f(1.0,1.0,1.0);
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();//交换当前窗口使用层的缓存
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.5,1.5,-1.5,1.5);
	if(w <= h)
		glOrtho(-2.25,2.25,-2.25*h/w,2.25*h/w,-10.0,10.0);
	else
		glOrtho(-2.25*w/h,2.25*w/h,-2.25,2.25,-10.0,10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myAnimate(void)
{
	X += 1.0;
	Y += 1.0;
	Z += 1.0;

		glutPostRedisplay();//标记当前窗口需要重新绘制

}

int main(int argc,char ** argv)
{
	/*初始化*/
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(200,200);

	/*创建窗口*/
	glutCreateWindow("color");

	/*绘制与显示*/
	glutReshapeFunc(myReshape);

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myAnimate);//设置全局空闲回调函数

	glutMainLoop();

	return(0);
}
