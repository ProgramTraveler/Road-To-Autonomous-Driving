# cyber/component

## Component 介绍

* `component`是`cyber`为了帮助我们特意实现的类
* `component`加载的时候会自动帮我们创建一个`node` 通过`node`来订阅和发布对应消息 每个`component`有且只能对应一个`node`
* `component`对用户提供两个接口`Init()`和`Proc()` 用户在`Init()`中进行初始化 在`Proc()`中接受`Topic`执行具体的算法 对用户隐藏的部分包括`component`的`Initialize()`初始化 以及`Process()`调用执行
* `component`还可以动态的加载和卸载 也可以对应到在`dreamviewer`上动态的打开关系模块

## Component 工作流程

* 通过继承`cyber::Component` 用户自定义一个模块 并且实现`Init()`和`Proc()`函数 编译生成`.so`文件
* 通过`classloader`加载`component`模块到内存 创建`component`对象 调用`Initialize()`初始化 (`Initialize`中会调用`Init`)
* 创建协程任务 并且注册`Process()`回调 当数据到来的时候 唤醒对象的协程任务执行`Process()`处理数据 (`Process()`会调用`Proc`)
* `component`帮助用户把初始化和数据收发的流程进行封装 减少用户的工作量 `component`封装了整个数据的收发流程 `component`本身并不是一个单独的一个线程执行 模块的初始化都在主线程中执行 而具体的任务则是在协程池中执行

## cyber 入口

* `cyber`入口在`cyber/mainboard/http://mainboard.cc`中
* 主函数会先进行`cyber`的初始化 然后启动`cyber`模块 然后运行 一直等到系统结束

```cpp
int main(int argc, char** argv) {
  // parse the argument
  // 解析参数
  ModuleArgument module_args;
  module_args.ParseArgument(argc, argv);

  // initialize cyber
  // 初始化 cyber
  apollo::cyber::Init(argv[0]);

  // start module
  // 运行模块 启动 cyber 模块
  ModuleController controller(module_args);
  if (!controller.Init()) {
    controller.Clear();
    AERROR << "module start error.";
    return -1;
  }
  
  // 等待 cyber 关闭
  apollo::cyber::WaitForShutdown();
  // 卸载模块
  controller.Clear();
  AINFO << "exit mainboard.";

  return 0;
}
```

---

## component 动态加载

* `cyber`函数在`ModuleController::Init()`进行加载 具体的加载过程在`ModuleController::LoadModule`中
* 模块首先通过`classloader`加载到内存 然后创建对象 并且调用模块的初始化方法 
* `component`中每个模块都设计为可以动态加载和卸载 可以实时在线的开启和关闭模块 实现的方式是通过`classloader`来进行动态的加载动态库

```cpp
bool ModuleController::LoadModule(const DagConfig& dag_config) {
  const std::string work_root = common::WorkRoot();

  for (auto module_config : dag_config.module_config()) {
    
    std::string load_path;
    if (module_config.module_library().front() == '/') {
      load_path = module_config.module_library();
    } else {
      load_path =
          common::GetAbsolutePath(work_root, module_config.module_library());
    }

    if (!common::PathExists(load_path)) {
      AERROR << "Path does not exist: " << load_path;
      return false;
    }
	
	// 加载动态库
    class_loader_manager_.LoadLibrary(load_path);
	
	// 加载消息触发模块
    for (auto& component : module_config.components()) {
      const std::string& class_name = component.class_name();
      
      // 创建对象
      std::shared_ptr<ComponentBase> base =
          class_loader_manager_.CreateClassObj<ComponentBase>(class_name);
      
      // 调用对象的 Initialize 方法
      if (base == nullptr || !base->Initialize(component.config())) {
        return false;
      }
      component_list_.emplace_back(std::move(base));
    }
	
	// 加载定时触发模块
    for (auto& component : module_config.timer_components()) {
      // 创建对象
      const std::string& class_name = component.class_name();
      std::shared_ptr<ComponentBase> base =
          class_loader_manager_.CreateClassObj<ComponentBase>(class_name);
      
      // 调用对象的 Initialize 方法
      if (base == nullptr || !base->Initialize(component.config())) {
        return false;
      }
      component_list_.emplace_back(std::move(base));
    }
  }
  return true;
}
```

---

## 部分函数功能解释

* 见 pdf