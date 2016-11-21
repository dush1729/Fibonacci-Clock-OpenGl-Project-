#include<GL/glut.h> //for graphics
#include<iostream> //for cin/cout
#include<vector> //for vectors
#include<ctime> //for time
#include<cstdlib> //for rand()
using namespace std;

// all 5 square co-ordinates
float sc[5][4] = { -0.5f, 0.2f, -0.25f, 0.6f,
-0.5f, 0.6f, -0.25f, 1.0f,
-1.0f, 0.2f, -0.5f, 1.0f,
-1.0f, -1.0f, -0.25f, 0.2f,
-0.25f, -1.0f, 1.0f, 1.0f };

// All 5 fibonacci numbers
int fib[5] = { 1, 1, 2, 3, 5 }, i, j, hours, minutes;
// All possible value from fibonacci numbers stored in this vector(values)
vector <vector<int>> values[13];
// Tells which value to choose for hour and minute
vector <int> h, m;
// Marks values to be taken
bool hp[5], mp[5];

//prints rectangle
void rect(float x1, float y1, float x2, float y2)
{
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

// Finds color according to state of block(hour,minute)
void color(bool h, bool m)
{
	if (h && m) glColor3f(0.0f, 0.0f, 1.0f); //Blue
	else if (h) glColor3f(1.0f, 0.0f, 0.0f); //Red
	else if (m) glColor3f(0.0f, 1.0f, 0.0f); //Green
	else glColor3f(1.0f, 1.0f, 1.0f); //White
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	// Takes hours and minutes from local time
	time_t t = time(NULL);
	struct tm *tmp = localtime(&t);
	hours = tmp->tm_hour;
	minutes = tmp->tm_min / 5;
	if (hours > 12) hours -= 12;
	cout << hours << ":" << minutes * 5 << endl;

	//Randomly takes possible indexes for hour and minutes and marks them
	srand(time(NULL));
	h = values[hours][rand() % values[hours].size()];
	m = values[minutes][rand() % values[minutes].size()];
	//Marks them
	for (i = 0; i < 5; i++) hp[i] = mp[i] = false;
	for (auto i : h) hp[i] = true;
	for (auto i : m) mp[i] = true;


	color(hp[0], mp[0]);
	rect(sc[0][0], sc[0][1], sc[0][2], sc[0][3]);

	color(hp[1], mp[1]);
	rect(sc[1][0], sc[1][1], sc[1][2], sc[1][3]);

	color(hp[2], mp[2]);
	rect(sc[2][0], sc[2][1], sc[2][2], sc[2][3]);

	color(hp[3], mp[3]);
	rect(sc[3][0], sc[3][1], sc[3][2], sc[3][3]);

	color(hp[4], mp[4]);
	rect(sc[4][0], sc[4][1], sc[4][2], sc[4][3]);


	//LINES
	glLineWidth(2.5);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex3f(sc[2][0], sc[2][1], 0.0);
	glVertex3f(sc[3][2], sc[3][3], 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(sc[4][0], sc[4][1], 0.0);
	glVertex3f(sc[4][0], sc[1][3], 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(sc[0][0], sc[0][1], 0.0);
	glVertex3f(sc[2][2], sc[2][3], 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(sc[1][0], sc[1][1], 0.0);
	glVertex3f(sc[0][2], sc[0][3], 0.0);
	glEnd();

	//Border Lines
	glLineWidth(5.5);

	glBegin(GL_LINES);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0);
	glEnd();

	glFlush();  // Render now
	Sleep(2000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{

	//Generates all subsets of 5 fibonacci numbers using bitmasking technique
	for (i = 0; i < (1 << 5); i++)
	{
		int sum = 0;
		vector <int> temp;
		for (j = 0; j < 5; j++)
		{
			if (i&(1 << j))
			{
				sum += fib[j];
				temp.push_back(j); //pushes indexes
			}
		}
		values[sum].push_back(temp);
	}


	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowPosition(60, 0); // Position the window's initial top-left corner
	glutInitWindowSize(960, 640);   // Set the window's initial width & height
	glutCreateWindow("Fibonacci Clock"); // Create a window with the given title


	// Prints current time
	glutDisplayFunc(display); // Register display callback handler for window re-paint

	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
