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
#include "modulo1tunado.hpp"
#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "irparedepelaparedeprocurandodisco.hpp"
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
#define  RE 30
#define MAQ_A_X 154
#define MAQ_A_Y -97
#define MAQ_A_THETA 0
#define MAQ_B_X 154
#define MAQ_B_Y -284
#define MAQ_B_THETA 0
#define MAQ_C_X 276
#define MAQ_C_Y -326
#define MAQ_C_THETA -90
#define DIST_SAFETY 80
#define DEPOSITOS 120
#define AREA_12 330
#define AREA_34 200
#define AREA_56 69
#define TESTES 203

//DEFINES ENTREGAR
#define CONTALINHASEENTREGA -55
#define VOLTAINICIO -30
#define ENTREGADISCO1 -56
#define ENTREGADISCO2 -57
#define ENTREGA1 -58
#define ENTREGA2 -59
#define FIMENTREGA1 -60
#define FIMENTREGA2 -61

//*****************************************************************************************************************
// Modulo1Tunado
//*****************************************************************************************************************


Modulo1Tunado  *Modulo1Tunado::instance()
{
    static Modulo1Tunado  Modulo1TunadoStateInstance;
    return &Modulo1TunadoStateInstance;
}

Modulo1Tunado::Modulo1Tunado() {}

Modulo1Tunado::~Modulo1Tunado() {}

void Modulo1Tunado::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Modulo1Tunado...\n";
}

