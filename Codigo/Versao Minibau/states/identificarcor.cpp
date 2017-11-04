#include "identificarcor.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 8*8;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";


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


void IdentificarCor::execute(Robotino *robotino)
{
    //Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    //static Mat threshold;
    //static Mat thresholdr1;
    //static Mat thresholdr2;
    static Mat YCrCb;
    static Mat Y,B,R;
    //static Mat src;

    static int erode_size = 2;
    static int dilate_size = 2;
    static Mat element = getStructuringElement( MORPH_CROSS,Size(2*erode_size+1,2*erode_size+1));
    static Mat dlement = getStructuringElement( MORPH_ELLIPSE,Size(2*dilate_size+1,2*dilate_size+1));

    //cv::waitKey();

    cameraFeed = robotino->getImage();
    //src = cameraFeed;

    //convert frame from BGR to HSV colorspace
    //cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);


    //create some temp fruit objects so that
    //we can use their member functions/information
    Object blue("blue"), yellow("yellow"), red("red"), black("black");
    bool azul, amarelo, vermelho, preto;

    cvtColor(cameraFeed,YCrCb,COLOR_BGR2YCrCb);

    //first find blue objects

    inRange(YCrCb,blue.getHSVmin(),blue.getHSVmax(),B);
    //morphOps(threshold);
    erode(B,B,element);
    dilate(B,B,dlement);
    imshow("blue",B);
    azul = trackFilteredObject(blue,B,YCrCb,cameraFeed, robotino);
    /*if (azul>0){
        robotino->lightLed(Robotino::LED_AZUL, 1);
    }
    else{
        robotino->lightLed(Robotino::LED_AZUL, 0);
    }*/
    //then yellows

    inRange(YCrCb,yellow.getHSVmin(),yellow.getHSVmax(),Y);
    //morphOps(threshold);
    imshow("yellow",Y);
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
    erode(R,R,element);
    dilate(R,R,dlement);
    imshow("red",R);
    //inRange(HSV,Scalar(0,120,0),Scalar(8,255,255),thresholdr2);
    //bitwise_or(thresholdr1,thresholdr2, threshold);
    //morphOps(threshold);
    vermelho = trackFilteredObject(red,R,YCrCb,cameraFeed, robotino);
    /*if (vermelho>0){
        robotino->lightLed(Robotino::LED_VERMELHO, 1);
    }
    else{
        robotino->lightLed(Robotino::LED_VERMELHO, 0);
    }*/

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
    robotino->change_state(robotino->previous_state());
}

void IdentificarCor::exit(Robotino *robotino) {}
