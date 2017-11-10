#include "identificarcor.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"
#include "Segmento.hpp"



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

IdentificarCor  *IdentificarCor::instance()
{
    static IdentificarCor  IdentificarCorStateInstance;
    return &IdentificarCorStateInstance;
}

IdentificarCor::IdentificarCor() {}

IdentificarCor::~IdentificarCor() {}

void IdentificarCor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}

string intToString(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

/*
void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,intToString(theObjects.at(i).getXPos())+ " , " + intToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}
*/

void drawObject(vector<Object> theObjects,Mat &frame, vector<Segmento > segmentos){

    for(int i =0; i<theObjects.size(); i++){
        rectangle(frame, segmentos[i].inicio, segmentos[i].fim,theObjects.at(i).getColor());
        cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
        cv::putText(frame,intToString(theObjects.at(i).getXPos())+ " , " + intToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
        cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}


void segmenta(Mat src, vector<Segmento> *objetos)
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

bool trackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

    vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);
    vector<Segmento> segmentos;
    segmentos.clear();
    segmenta(temp,&segmentos);


    double refArea = 0;
    bool objectFound = false;



    if(theObject.getType() == "red"){
        robotino->objetosVermelhos.clear() ;
    }else if(theObject.getType() == "blue"){
        robotino->objetosAzuis.clear() ;
    }else if(theObject.getType() == "yellow"){
        robotino->objetosAmarelos.clear() ;
    }

    if (segmentos.size() > 0) {
        int numObjects = segmentos.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            objectFound = false;
            for (int index = 0; index < numObjects; index++) {

                double area = segmentos[index].num_pontos;

        //if the area is less than 20 px by 20px then it is probably just noise
        //if the area is the same as the 3/2 of the image size, probably just a bad filter
        //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA){

                    Object object;

                    //segmentos[index].calc_centro();


                    object.setXPos(segmentos[index].centroX());
                    object.setYPos(segmentos[index].centroY());
                    object.setType(theObject.getType());
                    object.setColor(theObject.getColor());
                    object.setHSVmin(theObject.getHSVmin());
                    object.setHSVmax(theObject.getHSVmax());

                    objects.push_back(object);

                    objectFound = true;

                    if(theObject.getType() == "red"){
                        robotino->objetosVermelhos.push_back(object);
                    }else if(theObject.getType() == "blue"){
                        robotino->objetosAzuis.push_back(object);
                    }else if(theObject.getType() == "yellow"){
                        robotino->objetosAmarelos.push_back(object);
                    }
                }
            }

            #ifdef DEBUG
            //let user know you found an object
            if(objectFound ==true){
                //draw object location on screen
                drawObject(objects,cameraFeed,segmentos);

            }
            #endif

        }
        #ifdef DEBUG
        else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
        #endif
    }
    return objectFound;
}


void ApagaLinhas(Mat src,Mat *dst)
{
    vector<Mat> channels;
    split(src,channels);

    int erode_size = 3;
    Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));
    Mat dlement = getStructuringElement( MORPH_ELLIPSE,Size(2*erode_size+1,2*erode_size+1));
    Mat temp;

    //apaga manchas brancas
    erode(channels[0],channels[0],element);
    dilate(channels[0],channels[0],element);

    dilate(channels[0],channels[0],element);
    dilate(channels[0],channels[0],element);

    channels[0](Rect(0,src.rows/2,src.cols,src.rows-src.rows/2 ) ).copyTo(temp);
    dilate(temp,temp,element);
    dilate(temp,temp,element);
    Mat Roi(channels[0], Rect(0, src.rows/2, temp.cols, temp.rows));
    temp.copyTo(Roi);
    channels[0](Rect(0,3*src.rows/4,src.cols,src.rows-3*src.rows/4)).copyTo(temp);
    dilate(temp,temp,element);
    dilate(temp,temp,element);
    Mat Roi2(channels[0], Rect(0, 3*src.rows/4, temp.cols, temp.rows));
    temp.copyTo(Roi2);


    erode(channels[0],channels[0],element);
    erode(channels[0],channels[0],element);

    channels[0](Rect(0,src.rows/2,src.cols,src.rows-src.rows/2 ) ).copyTo(temp);
    erode(temp,temp,element);
    erode(temp,temp,element);
    temp.copyTo(Roi);
    channels[0](Rect(0,3*src.rows/4,src.cols,src.rows-3*src.rows/4)).copyTo(temp);
    erode(temp,temp,element);
    erode(temp,temp,element);
    temp.copyTo(Roi2);

    merge(channels, *dst);


    //erode(temp,temp,element);
    //erode(temp,temp,element);
    //erode(temp,temp,element);
    /*
    for(i=0;i+2*erode_size<src.rows;i+=2*erode_size-2)
    {
        Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));
        Mat temp = channels[0](Rect(0,i,src.cols,2*erode_size+1));
        dilate(temp,temp,element);
        cont++;
        if(cont>5)
        {
            erode_size++;
            cont = 0;
        }
    }
    */

}



