#include "pededisco.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

#define PI 3.14159265
#define FATOR_VELOCIDADE  3
#define limiarAfastamento 15
#define limiarIdeal 9
#define Kpir 10

//*****************************************************************************************************************
// PedeDisco
//*****************************************************************************************************************

PedeDisco  *PedeDisco::instance()
{
    static PedeDisco  PedeDiscoStateInstance;
    return &PedeDiscoStateInstance;
}

PedeDisco::PedeDisco() {}

PedeDisco::~PedeDisco() {}

void PedeDisco::enter(Robotino *robotino)
{
    std::cout << "Pedindo disco...\n";
}

void PedeDisco::execute(Robotino *robotino)
{
    //static State<Robotino> *voltar;
       //Armazenando o estado da maquina de estados, para poder chamar um estado aqui dentro e depois voltar a maquina de estados
    robotino->amarelo = false;
    robotino->azul = false;
    robotino->vermelho = false;
    if( (robotino->objetosAmarelos.size()!= 0) || (robotino->objetosAzuis.size()!= 0) || (robotino->objetosVermelhos.size()!= 0)){
        if( (robotino->objetosAmarelos.size()!= 0) && ( (robotino->objetosAzuis.size()== 0) && (robotino->objetosVermelhos.size()== 0) ) ){
            robotino->offLeds();
            robotino->lightLed(Robotino::LED_AMARELO, 1);
            robotino->definirObjetoAlvo(Robotino::AMARELO);
           robotino->amarelo = true;
            robotino->azul = false;
            robotino->vermelho = false;
        }
        else if( (robotino->objetosAzuis.size()!= 0) && ( (robotino->objetosAmarelos.size()== 0) && (robotino->objetosVermelhos.size()== 0) ) ){
            robotino->offLeds();
            robotino->lightLed(Robotino::LED_AZUL, 1);
            robotino->definirObjetoAlvo(Robotino::AZUL);
            robotino->amarelo = false;
            robotino->azul = true;
            robotino->vermelho = false;
        }
        else if( (robotino->objetosVermelhos.size()!= 0) && ( (robotino->objetosAzuis.size()== 0) && (robotino->objetosAmarelos.size()== 0) ) ){
            robotino->offLeds();
            robotino->lightLed(Robotino::LED_VERMELHO, 1);
            robotino->definirObjetoAlvo(Robotino::VERMELHO);
            robotino->amarelo = false;
            robotino->azul = false;
            robotino->vermelho = true;
        }
    }
    robotino->change_state(robotino->previous_state());

}

void PedeDisco::exit(Robotino *robotino) {
    std::cout << "Disco identificado...\n";
}
