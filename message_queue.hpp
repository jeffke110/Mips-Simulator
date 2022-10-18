#ifndef MESSAGE_QUEUE
#define MESSAGE_QUEUE

#include <queue>
#include <mutex>
#include <iostream>
#include <string>
#include <condition_variable>
#include <thread>

template<typename MessageType>
class message_queue
{
public:
    std::size_t length() const {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.size();
    }

    MessageType frontElement() const {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.front();
    }
    void push(MessageType const& message)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        the_queue.push(message);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(MessageType& popped_value)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }

        popped_value = the_queue.front();
        the_queue.pop();
        return true;
    }

    void wait_and_pop(MessageType& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        while (the_queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        popped_value = the_queue.front();
        the_queue.pop();

    }

private:
    std::queue<MessageType> the_queue;
    mutable std::mutex the_mutex;
    std::condition_variable the_condition_variable;

};

#endif 