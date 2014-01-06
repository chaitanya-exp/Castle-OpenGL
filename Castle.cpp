#include <GL/glut.h>
#include<math.h>
static double x1=0,rotX = 0.0, rotY = 0.0,rot=0;
int wire=0,panaroma=0,open=0,walk=0;
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

static void SpecialKey(int key, int x, int y)
{

    switch (key) {
      case GLUT_KEY_UP:
	rotX -= 0.1;
	glutPostRedisplay();
	break;
      case GLUT_KEY_DOWN:
	rotX += 0.1;
	glutPostRedisplay();
	break;
      case GLUT_KEY_LEFT:
	rotY -= 0.1;
	glutPostRedisplay();
	break;
      case GLUT_KEY_RIGHT:
	rotY += 0.1;
	glutPostRedisplay();
	break;
    }
}

void flag()
{
	glPushMatrix();
	glTranslated(3.9,6,-4.25);
	glScaled(8,5,0.5);
	if(wire)
    glutWireCube(0.1);
	else
	glutSolidCube(0.1);
	glPopMatrix();
}

void box()
{
glPushMatrix();
	glScaled(2,0.5,2);
	if(wire)
	glutWireCube(1);
	else
	glutSolidCube(1);
	glPopMatrix();
    
    glPushMatrix();
	glTranslated(0.75,0.5,0.75);
	if(wire)
	glutWireCube(0.5);
	else
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75,0.5,0.75);
	if(wire)
	glutWireCube(0.5);
	else
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75,0.5,0.75);
	if(wire)
	glutWireCube(0.5);
	else
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75,0.5,-0.75);
	if(wire)
	glutWireCube(0.5);
	else
	glutSolidCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(-0.75,0.5,-0.75);
	if(wire)
	glutWireCube(0.5);
	else
	glutSolidCube(0.5);
	glPopMatrix();
}



void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{

float vx = x2-x1;
float vy = y2-y1;
float vz = z2-z1;

//handle the degenerate case of z1 == z2 with an approximation
if(vz == 0)
    vz = .0001;

float v = sqrt( vx*vx + vy*vy + vz*vz );
float ax = 57.2957795*acos( vz/v );
if ( vz < 0.0 )
    ax = -ax;
float rx = -vy*vz;
float ry = vx*vz;
glPushMatrix();

//draw the cylinder body
glTranslatef( x1,y1,z1 );
glRotatef(ax, rx, ry, 0.0);
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluCylinder(quadric, radius, radius, v, subdivisions, 1);

//draw the first cap
gluQuadricOrientation(quadric,GLU_INSIDE);
gluDisk( quadric, 0.0, radius, subdivisions, 1);
glTranslatef( 0,0,v );

//draw the second cap
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluDisk( quadric, 0.0, radius, subdivisions, 1);
glPopMatrix();

}

void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
//the same quadric can be re-used for drawing many cylinders
GLUquadricObj *quadric=gluNewQuadric();
gluQuadricNormals(quadric, GLU_SMOOTH);
renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
gluDeleteQuadric(quadric);
}


