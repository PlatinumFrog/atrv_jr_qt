#pragma once
#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <type_traits>
#include <QMainWindow>
#include <cmath>

class Gui : public QMainWindow {
   std::vector<rclcpp::Node::SharedPtr> nodes;
public:
   Gui(): QMainWindow() {
      this->setWindowTitle("ATRV-JR");
      this->show();
   }
   template<typename T>
   void addNode(const char* name, QRect layout) {
      static_assert(std::is_base_of<rclcpp::Node, T>::value, "Type is NOT a subtype of rclcpp:Node" );
      nodes.push_back(std::make_shared<T>(name, layout, this));
      int32_t minX = std::min(this->frameGeometry().x(), layout.x());
      int32_t minY = std::min(
         this->frameGeometry().y() - this->frameGeometry().height(), 
         layout.y() - layout.height()
      );
      int32_t maxX = std::max(
         this->frameGeometry().x() + this->frameGeometry().width(), 
         layout.x() + layout.width()
      );
      int32_t maxY = std::max(this->frameGeometry().y(), layout.y());
      //this->update(QRect(, ));
      this->move(minX, minY);
      this->resize((maxX - minX), (maxY - minY));
      this->show();
   }
   void addExec(rclcpp::executors::MultiThreadedExecutor& exe) {
      for(const rclcpp::Node::SharedPtr& node : nodes){ exe.add_node(node, true); }
   };
   void removeExec(rclcpp::executors::MultiThreadedExecutor& exe) {
      for(const rclcpp::Node::SharedPtr& node : nodes){ exe.remove_node(node, true); }
   };
};