#include "ros/ros.h"
#include "plumbing_server_client/Addints.h"

/*
    客户端 提交两个整数 并处理响应的结果
        1. 包含头文件
        2. 初始化 ros 节点
        3. 创建节点句柄
        4. 创建一个客户端对象
        5. 提交请求并处理响应
    
    实现参数的动态提交
        1. 格式 rosrun xxxxx(包名) xxxxxx(节点名称) 12 34
        2. 节电执行时 需要获取命令中的参数 并组织进 request

    问题
        如果先启动客户端 那么会请求异常
    需求
        如果先启动客户端 不要直接抛异常 而是挂起 等服务器启动后 再正常请求
    解决
        在 ros 中内置了相关函数 这些函数可以让客户端挂起 等待服务器启动
        client.waitForExistence(); // 如果服务器没有启动就会挂起
        ros::service::waitForService("addInts"); // 需要传参 参数为服务的话题
*/

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // 优化实现 获取命令中的参数
    if (argc != 3) {
        ROS_INFO("提交的参数个数错误");

        return 1;
    }

    ros::init(argc, argv, "daBao");

    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::Addints>("addInts");

    // 提交请求并处理响应
    plumbing_server_client::Addints ai;

    // 组织请求
    // ai.request.num1 = 100;
    // ai.request.num2 = 200;

    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);

    // 处理响应
    // 调用判断服务器状态的函数
    // 函数 1
    // client.waitForExistence(); // 如果服务器没有启动就会挂起
    // 函数 2
    ros::service::waitForService("addInts"); // 需要传参 参数为服务的话题

    bool flag = client.call(ai);

    if (flag) ROS_INFO("响应成功, 结果 = %d", ai.response.sum);
    else ROS_INFO("响应失败");

    return 0;
}