
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
//#include <mutex>
#include "spi.h"
//#include <wiringPi.h>
//#include <wiringSerial.h>	

using namespace cv;
using namespace std;

#define FILTER_SIZE 5

Mat img_bgr, img_hsv, img_binary, img_binary_Y, img_edge_Y, img_roi, img_result2, img_result3, img_result, img_center;
Point2f leftP[2], rightP[2], vanishP, middleP0, middleP1, middleP2, middleP3;
Point p0 = Point(0, 0);
Point points[3];

Mat img_labels,stats,centroids;
int numOfLables;

Mat img_labels2,stats2,centroids2;
int numOfLables2;

char data;

float mx1,mx2;

int fd ;

double a,b,x,y;
float leftLineA ,leftLineB;
float rightLineA ;
float rightLineB ;

//hsv 트랙바에서 사용되는 변수(노란색 검출)
int LowH = 20;
int HighH = 58;
int LowS = 30;
int HighS = 255;
int LowV = 70;
int HighV = 255;

//Canny edge 트랙바 변수
int lowThreshold = 50;
int highThreshold = 150;

int center_x;
int center_y;

int i = 1;


#define ROIY img_edge_Y.cols / 3
#define LineLimitLeft CV_PI*1/5
#define LineLimitRight CV_PI*4/5
#define Calc (img_edge_Y.rows + img_edge_Y.cols)

Mat region_of_interest(Mat img_edges_R, Point *points)
{
        Mat img_mask = Mat::zeros(img_edges_R.rows, img_edges_R.cols, CV_8UC1);


        //Scalar ignore_mask_color = Scalar(255, 255, 255);
        const Point* ppt[1] = { points };
        int npt[] = { 4 };


        //filling pixels inside the polygon defined by "vertices" with the fill color
        fillPoly(img_mask, ppt, npt, 1, Scalar(255, 255, 255), LINE_8);

        //imshow("관심 영역", img_mask);

        //returning the image only where mask pixels are nonzero
        Mat img_masked;
        bitwise_and(img_edges_R, img_mask, img_masked);


        return img_masked;

}

void filter_color()
{       //특정색만 추출하는 함수
            cvtColor(img_bgr, img_hsv, COLOR_BGR2HSV); //hsv영상으로 변환
            inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary_Y); //특정색 검출
            //morphological opening 작은점들을 제거
            erode(img_binary_Y, img_binary_Y, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
            dilate(img_binary_Y, img_binary_Y, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
            //morphological closing 영역의 구멍 메우기
            dilate(img_binary_Y, img_binary_Y, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
            erode(img_binary_Y, img_binary_Y, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
            GaussianBlur(img_binary_Y, img_binary_Y, Size(5, 5), 0, 0); //가우시안 블러(Size로 블러세기 조절, 클수록 뭉개짐)
            Canny(img_binary_Y, img_edge_Y, lowThreshold, highThreshold); //Ä³ŽÏ¿§Áö °ËÃâ
}

int center_detect()
{
    img_center = img_bgr.clone();

    i = 1;
    int area[100]={};
    int x1[100]={};
    int y1[100]={};
    
    for(int j = 1; j<numOfLables2; j++)
    {
         area[j] = stats2.at<int>(j, CC_STAT_AREA);
         x1[j] = centroids2.at<double>(j,0) + ROIY; 
         y1[j] = centroids2.at<double>(j,1);
         //printf("%d\n",area);
    }
    
    center_y = y1[1];
     
    for (size_t i = 1; i < numOfLables2; i++)
    {
        if (area[i] > 200)
        {
         if (y1[i] > center_y)
         {
             center_x=x1[i];
             center_y=y1[i];
             
         }
         else
            continue;
        }
        else
            continue;
    }
    
    circle(img_center,Point(center_x, center_y),5,Scalar(255,0,255),1);
    center_x=10;
    return center_x;

}
void line_main(uint8_t* data)
{
       
        VideoCapture videoCapture0(0); //웹캠 불러오기(front)
        int tmp;
        if (!videoCapture0.isOpened())
        {
                cout << "0번카메라를 열 수 없습니다. \n" << endl;

                char a;
                cin >> a;

                //return 1;
        }


        while (1)
        {
                    videoCapture0.read(img_bgr); //웹캠 불러오기
                    if (img_bgr.empty()) continue;
                    resize(img_bgr,img_bgr,Size(640,480));
                    filter_color(); //특정색 추출
                    Mat img_roi(img_edge_Y, Rect(img_edge_Y.cols/3, 0, img_edge_Y.cols/3, img_edge_Y.rows));
                    numOfLables2 = connectedComponentsWithStats(img_roi, img_labels2, stats2, centroids2, 8, CV_32S);
                    
                    //(*data)=center_detect();
                    tmp=center_detect();
                    for(int i=0; i<4; i++){
                        data[i] = (uint8_t)tmp;
                        tmp=tmp<<8;
                    }
                    printf("\ndata:%d\n",data);
                          
                    

                if (waitKey(1) == 27) break; //ESC누르면 종료

        }


}
