#include "ros/ros.h"
#include "plumbing_pub_sub/person.h"

/*
    订阅方 订阅消息
        1. 包含头文件
            #include "plumbing_pub_sub/person.h"
        2. 初始化 ros 节点
        3. 创建 ros 节点句柄
        4. 创建订阅者对象
        5. 处理订阅的数据
        6. 调用 spin() 函数
*/

void doPerson(const plumbing_pub_sub::person::ConstPtr& per) {
    ROS_INFO("订阅人的信息:%s, %d, %.2f", per -> name.c_str(), per -> age, per -> height);
}

int main (int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ROS_INFO("订阅方实现");

    ros::init(argc, argv, "person_sub"); // 最后一个是节点名称

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("chat", 10, doPerson);

    ros::spin();

    return 0;
}