void FiltraAzul(Mat src, Mat *dst)
{

vector<Mat> channels;

static bool filtrou = false;

static int Tabela[256][256][256];
static float Y[256];
static float Cr[256];
static float Cb[256];

static int minYo = 20;
static int maxYo = 85;
static int minCro = 115;
static int maxCro = 129;
static int minCbo = 127;
static int maxCbo = 150;

static int minY = 10;
static int maxY = 120;
static int minCr = 100;
static int maxCr = 135;
static int minCb = 80;
static int maxCb = 180;

static int minAceita = 200;
static int erode_size = 3;

namedWindow("Ajuste");
createTrackbar("minY","Ajuste",&minY,256);
createTrackbar("minYo","Ajuste",&minYo,256);
createTrackbar("maxY","Ajuste",&maxY,256);
createTrackbar("maxYo","Ajuste",&maxYo,256);

createTrackbar("minCr","Ajuste",&minCr,256);
createTrackbar("minCro","Ajuste",&minCro,256);
createTrackbar("maxCr","Ajuste",&maxCr,256);
createTrackbar("maxCro","Ajuste",&maxCro,256);

namedWindow("Ajuste2");
createTrackbar("minCb","Ajuste2",&minCb,256);
createTrackbar("minCbo","Ajuste2",&minCbo,256);
createTrackbar("maxCb","Ajuste2",&maxCb,256);
createTrackbar("maxCbo","Ajuste2",&maxCbo,256);
createTrackbar("minAceita","Ajuste2",&minAceita,256);
createTrackbar("esize","Ajuste2",&erode_size,10);

Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));

char comando = waitKey(1);
if(comando == 'a')
{
    filtrou = false;
}


if(!filtrou)
{
    cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa"<<endl<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa"<<endl;
    filtrou = true;
    filtrou = true;
    int i, j, k;
    float incremento;
    float valor;

    //Preenche tabela de cor
    //Filtro da Luminancia
    for(i = 0; i<minY; i++){
        Y[i] = 0;
    }
    incremento = (1.0 )/(float)(minYo - minY);
    valor = 0;
    for( i = minY; i<minYo; i++){
        valor += incremento;
        Y[i] = valor;
    }
    for(i = minYo ; i<maxYo; i++){
        Y[i] = 1;
    }
    valor = 1;
    incremento = (1.0 )/(float)(maxYo - maxY);
    for(i = maxYo; i<maxY; i++){
        valor += incremento;
        Y[i] = valor;
    }
    for(i = maxY; i<256; i++){
        Y[i] = 0;
    }

    for(i = 0; i<minCr; i++){
        Cr[i] = 0;
    }
    incremento = (1.0 )/(float)(minCro - minCr);
    valor = 0;

    for( i = minCr; i<minCro; i++){
        valor += incremento;
        Cr[i] = valor;
    }
    for(i = minCro ; i<maxCro; i++){
        Cr[i] = 1;
    }
    valor = 1;
    incremento = (1.0 )/(float)(maxCro - maxCr);
    for(i = maxCro; i<maxCr; i++){
        valor += incremento;
        Cr[i] = valor;
    }
    for(i = maxCr; i<256; i++){
        Cr[i] = 0;
    }


    //Filtro do Value
    for(i = 0; i<minCb; i++){
        Cb[i] = 0;
    }

    incremento = (1.0  )/(float)(minCbo - minCb);
    valor = 0;

    for( i = minCb; i<minCbo; i++){
        valor += incremento;
        Cb[i] = valor;
    }
    for(i = minCbo ; i<maxCbo; i++){
        Cb[i] = 1;
    }
    valor = 1;
    incremento = (1.0 )/(float)(maxCbo - maxCb);
    for(i = maxCbo; i<maxCb; i++){
        valor += incremento;
        Cb[i] = valor;
    }
    for(i = maxCb; i<256; i++){
        Cb[i] = 0;
    }


    for(k = 0; k<256; k++){
        for(i = 0; i<256; i++){
            for(j = 0; j<256; j++){
                Tabela[i][j][k] = (uchar) 255*Y[i]*Cr[j]*Cb[k];
            }
        }
    }

}


