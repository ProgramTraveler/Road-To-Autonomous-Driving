#include "ros/ros.h"
#include "plumbing_server_client/Addints.h"
/*
    服务端实现 解析客户端提交的数据 并运算再产生响应
        1. 包含头文件
        2. 初始化 ros 节点
        3. 创建节点句柄
        4. 创建一个服务对象
        5. 处理请求并产生响应
        6. spin()
*/

bool doNums(plumbing_server_client::Addints::Request &request, 
            plumbing_server_client::Addints::Response &response) { // 返回是一个 bool 值 要么是请求处理成功 要么是请求处理失败
    // 处理请求
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("收到的请求数据为: num1 = %d, num2 = %d", num1, num2);

    // 组织响应
    response.sum = num1 + num2;
    ROS_INFO("响应的请求数据为: sum = %d", response.sum);
    
    return true;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ROS_INFO("NO ERROR");

    ros::init(argc, argv, "heiShui"); // 参数三是节点名称 必须保证唯一

    ros::NodeHandle nh;

    ros::ServiceServer server = nh.advertiseService("addInts", doNums);
    ROS_INFO("服务器启动");

    ros::spin();

    return 0;
}