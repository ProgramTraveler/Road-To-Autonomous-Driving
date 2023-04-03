# Planning

## Planning 模块入口

* Planning 模块入口为 planning_component.cc 和 planning_component.h 两个文件
* 在 .h 文件中可以看见实现订阅和发布消息 也就是定义了一堆 reader 和 writer
* 同时在 .h 文件中也实现在 cyber 中注册模块 **不知道是不是固定写法**

## 模块初始化

* 模块的初始化通过 planning_component.cc 中的 Init() 方法来实现初始化