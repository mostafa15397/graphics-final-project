#include <windows.h>
#include <F:\New folder\codeblocks\MinGW\include\GL\glut.h>
#include <F:\New folder\codeblocks\MinGW\include\stdlib.h>
#include <F:\New folder\codeblocks\MinGW\include\math.h>


static int shoulder_1 = -90,shoulder_2 =0, elbow = 0.25,  fingerBase = 0, fingerUp = 0
                        ,r_hip = 0, r_hip2 = 0, r_knee = 0, l_hip = 0, l_hip2 = 0 ,l_knee = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };

void init(void)
{
   glMatrixMode(GL_PROJECTION);
   gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);

}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()
{
	// implement camera rotation arround vertical window screen axis to the left
	// used by mouse and left arrow
	rotatePoint(up,-0.1,eye);
}

void Right()
{
	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
	rotatePoint(up,0.1,eye);
}

void Up()
{
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
	double rotationVector[] = {0,0,0} ;
    double lookVector[] = {center[0]-eye[0],center[1]-eye[1],center[2]-eye[2]} ;
    crossProduct(up,lookVector,rotationVector) ;
    normalize(rotationVector) ;
    rotatePoint(rotationVector,0.1,eye);
    rotatePoint(rotationVector,0.1,up);
}

void Down()
{
	// implement camera rotation arround horizontal window screen axis
	// used by down arrow
	double rotationVector[] = {0,0,0} ;
    double lookVector[] = {center[0]-eye[0],center[1]-eye[1],center[2]-eye[2]} ;
    crossProduct(up,lookVector,rotationVector) ;
    normalize(rotationVector) ;
    rotatePoint(rotationVector,-0.1,eye);
    rotatePoint(rotationVector,-0.1,up);
}

void moveForward()
{
    double speed = .1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;

}

void moveBack()
{
    double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);


	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}


void draw_right_arm (void)
{
    // shoulder_1 right
   glRotatef (0, 0.0, 1.0 , 0.0);

   glTranslatef ( 2.0 , 4.0 , 0.0);
   glRotatef ((GLfloat) shoulder_1, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef((GLfloat)shoulder_2*-1,1,0,0) ;
   glRotatef(180,1,0,0) ;

   glPushMatrix();
   glScalef (2.0, 0.6, 0.4);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.6, 0.4);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1_right
   glPushMatrix();
       glTranslatef(1.0, 0.0, 0.0);

       glTranslatef(0.0, 0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 1_right
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();

    //Draw finger flang 2
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, 0.3, -0.1);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 2
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();




   //Draw finger flang 3
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, 0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.1);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 3
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();

   //Draw finger flang 4
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, -0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 4
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();



// end
}

void draw_left_arm(void)
{

   glRotatef (180, 0.0, 1.0 , 0.0);

   glTranslatef ( 2.0 , 4.0 , 0.0);
   glRotatef ((GLfloat) shoulder_1, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef((GLfloat)shoulder_2*1,1,0,0) ;
   glRotatef(180,1,0,0) ;

   glPushMatrix();
   glScalef (2.0, 0.6, 0.4);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.6, 0.4);
   glutWireCube (1.0);
   glPopMatrix();

   //Draw finger flang 1
   glPushMatrix();
       glTranslatef(1.0, 0.0, 0.0);

       glTranslatef(0.0, 0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 1
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();

    //Draw finger flang 2
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, 0.3, -0.1);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 2
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();




   //Draw finger flang 3
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, 0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, -0.05, 0.1);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 3
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();

   //Draw finger flang 4
   glPushMatrix();

       glTranslatef(1.0, 0.0, 0.0);
       glTranslatef(0.0, -0.3, 0.0);
       glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.05, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();


       //Draw finger flang 4
       glTranslatef(0.15, 0.0, 0.0);
       glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
       glTranslatef(0.15, 0.0, 0.0);
       glPushMatrix();
       glScalef(0.3, 0.1, 0.1);
       glutWireCube(1);
       glPopMatrix();

   glPopMatrix();
}

void draw_left_leg(void)
{
   glTranslatef ( -1.5 , -3+ 1 , 0.0 );

   glRotatef ((GLfloat) l_hip2*-1 , 0.0, 0.0, 1.0 );
   glTranslatef(0.5, 0.0 , 0.0 );

   glRotatef ((GLfloat) l_hip , 1.0, 0.0, 0 );
   glTranslatef(0.0, -1.5 , 0.0 );


   glPushMatrix();
   glScalef (1.0, 3 , 1.2);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef ( 0 , -1.5 , 0.0);
   glRotatef ((GLfloat) l_knee , 1.0, 0.0, 0.0);
   glTranslatef(0.0, -1.5 , 0.0 );

   glPushMatrix();
   glScalef (1.0, 3 , 1.2);
   glutWireCube (1.0);
   glPopMatrix();


   glTranslatef(0.0, -1.9 , 0.3 );

   glPushMatrix();
   glScalef (1.0, 0.8 , 1.8 );
   glutWireCube (1.0);
   glPopMatrix();

}

