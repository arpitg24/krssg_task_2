#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui/highgui.hpp"
#include<iostream>
#include<vector>
#include<time.h>
#include<sys/socket.h>
#include <netinet/in.h> 

using namespace std;
using namespace cv;

struct node{
    Point pos;
    int parent;
};

struct pairs{
    node n1,n2;
};

Mat img = imread("tut1.jpg",1);
bool stop = false;
node source,dest;
int stepsize = 10;

vector<node>pts;
vector<pairs>lines;

//calculates distance betn 2 pts
float dist(Point a,Point b){
    float ret;
    a.x = float(a.x);
    b.x = float(b.x);   
    a.y = float(a.y);
    b.y = float(b.y);
    ret = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    return ret;
}

//joins 2 pts with line
void join(Point p1,Point p2,int a,int b,int c){
    line(img,p1,p2,Scalar(a,b,c),1,4);
}

//checks if 2 pts intesect white space
bool intersect(Point a,Point b){
    bool check = false;
    LineIterator it1(img,a,b,4);
    /*if(a.x>b.x){
        LineIterator it2(img,b,a,4);
        it1 = it2;
    }*/
    for(int i=0;i<it1.count;i++,++it1){
        Point ret = it1.pos();
        int x = ret.x;
        int y = ret.y;
        if(img.at<Vec3b>(y,x)[0]==255 && img.at<Vec3b>(y,x)[1]==255 && img.at<Vec3b>(y,x)[2]==255){
            check = true;
            break;
        }
    }
    return check;
}

//produce random point
Point next_node(){
    Point ret;
    srand(time(0)+rand());
    ret.x = rand()%600;
    ret.y = rand()%600;
    
    return ret;
}

//returns nearest node to p
node prev_node(node p){
    node ret;
    int temp1 = 9999999;
    for(int i=0;i<pts.size();i++){
        if(temp1>=dist(pts[i].pos,p.pos) /*&& intersect(pts[i].pos,p.pos)==false*/){
            temp1 = dist(pts[i].pos,p.pos);
            ret.pos = pts[i].pos;
            ret.parent = pts[i].parent;
        }
    }
    return ret;
}

//ends program if 2 pts one from src and one from des are joined
void end(){
    int flag = 0;
    for(int i=0;i<pts.size();i++){
        for(int j=0;j<pts.size();j++){
            if(i!=j){
                if(pts[i].parent==0 && pts[j].parent==1 && intersect(pts[i].pos,pts[j].pos)==false){
                    if(dist(pts[i].pos,pts[j].pos)<1000){
                        join(pts[i].pos,pts[j].pos,255,0,0);
                        //cout<<pts[i].pos.x<<" "<<pts[i].pos.y<<"    "<<pts[j].pos.x<<" "<<pts[j].pos.y<<endl;
                        flag = 1;
                        pairs push;
                        push.n1 = pts[i];
                        push.n2 = pts[j];
                        lines.push_back(push);
                        //cout<<push.n1.pos.x <<" "<< push.n1.pos.y<<"    "<<push.n2.pos.x<<" "<<push.n2.pos.y<<endl;
                        //cout<<endl; 
                        stop = true;
                        break; 
                    } 
                }
            }
        }
        if(flag==1){
            break;
        }
    }
}

