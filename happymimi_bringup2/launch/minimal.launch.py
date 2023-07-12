from ament_index_python.packages import get_package_share_path
from launch.actions import DeclareLaunchArgument # Launchファイルのトップレベルの要素.複数のノードやアクションを含むLaunchの記述を作成
from launch import LaunchDescription
from launch_ros.actions import Node # ノードを起動するため
from launch.substitutions import Command, # コマンドライン実行の置換.LaunchFile内で動的なコマンドを生成
                                 LaunchConfiguration # 起動引数の値を取得するための置換.パラメータを外部ノードから扱えるようにパイプ接続
from launch_ros.parameter_descriptions import ParameterValue # Sノードのパラメータの値を表すため

def generate_launch_description():
    description_package_path = get_package_share_path('happymimi_description')
    bringup_package_path = get_package_share_path('happymimi_bringup')
    default_model_path = description_package_path / 'robots/happymimi.urdf.xacro' ###
    default_rviz_config_path = bringup_package_path / 'rviz/mega3.rviz'
    rviz_arg = DeclareLaunchArgument(name='rvizconfig', default_value=str(default_rviz_config_path),
                                     description='Absolute path to rviz config file')


    # rviz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
    )

    # joint_state_publisher_node


    # robot_state_publisher_node

    
    # pub_odom
    pub_odom_node = Node(
        package="happymimi_bringup",
        executable="pub_odom",
        name='pub_odom'
        parameters=[{
            "port":"/dev/ttyUSB0",
            "baud":115200
        }]
        remappings=[('/rover_twist', '/cml_vel')],
    )

    return LaunchDescription([
        model_arg,
        #rviz_arg,
        #robot_state_publisher_node,
        #joint_state_publisher_node,
        pub_odom_node,
        rviz_node,
    ])
