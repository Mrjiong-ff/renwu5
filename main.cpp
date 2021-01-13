#include<iostream>
#include<sstream>
#include<math.h>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(){
     Mat srcImage,dstImage1,dstImage2,drawingImage;
     int x1=17,x2=42;
     float focal=435.675;
     float Distance,planedistance,Camhigh=20.0;
     float tabledistance,tablelong=100.0,Camdistance=60.0;
     tabledistance=sqrt(pow(Camdistance,2)-pow(Camhigh,2))*10;
     cout<<tabledistance<<endl;
     cout<<tablelong*10<<endl;
     int Coefficient=(int)(x2/x1);
     Point dis;
     Point s;
     vector<Vec3f>circles;
     vector<Vec2f>lines;
     drawingImage=Mat::zeros(Size(tablelong*10,tabledistance),CV_8UC3);
     srcImage=imread("/home/ma/下载/renwu52.jpg");
     cvtColor(srcImage,dstImage1,COLOR_BGR2GRAY);
     GaussianBlur(dstImage1,dstImage1,Size(5,5),3,3);
     Canny(dstImage1,dstImage2,3,9,3);
     HoughLines(dstImage2,lines,1,CV_PI/180,150,0,0);
     for(auto i=0;i<lines.size();i++){
         float k;
        k = (double)(lines[i][3] - lines[i][1]) / (double)(lines[i][2] - lines[i][0]);
     }
     HoughCircles(dstImage2,circles,HOUGH_GRADIENT,1,40,105,30,8,51);
     for(auto i=0;i<circles.size();i++){
         Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
         int radius=cvRound(circles[i][2]);
         dis.x=center.x;
         dis.y=center.y-30;
         s.x=center.x-50;
         s.y=center.y-30;
         if(radius!=18&&radius!=35){
         circle(srcImage,center,radius,Scalar(155,50,255),3,8,0);
         if(radius==19)
         {
             Distance=focal*x1/radius;
             planedistance=sqrt(pow(Distance,2)-pow(Camhigh,2));
             String Adistance;
             Point Acenter;
             Acenter.x=center.x;
             Acenter.y=tabledistance-planedistance;
             Adistance=to_string(Distance/10);
             putText(srcImage,"S=",s,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             putText(srcImage,Adistance,dis,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             circle(drawingImage,Acenter,17,Scalar(0,0,255),1,8,0);
             cout<<Adistance<<endl;
             cout<<Acenter<<endl;
             cout<<radius<<endl;
             cout<<"平面"<<planedistance<<endl;
         }else  if(radius==21)
         {
             String Bdistance;
             Distance=focal*x1/radius;
             planedistance=sqrt(pow(Distance,2)-pow(Camhigh,2));
             Point Bcenter;
             Bcenter.x=center.x;
             Bcenter.y=tabledistance-planedistance;
             Bdistance=to_string(Distance/10);
             putText(srcImage,"S=",s,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             putText(srcImage,Bdistance,dis,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             circle(drawingImage,Bcenter,17,Scalar(0,0,255),1,8,0);
             cout<<Bdistance<<endl;
             cout<<"平面"<<planedistance<<endl;
         }
         else if(radius==40)
         {
             Distance=focal*x2/radius;
             planedistance=sqrt(pow(Distance,2)-pow(Camhigh,2));
             String Cdistance;
             Point Ccenter;
             Ccenter.x=center.x;
             Ccenter.y=tabledistance-planedistance;
             Cdistance=to_string(Distance/10);
             putText(srcImage,"S=",s,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             putText(srcImage,Cdistance,dis,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             circle(drawingImage,Ccenter,42,Scalar(0,0,255),1,8,0);
             cout<<Cdistance<<endl;
             cout<<"平面"<<planedistance<<endl;
         }
         else if(radius==16)
         {
             Distance=focal*x1/(radius+Coefficient);
             planedistance=sqrt(pow(Distance,2)-pow(Camhigh,2));
             String Ddistance;
             Point Dcenter;
             Dcenter.x=center.x;
             Dcenter.y=tabledistance-planedistance;
             Ddistance=to_string(Distance/10);
             putText(srcImage,"S=",s,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             putText(srcImage,Ddistance,dis,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             circle(drawingImage,Dcenter,17,Scalar(0,0,255),1,8,0);
             cout<<Ddistance<<endl;
             cout<<"平面"<<planedistance<<endl;
         }
         else if(radius==50)
         {
             Distance=focal*x2/(radius+Coefficient*4);
             planedistance=sqrt(pow(Distance,2)-pow(Camhigh,2));
             Point Ecenter;
             Ecenter.x=center.x;
             Ecenter.y=tabledistance-planedistance;
             String Edistance;
             Edistance=to_string(Distance/10);
             putText(srcImage,"S=",s,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             putText(srcImage,Edistance,dis,FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
             circle(drawingImage,Ecenter,42,Scalar(0,0,255),1,8,0);
             cout<<Edistance<<endl;
             cout<<"平面"<<planedistance<<endl;
         }
         }
     }
     imshow("dst",srcImage);
     imshow("drawing",drawingImage);
     waitKey(0);
     return 0;
}
