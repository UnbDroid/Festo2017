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
#include "Modulo3_2017.hpp"
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
#include "pededisco.hpp"
#include "irdistpelaparede.hpp"
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
#define VERMELHO 0
#define AMARELO 1
#define AZUL 2
#define DEPOSITO 40







//GALERAAAAA MUDA ISSO POR FAVOR, INVENTEI QQR VALOR SO PRA PODER COMPILAR
#define MAQ_A_X 180
#define MAQ_A_Y -80
#define MAQ_A_THETA 45
#define maqA 0
#define maqB 1
#define maqC 2
#define maqD 3
#define maqE 4
#define maqF 5



#define maxAzul 3
#define maxAmarelo 3
#define maxVermelho 3






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
// Modulo3_2017
//*****************************************************************************************************************


Modulo3_2017  *Modulo3_2017::instance()
{
    static Modulo3_2017  Modulo3_2017StateInstance;
    return &Modulo3_2017StateInstance;
}

Modulo3_2017::Modulo3_2017() {}

Modulo3_2017::~Modulo3_2017() {}

void Modulo3_2017::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Modulo3_2017...\n";
}

void Modulo3_2017::execute(Robotino *robotino)
{

    static int objetivo_completo = -1;
    static int discos_entregues = 0;
    static int discos_vermelhos =0;
    static int discos_amarelos = 0;
    static int discos_azuis =0;
    static int ultimo_objetivo = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;
    static int maqx_at = MAQ_A_X;
    static int maqy_at = MAQ_A_Y;
    static int maqth_at = MAQ_A_THETA;
    static int voltaPercorrer = 0;
    static bool cima;
    static int shift = 20;
    static int times2 = 0;
    static int primeiraVez = 0;
    //static Coordenadas maquinas[6] = {new Coordenadas,-1,-1,-1,-1,-1};   //A -> 0 // B -> 1 etc
    static int deposito_atual = maqA;
    static int deposito_atualy = -175;
    static int maquina_atual = maqA;



    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;
    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;
    if(objetivo_completo == -1){
        robotino->setDistTrasParede(10);
     //   robotino->change_state(AlinharTraseiro::instance());
        robotino->setOdometry(30,-30, -90);
        objetivo_completo = 0;
    }
    else if(objetivo_completo == 0){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 1;
        //vai pra maquina atual
        //pega a cor dele e seta, caso nao maquina[x] == -1
        //pega o disco
    }
    else if(objetivo_completo == 1){
        //robotino->definirDestino(250, robotino->odometryY()/10);
        //robotino->change_state(IrParaPonto::instance());

        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->setDeslocamento(130*10);
        robotino->change_state(IrDistPelaParede::instance());
 //       robotino->definirDestino(170,robotino->odometryY()/10 );
   //     robotino->change_state(IrParaPonto::instance());
         objetivo_completo = 2;
    }
    else if(objetivo_completo == 2){
        robotino->definirDestino(robotino->odometryX()/10,robotino->odometryY()/10 - 30);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 3){
        robotino->change_state(ContarLinhas::instance());
     objetivo_completo++;
    }
    else if(objetivo_completo == 4){
        if(MAQ_A_THETA > 0){
            robotino->setThetaR(MAQ_A_THETA - 179);
            robotino->change_state(Girar::instance());
        }
        else {
            robotino->setThetaR(MAQ_A_THETA + 180);
            robotino->change_state(Girar::instance());
        }
        objetivo_completo = 1000;

    }
    else if(objetivo_completo == 1000){
        robotino->onLeds();
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 1001){
            robotino->change_state(PedeDisco::instance());
            objetivo_completo = 1002;
    }
    else if(objetivo_completo == 1002){
        if(robotino->azul || robotino->amarelo || robotino->vermelho){
            objetivo_completo = 5;
        }
        else {
            objetivo_completo = 1000;
        }
    }
    else if(objetivo_completo == 5){
       if(primeiraVez == 0){
                deposito_atualy = -125;
            }
            else if(primeiraVez == 1){
                deposito_atualy = -175;
            }
            else if(primeiraVez == 2){
                deposito_atualy = -225;
            }
            else if(primeiraVez == 3){
                deposito_atualy = -375;
            }
            objetivo_completo = 6;
    }
    else if(objetivo_completo == 6){
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 960;
    }
    else if(objetivo_completo == 960){
        if(!robotino->pegou_disco){
            objetivo_completo = 961;
        }
        else {
            objetivo_completo = 977;
        }
    }
    else if(objetivo_completo == 961){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 962;
    }
    else if(objetivo_completo == 962){
        if(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0){
            objetivo_completo = 961;
        }
        else {
            objetivo_completo = 6;
        }
    }
    else if(objetivo_completo == 977){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 978;
    }
    else if(objetivo_completo == 978)
    {
        robotino->definirDestino(robotino->odometryX()/10 + 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 979;
    }
    else if(objetivo_completo == 979){
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 7;
    }
    else if(objetivo_completo == 7){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 8;

    }
    //devolve disco
    else if(objetivo_completo == 8){
        ultimo_objetivo = ++objetivo_completo;
        if(maquina_atual == maqA){
            objetivo_completo = 2000;
        }
        else if(maquina_atual == maqB || maquina_atual == maqF){
            objetivo_completo = 2015;
        }
        else if(maquina_atual == maqC ||maquina_atual == maqD ||maquina_atual == maqE){
            objetivo_completo = 2030;
        }
    }
    else if(objetivo_completo == 9){
            robotino->definirDestino(robotino->odometryX()/10, deposito_atualy - 27);
            robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 10){
        robotino->definirDestino(robotino->odometryX()/10 + 25, robotino->odometryY()/10);
            robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 11){
        robotino->offLeds();

        robotino->definirDestino(robotino->odometryX()/10 - 25, robotino->odometryY()/10);
            robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 12){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 13){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 14){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->change_state(IrParedePelaParede::instance());
        primeiraVez++;
        objetivo_completo = 0;
    }


    else if(objetivo_completo == 9123123){
        ultimo_objetivo = ++objetivo_completo;
        if(maquina_atual == maqA){
            objetivo_completo = 2045;
        }
        else if(maquina_atual == maqB || maquina_atual == maqF){
            objetivo_completo = 2060;
        }
        else if(maquina_atual == maqC ||maquina_atual == maqD ||maquina_atual == maqE){
            objetivo_completo = 2070;
        }
    }






    else if(objetivo_completo == 2000){
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2001){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2002){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2003){
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2004){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->setDeslocamento(DEPOSITO*10);
  //     robotino->definirDestino(robotino->odometryX()/10,deposito_atualy);
        robotino->change_state(IrDistPelaParede::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2005){
       robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 2006){
        objetivo_completo = ultimo_objetivo;
    }





    else if(objetivo_completo == 20){
        //ve se ja entregou todos os discos
            //se nao, objetivo completo++
                //procura nova maquina
                //ve se a nova maquina tem cor DIFERENTE da anterior
                //se sim, objetivo completo = 0
                //se nao, vai pra proxima maquina e repete a checagem

            //se sim, objetivo completo 30

    }
    else if(objetivo_completo == 30){
        //volta pra base
        //objetivo = 1000
    }


    else if(objetivo_completo == 1000){

    }
    else {
        std::cout << "TERMINEI!" << std::endl;
        while(true);
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Modulo3_2017::exit(Robotino *robotino) {}
