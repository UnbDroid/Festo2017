#include "identificarcor2.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

#include "opencv2/core/core.hpp"
#include <vector>


//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 10*10;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";


//*****************************************************************************************************************
// IdentificarCor
//*****************************************************************************************************************

IdentificarCor2  *IdentificarCor2::instance()
{
    static IdentificarCor2  IdentificarCorStateInstance;
    return &IdentificarCorStateInstance;
}

IdentificarCor2::IdentificarCor2() {}

IdentificarCor2::~IdentificarCor2() {}

void IdentificarCor2::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}

string IdentificarCor2::intToString(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void IdentificarCor2::drawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,intToString(theObjects.at(i).getXPos())+ " , " + intToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}

/*
void morphOps(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(17,17));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);

   // imshow("morph2",thresh);
   // waitKey(1);
}
*/
bool IdentificarCor2::trackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

    vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;

    if(theObject.getType() == "red"){
        robotino->objetosVermelhos.clear() ;
    }else if(theObject.getType() == "blue"){
        robotino->objetosAzuis.clear() ;
    }else if(theObject.getType() == "yellow"){
        robotino->objetosAmarelos.clear() ;
    }



    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            cout<<numObjects<<endl;
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

        //if the area is less than 20 px by 20px then it is probably just noise
        //if the area is the same as the 3/2 of the image size, probably just a bad filter
        //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                cout<<area<<endl;
                if(area>MIN_OBJECT_AREA){

                    Object object;

                    object.setXPos(moment.m10/area);
                    object.setYPos(moment.m01/area);
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

                }else objectFound = false;
            }
            //let user know you found an object
            if(objectFound ==true){
                //draw object location on screen
                drawObject(objects,cameraFeed,temp,contours,hierarchy);

            }

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
    return objectFound;
}


void IdentificarCor2::execute(Robotino *robotino)
{
    //Matrix to store each frame of the webcam feed
    static Mat src;

    static int erode_size = 2;

    static int minYB = 20;
    static int maxYB = 85;
    static int minCrB = 100;
    static int maxCrB = 125;
    static int minCbB = 125;
    static int maxCbB = 170;

    static int minYG = 0;
    static int maxYG = 100;
    static int minCrG = 110;
    static int maxCrG = 140;
    static int minCbG = 110;
    static int maxCbG = 140;

    static int minYR = 20;
    static int maxYR = 100;
    static int minCrR = 145;
    static int maxCrR = 170;
    static int minCbR = 100;
    static int maxCbR = 120;

    static int minYY = 100;
    static int maxYY = 165;
    static int minCrY = 140;
    static int maxCrY = 170;
    static int minCbY = 0;
    static int maxCbY = 95;

    /*
    namedWindow("Painel1");
    createTrackbar("minYR","Painel1",&minYR,256);
    createTrackbar("maxYR","Painel1",&maxYR,256);
    createTrackbar("minCrR","Painel1",&minCrR,256);
    createTrackbar("maxCrR","Painel1",&maxCrR,256);
    createTrackbar("minCbR","Painel1",&minCbR,256);
    createTrackbar("maxCbR","Painel1",&maxCbR,256);


    namedWindow("Painel2");
    createTrackbar("minYB","Painel2",&minYB,256);
    createTrackbar("maxYB","Painel2",&maxYB,256);
    createTrackbar("minCrB","Painel2",&minCrB,256);
    createTrackbar("maxCrB","Painel2",&maxCrB,256);
    createTrackbar("minCbB","Painel2",&minCbB,256);
    createTrackbar("maxCbB","Painel2",&maxCbB,256);
    createTrackbar("erode","Painel2",&erode_size,20);

    namedWindow("Painel3");
    createTrackbar("minYY","Painel3",&minYY,256);
    createTrackbar("maxYY","Painel3",&maxYY,256);
    createTrackbar("minCrY","Painel3",&minCrY,256);
    createTrackbar("maxCrY","Painel3",&maxCrY,256);
    createTrackbar("minCbY","Painel3",&minCbY,256);
    createTrackbar("maxCbY","Painel3",&maxCbY,256);
    */

    src = robotino->getImage();
    //imshow("BGR",src);

    Object blue("blue"), yellow("yellow"), red("red"), black("black");
    bool azul, amarelo, vermelho, preto;


    Mat temp;
    Mat B,R,Y;
    Mat element = getStructuringElement( MORPH_CROSS,Size(2*erode_size+1,2*erode_size+1));
    Mat dlement = getStructuringElement( MORPH_ELLIPSE,Size(2*erode_size+1,2*erode_size+1));

//Mudança de espaço de cor para YCrCb
cvtColor(src,temp,CV_BGR2YCrCb);
//Mostra partes
/*
    vector<Mat> ycrcb(3);
    split(temp,ycrcb);
    imshow("Y",ycrcb[0]);
    imshow("Cr",ycrcb[1]);
    imshow("Cb",ycrcb[2]);

    inRange(ycrcb[0],Scalar(minYB),Scalar(maxYB),temp);
    imshow("BlueY",temp);
    inRange(ycrcb[1],Scalar(minCrB),Scalar(maxCrB),temp);
    imshow("BlueCr",temp);
    inRange(ycrcb[2],Scalar(minCbB),Scalar(maxCbB),temp);
    imshow("BlueCb",temp);

    merge(ycrcb,temp);
*/



    inRange(temp,Scalar(minYB,minCrB,minCbB),Scalar(maxYB,maxCrB,maxCbB),B);
    imshow("Blue",B);
    erode(B,B,element);
    dilate(B,B,dlement);
    imshow("blueFim",B);
    azul = trackFilteredObject(blue,B,temp,src, robotino);

    inRange(temp,Scalar(minYR,minCrR,minCbR),Scalar(maxYR,maxCrR,maxCbR),R);
    imshow("Red",R);
    erode(R,R,element);
    dilate(R,R,dlement);
    imshow("RedFim",R);
    vermelho = trackFilteredObject(red,R,temp,src, robotino);

    inRange(temp,Scalar(minYY,minCrY,minCbY),Scalar(maxYY,maxCrY,maxCbY),Y);
    imshow("Yellow",Y);
    amarelo = trackFilteredObject(yellow,Y,temp,src, robotino);

    //then blacks
    // cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    // inRange(HSV,black.getHSVmin(),black.getHSVmax(),threshold);
    // morphOpsBlack(threshold);
    // preto = trackFilteredObject(black,threshold,HSV,cameraFeed, robotino);


    if (azul)
        cout << "Azul: " << robotino->objetosAzuis.size() << endl;
     if (amarelo)
        cout << "Amarelo: " << robotino->objetosAmarelos.size() << endl;
     if (vermelho)
        cout << "Vermelho: " << robotino->objetosVermelhos.size() << endl;
    //if (preto)
       // cout << "Preto: " << robotino->objetosPretos.size() << endl;

    imshow("aqui",src);
    cvMoveWindow("aqui",500,300);
    //imshow(windowName1,HSV);

    //delay 30ms so that screen can refresh.
    //image will not appear without this waitKey() command
    waitKey(1);

    //robotino->definirObjetoAlvo(Robotino::AZUL);

    //robotino->change_state(SeguirCor::instance());

    robotino->change_state(robotino->previous_state());
}

void IdentificarCor2::exit(Robotino *robotino) {}
