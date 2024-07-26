#pragma once
#include "rclcpp/rclcpp.hpp"
#include <map>
#include <type_traits>
#include <QMainWindow>
#include <cmath>
#include "Button.hpp"

class Gui : public QMainWindow {
   std::map<const char* const, rclcpp::Node::SharedPtr> nodes;
public:
   Gui(): QMainWindow() {
      this->setWindowTitle("ATRV-JR");
      this->show();
   }

   template<typename T>
   void addNode(const char* name, QRect layout) {
      static_assert(std::is_base_of<rclcpp::Node, T>::value, "Type is NOT a subtype of rclcpp:Node" );
      nodes[name] = std::make_shared<T>(name, layout, this);
      int32_t minX = std::min(this->frameGeometry().x(), layout.x());
      int32_t minY = std::min(this->frameGeometry().y(), layout.y());
      int32_t maxX = std::max(this->frameGeometry().x() + this->frameGeometry().width(), layout.x() + layout.width());
      int32_t maxY = std::max(this->frameGeometry().y() + this->frameGeometry().height(), layout.y() + layout.height());
      this->move(minX, minY);
      this->resize(std::abs(maxX - minX), std::abs(maxY - minY));
      this->show();
   }

   template<typename T>
   std::shared_ptr<T> setNode(const char* name) {
      static_assert(std::is_base_of<rclcpp::Node, T>::value, "Type is NOT a subtype of rclcpp:Node" );
      return std::dynamic_pointer_cast<T>(nodes[name]);
   }

   void addExec(rclcpp::executors::MultiThreadedExecutor& exe) {
      for(const std::pair<const char* const, rclcpp::Node::SharedPtr>& node : nodes){ exe.add_node(node.second, true); }
   };
   void removeExec(rclcpp::executors::MultiThreadedExecutor& exe) {
      for(const std::pair<const char* const, rclcpp::Node::SharedPtr>& node : nodes){ exe.remove_node(node.second, true); }
   };
};

