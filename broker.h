#ifndef BROKER_H
#define BROKER_H
#include "topic.h"

#include <functional>
#include <map>
#include <queue>

template <typename T, int MaxLen, typename Container = std::deque<T>>
class FixedQueue : public std::queue<T, Container> {
public:
  void push(T value) {
    if (this->size() == MaxLen) {
      this->c.pop_front();
    }
    std::queue<T, Container>::push(std::move(value));
  }
};

class Broker {
  using TopicQueue = FixedQueue<Topic, 1>;

public:
  void Publish(std::size_t topic_id, Topic topic) {
    auto &q = topic_to_message_queue_[topic_id];
    q.push(std::move(topic));
  }

  template <typename Func> void Subscribe(std::size_t topic_id, Func &&cb) {
    auto &q = topic_to_message_queue_[topic_id];
    if (!q.empty()) {
      // only pass the lastest one
      std::forward<Func>(cb)(q.back());
    }
  }

private:
  std::map<std::size_t, TopicQueue> topic_to_message_queue_;
};
#endif
