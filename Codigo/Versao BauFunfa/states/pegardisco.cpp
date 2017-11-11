#include "seguircor.hpp"
#include "basestate.hpp"
#include "robotino.hpp"
#include <cmath>

#include "identificarcor.hpp"
#include "seguircor.hpp"
#include "pegardisco.hpp"

#define KpX 0.5
#define KiX 0.5*0

#define KpY 2.5
#define KiY 0.2*0

#define limiarAprox 30
#define limiarAprox2 8
#define limiarAprox3 6.1
#define limiarAproxLim 35

#define Kpir 10
#define Kpir2 20

#define dt 0.01


const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
//*****************************************************************************************************************
// SeguirCor
//*****************************************************************************************************************

PegarDisco  *PegarDisco::instance()
{
    static PegarDisco  PegarDiscoInstance;
    return &PegarDiscoInstance;
}

PegarDisco::PegarDisco() {}

PegarDisco::~PegarDisco() {}



void PegarDisco::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado SeguirCor...\n";
}

void PegarDisco::execute(Robotino *robotino)
{

    robotino->change_state(IdentificarCor::instance());
    while(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0 )
    {

    }

}

void PegarDisco::exit(Robotino *robotino) {
    std::cout << "O disco está na garra\n";

    robotino->setVelocity(0,0,0);
}
