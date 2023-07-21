#include "node.h"
#include "topics/position.h"

class SubNode : public Node {
public:
  using Node::Node;

  void Init() override {
    AddSubscriber<Position>([this](const auto &msg) { position_ = msg; });
  }
  const Position &GetPosition() const { return position_; }

private:
  void StepOnce() override {}
  Position position_{};
};
