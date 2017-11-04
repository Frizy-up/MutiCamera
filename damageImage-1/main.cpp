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

    cv::fillConvexPoly(srcImage,vert,color);

    return;
}

int main(int argc, char *argv[])
{
    QString filePath = \
            "/home/lab/Program/MultiCamera/CamerDataDir/CamerData/";

    QString dstPath = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/dstData1-min/";


    srand( (unsigned)time( NULL ) );
    for(int i=0; i<12422; i++)
    {
        int n = rand() % 4 + 1;
        for(int j=1; j<=4; j++)
        {
            QString ImageName = filePath + QString::number(j) + "/"
                    + QString::number(i).sprintf("%05d",i) +".jpg";




            QString label = "0";

            QString justName = QString::number(i).sprintf("%05d",i) + "-1";



            QString dstTxtName =  dstPath + QString::number(j) + "/" + "filelist.txt";

            QFile curImage(ImageName);
            if( ! curImage.exists() )
            {
                qDebug() << ImageName << " " << "don't exitst !";
                return -1;
            }


            if( j != n )
            {
                QString justImageName = justName +".jpg";

                QString dstImageName = dstPath + QString::number(j) + "/"
                        + justImageName;

                cv::Mat srcImage = cv::imread(ImageName.toStdString());
                cv::imwrite(dstImageName.toStdString(),srcImage);

                QFile resultTxtfile(dstTxtName);
                if( !resultTxtfile.open(QFile::WriteOnly | QFile::Append))
                {
                    qDebug() <<"Can't write result txt file";
                    return -1;
                }

                label = "0";

                QString line = justImageName + QString(" %1").arg(label) + "\r\n";
                resultTxtfile.write(line.toLatin1());
                resultTxtfile.close();

                qDebug() <<line;
            }
            else
            {
                QString justImageName = justName +"-y" +".jpg";
                QString dstImageName = dstPath + QString::number(j) + "/"
                        + justImageName;

                cv::Mat srcImage = cv::imread(ImageName.toStdString());

                damageImage(srcImage);

                cv::imwrite(dstImageName.toStdString(),srcImage);

                QFile resultTxtfile(dstTxtName);
                if( !resultTxtfile.open(QFile::WriteOnly | QFile::Append))
                {
                    qDebug() <<"Can't write result txt file";
                    return -1;
                }

                label = "1";

                QString line = justImageName + QString(" %1").arg(label) + "\r\n";
                resultTxtfile.write(line.toLatin1());
                resultTxtfile.close();

                qDebug() <<line;
            }

        }
    }

    return 0;
}
























