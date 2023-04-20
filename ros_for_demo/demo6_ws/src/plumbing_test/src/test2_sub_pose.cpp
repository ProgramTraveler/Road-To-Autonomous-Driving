#include "ros/ros.h"
#include "turtlesim/Pose.h"

/*
    需求 订阅乌龟的位资信息 并输出到控制台
    
    1. 包含头文件
    2. 初始化 ros 节点
    3. 创建节点句柄
    4. 创建订阅对象
    5. 处理订阅的数据(回调函数)
    6.  spin()
*/

// 处理订阅的到的数据
void doPose(const turtlesim::Pose::ConstPtr &pose) {
    ROS_INFO("乌龟的位置信息: 坐标:(%.2f, %.2f), 朝向:(%.2f), 线速度:(%.2f), 角速度:(%.2f)",
    pose -> x, pose -> y, pose -> theta, pose -> linear_velocity, pose -> angular_velocity);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "sub_pose");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 100, doPose);

    ros::spin();
    
    return 0;
}