#include "linhassensor.hpp"
#include "robotino.hpp"
#include "irparaponto.hpp"

//*****************************************************************************************************************
// LinhasSensor
//*****************************************************************************************************************

LinhasSensor  *LinhasSensor::instance()
{
    static LinhasSensor  LinhasSensorStateInstance;
    return &LinhasSensorStateInstance;
}

LinhasSensor::LinhasSensor() {}

LinhasSensor::~LinhasSensor() {}

void LinhasSensor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado LinhasSensor...\n";
}

void LinhasSensor::execute(Robotino *robotino)
{
    static bool viMetal = false;
    static bool preto = false;
    static bool tag = false;
    static bool bati = false;
    static int numeroLinhas = 0;
    static State<Robotino> * voltar;

    std::cout << viMetal<<"\n";
    std::cout << robotino->readInductiveSensor()<<"\n--------------\n";
    std::cout << "Numero Linhas: "<<numeroLinhas << std::endl;


    if (robotino->readColorSensor(Robotino::SC_DIREITO) && robotino->readColorSensor(Robotino::SC_ESQUERDO))
    {
        robotino->setVelocity(0,0,0);
        robotino->change_state(robotino->previous_state());
    }
    else if(robotino->readColorSensor(Robotino::SC_DIREITO))
    {
        robotino->setVelocity(0,-10,-50);
    }
    else if(robotino->readColorSensor(Robotino::SC_ESQUERDO))
    {
        robotino->setVelocity(0,-10,50);
    }
    else
    {
        robotino->setVelocity(40,0,0);
    }

}

void LinhasSensor::exit(Robotino *robotino) {
    robotino->setVelocity(0,0,0);
    std::cout << "Saindo do estado LinhasSensor...\n";
}
