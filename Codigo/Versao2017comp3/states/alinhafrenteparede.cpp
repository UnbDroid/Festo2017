#include "alinhafrenteparede.hpp"
#include "robotino.hpp"

#define Kpx -1
#define limiar 0.5
#define R 20
#define PI 3.14159265
#define Kp -2
#define Ki 1

//*****************************************************************************************************************
// AlinhaFrenteParede
//*****************************************************************************************************************

AlinhaFrenteParede  *AlinhaFrenteParede::instance()
{
    static AlinhaFrenteParede  AlinhaFrenteParedeStateInstance;
    return &AlinhaFrenteParedeStateInstance;
}

AlinhaFrenteParede::AlinhaFrenteParede() {}

AlinhaFrenteParede::~AlinhaFrenteParede() {}

void AlinhaFrenteParede::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado AlinhaFrenteParede...\n";
}

void AlinhaFrenteParede::execute(Robotino *robotino)
    {

    float refDistfrente = robotino->getRefDistFrenteParede();

    float   Vx = 0;
    float erroDistfrente = 0;
    int paredeAlvo = robotino->paredeAlvo();

    //static float a = std::sin(60*PI/180)/std::sin(80*PI/180);
    //static float cos20 = std::cos(20*PI/180);
    static float cos40 = std::cos(40*PI/180);
    //static float K = R*(a-1);
    static float erro_int = 0;

    float w;

    float te = robotino->irDistance(Robotino::IR_F_ESQUERDO);
    float td = robotino->irDistance(Robotino::IR_F_DIREITO);

    float distancia_de_frente;
    float erro;


    // Alinha o bumbum

    distancia_de_frente= ((te+td+2*R)*cos40)/2;

    erroDistfrente = refDistfrente - (distancia_de_frente - 20);

    Vx = Kpx*erroDistfrente;

    erro = te - td;
    w = Kp*erro;

    robotino->setVelocity(Vx,0, w);

    std::cout << "Soma erros AlinhaFrenteParede:  " << erro+erroDistfrente << std::endl;

    if (/*std::abs(erroDistfrente)+*/std::abs(erro) < limiar) {
        std::cout << "Alinhei o bumbum na parede" << std::endl;
        robotino->setVelocity(0,0,0);
        robotino->change_state(robotino->previous_state());
    }


    // Reseta odometria

    if (paredeAlvo == Robotino::OESTE0 || paredeAlvo == Robotino::OESTE180) {
        robotino->setOdometry(robotino->odometryX(),-(distancia_de_frente*10+15),-90);
    }
    if (paredeAlvo == Robotino::NORTEN90 || paredeAlvo == Robotino::NORTE90) {
        robotino->setOdometry((robotino->getAlturaMapa())*10 -(distancia_de_frente*10+15),robotino->odometryY(),180);
    }
     if (paredeAlvo == Robotino::SUL90 || paredeAlvo == Robotino::SULN90) {
        robotino->setOdometry((distancia_de_frente*10+15),robotino->odometryY(),0);
    }
     if (paredeAlvo == Robotino::LESTE180 || paredeAlvo == Robotino::LESTE0) {
        robotino->setOdometry(robotino->odometryX(),-((robotino->getLarguraMapa())*10 -(distancia_de_frente*10+15)),90);
    }


}

void AlinhaFrenteParede::exit(Robotino *robotino) {}
