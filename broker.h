#ifndef BROKER_H
#define BROKER_H
#include "topic.h"

#include <functional>
#include <map>
#include <queue>

class Broker {
  using TopicQueue = std::vector<Topic>;

public:
  void Publish(std::size_t topic_id, Topic topic) {
    auto &q = topic_to_message_queue_[topic_id];
    q.push_back(std::move(topic));
  }

  template <typename Func> void Subscribe(std::size_t topic_id, Func &&cb) {
    auto &q = topic_to_message_queue_[topic_id];
    for (const auto &v : q) {
      std::forward<Func>(cb)(v);
      // only pass the lastest one
      break;
    }
  }

private:
  std::map<std::size_t, TopicQueue> topic_to_message_queue_;
};
#endif
