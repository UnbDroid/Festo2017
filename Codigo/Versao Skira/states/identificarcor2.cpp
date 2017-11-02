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
const int MIN_OBJECT_AREA = 20*20;
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
/*
string intToString(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,intToString(theObjects.at(i).getXPos())+ " , " + intToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}

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

bool trackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

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
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

        //if the area is less than 20 px by 20px then it is probably just noise
        //if the area is the same as the 3/2 of the image size, probably just a bad filter
        //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
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

*/
void IdentificarCor2::execute(Robotino *robotino)
{
    //Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    static Mat threshold;
    static Mat threshold1;
    static Mat threshold2;

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

    //cv::waitKey();



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



    cameraFeed = robotino->getImage();
    src = cameraFeed;

    imshow("BGR",src);

    Mat temp;

    Mat element = getStructuringElement( MORPH_CROSS,Size(2*erode_size+1,2*erode_size+1));
    //dilate(src,temp,element);
    //imshow("dilate",temp);
    //medianBlur(temp,temp,3);
    //imshow("median",temp);
    //erode(temp,temp,element);
    //imshow("erode",temp);

    //convert frame from BGR to HSV colorspace
    /*
    vector<Mat> lab(3);
    vector<Mat> hsv(3);
    cvtColor(src,temp,CV_BGR2Lab);
    split(temp,lab);
    imshow("L",lab[0]);
    imshow("a",lab[1]);
    imshow("b",lab[2]);
    cvtColor(src,temp,CV_BGR2HSV);
    split(temp,hsv);
    imshow("H",hsv[0]);
    imshow("S",hsv[1]);
    imshow("V",hsv[2]);


    erode(lab[1],lab[1],element);
    imshow("erodeA",lab[1]);
    GaussianBlur(lab[2],lab[2],Size(3,3),3,3,1 );
    imshow("gaussianB",lab[2]);
    equalizeHist(lab[0],lab[0]);
    imshow("eqL",lab[0]);
    */

//Mudança de espaço de cor para YCrCb
    cvtColor(src,temp,CV_BGR2YCrCb);

    vector<Mat> ycrcb(3);
    split(temp,ycrcb);
    imshow("Y",ycrcb[0]);
    imshow("Cr",ycrcb[1]);
    imshow("Cb",ycrcb[2]);
//Filtragem
    /*
    erode(ycrcb[0],ycrcb[0],element);
    imshow("erodeY",ycrcb[0]);
    dilate(ycrcb[0],ycrcb[0],element);
    imshow("erode_dilateY",ycrcb[0]);
    medianBlur(ycrcb[1],ycrcb[1],3);
    imshow("medianCr",ycrcb[1]);
    medianBlur(ycrcb[2],ycrcb[2],3);
    imshow("medianCb",ycrcb[2]);
    */
    /*
    erode(ycrcb[1],ycrcb[1],element);
    imshow("erodeCr",ycrcb[1]);
    dilate(ycrcb[1],ycrcb[1],element);
    imshow("erode_dilateCr",ycrcb[1]);
    erode(ycrcb[2],ycrcb[2],element);
    imshow("erodeCb",ycrcb[2]);
    dilate(ycrcb[2],ycrcb[2],element);
    imshow("erode_dilateCb",ycrcb[2]);
    */
    /*
    GaussianBlur(ycrcb[1],ycrcb[1],Size(3,3),3,3,1);
    imshow("GaussianCr",ycrcb[1]);
    GaussianBlur(ycrcb[2],ycrcb[2],Size(3,3),3,3,1);
    imshow("GaussianCb",ycrcb[2]);
    */


    /*
    erode(temp,temp,element);
    medianBlur(temp,temp,3);
    dilate(temp,temp,element);
    imshow("Filtro",temp);
    ycrcb.clear();
    split(temp,ycrcb);
    */



    inRange(ycrcb[0],Scalar(minYB),Scalar(maxYB),temp);
    imshow("BlueY",temp);
    inRange(ycrcb[1],Scalar(minCrB),Scalar(maxCrB),temp);
    imshow("BlueCr",temp);
    inRange(ycrcb[2],Scalar(minCbB),Scalar(maxCbB),temp);
    imshow("BlueCb",temp);

    merge(ycrcb,temp);
    imshow("NovoYCrCb",temp);



    Mat B,R,Y;
    inRange(temp,Scalar(minYB,minCrB,minCbB),Scalar(maxYB,maxCrB,maxCbB),B);
    imshow("Blue",B);

    inRange(temp,Scalar(minYR,minCrR,minCbR),Scalar(maxYR,maxCrR,maxCbR),R);
    imshow("Red",R);

    inRange(temp,Scalar(minYY,minCrY,minCbY),Scalar(maxYY,maxCrY,maxCbY),Y);
    imshow("Yellow",Y);

    erode(B,B,element);
    dilate(B,B,element);
    imshow("blueFim",B);

    erode(R,R,element);
    dilate(R,R,element);
    imshow("RedFim",R);

    /*
    erode(,temp,element);
    erode(temp,temp,element);
    dilate(temp,temp,element);
    dilate(temp,temp,element);
    cvtColor(temp,temp,CV_Lab2BGR);
    imshow("erodeLab",temp);
    */


    waitKey(1);

    /*
    //create some temp fruit objects so that
    //we can use their member functions/information
    Object blue("blue"), yellow("yellow"), red("red"), black("black");
    bool azul, amarelo, vermelho, preto;

    //first find blue objects
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,blue.getHSVmin(),blue.getHSVmax(),threshold);
    morphOps(threshold);
    azul = trackFilteredObject(blue,threshold,HSV,cameraFeed, robotino);
    //then yellows
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,yellow.getHSVmin(),yellow.getHSVmax(),threshold);
    morphOps(threshold);
    amarelo = trackFilteredObject(yellow,threshold,HSV,cameraFeed, robotino);
    //then reds
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,red.getHSVmin(),red.getHSVmax(),thresholdr1);
    inRange(HSV,Scalar(0,120,0),Scalar(8,255,255),thresholdr2);
    bitwise_or(thresholdr1,thresholdr2, threshold);
    morphOps(threshold);
    vermelho = trackFilteredObject(red,threshold,HSV,cameraFeed, robotino);

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

    imshow(windowName,cameraFeed);
    cvMoveWindow(windowName.c_str(),500,300);
    //imshow(windowName1,HSV);

    //delay 30ms so that screen can refresh.
    //image will not appear without this waitKey() command
    waitKey(1);

    //robotino->definirObjetoAlvo(Robotino::AZUL);

    //robotino->change_state(SeguirCor::instance());
    */
    robotino->change_state(robotino->previous_state());
}

void IdentificarCor2::exit(Robotino *robotino) {}