void draw_right_leg(void)
{
   glTranslatef ( 1.5 , -3+1 , 0.0);

   glRotatef ((GLfloat) r_hip2 , 0.0, 0.0, 1.0 );
   glTranslatef(-0.5, 0.0 , 0.0 );

   glRotatef ((GLfloat) r_hip , 1.0, 0.0, 0 );
   glTranslatef(0.0, -1.5 , 0.0 );


   glPushMatrix();
   glScalef (1.0, 3 , 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef ( 0 , -1.5 , 0.0);
   glRotatef ((GLfloat) r_knee , 1.0, 0.0, 0.0);
   glTranslatef(0.0, -1.5 , 0.0 );

   glPushMatrix();
   glScalef (1.0, 3 , 1.0);
   glutWireCube (1.0);
   glPopMatrix();


   glTranslatef(0.0, -1.9, 0.3 );

   glPushMatrix();
   glScalef (1.0, 0.8 , 1.8 );
   glutWireCube (1.0);
   glPopMatrix();
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT );
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef (-1.0, 0.0, 0.0);


    // draw trunck
    glPushMatrix();
    glTranslatef (0, 1.0 , 0.0);
    glScalef (3 , 6.0 , 1.0);
    glutWireCube(1.0);
    glPopMatrix() ;

     // draw head
	glPushMatrix();
    glTranslatef (0, 5.7 , 0.0);
    glutWireSphere(0.7,60,60);
    glPopMatrix() ;

    glPushMatrix();
    draw_left_arm();
    glPopMatrix() ;

    glPushMatrix();
    draw_right_arm();
    glPopMatrix();

    glPushMatrix();
    draw_right_leg();
    glPopMatrix();

    glPushMatrix();
    draw_left_leg();
    glPopMatrix();





   glPopMatrix();
   glutSwapBuffers();
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
    case 'N':
        moveForward();
        glutPostRedisplay();
       break;
    case 'B':
		moveBack();
		glutPostRedisplay();
		break;
       // to move sholder up & down
    case 's':
       if (shoulder_1<= 30)
       {
           shoulder_1 = (shoulder_1 + 5) % 360;
           glutPostRedisplay();
       }

      break;

   case 'S':
       if (shoulder_1>-90)
       {
           shoulder_1 = (shoulder_1 - 5) % 360;
           glutPostRedisplay();
       }

      break;
   case 'a':
	    if (shoulder_2<180)
		{
		    shoulder_2 = (shoulder_2 + 5) % 360;
        }
		glutPostRedisplay();
		break;
    case 'A':
	    if (shoulder_2>0)
		{shoulder_2 = (shoulder_2 - 5) % 360;}
		glutPostRedisplay();
		break;
   case 'e':
       if(elbow <=150)
       {
           elbow = (elbow + 5) % 360;
           glutPostRedisplay();
       }

      break;
   case 'E':
       if (elbow>0)
       {
           elbow = (elbow - 5) % 360;
           glutPostRedisplay();
       }

      break;
   case 'x':
	    if (r_hip<50)
		{r_hip = (r_hip + 5) % 360;}
		glutPostRedisplay();
		break;
	case 'X':
	    if (r_hip>-90)
		{r_hip = (r_hip - 5) % 360;}
		glutPostRedisplay();
		break;
	case 'c':
	    if(r_knee<180)
		{r_knee = (r_knee + 5) % 360;}
		glutPostRedisplay();
		break;
	case 'C':
        if(r_knee>0)
		{r_knee = (r_knee - 5) % 360;}
		glutPostRedisplay();
		break;
	case 'z':
	    if(r_hip2<90)
		{
		    r_hip2 = (r_hip2 + 5) % 360;
		    glutPostRedisplay();
        }

		break;
	case 'Z':
	    if(r_hip2>-5.0)
		{
		    r_hip2 = (r_hip2 - 5) % 360;
		    glutPostRedisplay();
		 }
		break;
	case 'r':
        if (l_hip<50)
		{
		    l_hip = (l_hip + 5) % 360;
            glutPostRedisplay();
		}
		break;
	case 'R':
        if (l_hip>-90)
		{l_hip = (l_hip - 5) % 360;}
		glutPostRedisplay();
		break;
	case 't':
        if(l_knee<180)
		{l_knee = (l_knee + 5) % 360;}
		glutPostRedisplay();
		break;
	case 'T':
        if(l_knee>0)
		{l_knee = (l_knee - 5) % 360;}
		glutPostRedisplay();
		break;
	case 'y':
        if(l_hip2<90)
		{l_hip2 = (l_hip2 + 5) % 360;}
		glutPostRedisplay();
		break;
	case 'Y':
        if(l_hip2>-5.0)
		{l_hip2 = (l_hip2 - 5) % 360;}
		glutPostRedisplay();
		break;

   case 'f':
       if (fingerBase>-90)
       {
            fingerBase = (fingerBase - 5) % 360;
            glutPostRedisplay();
       }

      break;
   case 'F':
       if (fingerBase<0)
        {
            fingerBase = (fingerBase + 5) % 360;
            glutPostRedisplay();
       }

      break;
      case 'g':
            if (fingerUp>-180)
                {
                    fingerUp = (fingerUp - 5) % 360;
                    glutPostRedisplay();

                }

      break;
   case 'G':
        if (fingerUp<0)
            {
                fingerUp = (fingerUp + 5) % 360;
                glutPostRedisplay();

            }
      break;

   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

static void mouse(int button, int state, int x ,int y )
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      moving = 1;
      startx = x;
      starty = y ;
    }
    if (state == GLUT_UP) {
      moving = 0;
    }
  }
}


static void motion(int x, int y)
{
  if (moving) {
    angle = (angle +(x - startx))/25.0;
    rotatePoint(up,angle,eye);
   // angle2 = (angle2 +(y - startx))/25.0;
    startx = x;
   // starty = y ;
    //glutPostRedisplay();
    glutPostRedisplay();
  }
}



int main(int argc, char **argv)
{
   glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
   glutCreateWindow("body");
   init();
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutDisplayFunc(display);
   glutSpecialFunc(specialKeys);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
