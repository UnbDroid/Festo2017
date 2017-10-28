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
#include "Testin2017.hpp"
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

//*****************************************************************************************************************
// Testin2017
//*****************************************************************************************************************


Testin2017  *Testin2017::instance()
{
    static Testin2017  Testin2017StateInstance;
    return &Testin2017StateInstance;
}

Testin2017::Testin2017() {}

Testin2017::~Testin2017() {}

void Testin2017::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado Testin2017...\n";
}

void Testin2017::execute(Robotino *robotino)
{

    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;

    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;
	if(objetivo_completo == 0){	
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
//	robotino->setDistParede(15);
//	robotino->setDistTrasParede(15);
//	robotino->change_state(IrParedePelaParede::instance());
	objetivo_completo = 3;
	usleep(2000000);
	}
	else if(objetivo_completo == 3){
	robotino->definirObjetoAlvo(Robotino::AMARELO);
	robotino->change_state(SeguirCor::instance());
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
        objetivo_completo = 6;
	}
	else if(objetivo_completo == 6){
	robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->change_state(AndarPelaParedeAteLinha::instance());	
	objetivo_completo = 7;
	}
	else if(objetivo_completo == 7){
	robotino->change_state(AjustarNasLinhas::instance());
	objetivo_completo = 8;
   	}
	else if (objetivo_completo == 8){
	robotino->change_state(ContarLinhas::instance());
	objetivo_completo = 9;
	}
	else if(objetivo_completo == 9){
	robotino->definirDestino(robotino->odometryX()/10 - 15, robotino->odometryY()/10);
	robotino->change_state(IrParaPonto::instance());
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
	else {
while(true);
}
	

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Testin2017::exit(Robotino *robotino) {}