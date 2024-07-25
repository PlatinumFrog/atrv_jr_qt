from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node
from launch.substitutions import Command
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    ld = LaunchDescription()

    ld.add_action(
        Node(
            package='usb_cam',
            executable='usb_cam_node_exe',
            output='screen'
        )
    )

    ld.add_action(
        Node(
            package='atrv_jr_qt',
            executable='atrv_jr_qt',
            output='screen'
        )
    )
    
    return ld