Mat threshY(src.size(),CV_8UC1);
threshY = Scalar(0);
Mat threshCr(src.size(),CV_8UC1);
threshCr = Scalar(0);
Mat threshCb(src.size(),CV_8UC1);
threshCb = Scalar(0);



Mat temp;
channels.clear();
split(src,channels);

erode(channels[2],channels[2],element);
//imshow("erodeCb",channels[2]);
//blur(channels[2],channels[2],Size(5,5));
//imshow("blurCb",channels[2]);
dilate(channels[2],channels[2],element);
//imshow("edCb",channels[2]);

dilate(channels[1],channels[1],element);
//imshow("dilateCr",channels[1]);
//blur(channels[1],channels[1],Size(5,5));
//imshow("blurCr",channels[1]);
erode(channels[1],channels[1],element);
 //imshow("deCr",channels[1]);

erode(channels[0],channels[0],element);
dilate(channels[0],channels[0],element);

dilate(channels[0],channels[0],element);
dilate(channels[0],channels[0],element);
dilate(channels[0],channels[0],element);
erode(channels[0],channels[0],element);
erode(channels[0],channels[0],element);
erode(channels[0],channels[0],element);
imshow("hehehe",channels[0]);

//imshow("erodeCb",channels[2]);

merge(channels,temp);

uchar *p;
uchar *p2;

uchar *p3;
uchar *p4;
uchar *p5;

int i, j, k;
for(i=0;i<src.rows;i++)
{
    p = temp.ptr<uchar>(i);
    p2 = dst->ptr<uchar>(i);

    p3 = threshY.ptr<uchar>(i);
    p4 = threshCr.ptr<uchar>(i);
    p5 = threshCb.ptr<uchar>(i);
    for(j=0,k=0;j<src.cols;j++,k+=3)
    {
        p2[j] =  Tabela[p[k] ][p[k+1]  ][p[k+2] ];

        p3[j] = 255*Y[p[k]];
        p4[j] = 255*Cr[p[k+1]];
        p5[j] = 255*Cb[p[k+2]];

    }
}

imshow("Fuzzy azul",*dst);
imshow("threshY",threshY);
imshow("threshCr",threshCr);
imshow("threshCb",threshCb);


blur(*dst,temp,Size(9,9));
imshow("blur",temp);

threshold(temp,temp,minAceita,255,THRESH_BINARY);
imshow("thresh",temp);

Mat element2 = getStructuringElement( MORPH_RECT,Size(3,3));
erode(temp,temp,element2);
dilate(temp,temp,element);
imshow("mask",temp);



