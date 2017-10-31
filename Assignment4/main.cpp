/************************************************************************
Program:		Assignment 4 (Checkpoint)
Author:			Joey Brown
Class:			CSC372 Analysis of Algorithms
Instructor:		Dr. Rebenitsch
Date:			November 2, 2017
Description:	This program is for the assignment 4 checkpoint. So far 
					it only needs to accept a polygon from a file via 
					command line (Polygon_area.exe file_name). Then the 
					program only needs to output the contents as follows:
					0		0
					1.0 	0
					1.0 	1.0
					0		1.0
					Area: 1.0
*************************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
using namespace std;

/************************************************************************
   Name:			Point
   Author:			Joey Brown
   Description:		Structure to holds (x,y) coordinats of a single point.
 ************************************************************************/
struct Point
{
	float _x;
	float _y;
	
	void setCoords(float x, float y) { _x = x; _y = y; }
	void setCoords(vector<float> p) { _x = p.at(0); _y = p.at(1); }
	
	float getX() { return _x; }
	float getY() { return _y; }

	vector<float> getCoords() { vector<float> c; c.push_back(_x); 
		c.push_back(_y); return c; }
};

/************************************************************************
   Function:		openFileIn()
   Author:			Joey Brown
   Description:		Safely open a file, return true is file is opened, 
   						false otherwise
   Parameters:
 ************************************************************************/
bool openFileIn(fstream &file, string name)
{
	file.open(name.c_str(), ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

/************************************************************************
   Function:		getNums()
   Author:			Joey Brown
   Description:		Extracts a vector of floats from a string and returns 
   						the list as a vector of floats. 
   Parameters:		String of numbers to extract.
 ************************************************************************/
vector<float> getNums(string str)
{
	// Find space separating integers
	vector<float> nums;
	stringstream ss;
	ss << str;
	string temp;
	float found;
	if(str.size() > 0)
	{
		while(!ss.eof())
		{
			// extract characters from string
			ss >> temp;
			// check if int
			if(stringstream(temp) >> found)
			{
				nums.push_back(found);
			}
			temp = "";
		}
	}
	return nums;
}

/************************************************************************
   Function:		area()
   Author:			Joey Brown
   Description:		Calculates the area from a set of points.
   Parameters:		vector of Points
   Source:			
   		https://www.mathopenref.com/coordpolygonarea.html
 ************************************************************************/
float getArea(vector<Point> coords)
{
	float a = 0;
	// TODO: 
	// 	- create vector<Point> coordinates in displayFile()
	//	- use the coordinates vector to calculate the area
	float sum = 0;
	for (int i = 0; i < coords.size(); ++i)
	{
		float x1;
		float y1;
		
		float x2;
		float y2;

		// Wrap around to first coordinate when end is reached
		if(i+1 == coords.size())
		{
			x1 = coords.at(i).getX();
			y1 = coords.at(i).getY();

			x2 = coords.at(0).getX();
			y2 = coords.at(0).getY();
		}
		else
		{
			x1 = coords.at(i).getX();
			y1 = coords.at(i).getY();

			x2 = coords.at(i+1).getX();
			y2 = coords.at(i+1).getY();
		}
		sum += ((x1*y2)-(y1*x2));
	}
	a = abs(sum/2);
	return a;
}

/************************************************************************
   Function:		displayFile()
   Author:			Joey Brown
   Description:		Displays the contents of a file from a file object.
   Parameters:		Files object to open and display.
 ************************************************************************/
void displayFile(const char* infile)
{
	fstream file;
	vector<Point> coordinates;

	// Check if file was opened safely
	if(openFileIn(file, infile))
	{
		string s(infile);
		string f = "\033[1;32m" + s + "\033[0m";
		cout << "\n[" << f << " opened successfully.]\n";
		string line;		// Stores text read from txt file
		vector<float> nums;	// Stores ints read from txt file
		Point p;
		vector<Point> coords;
		float area = 0.0;

		cout << "\nContents: \n";
		cout <<   "------------------------\n";
		
		// Colored text ( [1] - Colored Text )
		// string x = "\033[1;4;32mX\033[0m";
		// string y = "\033[1;4;32mY\033[0m";
		// cout << setw(4) << right << " " << x << setw(4) << right << " " << y;
		
		// Loop through file
		while(!file.eof())
		{
			// Read line and convert to float
			getline(file, line, '\n');

			// Quit processing if reading the end of file
			if(file.eof())
				break;
			else
			{	
				// Print coordinates
				nums = getNums(line);
				p.setCoords(nums);
				coords.push_back(p);
				cout << setprecision(1);
				cout << setw(8) << left << fixed << nums.at(0) 
						<< fixed << nums.at(1) << endl;
			}
		}
		// Print area
		area = getArea(coords);
		cout << "Area: " << fixed << area << endl;
		cout <<   "------------------------\n";

		file.close();
	}
	else 
		cout << "File open error" << endl;
	cout << "File closed\n";
}


/************************************************************************
   Function:		main()
   Author:			Joey Brown
   Description:		main fucntion where everything is executed
   Parameters:		Number of command line arguments and arguments in a 
   						char array.
************************************************************************/
int main(int argc, char const *argv[])
{
	// Check if file name was passed
	if (argc < 2)
	{
		cout << "Usage: Polygon_area.exe file_name\n";
		return -1;
	}

	// Print all files passed as arguments from the command line
	for (int i = 1; i < argc; ++i)
	{
		displayFile(argv[i]);
	}


	return 0;
}


/*SOURCES***************************************************************
[1] - Colored text
 https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
************************************************************************/