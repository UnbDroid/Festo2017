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
#include "testeVisao.hpp"

#include "ajustarnaslinhas.hpp"
#include "ajustarnaslinhasortogonais.hpp"
#include "andarpelaparedeatelinha.hpp"
#include "andarpelaparedeatelinhasensor.hpp"
#include "contarlinhas.hpp"
#include "percorrerprocurandodiscos.hpp"
#include "irparedepelaparede.hpp"
#include "irparedepelaparedeprocurandodisco.hpp"
#include "alinhafrenteparede.hpp"


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

#include <sys/time.h>


//#include "pegardisco.hpp"

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

/*modulo2
#define XA0 375
#define YA0 -25

#define XA1 375
#define YA1 -125

#define XA2 375
#define YA2 -176

#define XA3 375
#define YA3 -227

#define XA4 30
#define YA4 -370

#define XA5 30
#define YA5 -30
*/
#define XA0 30
#define YA0 -25

#define XA1 375
#define YA1 -375

#define XA2 375
#define YA2 -225

#define XA3 375
#define YA3 -174

#define XA4 375
#define YA4 -124

#define XA5 -5000
#define YA5 -5000

#define XYAErro 24

//*****************************************************************************************************************
// teste003Locomocao
//*****************************************************************************************************************


testeVisao  *testeVisao::instance()
{
    static testeVisao  testeVisaoStateInstance;
    return &testeVisaoStateInstance;
}

testeVisao::testeVisao() {}

testeVisao::~testeVisao() {}


void testeVisao::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado testeVisao...\n";
}

