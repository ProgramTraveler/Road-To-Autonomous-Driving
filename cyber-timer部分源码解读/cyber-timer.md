# cyber/timer 目录下的函数

## 部分函数功能解释

* `Timer`对象是开放给用户的接口 主要实现了定时器的配置`TimerOption` 启动定时器和关闭定时器 3 个接口
* 定时器的配置 包括定时器周期 回调函数 一次触发还是周期触发(默认为周期触发)

```cpp
	TimerOption(uint32_t period, std::function<void()> callback, bool oneshot) : period(period), callback(callback), oneshot(oneshot) {}
```

---

### timer

* `Timer`对象主要的实现都在`Start()`中
* `Start`中的步骤就是 -> 判断定时器是否以及启动 -> 如果定时没有启动 则初始化定时任务 -> 在时间轮中增加任务

```cpp
void Timer::Start() {

  // 首先判断定时器是否已经启动
  if (!started_.exchange(true)) {
    // 初始化任务
    if (InitTimerTask()) {
      // 在时间轮中增加任务
      timing_wheel_->AddTask(task_);
      AINFO << "start timer [" << task_->timer_id_ << "]";
    }
  }
}
```

---

* 在`Timer`对象中创建`Task`任务并注册回调`task->callback` 任务回调中首先会调用用户传入的`callback()`函数 然后把新的任务放入到下一个时间轮`bucket`中 对应到代码里就是`TimingWheel::Instance()->AddTask(task)`
* `task->next_fire_duration_ms`是任务的下一次执行的间隔 这个时间间隔是以`task`执行完成之后为起始时间的 因为每次插入新任务到时间轮都是在用户`callback`函数执行之后进行的 因此这里的时间起点也是以这个时间为准
* `task->accumulater_error_ns`是累计时间误差 每次插入任务的时候都会修复这个误差 因此这个误差不会一直增大 也就是说假设你第一次执行的比较早 那么累计误差为负值 下次执行的时间间隔就会变长 如果第一次执行的时间比较晚 那么累计误差为正值 下次执行的时间间隔就会缩短 通过动态的调节 保持绝对的时间执行间隔一致

```cpp
bool Timer::InitTimerTask() {

  // 初始化定时任务
  task_.reset(new TimerTask(timer_id_));
  task_->interval_ms = timer_opt_.period;
  task_->next_fire_duration_ms = task_->interval_ms;
  
  // 是否单次触发
  if (timer_opt_.oneshot) {
    std::weak_ptr<TimerTask> task_weak_ptr = task_;
    // 注册任务回调
    task_->callback = [callback = this->timer_opt_.callback, task_weak_ptr]() {
      auto task = task_weak_ptr.lock();
      if (task) {
        std::lock_guard<std::mutex> lg(task->mutex);
        callback();
      }
    };
  } else {
    std::weak_ptr<TimerTask> task_weak_ptr = task_;
    // 注册任务回调
    task_->callback = [callback = this->timer_opt_.callback, task_weak_ptr]() {

      std::lock_guard<std::mutex> lg(task->mutex);
      auto start = Time::MonoTime().ToNanosecond();
      callback();
      auto end = Time::MonoTime().ToNanosecond();
      uint64_t execute_time_ns = end - start;

      if (task->last_execute_time_ns == 0) {
        task->last_execute_time_ns = start;
      } else {
        // start - task->last_execute_time_ns 为2次执行真实间隔时间，task->interval_ms是设定的间隔时间
        // 注意误差会修复补偿，因此这里用的是累计，2次误差会抵消，保持绝对误差为0
        task->accumulated_error_ns +=
            start - task->last_execute_time_ns - task->interval_ms * 1000000;
      }

      task->last_execute_time_ns = start;
      // 如果执行时间大于任务周期时间，则下一个tick马上执行
      if (execute_time_ms >= task->interval_ms) {
        task->next_fire_duration_ms = TIMER_RESOLUTION_MS;
      } else {
        int64_t accumulated_error_ms = ::llround(
            static_cast<double>(task->accumulated_error_ns) / 1e6);
        if (static_cast<int64_t>(task->interval_ms - execute_time_ms -
                                 TIMER_RESOLUTION_MS) >= accumulated_error_ms) {
          // 这里会补偿误差
          task->next_fire_duration_ms =
              task->interval_ms - execute_time_ms - accumulated_error_ms;
        } else {
          task->next_fire_duration_ms = TIMER_RESOLUTION_MS;
        }
 
      }
      TimingWheel::Instance()->AddTask(task);
    };
  }
  return true;
}
```

---

### timing_wheel

* 