void fort(double rang) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	if(walk)
	{
	glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on 
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the 
    glTranslated(-xpos,-ypos,-zpos);
	}
	else
    if(panaroma)
	gluLookAt(0.5,15,1,0,9,-7,0,1,0);
    if(!walk)
	glTranslatef(0.0f,-5.0f,-48.0f);
	else
	{
		glTranslatef(0,1,-75);
        glScaled(2,2,2.5);
	}
    glRotatef(rang,0.0f,1.0f,0.0f);
    glPushMatrix();
	glTranslated(0,0,-10);
	glScaled(1,1,1.3);
    
   glColor3f(210/255.0,180/255.0,140/255.0);
	//Draw fleft cylinder
	glPushMatrix();
	glTranslatef(-22.5,-3.0,23);
	renderCylinder_convenient(0,0,0,0,5,0,1.4,20);
	glPopMatrix();
    
    //Draw fright cylinder
	glPushMatrix();
	glTranslatef(22.5,-3.0,23);
	renderCylinder_convenient(0,0,0,0,5,0,1.4,20);
	glPopMatrix();


	//Draw bleft cylinder
	glPushMatrix();
	glTranslatef(-22.5,-3.0,-8.0);
	renderCylinder_convenient(0,0,0,0,5,0,1.4,20);
	glPopMatrix();

	//Draw bright cylinder
	glPushMatrix();
	glTranslatef(22.5,-3.0,-8.0);
	renderCylinder_convenient(0,0,0,0,5,0,1.4,20);
	glPopMatrix();



	// Draw the left Wall 
	glPushMatrix();
	glScaled(0.3,1.5,15);
	glTranslatef(0.0,0.0,-0.5);
	glTranslatef(-75,-1,1.0);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();

	// Draw right wall

	glPushMatrix();
	glScaled(0.3,1.5,15);
	glTranslatef(0.0,0.0,-0.5);
	glTranslatef(75,-1,1.0);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix(); 

    // Draw rear wall
	
	glPushMatrix();
	glRotatef(90,0,1,0);
	glScaled(0.3,1.5,23);
	glTranslatef(0.0,0.0,-0.5);
	glTranslatef(26.5,-1.0,0.5);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix(); 
    //Draw bottom
	glColor3f(0/255.0,255/255.0,0/255.0);
	glPushMatrix();
    glTranslated(0,-3.5,8);
	glScaled(60,0.5,44);
	if(wire)
		glutWireCube(1);
	else
	glutSolidCube(1);
	glPopMatrix();

   glColor3f(210/255.0,180/255.0,140/255.0);
	
   //Gate wall 1
	glPushMatrix();
    glScaled(9,1.5,0.5);
	glTranslatef(-1.5,-1,47.0);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();
    //Gate wall 2
	glPushMatrix();
    glScaled(9,1.5,0.5);
	glTranslatef(1.5,-1,47.0);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();
    
    //Entrance l
	glPushMatrix();
    glScaled(1.2,2.6,0.9);
	glTranslatef(-4.6,-0.2,26);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();
    //Entrance r
	glPushMatrix();
    glScaled(1.2,2.6,0.9);
	glTranslatef(4.6,-0.2,26);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();

	//Entrance t
	glPushMatrix();
    glScaled(4.4,1,0.9);
	glTranslatef(0,2,26);
	if(wire)
	glutWireCube(2);
	else
	glutSolidCube(2);
	glPopMatrix();
	//Entrance t1
	glPushMatrix();
    glScaled(4.4,1,0.9);
	glTranslatef(0,3,26);
	if(wire)
	glutWireCube(1.5);
	else
	glutSolidCube(1.5);
	glPopMatrix();
	//Entrance t2
	glPushMatrix();
    glScaled(4.4,1,0.9);
	glTranslatef(0,4,26);
	if(wire)
	glutWireCube(1.0);
	else
	glutSolidCube(1.0);
	glPopMatrix();
    
    glColor3d(230,232,250);
	
	//Audi 1
	glPushMatrix();
	glTranslated(0,4.78,23.5);
	if(wire)
	glutWireTorus(0.08,0.3,10,20);
	else
	glutSolidTorus(0.08,0.3,10,20);
	glPopMatrix();
    //Audi 2
	glPushMatrix();
	glTranslated(0.5,4.78,23.5);
	if(wire)
	glutWireTorus(0.08,0.3,10,20);
	else
	glutSolidTorus(0.08,0.3,10,20);
	glPopMatrix();
	//Audi 3
	glPushMatrix();
	glTranslated(-0.5,4.78,23.5);
	if(wire)
	glutWireTorus(0.08,0.3,10,20);
	else
	glutSolidTorus(0.08,0.3,10,20);
	glPopMatrix();

    glColor3f(139/255.0,69/255.0,19/255.0);

    //Gate1
    glPushMatrix();
	if(open)
	glRotatef(-10,0,1,0);
    glScaled(4.2,5,0.5);
	glTranslatef(-0.5,-0.2,46);
	if(wire)
	glutWireCube(1.0);
	else
	glutSolidCube(1.0);
	glPopMatrix();
	//Gate2
    glPushMatrix();
	if(open)
	glRotatef(10,0,1,0);
    glScaled(4.2,5,0.5);
    glTranslatef(0.5,-0.2,46);
	if(wire)
	glutWireCube(1.0);
	else
	glutSolidCube(1.0);
	glPopMatrix();

	
	glPopMatrix();
  
	glTranslated(0.5,-1.5,-6);
	glPopMatrix(); 

	//Draw the main cube
    
	//Draw front wall
    glColor3f(255/255.0,185/255.0,15/255.0);
    glPushMatrix();
	glTranslated(-7.5,-1,3);
	glScaled(7,3,0.8);
	if(wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Draw sidewall
	glPushMatrix();
	glTranslated(-10.6,-1,1.3);
	glRotated(-90,0,1,0);
	glScaled(3,3,0.8);
	if(wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Draw b wall
	glPushMatrix();
	glTranslated(-6.2,-1,-3.6);
	glScaled(6,3,0.8);
	if(wire)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	glPopMatrix();
   
   glColor3f(148/255.0,0/255.0,211/255.0);

    //Draw big cylinder
	glPushMatrix();
	glTranslated(-10.3,-2.5,-2.2);
    renderCylinder_convenient(0,0,0,0,4.4,0,2.2,20);
	glPopMatrix();
	glColor3f(255/255.0,0/255.0,0/255.0);
	//Draw big cone
	glPushMatrix();
	glRotatef(-90,1,0,0);
    glTranslated(-10.3,2,1.6);
	if(wire)
	glutWireCone(3.4,3,15,15);
	else
	glutSolidCone(3.4,3,15,15);
	glPopMatrix();
    
	//Draw cube
    glColor3f(255/255.0,185/255.0,15/255.0);
	glPushMatrix();
	glTranslated(7.6,-1,-1);
	glScaled(2.2,1,1.5);
	if(wire)
		glutWireCube(4.0);
	else
		glutSolidCube(4.0);
    glPopMatrix();
    glColor3f(238/255.0,44/255.0,44/255.0);
	//Draw sphere
	glPushMatrix();
	
    glTranslated(8,1.3,-1);
	if(wire)
	glutWireSphere(2.5,15,15);
	else
	glutSolidSphere(2.5,15,15);
	glPopMatrix();

	glColor3f(255/255.0,185/255.0,15/255.0);

	glPushMatrix();
    glTranslatef(0.0,0.0,-0.5);
	glScaled(1.6,1.2,2);
	if(wire)
	glutWireCube(4);
	else
	glutSolidCube(4);
	glPopMatrix();
    
    glColor3f(0.576471,0.439216,0.858824);

	//Draw fr cylinder
	glPushMatrix();
	glTranslated(2.9,-2.45,3.0);
    renderCylinder_convenient(0,0,0,0,6.05,0,0.7,20);
	glPopMatrix();

	//Draw fl cylinder
	glPushMatrix();
	glTranslated(-3.6,-2.4,3.0);
    renderCylinder_convenient(0,0,0,0,5.2,0,1.3,20);
	glPopMatrix();

	//Draw br cylinder
	glPushMatrix();
	glTranslated(2.9,-2.4,-5.0);
    renderCylinder_convenient(0,0,0,0,10,0,1.5,20);
	glPopMatrix(); 

	//Draw bm cylinder
	glPushMatrix();
	glTranslated(-1.2,-2.45,-4.1);
    renderCylinder_convenient(0,0,0,0,8,0,1.2,50);
	glPopMatrix(); 
    
    glColor3f(1,0,0);

    //Draw cone1
	glPushMatrix();
	glRotatef(-90,1,0,0);
    glTranslated(-1.2,4.1,4.6);
	if(wire)
	glutWireCone(1.8,3.5,15,15);
	else
	glutSolidCone(1.8,3.5,15,15);
	glPopMatrix();

	//Draw cone2
	glPushMatrix();
	glRotatef(-90,1,0,0);
    glTranslated(2.8,4.8,6.4);
	if(wire)
	glutWireCone(2.5,5,15,15);
	else
	glutSolidCone(2.5,5,15,15);
	glPopMatrix();

	glScaled(1.8,1.6,1.8);
	glTranslated(-1.9,2,1.6);
	glColor3f(238/255.0,44/255.0,44/255.0);
	//Draw box
	box();
    glColor3d(255,215,0);
	glPushMatrix();
	glTranslated(3.5,0.8,0);
	glRotated(rot,1,1,1);
	if(wire)
	glutWireTorus(0.15,0.4,10,20);
	else
	glutSolidTorus(0.15,0.4,10,20);
	glPopMatrix();
    
	glPushMatrix();
	glColor3d(230,232,250);
	glTranslated(3.5,1.2,0);
	glRotated(rot,0,0,0);
	if(wire)
	glutWireTorus(0.05,0.5,10,20);
	else
	glutSolidTorus(0.05,0.5,10,20);
	glPopMatrix();
    glColor3f(0.439216,0.858824,0.576471);
	glPushMatrix();
	glTranslated(3.45,4.5,-4.25);
    renderCylinder_convenient(0,0,0,0,2,0,0.03,20);
	glPopMatrix();

    glColor3f(166/255.0,128/255.0,100/255.0);
	glPushMatrix();
	glTranslated(-11,0.4,-9.6);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.2,0.4,12.75);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11,0.4,12.75);
	box();
	glPopMatrix();

	glPushMatrix();
	glTranslated(14.2,0.4,-9.6);
	box();
	glPopMatrix();
	glColor3f(1,0,0);
	flag();
	rot+=1;
    glFlush();
    glutSwapBuffers();
}



 
void inc() 
{
	x1 += 0.05;
	fort(x1);
}