/*



static int alphaY = 100;
static int alphaCr = 100;
static int alphaCb = 100;
static int betaY = 0;
static int betaCr  = 0;
static int betaCb = 0;

Mat temp(src.size(),CV_8UC3);
namedWindow("Ajuste");
createTrackbar("alphaY","Ajuste",&alphaY,2000);
createTrackbar("alphaCr","Ajuste",&alphaCr,2000);
createTrackbar("alphaCb","Ajuste",&alphaCb,2000);
createTrackbar("betaY","Ajuste",&betaY,255);
createTrackbar("betaCr","Ajuste",&betaCr,255);
createTrackbar("betaCb","Ajuste",&betaCb,255);



double alphay = (double)alphaY/100.0;
double alphacr = (double)alphaCr/100.0;
double alphacb = (double)alphaCb/100.0;

for( int y = 0; y < src.rows; y++ )
{
    for( int x = 0; x < src.cols; x++ )
    {
        temp.at<Vec3b>(y,x)[0] = saturate_cast<uchar>( alphay*( src.at<Vec3b>(y,x)[0] ) + betaY );
        temp.at<Vec3b>(y,x)[1] = saturate_cast<uchar>( alphacr*( src.at<Vec3b>(y,x)[1] ) + betaCr );
        temp.at<Vec3b>(y,x)[2] = saturate_cast<uchar>( alphacb*( src.at<Vec3b>(y,x)[2] ) + betaCb );
    }
}

imshow("temp",temp);

    split(temp,channels);
    //imshow("Y",channels[0]);
    //imshow("Cr",channels[1]);
    //imshow("Cb",channels[2]);

    static int erode_size = 9;

    static Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));

    erode(channels[2],channels[2],element);
    //imshow("erodeCb",channels[2]);
    blur(channels[2],channels[2],Size(5,5));
    //imshow("blurCb",channels[2]);
    dilate(channels[2],channels[2],element);
    //imshow("edCb",channels[2]);

    dilate(channels[1],channels[1],element);
    //imshow("dilateCr",channels[1]);
    blur(channels[1],channels[1],Size(5,5));
    //imshow("blurCr",channels[1]);
    erode(channels[1],channels[1],element);
    //imshow("deCr",channels[1]);

    erode(channels[0],channels[0],element);
    //imshow("erodeCb",channels[2]);


    //imshow("edCb",channels[2]);



    merge(channels, *dst);
*/
}



