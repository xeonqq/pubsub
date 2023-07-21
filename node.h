#ifndef NODE_H
#define NODE_H
#include <algorithm>
#include <utility>
#include <vector>

#include "broker.h"

class Node {
public:
  Node(Broker *broker) : broker_{broker} {}

  virtual void Init() = 0;

  void Step() {
    Subscribe();
    StepOnce();
    Publish();
  }

protected:
  template <typename Message, typename Func> void AddSubscriber(Func func) {
    auto topic_cb = [func](const Topic &topic) {
      func(GetMessage<Message>(topic));
    };
    sub_cbs_.emplace_back(GetTopicId<Message>(), std::move(topic_cb));
  }

  template <typename Message, typename Func> void AddPublisher(Func func) {
    auto cb = [func]() -> Topic { return Topic{func()}; };
    pub_cbs_.emplace_back(GetTopicId<Message>(), cb);
  }

private:
  void Subscribe() {
    std::for_each(sub_cbs_.begin(), sub_cbs_.end(), [this](const auto &cb) {
      broker_->Subscribe(cb.first, cb.second);
    });
  };
  void Publish() {
    std::for_each(pub_cbs_.begin(), pub_cbs_.end(), [this](const auto &cb) {
      broker_->Publish(cb.first, cb.second());
    });
  }
  virtual void StepOnce() = 0;
  Broker *broker_;

  std::vector<std::pair<std::size_t, std::function<Topic(void)>>> pub_cbs_;

  std::vector<std::pair<std::size_t, std::function<void(const Topic &)>>>
      sub_cbs_;
};
#endif
