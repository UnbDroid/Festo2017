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
#include "testeVisao.hpp"

#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "irparedepelaparedeprocurandodisco.hpp"

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

#include "irdistpelaparede.hpp"

#include "linhassensor.hpp"


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

//*****************************************************************************************************************
// teste003Locomocao
//*****************************************************************************************************************


testeVisao  *testeVisao::instance()
{
    static testeVisao  testeVisaoStateInstance;
    return &testeVisaoStateInstance;
}

testeVisao::testeVisao() {}

testeVisao::~testeVisao() {}


void testeVisao::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado testeVisao...\n";
}

void testeVisao::execute(Robotino *robotino)
{
    static int objetivo_completo = 9786;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;

    static int num_buscas = 0;

    static int angulo = 0;


    static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
    static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------
//ANDA NAS 4 paredes da arena seguindo parede no sentido horário
    //usleep(2000000);
    if(objetivo_completo == 9786)
    {
        robotino->change_state(LinhasSensor::instance());

    }
    else if(objetivo_completo == 11)
    {
        cout<<"me ajuda"<<endl;
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 9;
    }
    else if(objetivo_completo == 9)
    {

       // usleep(2000000);
        robotino->setThetaR(angulo);
        robotino->change_state(Girar::instance());
        angulo+=90;
        if(angulo == 180)
            angulo = 179;
        if(angulo > 180)
            angulo = -90;
        objetivo_completo = 900;
    }
    else if(objetivo_completo == 10)
    {
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(10);
        robotino->setaDistParede(1400);
        robotino->change_state(IrDistPelaParede2::instance());
        objetivo_completo = 987;
    }
    else if(objetivo_completo == 987)
    {
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(10);
        robotino->setaDistParede(1300);
        robotino->change_state(IrDistPelaParede2::instance());
        objetivo_completo = 87;
    }
    else if(objetivo_completo == -2)
    {
        objetivo_completo = -1;
    }
    else if (objetivo_completo == 98)
    {
        num_buscas++;
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 98;
    }
    else if(objetivo_completo == 1)
    {
        if(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0)
        {
            objetivo_completo = -1;
        }
        else
        {
            objetivo_completo = 2;
        }
    }
    else if(objetivo_completo == 2)
    {
        robotino->pegou_disco = false;
        robotino->definirObjetoAlvo(Robotino::TODAS);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 3;
    }
    else if(objetivo_completo == 3)
    {
        if(!robotino->pegou_disco)
        {
            objetivo_completo = -1;
            cout<<"Falhei buabuabua"<<endl;
        }
        else
        {
            cout<<"i win hahahahha"<<endl;
            objetivo_completo = 1012;
        }

    }
    else if(objetivo_completo == 1012)
    {
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 1013;
    }
    else if(objetivo_completo == 1013)
    {
        robotino->definirDestino(robotino->odometryX()/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 1014;
    }
    else if(objetivo_completo == 1014)
    {
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 1015;
    }
    else if(objetivo_completo == 1015)
    {

        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());

        objetivo_completo = 1016;
    }
    else if(objetivo_completo == 1016)
    {
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 1017;
    }
    else if(objetivo_completo == 1017)
    {
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 87;
    }
    else if(objetivo_completo == 87){
        cout<<"CHEGUEI AQUI"<<endl;
    }
    else if(objetivo_completo == 87){}
    else if(objetivo_completo == 87){}
    else if(objetivo_completo == 87){}

    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void testeVisao::exit(Robotino *robotino) {}
