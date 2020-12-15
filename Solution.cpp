#include <iostream>
#include <ctime>
using namespace std;

const float pi = 3.1415;
const int iteration = 3000;
const float acceleration1 = 2.05; // The number of turns to his own conclusion
const float acceleration2 = 2.05; // The coefficient of orientation towards the best neighbor.
const float velocitymax = 3.0; 
const float velocitymin = 0.1;
const int n = 20; // We Have 20 Birds.

float g(float x1, float x2)
{
	float y = 50 + pow(x1, 2) + pow(x2, 2) - (20 * (cos(2 * pi * x1) + cos(2 * pi * x2)));
	return y;
}

float * pso(int max_it, float ac1, float ac2, float vmax, float vmin)
{
	float p1 = FLT_MAX, p2 = FLT_MAX;
	float x1[n + 1];
	float x2[n + 1];
	for (int i = 1; i <= n; i++) // We swung 20 birds to different points on the function between 5 and -5 to search for the x1 point.
	{
		x1[i] = (rand() % 10) - 5;
		srand((unsigned)time(NULL));
	}
	for (int i = 1; i <= n; i++) // We swung 20 birds to different points between 5 and -5 on the function to search for x2.
	{
		x2[i] = (rand() % 10) - 5;
		srand((unsigned)time(NULL));
	}
	float deltax = ((float)rand() +(vmax-vmin)); // Generating random numbers between 3.00 and 0.1.
	int t = 1;
	static float global[3];
	while (t <= max_it) // Repeat 3000 times.
	{
		for (int i = 1; i <= n; i++)
		{
			if (g(x1[i], x2[i]) < g(p1, p2)) // Check old and self-found results for x1 and x2.
			{
				p1 = x1[i];
				p2 = x2[i];
			}
			global[0] = p1; 
			global[1] = p2;
			global[2] = g(p1, p2);
			for (int j = 1; j <= n; j++) // Compare your friends' results with yours.
			{
				if (j != i)
				{
					if (g(x1[j], x2[j]) < g(p1, p2)) // Found best solution.
					{
						global[0] = x1[j];
						global[1] = x2[j];
						global[2] = g(x1[j], x2[j]);
					}
				}
				else continue;
			}
			float fi1 = 0 * ((float)rand() / (float)RAND_MAX) + ac1; // A random value between 0 and the coefficient of direction, that is, how much it will go.
			float fi2 = 0 * ((float)rand() / (float)RAND_MAX) + ac2;
			deltax = deltax + fi1*((p1 - x1[i])*(p2 - x2[i])) + fi2*((global[0] - x1[i])*(global[1] - x2[i])); // Improvement formula // How far to go in the next step.
			if (deltax < vmin) 
				deltax = vmin;
			else if (deltax > vmax)
				deltax = vmax;
			if ((x1[i] + deltax) <= 5 && x1[i] + deltax >= -5 && (x2[i] + deltax) <= 5 && x2[i] + deltax >= -5)
			{
				x1[i + 1] = x1[i] + deltax;
				x2[i + 1] = x2[i] + deltax;
			}
			srand((unsigned)time(NULL));
		}
		t += 1;
	}
	return global;
}

void main()
{
	float *p;
	p = pso(iteration, acceleration1, acceleration2, velocitymax, velocitymin);
	cout << "For particle swarm optimization algorithm, found values are like that:" << endl;
	cout << "Vmin=" << velocitymin << endl;
	cout << "Vmax=" << velocitymax << endl;
	cout << "x1 found: " << *(p + 0) << endl;
	cout << "x2 found: " << *(p + 1) << endl;
	cout << "y found: " << *(p + 2) << endl;
	system("Pause");
}