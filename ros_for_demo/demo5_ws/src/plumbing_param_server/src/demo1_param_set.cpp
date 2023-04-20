#include "ros/ros.h"

/*
    需要实现参数的新增与修改
    
    需求 首先设置机器人的共享参数 类型 半径(0.15m)
        再修改半径为(0.2m)
    
    实现
        ros::NodeHandle
            setParam("键", 值)
        ros::param
            set("键", 值)
    
    修改值的话 只需要继续调用 setParam 或 set 函数 保证键是存在的 那么值会直接覆盖
*/

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // 初始化 ros 节点
    ros::init(argc, argv, "set_param_c");
    // 创建 ros 节电句柄
    ros::NodeHandle nh;

    // 参数增-------------------------------
    // 方案 1 nh
    nh.setParam("type", "xiaoHuang");
    nh.setParam("radius", 0.15);
    // 方案 2 ros::param
    ros::param::set("type_param", "xiaoBai");
    ros::param::set("radius_param", 0.15);

    // 参数改-------------------------------
    // 方案 1 nh
    nh.setParam("radius", 0.2); // 其实就是参数的覆盖
    ros::param::set("radius_param", 0.25);
    // 方案 2 ros::param

    return 0;
}