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

int findSubFolder(QString path, QStringList& string_list)
{
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() <<"dir(path) don't exists!";
        return -1;
    }
    dir.setFilter(QDir::Dirs | QDir::NoSymLinks );
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
    {
        qDebug() <<"file_count<=0, no files!";
        return -1;
    }

    for(int i=2; i<file_count; i++)
    {
        QFileInfo file_info = list.at(i);
//        qDebug() <<"i= " <<i <<": " <<file_info.absoluteFilePath();

        QString absolute_file_path = file_info.absoluteFilePath();
        string_list.append(absolute_file_path);
    }

//    qDebug() <<string_list;
    return 0;
}

int findTxtFiles(QString path, QStringList& string_list)
{
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() <<"dir(path) don't exists!";
        return -1;
    }

    QStringList filters;
    filters <<QString("*.txt");
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::NoSymLinks );

    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
    {
        qDebug() <<"file_count<=0, no files!";
        return -1;
    }

    for(ulong i=0; i<file_count; i++)
    {
        QFileInfo file_info = list.at(i);

        QString absolute_file_path = file_info.absoluteFilePath();
        QString fileName = absolute_file_path;
        string_list.append(fileName);
    }

    return 0;
}

int findImageFiles(QString path, QStringList& string_list)
{
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        qDebug() <<"dir(path) don't exists!";
        return -1;
    }

    QStringList filters;
    filters <<QString("*.jpg");
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::NoSymLinks );

    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0)
    {
        qDebug() <<"file_count<=0, no files!";
        return -1;
    }

    for(ulong i=0; i<file_count; i++)
    {
        QFileInfo file_info = list.at(i);

        QString absolute_file_path = file_info.absoluteFilePath();
        QString fileName = absolute_file_path;
        string_list.append(fileName);
    }

    return 0;
}

cv::Mat AddGuassianNoise(cv::Mat src)    //添加高斯噪声
{
    cv::Mat dst = cv::Mat(src.size(),src.type());
    cv::Mat noise = dst.clone();
    cv::randn(noise,0,30);
    cv::add(src,noise,dst);
    return dst;
}


cv::Mat HSVadd(cv::Mat srcImage)
{
    cv::Mat result = cv::Mat(srcImage.size(),srcImage.type());
    cv::cvtColor(srcImage,result,cv::COLOR_BGR2HSV);
    for(int i=0; i<result.rows; i++)
    {
        for(int j=0; j<result.cols; j++)
        {
            result.at<cv::Vec3b>(i,j)[1] += 35;
        }
    }
    cv::Mat bgrresult;
    cv::cvtColor(result,bgrresult,cv::COLOR_HSV2BGR);
    return bgrresult;
}

void damageImage(cv::Mat& srcImage)
{
    if( srcImage.empty() )
    {
        cout <<"can't read this image!" <<"--->" <<endl;
        return ;
    }

    int width = srcImage.cols;
    int heigh = srcImage.rows;
//    srand( (unsigned)time( NULL ) );

    vector< cv::Scalar > color = {cv::Scalar(255,255,0),
                                 cv::Scalar(255,0,255),
                                 cv::Scalar(255,255,255),
                                 cv::Scalar(0,255,0),
                                 cv::Scalar(0,0,0)};

    int p1x = rand() % (width/4);
    int p1y = rand() % (heigh/4) + heigh/4;

    int p2x = rand() % (width/4) + width/4;
    int p2y = rand() % (heigh/4) + heigh/4;

    int p3x = rand() % (width/4) + width/4;
    int p3y = rand() % (heigh/4);

    int p4x = rand() % (width/4) + width/2;
    int p4y = rand() % (heigh/4);

    int p5x = rand() % (width/4) + width/2;
    int p5y = rand() % (heigh/4) + heigh/4;

    int p6x = rand() % (width/4) + width*3/4;
    int p6y = rand() % (heigh/4) + heigh/4;

    int p7x = rand() % (width/4) + width*3/4;
    int p7y = rand() % (heigh/4) + heigh/2;

    int p8x = rand() % (width/4) + width/2;
    int p8y = rand() % (heigh/4) + heigh/2;

    int p9x = rand() % (width/4) + width/2;
    int p9y = rand() % (heigh/4) + heigh*3/4;

    int p10x = rand() % (width/4) + width/4;
    int p10y = rand() % (heigh/4) + heigh*3/4;

    int p11x = rand() % (width/4) + width/4;
    int p11y = rand() % (heigh/4) + heigh/2;

    vector<cv::Point> vert(11);
    vert[0] = cv::Point(p1x,p1y);
    vert[1] = cv::Point(p2x,p2y);
    vert[2] = cv::Point(p3x,p3y);
    vert[3] = cv::Point(p4x,p4y);
    vert[4] = cv::Point(p5x,p5y);
    vert[5] = cv::Point(p6x,p6y);
    vert[6] = cv::Point(p7x,p7y);
    vert[7] = cv::Point(p8x,p8y);
    vert[8] = cv::Point(p9x,p9y);
    vert[9] = cv::Point(p10x,p10y);
    vert[10]= cv::Point(p11x,p11y);

    cv::fillConvexPoly(srcImage,vert,color[rand()%5]);

    return;
}

