# ros2-falcon

ros2-falcon is a ros2 package that abstracts the operation of the Novint Falcon haptic controller (using the open-source library [libnifalcon](https://github.com/libnifalcon/libnifalcon)) on the following topics:

### Publishers:

-   /falcon/buttons/center (std_msgs/Bool)
-   /falcon/buttons/left (std_msgs/Bool)
-   /falcon/buttons/right (std_msgs/Bool)
-   /falcon/buttons/up (std_msgs/Bool)
-   /falcon/position (geometry_msgs/Vector3)

### Subscribers:

-   /falcon/force (geometry_msgs/Vector3)
-   /falcon/rgb (geometry_msgs/Vector3)

## Installation

First, clone this repository to your workspace and run _install.sh_ to build and install libnifalcon:

```bash
cd ~/colcon_ws/src # considering that your workstation is named colcon_ws
git clone https://github.com/jvmoraiscb/ros2-falcon.git # clone the repo
cd ros2-falcon/libnifalcon && ./install.sh # cd and run installation script
```

Second, run rosdep to ensure that all ros dependencies are installed:

```bash
cd ~/colcon_ws # considering that your workstation is named colcon_ws
rosdep install --from-paths src -y --ignore-src
```

## Running

Build your workspace, source and run the package:

```bash
cd ~/colcon_ws # considering that your workstation is named colcon_ws
colcon build # build :)
source install/setup.bash # source :)
ros2 run ros2-falcon main # and finally, run :)
```
