#include "object.hpp"

Object::Object()
{
	//set values for default constructor
	setType("Object");
	setColor(Scalar(0,0,0));

}

Object::Object(string name){

	setType(name);

	if(name=="blue"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		/*setHSVmin(Scalar(85,120,20)); //(95,120,30)
		setHSVmax(Scalar(124,256,256));

		//BGR value for blue:
		setColor(Scalar(255,0,0));*/

		/*
		//using YCrCb
		setHSVmin(Scalar(20,100,125)); //(95,120,30)
		setHSVmax(Scalar(120,125,170));

		//BGR value for blue:
		setColor(Scalar(255,0,0));
		*/
		//Agora é verde!!!!!

		//using YCrCb
		setHSVmin(Scalar(33,100,125)); //(95,120,30)
		setHSVmax(Scalar(100,120,150));

		//BGR value for blue:
		setColor(Scalar(0,255,0));


		/*
		setHSVmin(Scalar(34,120,55)); // tava50
		setHSVmax(Scalar(90,256,256));

		//BGR value for green:
		setColor(Scalar(0,255,0));
		*/
		tipo = 2;
	}
	if(name=="green"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(34,50,50));
		setHSVmax(Scalar(80,220,200));

		//BGR value for Yellow:
		setColor(Scalar(0,255,0));

		tipo = 4;

	}
	if(name=="yellow"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		/*
		setHSVmin(Scalar(20,120,123));
		setHSVmax(Scalar(30,256,256));*/

		//using YCrCb
		//setHSVmin(Scalar(100,140,0));
		//setHSVmax(Scalar(165,170,95));

		//using Lab
		setHSVmin(Scalar(100,110,160));
		setHSVmax(Scalar(250,145,220));

		//BGR value for Red:
		setColor(Scalar(0,255,255));

		tipo = 1;

	}
	if(name=="red"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		/*
		setHSVmin(Scalar(140,120,0));
		setHSVmax(Scalar(255,255,255));
		*/
		//using YCrCb
		//setHSVmin(Scalar(20,145,100));
		//setHSVmax(Scalar(100,170,120));

		//using Lab
		setHSVmin(Scalar(40,140,140));
		setHSVmax(Scalar(115,175,160));

		//BGR value for Red:
		setColor(Scalar(0,0,255));

		tipo = 0;

	}
	if(name =="black"){

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(0,0,0));
		setHSVmax(Scalar(255,255,50));//(179,50,100));

		//BGR value for Red:
		setColor(Scalar(0,0,0));

		tipo = 5;

	}
}

Object::~Object(void)
{
}

int Object::getXPos(){

	return Object::xPos;

}

void Object::setXPos(int x){

	Object::xPos = x;

}

int Object::getYPos(){

	return Object::yPos;

}

void Object::setYPos(int y){

	Object::yPos = y;

}

Scalar Object::getHSVmin(){

	return Object::HSVmin;

}
Scalar Object::getHSVmax(){

	return Object::HSVmax;
}

void Object::setHSVmin(Scalar min){

	Object::HSVmin = min;
}


void Object::setHSVmax(Scalar max){

	Object::HSVmax = max;
}

Scalar Object::getLABmin(){

	return Object::LABmin;

}
Scalar Object::getLABmax(){

	return Object::LABmax;
}

void Object::setLABmin(Scalar min){

	Object::LABmin = min;
}


void Object::setLABmax(Scalar max){

	Object::LABmax = max;
}


Object& Object::operator= (Object o){

	this->xPos = o.getXPos();
	this ->yPos = o.getYPos();
	this->type = o.getType();
	this->HSVmin = o.getHSVmin();
	this->HSVmax = o.getHSVmax();
	this->Color = o.getColor();
	this->tipo = o.getTipo();
}