int main(int argc, char *argv[])
{
    QString filePath1 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/trainData-random/1/";
    QString filePath2 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/trainData-random/2/";
    QString filePath3 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/trainData-random/3/";
    QString filePath4 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/trainData-random/4/";


    QString dstPath1 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/testData-random/1/";
    QString dstPath2 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/testData-random/2/";
    QString dstPath3 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/testData-random/3/";
    QString dstPath4 = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/testData-random/4/";


    srand( (unsigned)time( NULL ) );


    int isfindImageFiles1;
    QStringList ImageFileList1;
    isfindImageFiles1 = findImageFiles(filePath1, ImageFileList1);
    if( isfindImageFiles1 != 0)
    {
        return -1;
    }

    int isfindImageFiles2;
    QStringList ImageFileList2;
    isfindImageFiles2 = findImageFiles(filePath2, ImageFileList2);
    if( isfindImageFiles2 != 0)
    {
        return -1;
    }

    int isfindImageFiles3;
    QStringList ImageFileList3;
    isfindImageFiles3 = findImageFiles(filePath3, ImageFileList3);
    if( isfindImageFiles3 != 0)
    {
        return -1;
    }

    int isfindImageFiles4;
    QStringList ImageFileList4;
    isfindImageFiles4 = findImageFiles(filePath4, ImageFileList4);
    if( isfindImageFiles4 != 0)
    {
        return -1;
    }


    int num = ImageFileList1.count();
    if(num != ImageFileList2.count() || num != ImageFileList3.count() || num != ImageFileList4.count())
    {
        cout << "the four files image numbers is not equal !" <<endl;
        cout <<num <<" " <<ImageFileList2.count() <<" "
            <<ImageFileList3.count() <<" " <<ImageFileList4.count() <<endl;
        return -1;
    }

    for(int i=0; i<num; i = i+4)
    {
        int n = rand() % 4;



        QString fullName1 = ImageFileList1.at(i+n);
        QString ImageName1 = fullName1.split('/').last();
        QString dstImageName1 = dstPath1 + ImageName1;

        QFile::copy(fullName1,dstImageName1);
        QFile::remove(fullName1);




        QString fullName2 = ImageFileList2.at(i+n);
        QString ImageName2 = fullName2.split('/').last();
        QString dstImageName2 = dstPath2 + ImageName2;

        QFile::copy(fullName2,dstImageName2);
        QFile::remove(fullName2);




        QString fullName3 = ImageFileList3.at(i+n);
        QString ImageName3 = fullName3.split('/').last();
        QString dstImageName3 = dstPath3 + ImageName3;

        QFile::copy(fullName3,dstImageName3);
        QFile::remove(fullName3);




        QString fullName4 = ImageFileList4.at(i+n);
        QString ImageName4 = fullName4.split('/').last();
        QString dstImageName4 = dstPath4 + ImageName4;

        QFile::copy(fullName4,dstImageName4);
        QFile::remove(fullName4);


    }

    return 0;
}
