void Modulo1Tunado::execute(Robotino *robotino)
{

    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;
    static int maqx_at = MAQ_A_X;
    static int maqy_at = MAQ_A_Y;
    static int maqth_at = MAQ_A_THETA;
    static int voltaPercorrer = 0;
    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;
    if(objetivo_completo == 0){
      //  robotino->setThetaR(-90);
       robotino->definirParedeAlvo(Robotino::OESTE180);//OESTE180);
       robotino->setDistTrasParede(10);
      robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo++;
    }
    //A>>B>>C;
    else if(objetivo_completo == 1){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistTrasParede(15);
        robotino->setDistParede(15);
        robotino->change_state(IrParedePelaParede::instance());
            objetivo_completo++;
    }
    else if(objetivo_completo == 2){
        robotino->definirDestino(maqx_at - DIST_SAFETY, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 3){
        robotino->setThetaR(179);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 4){
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 5){
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 6){
        robotino->definirObjetoAlvo(Robotino::AMARELO);
        robotino->change_state(IdentificarCor::instance());
         if(maqx_at == MAQ_A_X){
            robotino->lightLed(Robotino::LED_AMARELO, 1);
        }
        else if(maqx_at == MAQ_B_X){
            robotino->lightLed(Robotino::LED_VERMELHO, 1);
        }
        else if(maqx_at == MAQ_C_X){
            robotino->lightLed(Robotino::LED_AZUL, 1);
        }
        //if(robotino->objetosAzuis.size() || robotino->objetosAmarelos.size() | robotino->objetosVermelhos.size()){
            objetivo_completo++;
           // std::
        //}
        //objetivo_completo = 4;

    }
    else if(objetivo_completo == 7){
        if(maqx_at == MAQ_A_X){
            robotino->definirObjetoAlvo(Robotino::AMARELO);
        }
        else if(maqx_at == MAQ_B_X){
            robotino->definirObjetoAlvo(Robotino::VERMELHO);
        }
        else if(maqx_at == MAQ_C_X){
            robotino->definirObjetoAlvo(Robotino::AZUL);
        }
        robotino->change_state(SeguirCor::instance());
        //objetivo_completo = TESTES;
        objetivo_completo++;
    }
    else if(objetivo_completo == 8){
        robotino->setThetaR(179);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 9){
        robotino->definirDestino(robotino->odometryX()/10 - 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 10){
        robotino->definirDestino(DEPOSITOS, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 11){
        if(maqx_at == MAQ_A_X){
            robotino->lightLed(Robotino::LED_AMARELO, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_12);
        }
        else if(maqx_at == MAQ_B_X){
            robotino->lightLed(Robotino::LED_VERMELHO, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_34);
        }
        else if(maqx_at == MAQ_C_X){
            robotino->lightLed(Robotino::LED_AZUL, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_56);
        }
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 12){
    robotino->change_state(AjustarNasLinhas::instance());
    //voltaPercorrer = ++objetivo_completo;
    //objetivo_completo = CONTALINHASEENTREGA;
    objetivo_completo++;
    }
    else if (objetivo_completo == 13){
   // robotino->
    robotino->change_state(ContarLinhas::instance());
    objetivo_completo++ ;
    }
    else if(objetivo_completo == 14){
    robotino->definirDestino(robotino->odometryX()/10 - 15, robotino->odometryY()/10);
    robotino->change_state(IrParaPonto::instance());
        objetivo_completo ++;
    }
    else if(objetivo_completo == 15){
        if(discos_entregues%2==0){
            robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 - 20);
        }
        else {
            robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 + 20);
        }
        discos_entregues++;
    robotino->change_state(IrParaPonto::instance());
    objetivo_completo++;
    }
     else if(objetivo_completo == 16){
    robotino->offLeds();
    robotino->definirDestino(robotino->odometryX()/10 + 50, robotino->odometryY()/10);
    robotino->change_state(IrParaPonto::instance());
    objetivo_completo++;
    }
    else if(objetivo_completo == 17){
       robotino->definirParedeAlvo(Robotino::OESTE180);
      robotino->change_state(IrParaParede::instance());

      if(discos_entregues == 2){
        maqx_at = MAQ_B_X;
        maqy_at = MAQ_B_Y;
        maqth_at = MAQ_B_THETA;
        objetivo_completo = 0;
      }
  /*    else if(discos_entregues == 4){
        maqx_at = MAQ_C_X;
        maqy_at = MAQ_C_Y;
        maqth_at = MAQ_C_THETA;
        objetivo_completo = 0;
      }*/
        else objetivo_completo = 99;

    }
    else if(objetivo_completo == 99){
         robotino->definirParedeAlvo(Robotino::NORTEN90);
         robotino->setDistTrasParede(10);
         robotino->change_state(IrParedePelaParede::instance());
         objetivo_completo++;

    }
    else if(objetivo_completo == TESTES){
         if(maqx_at == MAQ_A_X){
            robotino->lightLed(Robotino::LED_AMARELO, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_12);
        }
        else if(maqx_at == MAQ_B_X){
            robotino->lightLed(Robotino::LED_VERMELHO, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_34);
        }
        else if(maqx_at == MAQ_C_X){
            robotino->lightLed(Robotino::LED_AZUL, 1);
            robotino->definirDestino(robotino->odometryX(), AREA_56);
        }
    }


    else if(objetivo_completo == CONTALINHASEENTREGA)
    {
        if(voltaPercorrer == 0)
        {
            std::cout << "SETA O ESTADO INTERIOR PORRAAAAAAAAA CABEÇA DE CARAMELHO TORTAO PRA ESQUERDA\n\n\n\n\n\n\n\n\n";
            usleep(100000000);
        }
        robotino->change_state(ContarLinhas::instance());
        Object aux;
        if(discos_entregues == 0)
        {
            aux = robotino->area1disco1;
        }
        else if(discos_entregues == 1)
        {
            aux = robotino->area1disco2;
        }
        else if(discos_entregues == 2)
        {
            aux = robotino->area2disco1;
        }
        else if(discos_entregues == 3)
        {
            aux = robotino->area2disco2;
        }
        else if(discos_entregues == 4)
        {
            aux = robotino->area3disco1;
        }
        else if(discos_entregues == 5)
        {
            aux = robotino->area3disco2;
        }
        else if(discos_entregues == 6)
        {
            objetivo_completo == VOLTAINICIO;
        }

        if((robotino->objetoAlvo.getType() == aux.getType())&&(discos_entregues%2 == 0))
            objetivo_completo = ENTREGADISCO1;
        else if(robotino->objetoAlvo.getType() == aux.getType())//JA TEM 1 DISCO
        {
            objetivo_completo = ENTREGADISCO2;
        }
        usleep(2000000);
    }

    else if(objetivo_completo = ENTREGADISCO1)
    {
        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10 + 20);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = ENTREGA1;
        usleep(2000000);
    }

    else if(objetivo_completo == ENTREGADISCO2)
    {
        robotino->definirDestino((robotino->odometryX())/10, robotino->odometryY()/10 - 20);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = ENTREGA2;
        usleep(2000000);
    }

    else if(objetivo_completo == ENTREGA1)
    {
        robotino->definirDestino((robotino->odometryX())/10 - 30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = FIMENTREGA1;
        usleep(2000000);
    }

    else if(objetivo_completo == ENTREGA2)
    {
        robotino->definirDestino((robotino->odometryX())/10 - 30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = FIMENTREGA2;
        usleep(2000000);
    }

    else if(objetivo_completo == FIMENTREGA1)
    {
        robotino->definirDestino((robotino->odometryX())/10+30, robotino->odometryY()/10-20);
        robotino->change_state(IrParaPonto::instance());
        discos_entregues++;
        objetivo_completo = voltaPercorrer;
        usleep(2000000);
    }

    else if(objetivo_completo == FIMENTREGA2)
    {
        robotino->definirDestino((robotino->odometryX())/10+30, robotino->odometryY()/10+20);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = voltaPercorrer;
        discos_entregues++;
        usleep(2000000);
    }
    else if(objetivo_completo == 444){
        robotino->definirDestino((robotino->odometryX())/10,  -40);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 445){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 446){
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 2;
    }



    // else if(objetivo_completo == 2){
    //     robotino->change_state(SeguirCor::instance());
    //     objetivo_completo++;
    // }
    //else if(objetivo_completo == 3){
      //  robotino->change_state()
    //}*/
    else {
        std::cout << "TERMINEI!" << std::endl;
        while(true);
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Modulo1Tunado::exit(Robotino *robotino) {}
