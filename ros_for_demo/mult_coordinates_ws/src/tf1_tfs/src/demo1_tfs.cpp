#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"

/*
    订阅方实现 
        1. 计算 son1 与 son2 的相对关系
        2. 计算 son1 中的某个坐标点在 son2 中的坐标值
    
    流程
        1. 包含头文件
        2. 编码 初始化 NodeHandle
        3. 创建订阅对象
        4. 编写解析逻辑
        5. spinOnce()
*/

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "tfs_sub");

    ros::NodeHandle nh;
    
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);

    ros::Rate rate(10);

    // 创建坐标点
    geometry_msgs::PointStamped psAtSon1;

    psAtSon1.header.stamp = ros::Time::now();
    psAtSon1.header.frame_id = "son1";
    psAtSon1.point.x = 1.0;
    psAtSon1.point.y = 2.0;
    psAtSon1.point.z = 3.0;

    while (ros::ok()) {
        try {
            // 计算 son1 与 son2 的相对关系
            /*
                A 相对与 B 的坐标系关系

                参数1 目标坐标系 B
                参数2 源坐标系 A
                参数3 ros::Time(0) 取间隔最短的两个坐标关系帧计算相对关系
                返回值 geometry_msgs::TransforStamped 源相对与目标坐标系的相对关系
            */
            geometry_msgs::TransformStamped son1ToSon2 =  buffer.lookupTransform("son2", "son1", ros::Time(0));
            ROS_INFO("son1 关于v son2 的信息: 父级:%s, 子级:%s, 偏移量(%.2f, %.2f, %.2f)", 
                    son1ToSon2.header.frame_id.c_str(), 
                    son1ToSon2.child_frame_id.c_str(),
                    son1ToSon2.transform.translation.x,
                    son1ToSon2.transform.translation.y,
                    son1ToSon2.transform.translation.z
                    );
            
            // 计算 son1 中的某个坐标点在 son2 中的坐标值
            geometry_msgs::PointStamped psAtSon2 = buffer.transform(psAtSon1, "son2");
            ROS_INFO("坐标点在 son2 中的值(%.2f, %.2f, %.2f)",
                    psAtSon2.point.x,
                    psAtSon2.point.y,
                    psAtSon2.point.z);

        } catch (const std::exception& e) {
            ROS_INFO("错误提示:%s", e.what());
        }

        rate.sleep();

        ros::spinOnce();
    }
    
    return 0;
}