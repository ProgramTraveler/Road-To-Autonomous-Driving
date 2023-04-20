#include "ros/ros.h"
#include "plumbing_head_src/hello.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "hello_head_src");
    ros::NodeHandle nh;

    hello_ns::MyHello myHello;

    myHello.run();

    return 0;
}