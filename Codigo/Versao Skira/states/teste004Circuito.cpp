#include "control.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "irparaponto.hpp"
#include "controleposicao.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "identificarcor.hpp"
#include "procurarcor.hpp"
#include "seguircor.hpp"
#include "irparaparede.hpp"
#include "irparalinha.hpp"
#include "modulo3testar.hpp"
#include "teste004Circuito.hpp"
#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "nobusca.hpp"
#include "navegarentreareas.hpp"
#include "navegarentreareas2.hpp"
#include "navegarentreareas3.hpp"
#include "alinhartraseiro.hpp"
#include "acharlinhas.hpp"

#include <unistd.h>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>


#define PI 3.14159265
#define R 0
#define Y 1
#define B 2
#define INDEFINIDO -1
#define VAZIO 4
#define AREA_D1 20
#define AREA_D2 21
#define AREA_D3 22
#define AREA_D4 23
#define AREA_D5 24
#define AREA_D6 25
#define AREA_INTERMEDIARIA 34
#define VOLTARINICIO 50
#define  RE 20// era 30

//*****************************************************************************************************************
// teste004Circuito
//*****************************************************************************************************************


teste004Circuito  *teste004Circuito::instance()
{
    static teste004Circuito  teste004CircuitoStateInstance;
    return &teste004CircuitoStateInstance;
}

teste004Circuito::teste004Circuito() {}

teste004Circuito::~teste004Circuito() {}


void teste004Circuito::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado teste004Circuito...\n";
}

void teste004Circuito::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;

    static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
    static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


    if(objetivo_completo == 0){
        robotino->setOdometry(30,-180,180);
        robotino->definirDestino(robotino->odometryX()/10+30,robotino->odometryY()/10);//(robotino->odometryX())/10+RE, (robotino->odometryY())/10+RE);
        robotino->change_state(IrParaPonto::instance());
        std::cout << "odometryX: " << robotino->odometryX()/10 << "\todometryY: " << robotino->odometryX()/10;
        objetivo_completo = 7;
        // std::cout << "Sensor indutivo: "<< robotino->readInductiveSensor();
        // usleep(2000000);

    }
    else if(objetivo_completo == 7){
        std::cout << "Ta CERTO";
        usleep(2000000);
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo = 8;
    }
    else if (objetivo_completo == 8){
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 9;
    }


    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }

    else
    {
        while(true);
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void teste004Circuito::exit(Robotino *robotino) {}
