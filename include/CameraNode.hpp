#pragma once
#include <QMainWindow>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "ros_image_to_qimage/ros_image_to_qimage.hpp"
#include <QImage>
#include <QLabel>

class CameraNode : public rclcpp::Node {
 private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription;
    void subCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
        label->setPixmap(QPixmap::fromImage(ros_image_to_qimage::Convert(*msg)));
    }
    QLabel* label;
 public:

    CameraNode(const char* name, QRect layout, QMainWindow* window):
        Node(name),
        label(new QLabel(window))
    {
        
        subscription = this->create_subscription<sensor_msgs::msg::Image>(
            "/image_raw", 
            10, 
            std::bind(
                &CameraNode::subCallback,
                this, 
                std::placeholders::_1
            )
        );

        //label->update(layout);
        label->move(layout.x(), layout.y());
        label->resize(layout.width(), layout.height());
        label->show();
    }
    ~CameraNode() {
        delete label;
    }
};