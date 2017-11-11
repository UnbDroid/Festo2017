#include "identificarcor.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"
#include "Segmento.hpp"



#include "LinhasVisao.hpp"

//default capture width and height
const int FRAME_WIDTH = 320;
const int FRAME_HEIGHT = 240;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";

using namespace cv;

//*****************************************************************************************************************
// IdentificarCor
//*****************************************************************************************************************

LinhasVisao *LinhasVisao::instance()
{
    static LinhasVisao  LinhasVisaoStateInstance;
    return &LinhasVisaoStateInstance;
}

LinhasVisao::LinhasVisao() {}

LinhasVisao::~LinhasVisao() {}

void LinhasVisao::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}


void segmentaVisao(Mat src, vector<Segmento> *objetos)
{
    Segmento segmento;
    Point ponto;
    int nRows = src.rows;
    int nCols = src.cols;
    //indices
    int i,j,l,m;
    //posicao pixel
    int x,y,x2,y2;

    int num_dir = 4;
    Point lados[4] = {Point(-1,0),Point(0,-1),Point(1,0),Point(0,1)};
    uchar *p;

    for(i=0;i<nRows;i++)
    {
        p=src.ptr<uchar>(i);
        for(j=0;j<nCols;j++)
        {
            if( p[j] > 120 )
            {
                segmento.clear();
                ponto = Point(j,i);
                segmento.addPoint(ponto);
                p[j] = 0;
                l=0;
                while(l<segmento.num_pontos)
                {
                    //posicao do ponto pertencente ao segmento
                    x = segmento.pontos[l].x;
                    y = segmento.pontos[l].y;
                    for(m=0;m<num_dir;m++)
                    {
                        //posicao do novo ponto
                        x2 = x+lados[m].x;
                        y2 = y+lados[m].y;
                        //ponto dentro da imagem
                        if(x2>=0&&y2>=0&&x2<nCols&&y2<nRows)
                        {
                            if(src.at<uchar>(Point(x2,y2)) > 120  )
                            {
                                segmento.addPoint(Point(x2,y2));
                                src.at<uchar>(Point(x2,y2)) = 0;
                            }
                        }
                    }
                    l++;
                }

                if(segmento.num_pontos > MIN_OBJECT_AREA && segmento.num_pontos <  MAX_OBJECT_AREA)
                 {
                    objetos->push_back(segmento);
                }

            }

        }
    }

}



void LinhasVisao::execute(Robotino *robotino)
{
    Mat src,temp;
    src = robotino->getImage();

    int min_Hough = 100, dist_Hough = 50;
    vector<Vec4i> lines;

    static int erode_size = 3;
    static int dilate_size = 3;
    static Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));
    static Mat dlement = getStructuringElement( MORPH_RECT,Size(2*dilate_size+1,2*dilate_size+1));

    imshow("src",src);
    cvtColor(src,temp,CV_BGR2GRAY);

    imshow("Gray",temp);


    erode(temp,temp,element);
    dilate(temp,temp,dlement);
    imshow("ed",temp);

    threshold(temp,temp,30,255,CV_THRESH_BINARY_INV);
    imshow("thresh",temp);

    vector<Segmento> segmentos;
    segmentaVisao(temp,&segmentos);



    for(int i = 0; i<segmentos.size();i++)
    {
        segmentos[i].calc_centro();
        circle(src,segmentos[i].centro,1,Scalar(0,255,0));
    }
    imshow("seg",src);

    /*
    double min_canny = 60;
    double max_canny = 180;
    Canny( temp, temp, min_canny, max_canny, 3 );
    convertScaleAbs(temp, temp);
    imshow("Canny",temp);

    HoughLinesP(temp, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( temp, temp, CV_GRAY2BGR );

    for( size_t i = 0; i < lines.size(); i++ ){
        line(temp,Point(lines[i][0],lines[i][1]),Point(lines[i][2],lines[i][3]),Scalar(0,0,255));
    }
    imshow("lines",temp);
    */
    //equalizeHist(temp,temp);
    //imshow("eq",temp);
    //threshold(temp,temp,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
    //imshow("otsu",temp);



    robotino->change_state(robotino->previous_state());

}

void LinhasVisao::exit(Robotino *robotino) {}
