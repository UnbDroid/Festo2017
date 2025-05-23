//  Copyright (C) 2004-2008, Robotics Equipment Corporation GmbH

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <unistd.h>

#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"

#include "robotino.hpp"
#include "control.hpp"
#include "ajusteinicial.hpp"
#include "irparaponto.hpp"
#include "mapa.hpp"
#include "coordenadas.hpp"
#include "identificarcor.hpp"
#include "procurarcor.hpp"
#include "basestate.hpp"
#include "irparaparede.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace rec::robotino::com;


int main( int argc, char **argv )
{
	try{
		std::string hostname = "172.26.201.1";
		if( argc > 1 )
		{
			hostname = argv[1];
		}
		//Banana
		Robotino robo(hostname.c_str(), Control::instance());

		std::cerr << "Faz sentido?\n";

		while(true){
			try{
				//std::cerr << "Nao\n";
				robo.update();
			}catch(const char * erro){
				std::cerr << erro << std::endl;
				throw erro;
			}
		}
	}catch(const char * erro){
		std::cerr << erro << std::endl;
	}
	//std::cout << "Press any key to exit..." << std::endl;
	//rec::core_lt::waitForKey();
}
