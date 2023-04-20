/*
    编写发布订阅实现 
    要求发布方以10HZ(每秒10次)的频率发布文本消息 
    订阅方订阅消息并将消息内容打印输出
*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

/*
    订阅方实现
        1 包含头文件
            ROS 中的文本类型 ---> std_msgs/String.h
        2 初始化 ros 节点
        3 创建节点句柄
        4 创建发布者对象e
        5 编写发布逻辑并发布数据
*/

int main(int argc, char *argv[]) {
    // 避免中文乱码问题
    setlocale(LC_ALL, "");

    // 初始化 ros 节点
    ros::init(argc, argv, "erGouZi");
    // 创建节点句柄
    ros::NodeHandle nh;
    // 创建发布者对象
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang", 10);
    // 编写发布逻辑并发布数据
    // 要求以 10HZ 的频率发布数据 并且文本后添加编号
    // 先创建被发布的消息
    std_msgs::String msg;
    // 发布频率
    ros::Rate rate(10);
    // 设置编号
    int count = 0;
    // 编写循环 循环中发布数据
    ros::Duration(3).sleep(); // 延迟第一条数据的发送 3s 后发送
    while (ros::ok()) { // 如果这个节点还活着 这个循环就成立
        count ++;
        // msg.data = "hello"; // 添加数据
        // 实现字符串的拼接数字
        std::stringstream ss;
        ss << "hello --->" << count;
        msg.data = ss.str();
        pub.publish(msg); // 发布数据

        // 添加日志
        ROS_INFO("发布的数据是:%s", ss.str().c_str());

        rate.sleep();

        ros::spinOnce(); // 回头一次 官方建议 处理回调函数
    }
    return 0;
}
