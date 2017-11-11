#include "irdistpelaparede.hpp"
#include "robotino.hpp"
#include "girar.hpp"

#define Kpx 2
#define Kpy 10
#define Kiy 0
#define dt 0.01
#define limiar 2
#define limiar2 0.5
#define R 20
#define PI 3.14159265
#define Kp 5
#define Ki 1

//*****************************************************************************************************************
// IrDistPelaParede
//*****************************************************************************************************************

IrDistPelaParede2 *IrDistPelaParede2::instance()
{
    static IrDistPelaParede2  IrDistPelaParedeStateInstance;
    return &IrDistPelaParedeStateInstance;
}

IrDistPelaParede2::IrDistPelaParede2() {}

IrDistPelaParede2::~IrDistPelaParede2() {}

void IrDistPelaParede2::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IrDistPelaParede...\n";
}

void IrDistPelaParede2::execute(Robotino *robotino)
{
    float refDist = robotino->getRefDistParede();
    float refDistTras = robotino->getRefDistTrasParede();

    float   Vy = 0, Vx = 0;
    float direcao = 0;
    float erroDist = 0;
    float erroDistTras = 0;
    int paredeAlvo = robotino->paredeAlvo();
   // static bool girei = robotino->getNaoDevoGirarParede();
    static bool girei = true;
    girei = true;
    static float erro_intDist = 0;
    static bool ajuste = false;
    static bool pronto = false;
    static State<Robotino> * voltar;
    voltar = robotino->previous_state();

    static int iniciou = 0;
    static float inicio_x;
    static float inicio_y;

    static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    static float cos20 = std::cos(20*PI/180);
    static float K = R*(a-1);
    static float erro_int = 0;
    float w;
    float e1 = robotino->irDistance(Robotino::IR_ESQUERDO_1);
    float e2 = robotino->irDistance(Robotino::IR_ESQUERDO_2);
    float ref_e1 = e2*a+K;
    float d1 = robotino->irDistance(Robotino::IR_DIREITO_1);
    float d2 = robotino->irDistance(Robotino::IR_DIREITO_2);
    float te = robotino->irDistance(Robotino::IR_T_ESQUERDO);
    float td = robotino->irDistance(Robotino::IR_T_DIREITO);
    float ref_d1 = 1.15*(d2*a+K);
    float distancia_da_esquerda, distancia_da_direita, distancia_de_tras;
    float erro;


    // Anda até a parede desejada

    if ((paredeAlvo == Robotino::NORTEN90  || paredeAlvo == Robotino::OESTE0 || paredeAlvo == Robotino::SUL90 || paredeAlvo == Robotino::LESTE180) && girei && !ajuste ) {

        distancia_da_esquerda = ((e1+ref_e1+2*R)*cos20)/2;
        erroDist = (distancia_da_esquerda-20) - refDist;
        erro_intDist += erroDist*dt;
        Vy = Kpy*erroDist+Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;

        distancia_de_tras= ((te+td+2*R)*cos20)/2;

        erroDistTras = refDistTras - (distancia_de_tras -20);

        Vx = Kpx*erroDistTras;

        erro = te - td;
        w = Kp*erro;

        robotino->setVelocity(Vx,Vy, w);

        if (std::abs(erroDist) < limiar) {
            std::cout << "Andei ate a parede" << std::endl;
            ajuste = true;
            robotino->setVelocity(0,0,0);
        }

    } else if ((paredeAlvo == Robotino::SULN90  || paredeAlvo == Robotino::LESTE0 || paredeAlvo == Robotino::NORTE90  || paredeAlvo == Robotino::OESTE180) && girei && !ajuste) {

        distancia_da_direita = ((d1+ref_d1+2*R)*cos20)/2;
        erroDist = (distancia_da_direita-20) - refDist;
        erro_intDist += erroDist*dt;
        Vy = -Kpy*erroDist-Kiy*erro_intDist;
        std::cout << "Erro: " << erroDist <<endl;

        distancia_de_tras= ((te+td+2*R)*cos20)/2;

        std::cout << "distancia_de_tras: " << distancia_de_tras <<"\n";

        erroDistTras = refDistTras - (distancia_de_tras - 20);

        Vx = Kpx*erroDistTras;

        erro = te - td;
        w = Kp*erro;

        robotino->setVelocity(Vx,Vy, w);

        if (std::abs(erroDist) < limiar) {
            ajuste = true;
            robotino->setVelocity(0,0,0);//andei ate a parede
            robotino->setVelocity(0,0,0);
        }
    }

    if(iniciou == 0)
    {
        inicio_x = robotino->odometryX();
        inicio_y = robotino->odometryY();
        iniciou = 1;
    }


    cout<<robotino->odometryX()<<"         "<<robotino->odometryY()<<endl;
    cout<<inicio_x<<"         "<<inicio_y<<"      "<<robotino->deslocamento<<endl;

    float posx = robotino->odometryX();
    float posy = robotino->odometryY();
    posx = (posx-inicio_x);
    posx *= posx;
    posy = (posy-inicio_y);
    posy*=posy;
    float dist = sqrt(posx+posy);
    cout<<"andei "<<dist<<"de distancia, sei la a unidade"<<endl;

    if(dist>=robotino->deslocamento)
    {
        ajuste = true;
        robotino->setVelocity(0,0,0);//andei ate a parede
        robotino->setVelocity(0,0,0);
    }






    // Gira para ficar paralelo à parede desejada

    if (paredeAlvo == Robotino::NORTEN90 && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::NORTE90 && !girei){
        direcao = 90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if(paredeAlvo == Robotino::SULN90 && !girei){
        direcao = -90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::SUL90 && !girei){
        direcao = 90;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if (paredeAlvo == Robotino::OESTE0 && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());

    }else if(paredeAlvo == Robotino::OESTE180 && !girei){
        direcao = 179;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if (paredeAlvo == Robotino::LESTE0 && !girei){
        direcao = 0;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }else if(paredeAlvo == Robotino::LESTE180 && !girei){
        direcao = 179;
        robotino->setThetaR(direcao);
        voltar = robotino->previous_state();
        girei = true;
        robotino->change_state(Girar::instance());
    }

    if(ajuste)
    {
        girei = false;
        robotino->setNaoDevoGirarParede(girei);
        ajuste = false;
        pronto = false;
        erro_intDist = 0;
        erro_int = 0;
        iniciou = 0;
        robotino->setVelocity(0,0,0);
        robotino->change_state(voltar);
    }

}

void IrDistPelaParede2::exit(Robotino *robotino) {}
