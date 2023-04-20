#include "ros/ros.h"
#include "std_msgs/String.h"

/*
    订阅方实现
        1 包含头文件
            ROS 中的文本类型 ---> std_msgs/String.h
        2 初始化 ros 节点
        3 创建节点句柄
        4 创建订阅者对象
        5 处理订阅到的数据
*/

void doMsg (const std_msgs::String::ConstPtr &msg) {
    // 通过 msg 获取并操作订阅的数据
    ROS_INFO("翠花订阅的数据:%s", msg -> data.c_str());
}

int main(int argc, char *argv []) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "cuiHua");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("fang", 10, doMsg); // domsg 回调函数

    // spin() 函数
    ros::spin(); // 回头

    return 0;
}