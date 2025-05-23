#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Object
{
public:
	Object();
	~Object(void);

	Object(string name);

	int getXPos();
	void setXPos(int x);

	int getYPos();
	void setYPos(int y);

	Scalar getHSVmin();
	Scalar getHSVmax();

	Scalar getLABmin();
	Scalar getLABmax();

	void setHSVmin(Scalar min);
	void setHSVmax(Scalar max);

	string getType(){return type;}
	void setType(string t){type = t;}

	void setLABmin(Scalar min);
	void setLABmax(Scalar max);

	Scalar getColor(){
		return Color;
	}
	void setColor(Scalar c){

		Color = c;
	}

	Object& operator=(Object);

	int getTipo(){return tipo;}

private:

	int xPos, yPos, tipo;
	string type;
	Scalar HSVmin, HSVmax;
	Scalar Color;
	Scalar LABmax, LABmin;
};

#endif //OBJECTS_HPP