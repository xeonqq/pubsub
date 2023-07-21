#ifndef TOPIC_H
#define TOPIC_H

#include <cstddef>
#include <functional>
#include <memory>

inline std::size_t NextId() {
  static size_t id = 0;
  return id++;
}

/** Returns a small value which identifies the type.
    Multiple calls with the same type return the same value. */
template <typename T> size_t GetTopicId() {
  static std::size_t id = NextId();
  return id;
}

class Topic {

private:
  struct Concept {
    virtual ~Concept() = default;
  };

public:
  template <typename T>
  Topic(T x) : self_(std::make_unique<Model<T>>(std::move(x))) {}

  template <typename U> friend U GetMessage(const Topic &topic);

private:
  template <typename T> struct Model final : public Concept {
    Model(T x) : data_(std::move(x)) {}
    T data_;
  };
  std::unique_ptr<const Concept> self_;
};

template <typename U> U GetMessage(const Topic &topic) {
  const auto concept = topic.self_.get();
  const auto model = static_cast<const Topic::Model<U> *const>(concept);
  return model->data_;
}
#endif
