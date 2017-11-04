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
#include "teste001.hpp"
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
// teste001
//*****************************************************************************************************************


teste001  *teste001::instance()
{
    static teste001  teste001StateInstance;
    return &teste001StateInstance;
}

teste001::teste001() {}

teste001::~teste001() {}


void teste001::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado teste001...\n";
}

void teste001::execute(Robotino *robotino)
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
        robotino->definirParedeAlvo(Robotino::LESTE180); // vira de costas pra parede, o robo virado pro norte, anda pro leste girando pro lado horario caso nao esteja virado pro norte
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 1; //mude aki pra pular objetivos/estados
    }
    else if(objetivo_completo == 1)
    {
        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 2;
    }
    else if(objetivo_completo == 2)
    {
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 3;
    }
    else if(objetivo_completo == 3)
    {
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 0;// se objetivo_completo = 0  loop horario
    }//////////////////////////////////////////
    else if(objetivo_completo == 8000)
    {
        robotino->definirParedeAlvo(Robotino::LESTE180); // vira de costas pra parede, o robo virado pro norte, anda pro leste girando pro lado horario caso nao esteja virado pro norte
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 4;
    }
      else if(objetivo_completo == 8001)
    {
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 4;
    }
    //ANDA NAS 4 PAREDES NO SENTIDO ANTI HORARIO
    // QUALQUER UM DOS CODIGOS FUNCIONA BEM SOZINHO, MAS JUNTOS DA ERRO NO OBJETIVO_COMPLETO 5, ainda não entendi por que
    if(objetivo_completo == 4)
    {
        robotino->definirParedeAlvo(Robotino::OESTE180); // vai pra leste quando começado virado de costas para parede
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 5;
    }
    else if(objetivo_completo == 5)
    {
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 6;
    }
    else if(objetivo_completo == 6)
    {
        robotino->definirParedeAlvo(Robotino::LESTE0);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 7;
    }
    else if(objetivo_completo == 7)
    {
        robotino->definirParedeAlvo(Robotino::NORTE90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 8;
    }
    else if(objetivo_completo == 8)
    {
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 0;
    }
    else if(objetivo_completo == 9)
    {
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 0;
    }
    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void teste001::exit(Robotino *robotino) {}