void rrt(){
    node temp,new_node;
    new_node.pos = next_node();   //random node
    temp = prev_node(new_node);     //node nearest to random node
    //if(img.at<Vec3b>(new_node.pos.y,new_node.pos.x)[0]==0 && img.at<Vec3b>(new_node.pos.y,new_node.pos.x)[1]==0 && img.at<Vec3b>(new_node.pos.y,new_node.pos.x)[2]==0){   
        //if(intersect(temp.pos,new_node.pos)==false){
            pairs push;
            new_node.parent = 0;
            if(temp.parent == 0 /*&& intersect(temp.pos,new_node.pos)==false*/){
                LineIterator it1(img,temp.pos,new_node.pos,4);
                int size1 = it1.count;
                if(size1>10){
                    size1 = 10;
                }
                for(int i=0;i<size1;i++,++it1){
                    new_node.pos = it1.pos();
                }
                if(intersect(temp.pos,new_node.pos)==false){
                    join(temp.pos,new_node.pos,0,0,255);
                    //cout<<temp.pos.x<<" "<<temp.pos.y<<"    "<<new_node.pos.x<<" "<<new_node.pos.y<<endl;
                    push.n1 = temp;
                    push.n2 = new_node;
                    lines.push_back(push);
                    //cout<<push.n1.pos.x <<" "<< push.n1.pos.y<<"    "<<push.n2.pos.x<<" "<<push.n2.pos.y<<endl;
                    //cout<<endl;
                    pts.push_back(new_node);
                }

            }
            else if(temp.parent == 1 /*&& intersect(temp.pos,new_node.pos)==false*/){
                LineIterator it2(img,new_node.pos,temp.pos,4);
                int size2 = it2.count;
                int max_size = size2;
                if(size2>10){
                    size2 = 10;
                }
                for(int i=0;i<max_size - size2;i++,++it2){
                    new_node.pos = it2.pos();
                }
                if(intersect(new_node.pos,temp.pos)==false){
                    new_node.parent = 1;
                    join(new_node.pos,temp.pos,0,255,0);
                    //cout<<new_node.pos.x<<" "<<new_node.pos.y<<"    "<<temp.pos.x<<" "<<temp.pos.y<<endl;
                    push.n1 = new_node;
                    push.n2 = temp;
                    lines.push_back(push);
                    //cout<<push.n1.pos.x <<" "<< push.n1.pos.y<<"    "<<push.n2.pos.x<<" "<<push.n2.pos.y<<endl;
                    //cout<<endl; 
                    pts.push_back(new_node);
                }

            }
        //}
    //}
}

int main(){
    namedWindow("w1",WINDOW_NORMAL);

    //resize(img, img, Size(), 2.5, 2.5);
 
    source.pos.x = 30;
    source.pos.y = 30;
    source.parent = 0;

    dest.pos.x = 590;
    dest.pos.y = 590;
    dest.parent = 1;

    for(int i=0;i<600;i++){
        for(int j=0;j<600;j++){
            if(img.at<Vec3b>(i,j)[0]>220 && img.at<Vec3b>(i,j)[1]>220 && img.at<Vec3b>(i,j)[2]>220){
                img.at<Vec3b>(i,j)[0] = 255;
                img.at<Vec3b>(i,j)[1] = 255;
                img.at<Vec3b>(i,j)[2] = 255;
            }else{
                img.at<Vec3b>(i,j)[0] = 0;
                img.at<Vec3b>(i,j)[1] = 0;
                img.at<Vec3b>(i,j)[2] = 0;
            }
        }
    }

    pts.push_back(source);
    pts.push_back(dest);

    while(stop == false){
        rrt();
        end();
        imshow("w1",img);
        cvWaitKey(10);
    }

    node flag;
    flag.pos = source.pos;

    while(flag.pos != dest.pos){

        for(auto it = lines.begin() ; it != lines.end(); ++it){
            pairs temp = *it;
            bool del = true;
            //cout<<flag.pos.x<<" "<<flag.pos.y<<endl;
            if(temp.n1.pos == flag.pos && temp.n1.pos != dest.pos){
                flag.pos = temp.n2.pos;
                //cout<<flag.pos.x<<" "<<flag.pos.y<<endl;
                if(flag.pos != dest.pos){    
                    for(auto it2 = lines.begin() ; it2 != lines.end() ; ++it2){
                        //cout<<"internal for lloop entered"<<endl;
                        pairs temp2 = *it2;
                        if(flag.pos == temp2.n1.pos && flag.pos != dest.pos){
                            del = false;
                            break;
                        }
                    }
                    if(del ==  true){
                        lines.erase(it);
                        flag.pos = source.pos;
                        break;
                    }
                }
            }
        }
    }

    flag.pos = source.pos;

    vector<Point>path;
    path.push_back(source.pos);


    while(flag.pos != dest.pos){

        for(auto it = lines.begin() ; it != lines.end(); ++it){
            pairs temp = *it;
            if(temp.n1.pos == flag.pos && temp.n1.pos != dest.pos){
                flag.pos = temp.n2.pos;
                join(temp.n1.pos,temp.n2.pos,255,0,0);
                imshow("w1",img);
                cvWaitKey(500);
                path.push_back(flag.pos);
            }
        }
    }

    cout<<path.size()/3<<endl;

    for(int i=0;i<path.size();i++){
        if(i%3 == 0){
            cout<<path[i].x/60.0<<endl;
            cout<<path[i].y/60.0<<endl;
        }
        
    }
  

    imshow("w1",img);
    cvWaitKey(0);
}
