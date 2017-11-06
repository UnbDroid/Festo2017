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
    static bool flaggg = true;

    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;
    if(flaggg == true){
        robotino->setOdometry(174, -30, 180);
        flaggg = false;
    }
    if(objetivo_completo == 0){
        std::cout << "odometryX: " << robotino->odometryX()/10<<std::endl;
        cv::waitKey(0);
        robotino->definirDestino(robotino->odometryX()/10, robotino->yMaq(0));
        //robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 1){
        robotino->change_state(IdentificarCor::instance());
        if(robotino->objetosVermelhos.size() > 0 ){
            objetivo_completo++;
        }
    }
    // else if(objetivo_completo == 2){
    //     robotino->change_state(SeguirCor::instance());
    //     objetivo_completo++;
    // }
    //else if(objetivo_completo == 3){
      //  robotino->change_state()
    //}*/
    else while(true);


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Testin2017::exit(Robotino *robotino) {}
