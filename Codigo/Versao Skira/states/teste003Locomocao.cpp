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

    static vector<int> ordemAtualDiscos = {INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO, INDEFINIDO}; //mudei para 6
    static vector<int> ordemCorreta = {B,B,R,R,Y,Y};

    static NoBusca noFinal(ordemCorreta,0);

    static NoBusca melhorResultado;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------
//ANDA NAS 4 paredes da arena seguindo parede no sentido horário

    if (objetivo_completo == 0)
    {
        robotino->definirObjetoAlvo(Robotino::VERMELHO);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 99999;
    }

    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void teste003Locomocao::exit(Robotino *robotino) {}
