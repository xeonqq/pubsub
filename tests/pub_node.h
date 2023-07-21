#include "node.h"
#include "topics/position.h"

class PubNode : public Node {
public:
  using Node::Node;

  void Init() override {
    AddPublisher<Position>([this]() { return Position{x_}; });
  }

private:
  void StepOnce() override { ++x_; }
  int x_{41};
};
