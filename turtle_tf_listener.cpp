
#include<ros/ros.h>
#include<turtlesim/Pose.h>
#include<geometry_msgs/Twist.h>
#include<math.h>
#include<vector>

float x,t;
int j=0;
turtlesim::Pose current_pose;
turtlesim::Pose dest_pose;
turtlesim::Pose temp;
geometry_msgs::Twist vel_;


//turtlesim::Pose poses[10];
std::vector<turtlesim::Pose>poses;

void poseCallback(const turtlesim::PoseConstPtr &msg){
  current_pose = *msg;
}

void update_pose(){
    j++;
    dest_pose = poses[j];
}


void vel_calc(){
  vel_.linear.x = (dest_pose.x - current_pose.x)*0.5;
  vel_.linear.y = (dest_pose.y - current_pose.y)*0.5;
  vel_.angular.z = atan((dest_pose.y - current_pose.y)/(dest_pose.x - current_pose.x)) - current_pose.theta;
}



int main(int argc,char** argv){
  ros::init(argc,argv,"turtle");
  ros::NodeHandle node;
  int size;

  std::cin>>size;
  size = size + 1;

  for(int i=0;i<size;i++){
    std::cin>>temp.x;
    std::cin>>temp.y;
    poses.push_back(temp);
  }

  dest_pose = poses[0];

  ros::Publisher vel = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
  ros::Subscriber pose = node.subscribe<turtlesim::Pose>("/turtle1/pose",10,poseCallback);

  while(j<size+1){
    ros::spinOnce();
    vel_calc();
    vel.publish(vel_);
    if(abs(current_pose.x - dest_pose.x) < 0.01 && abs(current_pose.y - dest_pose.y) < 0.01)
    {
      update_pose();
    }
    if(abs(current_pose.x - poses[size-1].x) < 0.01 && abs(current_pose.y - poses[size-1].y) < 0.01)
    {
      break;
    }
  }
  ros::spin();
}
