#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <string>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    string imagedir = "/home/lab/Program/Program/test/1.jpg";
    cv::Mat srcImage = cv::imread(imagedir);
    if( srcImage.empty() )
    {
        cout <<"can't read this image!" <<"--->"
            <<imagedir <<endl;
        return -1;
    }

    int width = srcImage.cols;
    int heigh = srcImage.rows;
    srand( (unsigned)time( NULL ) );
//    int p1x = rand() % (width/2);
//    int p1y = rand() % (heigh/2);

//    int p2x = rand() % (width/2) + width/2;
//    int p2y = rand() % (heigh/2) + heigh/2;

//    vector< cv::Scalar > color = {cv::Scalar(255,255,0),
////                                 cv::Scalar(0,255,255),
//                                 cv::Scalar(255,0,255),
//                                 cv::Scalar(255,255,255),
////                                 cv::Scalar(255,0,0),
//                                 cv::Scalar(0,255,0),
////                                 cv::Scalar(0,0,255),
//                                 cv::Scalar(0,0,0)};

    cv::Mat dstImage;
//    cv::rectangle(srcImage,cv::Point(p1x,p1y),cv::Point(p2x,p2y),color[rand()%7],CV_FILLED);


    for(int i=0; i<100; i++){

//    int p1x = rand() % (width/4);
//    int p1y = rand() % (heigh/4) + heigh/4;

//    int p2x = rand() % (width/4) + width/4;
//    int p2y = rand() % (heigh/4) + heigh/4;

//    int p3x = rand() % (width/4) + width/4;
//    int p3y = rand() % (heigh/4);

//    int p4x = rand() % (width/4) + width/2;
//    int p4y = rand() % (heigh/4);

//    int p5x = rand() % (width/4) + width/2;
//    int p5y = rand() % (heigh/4) + heigh/4;

//    int p6x = rand() % (width/4) + width*3/4;
//    int p6y = rand() % (heigh/4) + heigh/4;

//    int p7x = rand() % (width/4) + width*3/4;
//    int p7y = rand() % (heigh/4) + heigh/2;

//    int p8x = rand() % (width/4) + width/2;
//    int p8y = rand() % (heigh/4) + heigh/2;

//    int p9x = rand() % (width/4) + width/2;
//    int p9y = rand() % (heigh/4) + heigh*3/4;

//    int p10x = rand() % (width/4) + width/4;
//    int p10y = rand() % (heigh/4) + heigh*3/4;

//    int p11x = rand() % (width/4) + width/4;
//    int p11y = rand() % (heigh/4) + heigh/2;

//    vector<cv::Point> vert(11);
//    vert[0] = cv::Point(p1x,p1y);
//    vert[1] = cv::Point(p2x,p2y);
//    vert[2] = cv::Point(p3x,p3y);
//    vert[3] = cv::Point(p4x,p4y);
//    vert[4] = cv::Point(p5x,p5y);
//    vert[5] = cv::Point(p6x,p6y);
//    vert[6] = cv::Point(p7x,p7y);
//    vert[7] = cv::Point(p8x,p8y);
//    vert[8] = cv::Point(p9x,p9y);
//    vert[9] = cv::Point(p10x,p10y);
//    vert[10]= cv::Point(p11x,p11y);



    int p1x = rand() % width;
    int p1y = rand() % heigh;

    int p2x = rand() % width;
    int p2y = rand() % heigh;

    int p3x = rand() % width;
    int p3y = rand() % heigh;

    int p4x = rand() % width;
    int p4y = rand() % heigh;



    vector<cv::Point> vert(4);
    vert[0] = cv::Point(p1x,p1y);
    vert[1] = cv::Point(p2x,p2y);
    vert[2] = cv::Point(p3x,p3y);
    vert[3] = cv::Point(p4x,p4y);

    cv::Scalar color = cv::Scalar(rand()%256,rand()%256,rand()%256);
    cv::Mat srcImageCopy = srcImage.clone();
    cv::fillConvexPoly(srcImageCopy,vert,color);

//    cv::resize(srcImage,dstImage,cv::Size(300,300));
    cv::resize(srcImageCopy,dstImage,cv::Size(width/2,heigh/2));
    cv::imshow("afterImage",dstImage);
    cv::waitKey(3000);
    }

    return 0;
}
