#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <QPushButton>
#include <QMainWindow>

class ButtonPublisher : public rclcpp::Node, public QObject {
   rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
   QPushButton* button;

   void process_click() {
      std_msgs::msg::String m;
      m.data = msg;
      publisher->publish(m);
   }

   const char* msg;

public:
   ButtonPublisher(const char* name, QRect layout, QMainWindow* window): 
      Node(name),
      QObject(),
      button(new QPushButton(window))
   {
      publisher = this->create_publisher<std_msgs::msg::String>("string_msg_topic", 10);
      button->move(layout.x(), layout.y());
      button->resize(layout.width(), layout.height());
      button->setText(name);
      button->show();
      connect(button, &QPushButton::clicked, this, &ButtonPublisher::process_click);
   }

   void setText(const char* text) {
      button->setText(text);
   }

   void setMessage(const char* m) {
      msg = m;
   }
   ~ButtonPublisher() { delete button; }

};