void testeVisao::execute(Robotino *robotino)
{
    static int objetivo_completo = 0;
    static int discos_entregues = 0;
    static int numPassosFazer = 0;
    static int numPassosFeitos = 0;
    static int deixarDiscos = 0;
    static int pegar = 0;
    static bool deixando = false;
    static int areaAtual = -1;


    static int num_buscas = 0;

    static int angulo = 0;

    std::cout << "objetivo_completo:  " << objetivo_completo << std::endl;


    if(objetivo_completo == 0)
    {
        robotino->setOdometry(XA4,YA4,180);
        robotino->definirParedeAlvo(Robotino::SUL90);
        robotino->setDistFrenteParede(30);
        robotino->change_state(AlinhaFrenteParede::instance());
        // robotino->definirParedeAlvo(Robotino::SUL90);
        // robotino->setDistTrasParede(20);
        // robotino->change_state(AlinharTraseiro::instance());
        objetivo_completo = 1;
    }
    else if(objetivo_completo == 1)
    {

    }

    // //CODIGO DAS AREAS

    //     //Define areas TESTA AREAS
    //     //DEFINE 6 AREAS
    //     static std::vector<Area> a(6);
    //     static std::vector<Coordenadas> carea(6);
    //     carea[0] = Coordenadas(XA0,YA0);
    //     carea[1] = Coordenadas(XA1,YA1);
    //     carea[2] = Coordenadas(XA2,YA2);
    //     carea[3] = Coordenadas(XA3,YA3);
    //     carea[4] = Coordenadas(XA4,YA4);
    //     carea[5] = Coordenadas(XA5,YA5);

    //     for(int i = 0; i < 6; i++)
    //     {
    //         a[i].adicionar_coordenada(carea[i]);
    //     }
    // //DEFINE AREAS END
    // //robotino->setOdometry(XA4+20,YA5+20,-90);

    // static Coordenadas teste;
    // static Coordenadas robotinoAtual;
    // static bool condArea;

    // robotinoAtual = Coordenadas(robotino->odometryX(), robotino->odometryY());
    // static bool fora = false;

    // for(int i = 0; i < 6; i++)
    // {
    //     teste = a[i].pegar_coordenada(carea[i]);
    //     condArea = (abs(robotinoAtual.get_x() - teste.get_x()) < XYAErro)&&(abs(robotinoAtual.get_y() - teste.get_y()) < XYAErro);

    //     // std::cout << "RobX =\t" << robotinoAtual.get_x() << "\tRobY =\t" << robotinoAtual.get_y()<<std::endl;
    //     // std::cout << "AREAATUAL_X"<<i<<"=\t" << teste.get_x() << "\tAREAATUAL_Y =\t" << teste.get_y()<<std::endl;
    //     // usleep(200000);

    //     if(condArea)//DENTRO DA AREA
    //     {
    //         std::cout << "\n\n\n\nDENTRO DA AREA"<< i <<"\n\n\n\n"<<std::endl;
    //         fora = true;

    //         // while(true)
    //         // {
    //             // usleep(2000000);
    //         // }
    //     }
    // }
    // if(fora == false)
    // {std::cout << "\n\n\n\nFORA AREAS\n\n\n\n"<<std::endl;}

    // //TESTA AREAS END

    //VERSAO AREAS OO

    // robotino->setOdometry(XA4,YA4,-90);
    // if(objetivo_completo == 0){
    //     usleep(200000);
    //     areaAtual = robotino->getArea();
    //     if(areaAtual != -1)
    //     {
    //         std::cout << "\n\n\n\n\n\nDENTRO DA AREA"<<areaAtual<<"\n\n\n\n\n\n"<<std::endl;
    //     }else
    //     {
    //         std::cout << "\n\n\n\n\n\nFORA DAS AREAS\n\n\n\n\n\n"<<std::endl;
    //     }
    // }



    //VERSAO AREAS OO END



// Saindo da area de inicio e indo para a area de deposito 6------------------------------------------------------------------------------------------
//ANDA NAS 4 paredes da arena seguindo parede no sentido horário
    //usleep(2000000);
    // if(objetivo_completo == 0)
    // {
    //     robotino->definirParedeAlvo(Robotino::SULN90);
    //     robotino->setDistTrasParede(20);
    //     robotino->change_state(AlinharTraseiro::instance());
    //     objetivo_completo = 90;
    // }
    // else if(objetivo_completo == 90){
    //     robotino->definirDestino(robotino->odometryX()/10+50, robotino->odometryY()/10-20);
    //     robotino->change_state(IrParaPonto::instance());
    //     objetivo_completo = 91;
    // }

    /*if(objetivo_completo == 10)
    {
        robotino->definirParedeAlvo(Robotino::SULN90);
        robotino->setDistParede(15);
        robotino->setDistTrasParede(15);
        robotino->change_state(IrParedePelaParede::instance());
        objetivo_completo = 9;
    }
    else if(objetivo_completo == 9)
    {

       // usleep(2000000);
        robotino->setThetaR(angulo);
        robotino->change_state(Girar::instance());
        angulo+=90;
        if(angulo == 180)
            angulo = 179;
        if(angulo > 180)
            angulo = -90;
        objetivo_completo = 900;
    }
    else if(objetivo_completo == 900)
    {
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-80);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 0;
    }
    else if(objetivo_completo == 901)
    {
        robotino->definirDestino(robotino->odometryX()/10+30, robotino->odometryY()/10);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 0;
    }
    else if (objetivo_completo == 0)
    {
        num_buscas++;
        robotino->change_state(IdentificarCor::instance());
        objetivo_completo = 1;
    }
    else if(objetivo_completo == 1)
    {
        if(robotino->objetosAzuis.size() == 0 && robotino->objetosAmarelos.size() == 0 && robotino->objetosVermelhos.size() == 0)
        {
            objetivo_completo = 0;
        }
        else
        {
            objetivo_completo = 2;
        }
    }
    else if(objetivo_completo == 2)
    {
        robotino->pegou_disco = false;
        robotino->definirObjetoAlvo(Robotino::TODAS);
        robotino->change_state(SeguirCor::instance());
        objetivo_completo = 3;
    }
    else if(objetivo_completo == 3)
    {
        if(!robotino->pegou_disco)
        {
            objetivo_completo = 0;
            cout<<"Falhei buabuabua"<<endl;
        }
        else
        {
            cout<<"i win hahahahha"<<endl;
            objetivo_completo = 987;
        }

    }
    else if(objetivo_completo == 987){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10-20);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 908;
    }
    else if(objetivo_completo == 908)
    {
        robotino->setThetaR(90);
        robotino->change_state(Girar::instance());
        objetivo_completo = 9000;
    }

    else if(objetivo_completo == 9000)
    {
        robotino->definirDestino(robotino->odometryX()/10-30, robotino->odometryY()/10-10);
        robotino->change_state(IrParaPonto::instance());

        objetivo_completo = 9001;
    }
    else if(objetivo_completo == 9001)
    {
        //robotino->setVelocity(0,0,50);//GIRA LOUCAMENTE
        robotino->setThetaR(0);
        robotino->change_state(Girar::instance());
        angulo+=90;
        if(angulo == 180)
            angulo = 179;
        if(angulo > 180)
            angulo = -90;
        objetivo_completo = 9002;
    }
    else if(objetivo_completo == 9002){
        robotino->definirDestino(robotino->odometryX()/10, robotino->odometryY()/10+30);
        robotino->change_state(IrParaPonto::instance());
        objetivo_completo = 9003;
    }
    else if(objetivo_completo == 9003){//vai pra parede com disco

            }
    else if(objetivo_completo == 87){}
    else if(objetivo_completo == 87){}
    else if(objetivo_completo == 87){}
    else if(objetivo_completo == 87){}

    else if(objetivo_completo == 99999)
    {
        std::cout << "TERMINOU" << endl;
        robotino->~Robotino();
    }*/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void testeVisao::exit(Robotino *robotino) {}
