#include "node.h"
#include "topics/position.h"

class PubNode : public Node {
public:
  using Node::Node;

  void Init() override {
    AddPublisher<Position>([]() { return Position{42}; });
  }

private:
  void StepOnce() override {}
};
