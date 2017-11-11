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
#include "testeAlinhaFrente.hpp"

#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "irparedepelaparedeprocurandodisco.hpp"
#include "alinhafrenteparede.hpp"
#include  "testeAlinhaFrente.hpp"//EXCLUIR DEPOIS


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

#include <sys/time.h>


//#include "pegardisco.hpp"

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

#define XA0 30
#define YA0 -25

#define XA1 375
#define YA1 -375

#define XA2 375
#define YA2 -225

#define XA3 375
#define YA3 -174

#define XA4 375
#define YA4 -124

#define XA5 -5000
#define YA5 -5000

#define XYAErro 24

//*****************************************************************************************************************
// teste003Locomocao
//*****************************************************************************************************************


testeAlinhaFrente  *testeAlinhaFrente::instance()
{
    static testeAlinhaFrente  testeAlinhaFrenteStateInstance;
    return &testeAlinhaFrenteStateInstance;
}

testeAlinhaFrente::testeAlinhaFrente() {}

testeAlinhaFrente::~testeAlinhaFrente() {}


void testeAlinhaFrente::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado testeAlinhaFrente...\n";
}

void testeAlinhaFrente::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;
    static int areaAtual = -1;


    static int num_buscas = 0;

    static int angulo = 0;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


    if(objetivo_completo == 0)
    {
        robotino->setOdometry(XA4,YA4,180);
        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistFrenteParede(30);
        robotino->change_state(AlinhaFrenteParede::instance());
        // robotino->definirParedeAlvo(Robotino::SUL90);
        // robotino->setDistTrasParede(20);
        // robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 1;
    }
    else if(objetivo_completo == 1)
    {

    }



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void testeAlinhaFrente::exit(Robotino *robotino) {}
