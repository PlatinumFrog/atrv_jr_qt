#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class ButtonPublisher : public rclcpp::Node {
 private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;

 public:
   ButtonPublisher() : Node("Button_Node"){
      publisher = this->create_publisher<std_msgs::msg::String>("string_msg_topic", 10);
   };
   void publishMsg(const std::string msg){
      std_msgs::msg::String m;
      m.data = msg;
      publisher->publish(m);
   }
};