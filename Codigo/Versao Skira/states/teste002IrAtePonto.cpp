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
#include "teste002IrAtePonto.hpp"

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
#define  RE 10// era 30

//*****************************************************************************************************************
// teste002IrAtePonto
//*****************************************************************************************************************


teste002IrAtePonto  *teste002IrAtePonto::instance()
{
    static teste002IrAtePonto  teste002IrAtePontoStateInstance;
    return &teste002IrAtePontoStateInstance;
}

teste002IrAtePonto::teste002IrAtePonto() {}

teste002IrAtePonto::~teste002IrAtePonto() {}


void teste002IrAtePonto::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado teste002IrAtePonto...\n";
}

void teste002IrAtePonto::execute(Robotino *robotino)
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


// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------
//ANDA NAS 4 paredes da arena seguindo parede no sentido horário
    if(objetivo_completo == 0)
    {
        robotino->lightLed(7,true);
        robotino->lightLed(6,true);
        robotino->lightLed(5,true);
        usleep(1000000);
        objetivo_completo = 1; //mude aki pra pular objetivos/estados
    }
    else if (objetivo_completo == 1){
        robotino->lightLed(7,false);
        robotino->lightLed(6,false);
        robotino->lightLed(5,false);
        usleep(1000000);
        objetivo_completo = 0;
    }
    // else if(objetivo_completo == 1) /// TESTAR AGR
    // {
    //     if  (!chegueiPonto)
    //     {
    //             robotino->setOdometry(robotino->odometryX(), coordenadaAreaLouco(depositoAtual+contador-1,robotino), 180);
    //             Coordenadas destino = robotino->pegarCoordenadaArea(depositoAtual+contador);
    //             robotino->definirDestino(robotino->odometryX()/10, -(destino.get_y()));
    //             robotino->change_state(IrParaPonto::instance());
    //             chegueiPonto = true;
    //     }
    // }
    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void teste002IrAtePonto::exit(Robotino *robotino) {}
