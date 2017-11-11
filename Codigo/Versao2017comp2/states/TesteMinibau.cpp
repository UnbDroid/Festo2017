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
#include "TesteMinibau.hpp"
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
#define AREA_12 200
#define AREA_34 330
#define AREA_56 69
#define TESTES 203


//modulo2
#define AREA1x 123
#define AREA1y 123
#define AREA2x 123
#define AREA2y 123
#define AREA3x 123
#define AREA3y 123
#define AREA4x 30
#define AREA4y -30
#define AREA5x 30
#define AREA5y -370



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
// TesteMinibau
//*****************************************************************************************************************


TesteMinibau  *TesteMinibau::instance()
{
    static TesteMinibau  TesteMinibauStateInstance;
    return &TesteMinibauStateInstance;
}

TesteMinibau::TesteMinibau() {}

TesteMinibau::~TesteMinibau() {}

void TesteMinibau::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado TesteMinibau...\n";
}

void TesteMinibau::execute(Robotino *robotino)
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
    static bool cima;
    static int shift = 20;
    static int times2 = 0;
    //static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
   // static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

//    static NoBusca noFinal(ordemCorreta,0);

  //  static NoBusca melhorResultado;
    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;

    if(objetivo_completo == 0){
        robotino->change_state(PedeDisco::instance());
        objetivo_completo=1;
    }
    else if(objetivo_completo==1){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo=0;
    }

    else {
        std::cout << "TERMINEI!" << std::endl;
        while(true);
    }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void TesteMinibau::exit(Robotino *robotino) {}