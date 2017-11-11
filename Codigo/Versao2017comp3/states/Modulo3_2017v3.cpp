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
#include "Modulo3_2017v3.hpp"
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

#include "linhassensor.hpp"
#include "alinhafrenteparede.hpp"

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
// Modulo3_2017v3
//*****************************************************************************************************************


Modulo3_2017v3  *Modulo3_2017v3::instance()
{
    static Modulo3_2017v3  Modulo3_2017v3StateInstance;
    return &Modulo3_2017v3StateInstance;
}

Modulo3_2017v3::Modulo3_2017v3() {}

Modulo3_2017v3::~Modulo3_2017v3() {}

void Modulo3_2017v3::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Modulo3_2017v3...\n";
}

void Modulo3_2017v3::execute(Robotino *robotino)
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
    static int maquinas[6] = {-1,-1,-1,-1,-1,-1};   //A -> 0 // B -> 1 etc
    //static int maqx[6] = {};    //setar!
    //static int maqy[6] = {};    //setar!
    static int maqtheta[6] = {};
    static int deposito_atual = maqA;
    static int deposito_atualy = -175;
    static int maquina_atual = maqA;


    static int cor1;
    static int cor2;


    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;



    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


    //Vai até a máquina 1
    if(objetivo_completo == -1){
        robotino->setDistTrasParede(10);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 0;
    }
    else if(objetivo_completo == 0){
        robotino->setOdometry(30,-30, -90);
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 1;
    }
    else if(objetivo_completo == 1){
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->setDeslocamento(130*10);
        robotino->change_state(IrDistPelaParede::instance());
 //       robotino->definirDestino(170,robotino->odometryY()/10 );
   //     robotino->change_state(IrParaPonto::instance());
         objetivo_completo = -2;
    }
    if(objetivo_completo == -2){
        robotino->setDistTrasParede(10);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 2;
    }
    else if(objetivo_completo == 2){
        robotino->setOdometry(robotino->odometryX()/10,-30, -90);
        robotino->definirDestino(robotino->odometryX()/10,robotino->odometryY()/10 - 30);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo=3;
    }
    else if(objetivo_completo == 3){
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo=4;
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
        objetivo_completo = 5;
    }

    //Pedea disco
    else if(objetivo_completo == 5){
        robotino->onLeds();
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 6;
    }
    else if(objetivo_completo == 6){
            robotino->change_state(PedeDisco::instance());
            objetivo_completo = 7;
    }
    else if(objetivo_completo == 7){
        if(robotino->azul || robotino->amarelo || robotino->vermelho){
            if(robotino->azul){
                //maquinas[0] = AZUL;
                cor1 = AZUL;
            }
            else if(robotino->amarelo){
                //maquinas[0] = AMARELO;
                cor1 = AMARELO;
            }
            else if(robotino->vermelho){
                //maquinas[0] = VERMELHO;
                cor1 = VERMELHO;
            }
            objetivo_completo = 8;
        }
        else {
            objetivo_completo = 5;
        }
    }
    else if(objetivo_completo == 8){
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
            objetivo_completo = 9;
    }
    //Pega disco
    else if(objetivo_completo == 9){
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 10;
    }
    else if(objetivo_completo == 10){
        if(!robotino->pegou_disco){
            objetivo_completo = 11;
        }
        else {
            objetivo_completo = 13;
        }
    }
    else if(objetivo_completo == 11){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 12;
    }
    else if(objetivo_completo == 12){
        if(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0){
            objetivo_completo = 11;
        }
        else {
            objetivo_completo = 9;
        }
    }
    //Volta pra parede
    else if(objetivo_completo == 13){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 14;
    }
    else if(objetivo_completo == 14)
    {
        robotino->definirDestino(robotino->odometryX()/10 + 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 15;
    }
    else if(objetivo_completo == 15){
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 16;
    }
    else if(objetivo_completo == 16){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->setDistParede(10);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 17;
    }
    else if(objetivo_completo == 17){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo=18;
    }
    //vai para o canto
    else if(objetivo_completo == 18){
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 19;
    }
    else if(objetivo_completo == 19){
        robotino->setOdometry(370,robotino->odometryY()/10, robotino->odometryPhi());
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->setDeslocamento(DEPOSITO*10);
  //     robotino->definirDestino(robotino->odometryX()/10,deposito_atualy);
        robotino->change_state(IrDistPelaParede::instance());
        objetivo_completo = 20;
    }
    else if(objetivo_completo = 20)
    {
        robotino->setDistTrasParede(10);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 21;
    }
    else if(objetivo_completo == 21){
        robotino->setOdometry(robotino->odometryX()/10,-30, -90);
       robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        objetivo_completo = 22;
    }
    //vai para area de descarga
    else if(objetivo_completo ==22){
            robotino->definirDestino(robotino->odometryX()/10, deposito_atualy - 27);
            robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 23;
    }
    else if(objetivo_completo == 23)
    {
        robotino->change_stat(LinhasSensor::instance());
        objetivo_completo = 24;
    }
    //descarrega disco
    else if(objetivo_completo == 24){
        robotino->definirDestino(robotino->odometryX()/10 + 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 25;
    }
    else if(objetivo_completo == 25){
        robotino->offLeds();
        robotino->pegou_disco = false;
        robotino->definirDestino(robotino->odometryX()/10 - 20, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 26;
    }
    //Volta para  a parede e ponto inicial
    else if(objetivo_completo == 26)
    {
        robotino->change_stat(LinhasSensor::instance());
        objetivo_completo = 27;
        if(primeiraVez>=3){
            objetivo_completo = 30;
            primeiraVez = 0;
        }
    }
    else if(objetivo_completo == 27){
        robotino->definirParedeAlvo(Robotino::OESTE0);
        robotino->change_state(IrParaParede::instance());
        objetivo_completo = 28;
    }
    else if(objetivo_completo == 28){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = -29;
    }
    else if(objetivo_completo == -29)
    {
        robotino->setDistTrasParede(10);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 29;
    }
    else if(objetivo_completo == 29){
        robotino->setOdometry(robotino->odometryX()/10,-30, -90);
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->change_state(IrParedePelaParede::instance());
        primeiraVez++;
        if(primeiraVez < 4){
            objetivo_completo = 0;
        }
        else {
            primeiraVez = 0;
            objetivo_completo = 30;
        }
    }


    //SEGUNDA MAQUINA = canto superior
    else if(objetivo_completo == 30)
    {
            if(primeiraVez == 0){
                deposito_atualy = -375;
            }
            else if(primeiraVez == 1){
                deposito_atualy = -225;
            }
            else if(primeiraVez == 2){
                deposito_atualy = -175;
            }
            else if(primeiraVez == 3){
                deposito_atualy = -125;
            }
            objetivo_completo = 31;
    }
    else if(objetivo_completo == 31)
    {
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 32;
    }
    else if(objetivo_completo == 32)
    {
        robotino->setDistTrasParede(10);
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 33;
    }
    else if(objetivo_completo == 33)
    {
        robotino->setOdometry(robotino->odometryX()/10,-370, 90);
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10+50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 34;
    }
    else if(objetivo_completo == 34)
    {
        robotino->setThetaR(179);
        robotino->change_state(Girar::instance());
        objetivo_completo = 35;
    }
    else if(objetivo_completo == 35)
    {
        robotino->definirDestino(robotino->odometryX()/10-50, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 36;
    }
    else if(objetivo_completo == 36)
    {
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 37;
    }
    else if(objetivo_completo == 37)
    {
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo=38;
    }
    //pede disco
    else if(objetivo_completo == 38){
        robotino->onLeds();
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 39;
    }
    else if(objetivo_completo == 39){
            robotino->change_state(PedeDisco::instance());
            objetivo_completo = 40;
    }
    else if(objetivo_completo == 40){
        if(robotino->azul || robotino->amarelo || robotino->vermelho){
            if(robotino->azul){
                //maquinas[0] = AZUL;
                cor2 = AZUL;
            }
            else if(robotino->amarelo){
                //maquinas[0] = AMARELO;
                cor2 = AMARELO;
            }
            else if(robotino->vermelho){
                //maquinas[0] = VERMELHO;
                cor2 = VERMELHO;
            }
            if(cor1 != cor2)
                objetivo_completo = 41;
            else
                objetivo_completo = 8001;
        }
        else {
            objetivo_completo = 38;
        }
    }
    //Pega disco
    else if(objetivo_completo == 41){
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 42;
    }
    else if(objetivo_completo == 42){
        if(!robotino->pegou_disco){
            objetivo_completo = 43;
        }
        else {
            objetivo_completo = 45;
        }
    }
    else if(objetivo_completo == 43){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 44;
    }
    else if(objetivo_completo == 44){
        if(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0){
            objetivo_completo = 43;
        }
        else {
            objetivo_completo = 41;
        }
    }
    //pegou o disco
    //voltar para o canto superior direito 370x -370y







    else if(objetivo_completo == 8001)
    {
        cout<<"não sei o que fazer agora"<<endl;
    }
    else {
        std::cout << "TERMINEI!" << std::endl;
        while(true);
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Modulo3_2017v3::exit(Robotino *robotino) {}
