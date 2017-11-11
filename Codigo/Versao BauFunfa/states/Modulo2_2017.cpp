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
#include "modulo2_2017.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "irparedepelaparede.hpp"

#define PI 3.14159265
#define VELBUSCA 20
//*****************************************************************************************************************
// Modulo1
//*****************************************************************************************************************

Modulo2_2017  *Modulo2_2017::instance()
{
    static Modulo2_2017  Modulo1StateInstance;
    return &Modulo1StateInstance;
}

Modulo2_2017::Modulo2_2017() {}

Modulo2_2017::~Modulo2_2017() {}

void Modulo2_2017::enter(Robotino *robotino)
{
    //if(!c_Modulo101) throw std::invalid_argument("Modulo1 must have an owner to enter.");
    std::cout << "Entrando no Modulo1...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Modulo2_2017::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;

    static int corMaquina[5] = {1,1,1,1,1};
    static int sizeMaquina[5] = {-1,-1,-1,-1,-1};
    static int distrib1[5] = {1,1,1,1,1};
    static int distrib2[5] = {1,1,1,1,1};

    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());


    if(objetivo_completo == 0){

        //Alinhamento inicial
        robotino->definirParedeAlvo(Robotino::LESTE180);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 1;

    }else if (objetivo_completo == 1){
        //vai ate canto
        objetivo_completo = 2;
    }
    else if(objetivo_completo == 2)
    {
        //se alinha com canto
        objetivo_completo = 3;
    }
    else if(objetivo_completo)
    std::cout << "Discos entregues: " << discos_entregues << "\n";
    //robotino->update();
    //std::cout << test << "\n";
    std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
    std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
    std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";
    //cv::Mat img = robotino->getImage();
    //cv::Mat teste (img,cv::Rect(0,0,img.cols,img.rows - 10));
    //std::cout << img;
    //cv::imshow("Amor",img);
    //cv::waitKey(1);
    //std::cout << robotino->getImage();
}

void Modulo2_2017::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}