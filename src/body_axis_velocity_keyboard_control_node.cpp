#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <keyboard/Key.h>
#include <tf/tf.h>



geometry_msgs::TwistStamped vs;
ros::Publisher bodyAxisVelocityPublisher;
float value;

void sendCommand(const keyboard::Key &key)
{

  switch(key.code)
  {
      case 'i':
      {
        // Forward
        vs.twist.linear.x += value;
        ROS_INFO_STREAM("Forward speed: " << value);
        break;
      }
      case 'k':
      {
        // Backward
        vs.twist.linear.x -= value;
        ROS_INFO_STREAM("Backward speed: " << value);
        break;
      }
      case 'j':
      {
        // left
        vs.twist.linear.y += value;
        ROS_INFO_STREAM("Left speed:" << value);
        break;
      }
      case 'l':
      {
        // right
        vs.twist.linear.y -= value;
        ROS_INFO_STREAM("Right speed: " << value);
        break;
      }
      case 'u':
      {
        // turn left 
        vs.twist.angular.z += value;
        ROS_INFO_STREAM("Turn Left:" << value);
        break;
      }
      case 'o':
      {
        // turn right
        vs.twist.angular.z -= value;
        ROS_INFO_STREAM("Turn Right" << value);
        break;
      }
      case 'w':
      {
        // Up
        vs.twist.linear.z += value;
        
        ROS_INFO_STREAM("Up: " << value);
        break;
      }
      case 's':
      {
        // Down
        vs.twist.linear.z -= value;
  
        ROS_INFO_STREAM("Down: "<< value);
        break;
      }
      case 'a':
      {
        // Increase value
        value += 0.1f;
        ROS_INFO_STREAM("Increase value:" << value);
        break;
      }
      case 'd':
      {
        // decrease value
        value -= 0.1f;
        if (value == 0.0f)
        {
          value = 0.1f;
        }
        ROS_INFO_STREAM("Decrease value:" << value);
        break;
      }
      case 'x':
      {
        // reset to 0
        geometry_msgs::TwistStamped zeroVs;
        vs = zeroVs;
        ROS_INFO_STREAM("Turn to zero vs");
        break;
      }
      
      default:
      {

      }
  }


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "body_axis_velocity_control_keyboard_node");
  ros::NodeHandle nodeHandle;

  bodyAxisVelocityPublisher = nodeHandle.advertise<geometry_msgs::TwistStamped>("/CLDrone/body_axis_velocity/cmd_vel",10);
  ros::Subscriber commandSubscriber = nodeHandle.subscribe("/keyboard/keydown",1,sendCommand);
  
  value = 0.1f;

  ros::Rate loopRate(10.0);

  while(ros::ok())
  {

    vs.header.seq++;
    vs.header.stamp = ros::Time::now();
    bodyAxisVelocityPublisher.publish(vs);

    ros::spinOnce();

    loopRate.sleep();
  }

}