void init() 
{
    glClearColor(0.690196078,0.87843137,0.90196078,1.0);
    glViewport(0,0,1050,680);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(GLfloat)1050/(GLfloat)680,0.2f,200.0f);
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Display()
{

	GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_diffuse[]={0.5f,0.5f,.5f,1.0f};
	GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat mat_shininess[]={100.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	GLfloat lightIntensity[]={0.3f,0.3f,0.3f,1.0f};
	GLfloat light_position[]={2.0f,5.0f,6.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	glFlush();
	glutSwapBuffers();
    fort(x1);
    
}

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')//going up
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')//going down
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w')//going front
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s')//going back
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='d')//going left
    {
    yrot += 1;
    if (yrot >360) yrot -= 360;
    }

    if (key=='a')//going right
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }
    if (key==27)
    exit(0);
	if(key=='o')open=!open;
	Display();
}

void menu(int id)
{
	switch(id)
	{
	case 1:glutIdleFunc(inc);
		   break;
    case 2:panaroma=0;
		   break;
	case 3:panaroma=1;
		   break;
	case 4:wire=1;
		   break;
    case 5:wire=0;
		   break;
	case 6: walk=!walk;
		    break;
	case 7: exit(0);
		    break;
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(950,700);
    glutInitWindowPosition(50,0);
    glutCreateWindow("fort");
    glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKey);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutCreateMenu(menu);
    glutAddMenuEntry("Rotate",1);
	glutAddMenuEntry("Normal view",2);
	glutAddMenuEntry("Bird Eye view",3);
	glutAddMenuEntry("Wired structure",4);
	glutAddMenuEntry("Solid Structure",5);
    glutAddMenuEntry("Walk Mode",6);
	glutAddMenuEntry("Exit",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
    glutMainLoop();
	return 0; 
}
