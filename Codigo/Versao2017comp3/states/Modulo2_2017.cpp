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
#include "Modulo2_2017.hpp"
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
#define VELBUSCA 20
//*****************************************************************************************************************
// Modulo1
//*****************************************************************************************************************

Modulo2_2017  *Modulo2_2017::instance()
{
    static Modulo2_2017  Modulo2_2017StateInstance;
    return &Modulo2_2017StateInstance;
}

Modulo2_2017::Modulo2_2017() {}

Modulo2_2017::~Modulo2_2017() {}

void Modulo2_2017::enter(Robotino *robotino)
{
    //if(!c_Modulo101) throw std::invalid_argument("Modulo1 must have an owner to enter.");
    std::cout << "Entrando no Modulo2_2017...\n";
    //robotino->omniDrive.setVelocity(-100, 0 , 0 );
}

void Modulo2_2017::execute(Robotino *robotino)
{
    static int objetivo_completo = 191;
    static int discos_entregues = 0;
    static int disco1[5];
    static int disco2[5];
    static int dirMaq[5] = {1,1,1,1,1};
    static int posx;
    static int posy;
    static int quadrado_alvo = 5;
    static int maquina_alvo = 1;
    static bool busca;
    static vector<int> rotaX;
    static vector<int> rotaY;
    static int dir[5][5];
    //robotino->definirDestino(0,100);
    //robotino->change_state(IrParaPonto::instance());
    std::cout << "objetivo completo:" << objetivo_completo<<endl;
   // usleep(2000000);
    if(objetivo_completo == 0){
        robotino->definirDestino(400, robotino->odometryY()/10);
        robotino->setThetaR(90);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 193;
    }
    else if(objetivo_completo == 1){
        robotino->setOdometry(robotino->odometryX()/10, robotino->odometryY()/10, -90);
        cout<<"ciranda cirandinha"<<endl;
        objetivo_completo = 191;
    }
    else if(objetivo_completo == 191){

        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        //objetivo_completo = 192;

    }
    else if(objetivo_completo == 192){
        robotino->definirDestino(45, -45);
        robotino->setThetaR(90);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 2;
    }
    else if(objetivo_completo == 193){
        robotino->setOdometry(robotino->odometryX()/10, robotino->odometryY()/10, -90);
        robotino->setThetaR(90);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 193;
    }

   /* else if(objetivo_completo == 2){
        robotino->definirParedeAlvo(Robotino::LESTE0);
        robotino->setDistParede(20);
        robotino->change_state(IrParedePelaParedeProcurandoDisco::instance());
        objetivo_completo = 3;
    }*/
    else if(objetivo_completo == 2){
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 3;
    }
    else if(objetivo_completo == 3){
        if(robotino->objetosAzuis.size()== 0 && robotino->objetosAmarelos.size() ==0 && robotino->objetosVermelhos.size() == 0){
            objetivo_completo = 2;
        }
           else {
            objetivo_completo = 7;
           }

    }
    else if(objetivo_completo == 7){
        robotino->pegou_disco = false;
        robotino->definirObjetoAlvo(Robotino::TODAS);
        //cout<< "DEU RUIM ANTES\n\n\n";
        robotino->change_state(SeguirCor::instance());
        //cout<< "DEU RUIM DEPOIS\n\n\n";
      //  objetivo_completo = 7;
        objetivo_completo = 102;

    }

    else if(objetivo_completo == 102){
        if(!robotino->pegou_disco){
            objetivo_completo = 2;
            cout<<"falhei buabuabua"<<endl;
        }
        else {
            cout<< "i win hahahahah"<<endl;
           objetivo_completo = 4;
        }
    }
    else if(objetivo_completo == 4){
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 5){
        objetivo_completo = 10;
    }
    else if(objetivo_completo == 10){
        robotino->definirDestino(robotino->odometryX()/10, -40);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 11){
        robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo++;
    }
    else if(objetivo_completo == 12){
        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo++;
    }
    //else if()
    else
    {
        while(true);
        objetivo_completo = 909;
    }

    //std::cout << "Discos entregues: " << discos_entregues << "\n";
    //robotino->update();
    //std::cout << test << "\n";
    //std::cout << "Vendo na direita: " <<robotino->readColorSensor(Robotino::SC_DIREITO) << "\n";
    //std::cout << "Vendo na esquerda: " <<robotino->readColorSensor(Robotino::SC_ESQUERDO) << "\n";
    //std::cout << "Vendo no indutivo: " <<robotino->readInductiveSensor() << "\n";
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