#ifndef MYCAMERA_HPP
#define MYCAMERA_HPP

#include "rec/robotino/com/all.h"
#include "rec/robotino/com/Camera.h"
#include "robotino.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

//#include "rec/robotino/com/c/Camera.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

//using namespace cv;

using namespace rec::robotino::com;
using namespace std;
using namespace cv;

template <class owner_t> class MyCamera2:public Camera{
public:
    MyCamera2(owner_t *robo){
        this->meuRobo = robo;
    }

   virtual void imageReceivedEvent (const unsigned char *data, unsigned int dataSize, unsigned int width, unsigned int height, unsigned int numChannels, unsigned int bitsPerChannel, unsigned int step)
   {
        //f(this->isStreaming())
            //{
            if(dataSize > 0 && width> 0 && height>0)
            {
                Mat mostra(height,width,CV_8UC3);

                int i,j,k;
                uchar *p;
                for(int i = 0,k=0; i<height;i++ )
                {
                    p = mostra.ptr<uchar>(i);
                    for(j=0;j<width*numChannels;j+=numChannels,k+=numChannels)
                    {
                        p[j] = data[k+2];
                        p[j+1] = data[k+1];
                        p[j+2] = data[k];
                    }
                }
                imshow("mostra",mostra);
               //Mat mostra(height,width,CV_8UC3,dados);

               //Mat decodedImage  =  cv::imdecode(mostra ,CV_LOAD_IMAGE_COLOR);
                //imshow("mostra",decodedImage);
                //waitKey(1);
                cout<<dataSize<<"    "<<width<<"   "<<height<<endl;
                cout<<"imagem hehehe"<<endl;
            }
        //}
   }
    /*
    virtual void jpgReceivedEvent( const unsigned char* jpgData,
                                  unsigned int jpgDataSize ){
        //unsigned int width, height;

        //unsigned char *data=new unsigned char[jpgDataSize];
        //strcpy((char *)data,(const char *)jpgData);
        //this->resolution(&width,&height);
        //std::cout << "Imagem recebida\n";
        //cv::Mat rawData  =  cv::Mat( 1, jpgDataSize, CV_8UC3, data );
        //cv::Mat decodedImage  =  cv::imdecode(rawData ,CV_LOAD_IMAGE_COLOR);
        //cv::Mat img = cv::Mat(,CV_8UC3,data);
        //cv::Mat img = imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
        //cv::Mat img = cv::Mat(width,height,CV_8UC3,data);
        //cv::imshow("Original", img);
        std::ofstream myfile;
        myfile.open("temp.jpg");
        for (int i = 0; i < jpgDataSize; ++i)
        {
            myfile << jpgData[i];
        }
        //cv::Mat test = cv::imread("temp2.jpg",CV_LOAD_IMAGE_COLOR);
        //cv::imshow("Cu",test);
        //cv::waitKey(1);
        //std::cout << test << "\n";
        //std::cout << "\n-------------------------------------\n\n";

        //this->meuRobo->setImage(test);

        //std::cout << "Data SIze " << jpgDataSize << " WIdht " << width << " height " << height << "\n";
    */
private:
    owner_t * meuRobo;
};




#endif              /* MYCAMERA_HPP */
