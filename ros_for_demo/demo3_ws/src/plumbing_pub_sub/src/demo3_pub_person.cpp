#include "ros/ros.h"
#include "plumbing_pub_sub/person.h"

/*
    发布方 发布人的消息
        1. 包含头文件
            #include "plumbing_pub_sub/person.h"
        2. 初始化 ros 节点
        3. 创建 ros 节点句柄
        4. 创建发布者对象
        5. 编写发布逻辑 发布数据
*/

int main (int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    ROS_INFO("消息发布方");
    // 初始化 ros 节点
    ros::init(argc, argv, "person"); // 节点名称
    // 创建节点句柄
    ros::NodeHandle nh;
    // 创建发布者对象
    ros::Publisher pub = nh.advertise<plumbing_pub_sub::person>("chat", 10);
    // 编写发布逻辑 发布数据
    // 创建被发布的数据
    plumbing_pub_sub::person per;
    per.name = "wang";
    per.age = 20;
    per.height = 1.73;
    // 设置发布的频率
    ros::Rate rate(1); // 1s 一次
    // 循环发布数据
    while (ros::ok()) {
        // 核心 发布数据
        pub.publish(per);

        ROS_INFO("发布的消息:%s, %d, %f", per.name.c_str(), per.age, per.height);
        // 修改发布数据
        per.age ++;

        // 休眠
        rate.sleep();

        // 建议
        ros::spinOnce();
    }

    return 0;
}