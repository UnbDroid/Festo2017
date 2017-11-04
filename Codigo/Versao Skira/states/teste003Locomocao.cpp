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
#include "teste003Locomocao.hpp"
#include "controleremoto.hpp"

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


teste003Locomocao  *teste003Locomocao::instance()
{
    static teste003Locomocao  teste003LocomocaoStateInstance;
    return &teste003LocomocaoStateInstance;
}

teste003Locomocao::teste003Locomocao() {}

teste003Locomocao::~teste003Locomocao() {}


void teste003Locomocao::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado teste003Locomocao...\n";
}

void teste003Locomocao::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;
    static int init_count = 0;

    static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
    static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------
//ANDA NAS 4 paredes da arena seguindo parede no sentido horário

    if (objetivo_completo == 0)
    {
    //     /*robotino->definirObjetoAlvo(Robotino::VERMELHO);
    //     robotino->change_state(SeguirCor::instance());
    //     objetivo_completo = 99999;*/
        //  if(init_count<10){
        //      robotino->change_state(IdentificarCor::instance());
        //      init_count++;
        //  }
        //  else{
        //      objetivo_completo=-2;
        // }
        robotino->definirDestino(robotino->xMaq(0), robotino->yMaq(0));
        robotino->change_state(IrParaPonto::instance());
        //robotino->change_state(ControleRemoto::instance());

    }
    else if(objetivo_completo==-2){
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(SeguirCor::instance());
    }
    else if(objetivo_completo == -1){
        //robotino->adicionarCorFaltando(Robotino::AMARELO);
        //robotino->definirObjetoAlvo(Robotino::AMARELO);
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        // robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 1;
         usleep(2000000);
    }
    else if(objetivo_completo == 1){
        //robotino->adicionarCorFaltando(Robotino::AMARELO);
        robotino->definirParedeAlvo(Robotino::SULN90);
            robotino->setDistParede(10);
            robotino->setDistTrasParede(10);
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(IrParedePelaParedeProcurandoDisco::instance());
           // robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 2;
        usleep(2000000);
    }
    else if(objetivo_completo==2){
        //robotino->definirObjetoAlvo(Robotino::AMARELO);
        robotino->definirDestino(robotino->odometryX()/10 - 20, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
    //  robotino->setDistParede(15);
    //  robotino->setDistTrasParede(15);
    //  robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 3;
        usleep(2000000);
    }
    else if(objetivo_completo == 3){
        robotino->definirObjetoAlvo(Robotino::AMARELO);
        robotino->change_state(SeguirCor::instance()); ///SEGUE DISCO 1
        objetivo_completo = 4;
    }
    else if(objetivo_completo == 4){
        robotino->setThetaR(-179);
        robotino->change_state(Girar::instance());
        objetivo_completo = 5;
    }
    else if(objetivo_completo == 5){
        robotino->definirDestino(robotino->odometryX()/10, -30);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 6; //FICA DE FRENTE PRA AREA DEPOSITO
    }
    else if(objetivo_completo == 6){
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->change_state(AndarPelaParedeAteLinha::instance());
        objetivo_completo = 7; // VAI ATE LINHA DEPOSITO
    }
    else if(objetivo_completo == 7){
        robotino->change_state(AjustarNasLinhas::instance());//AJUSTA LINHA DEPOSITO
        objetivo_completo = 8;
    }
    else if (objetivo_completo == 8){
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo = 9;
    }
    else if(objetivo_completo == 9){
        robotino->definirDestino(robotino->odometryX()/10 - 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance()); //DEPOSITA DISCO
            objetivo_completo = 10;
    }
    else if(objetivo_completo == 10){
        robotino->definirDestino(robotino->odometryX()/10 + 50, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        robotino->setCarregando(false);
        discos_entregues++;
        objetivo_completo = 11;
    }
    else if(objetivo_completo == 11){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 99;
    }
    else if(objetivo_completo == 99){
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(10);
        robotino->setDistTrasParede(10);
        robotino->change_state(IrParedePelaParedeProcurandoDisco::instance());
        objetivo_completo = 12;
    }
    else if(objetivo_completo == 98){
        robotino->definirParedeAlvo(Robotino::OESTE180);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 14;
    }
    else if(objetivo_completo == 12){
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 13;
    }
    else if(objetivo_completo == 13){
        robotino->setThetaR(-179);
        robotino->change_state(Girar::instance());
        objetivo_completo = 98;
    }
    else if(objetivo_completo == 14){
        robotino->definirDestino(100, -120);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 15){
        objetivo_completo++;
    }
    else if(objetivo_completo == 16){
        robotino->change_state(AjustarNasLinhas::instance());
        objetivo_completo++;
    }
    else if (objetivo_completo == 17){
        robotino->change_state(ContarLinhas::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 18){
        robotino->definirDestino(robotino->odometryX()/10 - 15, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 19){
        robotino->definirDestino(robotino->odometryX()/10 + 50, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 20){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 + 50);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 21){
        robotino->setThetaR(-90);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }

    else if(objetivo_completo == 22){
        robotino->definirParedeAlvo(Robotino::NORTEN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 23){
        robotino->setThetaR(-179);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 24){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10 - 60);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }

    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }

    else {
        while(true);
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void teste003Locomocao::exit(Robotino *robotino) {}
