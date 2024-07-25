#include <iostream>

#include <QApplication>

#include "Gui.hpp"
#include "CameraNode.hpp"

int main(int argc, char* argv[]){

    QApplication app(argc, argv);
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor exec;

    Gui gui;
    gui.addNode<CameraNode>("Dog", QRect(0, 0, 640, 480));
    
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