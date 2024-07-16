#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    QPushButton button("Hello World!");
    button.show();

    return app.exec();
}