#ifndef FAKE_IO_CONTEXT_H
#define FAKE_IO_CONTEXT_H

#include <condition_variable>  // std::condition_variable
#include <functional>          // std::function
#include <mutex>               // std::mutex/lock_guard/unique_lock
#include <queue>               // std::queue

namespace asio {

using std::condition_variable;
using std::function;
using std::lock_guard;
using std::mutex;
using std::queue;
using std::unique_lock;

class io_context {
public:
    using task_t = function<void()>;

    void post(task_t task)
    {
        {
            lock_guard guard{mtx_};
            task_queue_.push(std::move(task));
        }
        state_.notify_one();
    }

    void run()
    {
        bool is_my_last_task{};
        for (;;) {
            task_t task;
            {
                unique_lock lock{mtx_};
                if (is_my_last_task) {
                    is_my_last_task = false;
                    --last_tasks_executing_;
                }
                state_.wait(lock, [&] {
                    return !task_queue_.empty() ||
                           last_tasks_executing_ == 0;
                });
                if (task_queue_.empty() &&
                    last_tasks_executing_ == 0) {
                    break;
                }
                task = std::move(task_queue_.front());
                task_queue_.pop();
                if (task_queue_.empty()) {
                    is_my_last_task = true;
                    ++last_tasks_executing_;
                }
            }
            task();
        }
        // Wake other threads potentially waiting
        state_.notify_one();
    }

private:
    mutex mtx_;
    condition_variable state_;
    queue<task_t> task_queue_;
    int last_tasks_executing_;
};

inline void post(io_context& ctx, io_context::task_t task)
{
    ctx.post(std::move(task));
}

} // namespace asio

#endif // FAKE_IO_CONTEXT_H