void IdentificarCor::execute(Robotino *robotino)
{

    static struct timeval t0, t1;
    static bool init = false;
    int tempo = 0;
    //robotino->newImage = false;
    //Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    Mat temp;
    //static Mat threshold;
    //static Mat thresholdr1;
    //static Mat thresholdr2;


    static int erode_size = 3;
    static int dilate_size = 3;
    static Mat element = getStructuringElement( MORPH_RECT,Size(2*erode_size+1,2*erode_size+1));
    static Mat dlement = getStructuringElement( MORPH_RECT,Size(2*dilate_size+1,2*dilate_size+1));

    //cv::waitKey();


    //gettimeofday(&t0,NULL);
    cameraFeed = robotino->getImage();

    static Mat YCrCb;
    static Mat Y(cameraFeed.size(),CV_8UC1);
    static Mat B(cameraFeed.size(),CV_8UC1);
    static Mat R(cameraFeed.size(),CV_8UC1);
    static Mat src;

    static int minY = 40;
    static int maxY = 115;
    static int minCr = 140;
    static int maxCr = 175;
    static int minCb = 140;
    static int maxCb = 160;


    namedWindow("painel");
    createTrackbar("minY","painel",&minY,256);
    createTrackbar("maxY","painel",&maxY,256);
    createTrackbar("minCr","painel",&minCr,256);
    createTrackbar("maxCr","painel",&maxCr,256);
    createTrackbar("minCb","painel",&minCb,256);
    createTrackbar("maxCb","painel",&maxCb,256);


    if(!init){
        gettimeofday(&t0,NULL);
        init = true;
    }
    gettimeofday(&t1,NULL);
    tempo = ( 1000000*(t1.tv_sec-t0.tv_sec)+(t1.tv_usec-t0.tv_usec)   );
    cout<<"TEMPO:  "<<tempo<<endl;
    gettimeofday(&t0,NULL);

    //Reduz tamanho da imagem para filtrar e diminuir tempo de processamento

    imshow("Original", cameraFeed);


    //resize(cameraFeed,cameraFeed,(Size(160,115)));


    if(true)
    {

        //create some temp fruit objects so that
        //we can use their member functions/information
        Object blue("blue"), yellow("yellow"), red("red"), black("black");
        bool azul, amarelo, vermelho, preto;

        Mat temp;
        vector<Mat> channels;

//TESTE1 AQUI
/*
        erode(cameraFeed,temp,element);
        erode(temp,temp,element);
        dilate(temp,temp,dlement);
        dilate(temp,temp,dlement);
        imshow("cor",temp);
*/



//Teste2 AQUI

        cvtColor(cameraFeed,temp,CV_BGR2HSV);
        split(temp,channels);
        imshow("H",channels[0]);
        imshow("S",channels[1]);
        imshow("V",channels[2]);


        //cvtColor(temp,YCrCb,COLOR_BGR2Lab);

        cvtColor(cameraFeed,YCrCb,COLOR_BGR2Lab);
        //imshow("YCrCb",YCrCb);





        channels.clear();
        split(YCrCb,channels);

        imshow("L",channels[0]);
        imshow("a",channels[1]);
        imshow("b",channels[2]);


        inRange(YCrCb,yellow.getHSVmin(),yellow.getHSVmax(),Y);

        //inRange(YCrCb,Scalar(minY,minCr,minCb),Scalar(maxY,maxCr,maxCb),Y);
        imshow("amarelo",Y);
/*
        inRange(channels[0],Scalar(minY),Scalar(maxY),channels[0]);
        imshow("rangeY",channels[0]);
        inRange(channels[1],Scalar(minCr),Scalar(maxCr),channels[1]);
        imshow("rangeCr",channels[1]);
        inRange(channels[2],Scalar(minCb),Scalar(maxCb),channels[2]);
        imshow("rangeCb",channels[2]);
    */

        erode(Y,Y,element);
        dilate(Y,Y,dlement);
        dilate(Y,Y,dlement);
        imshow("amarelofim",Y);
        amarelo = trackFilteredObject(yellow,Y,YCrCb,cameraFeed, robotino);
        /*if (amarelo>0){
            robotino->lightLed(Robotino::LED_AMARELO, 1);
        }
        else{
            robotino->lightLed(Robotino::LED_AMARELO, 0);
        }*/
        //then reds
        //cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
        inRange(YCrCb,red.getHSVmin(),red.getHSVmax(),R);

        //inRange(YCrCb,Scalar(minY,minCr,minCb),Scalar(maxY,maxCr,maxCb),R);

        /*
        inRange(channels[0],Scalar(minY),Scalar(maxY),channels[0]);
        imshow("rangeY",channels[0]);
        inRange(channels[1],Scalar(minCr),Scalar(maxCr),channels[1]);
        imshow("rangeCr",channels[1]);
        inRange(channels[2],Scalar(minCb),Scalar(maxCb),channels[2]);
        imshow("rangeCb",channels[2]);
    */
        //inRange(YCrCb,Scalar(minY,minCr,minCb),Scalar(maxY,maxCr,maxCb),R);
        erode(R,R,element);
        dilate(R,R,dlement);
        dilate(R,R,dlement);
        vermelho = trackFilteredObject(red,R,YCrCb,cameraFeed, robotino);


        inRange(YCrCb,blue.getHSVmin(),blue.getHSVmax(),B);
        //inRange(YCrCb,Scalar(minY,minCr,minCb),Scalar(maxY,maxCr,maxCb),B);
        //imshow("rangeVerde",B);
        erode(B,B,element);
        dilate(B,B,dlement);
        dilate(B,B,dlement);
        //imshow("verde2",B);

       /*
        inRange(channels[0],Scalar(minY),Scalar(maxY),channels[0]);
        imshow("rangeY",channels[0]);
        inRange(channels[1],Scalar(minCr),Scalar(maxCr),channels[1]);
        imshow("rangeCr",channels[1]);
        inRange(channels[2],Scalar(minCb),Scalar(maxCb),channels[2]);
        imshow("rangeCb",channels[2]);
        */
        azul = trackFilteredObject(blue,B,YCrCb,cameraFeed, robotino);



        #ifdef DEBUG
        if (azul)
            cout << "Azul: " << robotino->objetosAzuis.size() << endl;
         if (amarelo)
            cout << "Amarelo: " << robotino->objetosAmarelos.size() << endl;
         if (vermelho)
            cout << "Vermelho: " << robotino->objetosVermelhos.size() << endl;
        //if (preto)
           // cout << "Preto: " << robotino->objetosPretos.size() << endl;

        imshow("discos",cameraFeed);
        cvMoveWindow("discos",500,300);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(1);
        #endif
        //robotino->definirObjetoAlvo(Robotino::AZUL);

        //robotino->change_state(SeguirCor::instance());
    }

    robotino->change_state(robotino->previous_state());

}

void IdentificarCor::exit(Robotino *robotino) {}
