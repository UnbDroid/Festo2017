#include "irparaponto.hpp"
#include "robotino.hpp"
#include "classificadores.hpp"
#include "maquinainferencia.hpp"
#include "defuzzyficador.hpp"
#include "coordenadas.hpp"
#include "girar.hpp"
#include "controleremoto.hpp"
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

//*****************************************************************************************************************
// Controle para testes (para leitura dos sensores IR, principalmente)
//*****************************************************************************************************************

ControleRemoto  *ControleRemoto::instance()
{
    static ControleRemoto  ControleRemotoStateInstance;
    return &ControleRemotoStateInstance;
}

ControleRemoto::ControleRemoto() {}

ControleRemoto::~ControleRemoto() {}

void ControleRemoto::enter(Robotino *robotino)
{
    std::cout << "Entrando no controle ...\n";
}

void ControleRemoto::execute(Robotino *robotino)
{
    rec::iocontrol::remotestate::SensorState sensor;
    char key=-1;
    int vx=100, vy=100, w=100;      //velocidade dos movimentos
    float voltage[9], dist[9];

    std::cout<<"  inf1     inf2     inf3    inf4     inf5     inf6    inf7     inf8     inf9"<<std::endl;
    while(key!=27){
        //cv::imshow("Amor", robotino->getImage());         //para mostrar a imagem da camera. Deixar comentado caso nao seja necessario - essa funcao manda varias mensagens de erro da imagem JPEG, diciculta a leitura dos sensores IR
        key=waitKey(10);
        switch(key){
            case(-1):
                robotino->setVelocity(0, 0, 0);    //para se n tiver recebido comando
                usleep(25000);
                break;
            case('s'):
                robotino->setVelocity(-vx, 0, 0);       //a, s, d, w -> anda nos eixos x e y
                usleep(25000);
                break;
            case('d'):
                robotino->setVelocity(0, -vy, 0);
                usleep(25000);
                break;
            case('w'):
            robotino->setVelocity(vx, 0, 0);
                usleep(25000);
            break;
            case('a'):
                robotino->setVelocity(0, vy, 0);
                usleep(25000);
                break;
            case('q'):
                robotino->setVelocity(0, 0, w);         //"q" gira no sentido anti-horario, "e" no sentido horario
                usleep(25000);
                break;
            case('e'):
            robotino->setVelocity(0, 0, -w);
                usleep(25000);
            break;
            case('\n'):     //se apertar enter, mostra a situacao atual dos sensores infra-vermelhos
                sensor = robotino->sensorState();
                for(int i=0;i<9;i++){
                    voltage[i] = sensor.distanceSensor[i];      //calculo dos novos valores (n consigo acessar robotino->currentSensorState.distanceSensor[IF] aqui por ser privada)
                    dist[i] = (8.26)*voltage[i]*voltage[i]*voltage[i]*voltage[i]-55.77*voltage[i]*voltage[i]*voltage[i]+137.5*voltage[i]*voltage[i]-152.7*voltage[i]+75.13;
                }
                //std::cout<<dist[0]<<"  "<<dist[1]<<"  "<<dist[2]<<"  "<<dist[3]<<"  "<<dist[4]<<"  "<<dist[5]<<"  "<<dist[6]<<"  "<<dist[7]<<"  "<<dist[8]<<std::endl;
                std::cout<<"\ndist ate maquina 1: "<<robotino->calcDist(robotino->xMaq(0), (robotino->odometryX())/10, -robotino->yMaq(0), (robotino->odometryY())/10)<<std::endl;
                break;//<<robotino->odometryX()<<"  "<<robotino->odometryY()<<std::endl;
        }
    }
    robotino->change_state(robotino->previous_state());
}

void ControleRemoto::exit(Robotino *robotino) {
    std::cout << "Cabei...\n";
    robotino->setVelocity(0,0,0);
    usleep(500000);
}
