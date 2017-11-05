#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <string>

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

int main(int argc, char *argv[])
{
//    QString filePath = \
//            "/home/lab/Program-opt/MultiCamera/CamerDataDir/trainData-random/";
    QString filePath = \
            "/home/lab/Program-opt/MultiCamera/CamerDataDir/testData-random/";

    int findsubFolders;
    QStringList subFoldersList;

    findsubFolders = findSubFolder(filePath,subFoldersList);
    if( findsubFolders != 0)
    {
        return -1;
    }

    qDebug() <<subFoldersList;

    // /home/frizy/Program/420/sample
    ulong i=0, j=0;
    for(i=0; i<subFoldersList.count(); i++)
    {
        qDebug() <<subFoldersList.at(i);


        int isfindImageFiles;
        QStringList ImageFileList;
        isfindImageFiles = findImageFiles(subFoldersList.at(i),ImageFileList);
        if( isfindImageFiles != 0)
        {
            return -1;
        }

        // /home/frizy/Program/420/original/0/camera_0_0.jpg
        for(int v=0; v<ImageFileList.count(); v++)
        {
            QString fullName = ImageFileList.at(v);
            QString ImageName = fullName.split('/').last();

            QString resultImageName = ImageName;


            QString resultTxtName = subFoldersList.at(i) + QString("/") + "filelist.txt";

            QFile resultTxtfile(resultTxtName);
            if( !resultTxtfile.open(QFile::WriteOnly | QFile::Append))
            {
                qDebug() <<"Can't write result txt file";
                return -1;
            }

            QString justImageName = ImageName.split('.').first();
            QString ifDamage = justImageName.split('-').last();
            QString label = "0";
            if(ifDamage == "y")
            {
                label = QString::number(1);
            }
            QString line = resultImageName + QString(" %1").arg(label) + "\r\n";

            qDebug() <<line;

            resultTxtfile.write(line.toLatin1());
            resultTxtfile.close();
        }

    }

    return 0;
}
























