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
#include "modulo22.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "alinhartraseiro.hpp"

#define PI 3.14159265
#define VELBUSCA 20
//*****************************************************************************************************************
// Modulo1
//*****************************************************************************************************************

Modulo22  *Modulo22::instance()
{
    static Modulo22  Modulo22StateInstance;
    return &Modulo22StateInstance;
}

Modulo22::Modulo22() {}

Modulo22::~Modulo22() {}

void Modulo22::enter(Robotino *robotino)
{
    //if(!c_Modulo101) throw std::invalid_argument("Modulo1 must have an owner to enter.");
    std::cout << "Entrando no Modulo1...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Modulo22::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;

    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());


    if(objetivo_completo == 0)
    {

    }
    else if(objetivo_completo == 1)
    {
        //segue ate canto inferior direito pela parede
        objetivo_completo = 2;
    }
    else if(objetivo_completo == 2)
    {
        //alinha com os cantos da parede, seta odometria, repetidamente
        objetivo_completo = 3;
    }
    else if(objetivo_completo == 3)
    {
        //segue ate parede superior direita pela parede
        objetivo_completo = 4;
    }
    else if(objetivo_completo == 4)
    {
        //alinha com os cantos da parede, seta odometria, repetidamente
        objetivo_completo = 5;
    }
    else if(objetivo_completo == 5)
    {
        //segue ate parede superior direita pela parede
        objetivo_completo = 6;
    }
    else if(objetivo_completo == 6)
    {
        //alinha com os cantos da parede, seta odometria, repetidamente
        objetivo_completo = 7;
    }





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

void Modulo22::exit(Robotino *robotino) {
    std::cout << "Saindo no avoidance control...\n";
}