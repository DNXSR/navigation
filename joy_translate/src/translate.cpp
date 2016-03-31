#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class TeleopTurtle{
  public:
    TeleopTurtle();

  private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
    int x_, y_, w_;

    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;
};

 TeleopTurtle::TeleopTurtle(): y_(1),x_(0),w_(2){
   nh_.param("x_control", x_, x_);
   nh_.param("y_control", y_, y_);
   nh_.param("angular_control", w_, w_);

   vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
   joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);
}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy){
   geometry_msgs::Twist twist;
   double _m_x = -joy->axes[x_];
   double _m_y = joy->axes[y_];
   double _m_w = -joy->axes[w_];

   twist.linear.x = _m_x;
   twist.linear.y = _m_y;
   twist.angular.z = _m_w;

   ROS_INFO("PUBLISHING X: %f\tY: %f\tW: %f",_m_x,_m_y,_m_w);

   vel_pub_.publish(twist);}

int main(int argc, char** argv)
{
   ros::init(argc, argv, "teleop_turtle");
   TeleopTurtle teleop_turtle;
   ros::spin();
 }
