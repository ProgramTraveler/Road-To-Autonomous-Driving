#include "ros/ros.h"

/*
    演示参数查询

    实现
        ros::NodeHandle
            param(键,默认值) 
                存在，返回对应结果，否则返回默认值

            getParam(键,存储结果的变量)
                存在,返回 true,且将值赋值给参数2
                若果键不存在，那么返回值为 false，且不为参数2赋值

            getParamCached键,存储结果的变量)--提高变量获取效率
                存在,返回 true,且将值赋值给参数2
                若果键不存在，那么返回值为 false，且不为参数2赋值

            getParamNames(std::vector<std::string>)
                获取所有的键,并存储在参数 vector 中 

            hasParam(键)
                是否包含某个键，存在返回 true，否则返回 false

            searchParam(参数1，参数2)
                搜索键，参数1是被搜索的键，参数2存储搜索结果的变量
        ros::param
            与 NodeHandle 类似
*/

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // 设置编码

    ros::init(argc, argv, "get_param_c");

    ros::NodeHandle nh;
    
    // --------------------------------------------------
    double radius = nh.param("radius", 0.5);
    ROS_INFO("radius = %.2f", radius);

    // --------------------------------------------------
    bool res = nh.getParam("radius", radius);
    if (res) ROS_INFO("true");
    else ROS_INFO("false");

    ROS_INFO("radius = %.2f", radius);

    // --------------------------------------------------
    // getParamCached 与 getParam 类似 只是性能上有提升 一般测试下 看不出来
    res = nh.getParamCached("radius", radius);
    
    if (res) ROS_INFO("true");
    else ROS_INFO("false");

    ROS_INFO("radius = %.2f", radius);

    // --------------------------------------------------
    std::vector<std::string> names;

    nh.getParamNames(names);
    for (auto &name : names) {
        ROS_INFO("遍历的元素: %s", name.c_str());
    }

    // --------------------------------------------------
    bool flag_1 = nh.hasParam("radius");
    bool flag_2 = nh.hasParam("xxxxx");
    ROS_INFO("radius 存在? %d", flag_1);
    ROS_INFO("xxxxx 存在? %d", flag_2);

    // --------------------------------------------------
    std::string key;

    nh.searchParam("radius", key);
    ROS_INFO("搜索结果:%s", key.c_str());

    // ros::param 与 NodeHandle 类似
    double radius_param = ros::param::param("radius", 100.5);
    
    return 0;
}