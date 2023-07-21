#include "broker.h"
#include "pub_node.h"
#include "sub_node.h"
#include "gtest/gtest.h"

TEST(pubsub, OnePublishOneSubscribe) {
  Broker broker;

  PubNode pub_node{&broker};
  pub_node.Init();
  pub_node.Step();

  SubNode sub_node{&broker};
  sub_node.Init();
  sub_node.Step();

  EXPECT_EQ(sub_node.GetPosition().x, 42);
}

TEST(pubsub, OnePublishTwoSubscribe) {
  Broker broker;

  PubNode pub_node{&broker};
  pub_node.Init();
  pub_node.Step();

  SubNode sub_node{&broker};
  sub_node.Init();
  sub_node.Step();

  SubNode sub_node2{&broker};
  sub_node2.Init();
  sub_node2.Step();

  EXPECT_EQ(sub_node.GetPosition().x, 42);
  EXPECT_EQ(sub_node2.GetPosition().x, 42);
}

TEST(pubsub, OnePublishTwice_OneSubscribe) {
  Broker broker;

  PubNode pub_node{&broker};
  SubNode sub_node{&broker};
  pub_node.Init();
  sub_node.Init();

  pub_node.Step();
  sub_node.Step();
  EXPECT_EQ(sub_node.GetPosition().x, 42);

  pub_node.Step();
  sub_node.Step();
  EXPECT_EQ(sub_node.GetPosition().x, 43);
}
