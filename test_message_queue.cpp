#include <iostream>
//#include <memory>
#include <thread>
#include <mutex>

#include "message_queue.h"

#include <string>
typedef std::string Message;
typedef message_queue<Message> MessageQueue;

// for cout synchronization
std::mutex print_mutex;

class Worker
{
public:
  Worker(MessageQueue *mqptr)
  {
    m_mq = mqptr;
  };
  void operator()() const
  {
    while(true)
      {
	Message m;
	m_mq->wait_and_pop(m);
	std::lock_guard<std::mutex> guard(print_mutex);
	std::cout << "Message: " << m.c_str() << " from " << std::this_thread::get_id()  << std::endl;
	if(m == "quit") break;
      }
  };

private:
  
  MessageQueue * m_mq;
};

int main()
{
  std::cout << "Running in main thread" << std::endl;

  MessageQueue mq;

  std::cout << "Starting some threads" << std::endl;

  Worker w1(&mq);
  std::thread th1(w1);

  Worker w2(&mq);
  std::thread th2(w2);

  std::cout << "Sending messages to the threads" << std::endl;

  Message message = "Hello 1";
  mq.push(message);

  message = "Hello 2";
  mq.push(message);

  message = "Hello 3";
  mq.push(message);

  message = "quit";
  mq.push(message);
  mq.push(message);
  
  th1.join();
  th2.join();

  return 0;
}
