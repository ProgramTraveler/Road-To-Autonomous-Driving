// 1 包含 ros 的头文件
#include "ros/ros.h"

// 2 编写 main 函数
int main (int argc, char *argv[]) {
	// 3 初始化 ros 节点
	ros::init(argc, argv, "hello_node"); // 其中的字符串是节点名称
	// 4 输出日志
	ROS_INFO("hello world!");
	
	return 0;
}
