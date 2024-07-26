#include <iostream>

#include <QApplication>

#include "Gui.hpp"
#include "CameraNode.hpp"
#include "Button.hpp"
#include "MapSubscriber.hpp"

int main(int argc, char* argv[]){

    QApplication app(argc, argv);
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor exec;

    Gui gui;

    gui.addNode<CameraNode>("CameraNode", QRect(0, 0, 640, 480));
    gui.addNode<ButtonPublisher>("StringButtonNode", QRect(0, 480, 256, 64));

    gui.setNode<ButtonPublisher>("StringButtonNode")->setText("Publish String");
    gui.setNode<ButtonPublisher>("StringButtonNode")->setMessage("The node has published a string.");
    
    gui.addExec(exec);

    while (rclcpp::ok() && gui.isVisible())
    {
        exec.spin_some();
        app.processEvents();
    }
    gui.removeExec(exec);

    QApplication::quit();
    rclcpp::shutdown();
}