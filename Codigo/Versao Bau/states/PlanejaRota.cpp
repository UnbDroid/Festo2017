#include "PlanejaRota.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"
#include "Segmento.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
//#include <cv.h>
//#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/time.h>





#include <string>
#include <fstream>



//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 4*4;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";

using namespace cv;

//*****************************************************************************************************************
// IdentificarCor
//*****************************************************************************************************************

PlanejaRota  *PlanejaRota::instance()
{
    static PlanejaRota  PlanejaRotaStateInstance;
    return &PlanejaRotaStateInstance;
}

PlanejaRota::PlanejaRota() {}

PlanejaRota::~PlanejaRota() {}

void PlanejaRota::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}



void desenha_grid(Mat* imagem,float Q[6][6][4],int num_episodio, int passos){
    int i, j, k;
    int passo, passo2;
    int colunas = imagem->cols;
    int linhas = imagem->rows;
    string peso;
    (*imagem) = Scalar(255,255,255);
    passo = (imagem->cols)/6;

    for(i=1;i<6;i++){
        line( (*imagem), Point(i*passo,0), Point(i*passo,linhas), Scalar(0,0,0), 2, 8);
    }
    passo2 = (imagem->rows)/6;
    for(i=1;i<6;i++){
        line( (*imagem), Point(0,i*passo2), Point(colunas,i*passo2), Scalar(0,0,0), 2, 8);
    }
    line( (*imagem), Point(0,7*passo2), Point(colunas,7*passo2), Scalar(0,0,0), 4, 8);
    rectangle((*imagem), Point(7*passo+2,3*passo2+2), Point(8*passo-2,4*passo2-2), Scalar(200,200,200), -1, 8, 0);
    for(i = 0; i<6; i++){
        for(j = 0; j<6; j++){
            line( (*imagem), Point(i*passo,j*passo2), Point((i+1)*passo,(j+1)*passo2), Scalar(0,0,0), 1, 8);
            line( (*imagem), Point(i*passo,(j+1)*passo2), Point((i+1)*passo,j*passo2), Scalar(0,0,0), 1, 8);
            for(k = 0; k<4; k++){
                peso.clear();
                stringstream ss;
                ss.clear();
                ss << (int)Q[j][i][k];
                peso = ss.str();
                int desvio;
                if(Q[j][i][k] > 99){
                    desvio = 10;
                }
                else if(Q[j][i][k] > 9)
                    desvio = 6;
                else if(Q[j][i][k] > 0)
                    desvio = 2;
                else if(Q[j][i][k] > -10)
                    desvio = 6;
                else if(Q[j][i][k] > -100)
                    desvio = 10;
                else if(Q[j][i][k] > -1000)
                    desvio = 14;
                switch(k){
                    case(0):
                        putText((*imagem), peso, Point(i*passo+passo/2 - desvio,j*passo2+passo2 - 5), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(0,0,0), 1, 8, false );
                        break;
                    case(1):
                        putText((*imagem), peso, Point(i*passo+2,j*passo2+passo2/2 +2), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(0,0,0), 1, 8, false );
                        break;
                    case(2):
                        putText((*imagem), peso, Point(i*passo+passo/2 - desvio,j*passo2+passo2/8 + 5), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(0,0,0), 1, 8, false );
                        break;
                    case(3):
                        putText((*imagem), peso, Point(i*passo+(7*passo/8) - (3*desvio)/2,j*passo2+passo2/2 +2), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(0,0,0), 1, 8, false );
                        break;
                }
            }
        }
    }
    for(i=0; i<3; i++){
        circle( (*imagem), Point(i*passo + passo/2,(int)(7.5*(float)passo2)), 4, Scalar(0,0,0), -1);
    }
    for(i=3; i<6; i++){
        line( (*imagem), Point(i*passo + passo/2,7.8*passo2), Point(i*passo + passo/2,7.2*passo2), Scalar(0,0,0), 1, 8);
    }
    for(i=6; i<8; i++){
        line( (*imagem), Point(i*passo + passo/4,7.8*passo2), Point(i*passo + passo/4,7.2*passo2), Scalar(0,0,0), 1, 8);
        line( (*imagem), Point(i*passo + (3*passo)/4,7.8*passo2), Point(i*passo + (3*passo)/4,7.2*passo2), Scalar(0,0,0), 1, 8);
    }
    line( (*imagem), Point(8*passo + passo/2,7.8*passo2), Point(8*passo + passo/2,7.2*passo2), Scalar(0,0,0), 1, 8);
    circle( (*imagem), Point(9*passo + passo/2,(int)(7.5*(float)passo2)), 4, Scalar(0,0,0), -1);
    stringstream ss;
    ss.clear();
    ss << num_episodio;
    peso = ss.str();
    putText((*imagem), "episodio", Point(9*passo+5,7*passo2+(passo2/4)), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,0,255), 1, 8, false );
    int desvio;
    if(num_episodio < 10)
        desvio = 23;
    else if(num_episodio<100)
        desvio = 20;
    else if(num_episodio<1000)
        desvio = 15;
    else
        desvio = 10;
    putText((*imagem), peso, Point(9*passo+desvio,8*passo2 -10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1, 8, false );

    stringstream ss2;
    ss2.clear();
    passos++;
    ss2 << passos;
    peso = ss2.str();
    putText((*imagem), "passos", Point(8,7*passo2+(passo2/4)), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,255,0), 1, 8, false );
    if(passos < 10)
        desvio = 23;
    else if(passos<100)
        desvio = 20;
    else if(passos<1000)
        desvio = 15;
    else
        desvio = 10;
    putText((*imagem), peso, Point(desvio,8*passo2 -10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1, 8, false );
}

void PlanejaRota::execute(Robotino *robotino)
{
    float pos[6][6][4];
    int i, j,k;
    for(i = 0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            for(k=0;k<4;k++)
            {
                pos[i][j][k] = 0;
            }
        }
    }

    Mat imagem(Size(600,300),CV_8UC3);

    desenha_grid(&imagem,pos, 1, 0);

    imshow("grid",imagem);
    waitKey(0);
}

void PlanejaRota::exit(Robotino *robotino) {}
