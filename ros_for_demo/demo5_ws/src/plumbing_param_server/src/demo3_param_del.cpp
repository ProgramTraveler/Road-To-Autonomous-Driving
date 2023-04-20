#include "ros/ros.h"

/*
    演示参数的删除

    实现
    ros::NodeHandle
        deleteParam()
    ros::param
        del()
*/

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "param_del_c");

    ros::NodeHandle nh;

    bool res = nh.deleteParam("radius");
    if (res) ROS_INFO("delet SUCC");
    else ROS_INFO("delete EORRO");

    bool flag = ros::param::del("radius_param");
    if (flag) ROS_INFO("delet_param SUCC");
    else ROS_INFO("delete_param EORRO");

    return 0;
}