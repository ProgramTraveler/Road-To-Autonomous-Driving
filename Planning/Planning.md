# Planning

## Planning 模块入口

* Planning 模块入口为 planning_component.cc 和 planning_component.h 两个文件
* 在 .h 文件中可以看见实现订阅和发布消息 也就是定义了一堆 reader 和 writer
* 同时在 .h 文件中也实现在 cyber 中注册模块 **不知道是不是固定写法**

## 模块初始化

* 模块的初始化通过 planning_component.cc 中的 Init() 方法来实现初始化


## 函数调用过程

* 首先是从 **PlanningComponent.cc** 的初始化函数 Init() 中的 `planning_base_->Init(config)` 
* 进入到 **on_lane_planning.cc** 的初始化函数 Init() 然后是 `PlanningBase::Init(config)` 进行一些工厂类的注册 其中是一些决策类的初始化和类的一些注册(task_factory.cc) 重点是 `reference_line_provider_->Start()`
* 跳转到 **reference_line_provider.cc** 中的 `Start()` 其中 `&ReferenceLineProvider::GenerateThread` (单独开的一个线程) 其中有 `CreateReferenceLine(&reference_lines, &segment)` 进入到这个函数 有两个函数 一个是 `CreateRouteSegment()` (当前有多少车道) 进入这个函数查看内容 另一个是优化函数 `SmoothRouteSegment()` 重要的是 `Smooth()` (主要是 Discre...) 在 Smooth 里面又会看到两个优化方法 一个是 `CosThetaSmooth()` 另一个是 `FemPosSmooth()`
* 回到 `planning_component.cc` 执行完之后 会到 `Proc()` 最主要的是 `planning_base_->RunOnce()` (OnLanePlanning)
* 进入到 **on_lane_planning.cc** 中的 `RunOnce()` 可以顺便看一下 **Reference_line.h** (最主要的是参考点) 在 RunOnce() 中正式的路径规划入口 `Status = Plan()` 进入到 `Plan()` 方法 然后从 `status = planner_->Plan()` 进入到 **publice_road_planner.cc** 中的 `Plan()` 进行场景处理 进入到 **scenario.cc** 的 `Process()` 通过 `ret = current_stage_->Process()` 继续去处理
* 然后进入到 **lane_follow_stage.cc** 中的 `Process()` 通过 `cur_status = PlanOnReferenceLine()` 进入到 PlanOnReferenceLine() (task_list)
* 然后进入到 **decider.cc** 中的 `Excute` 返回一个 Process()
* 进入的是 **lane_change_decider.cc** 中的 `Process()` 
