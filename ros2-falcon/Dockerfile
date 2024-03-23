FROM ros:humble

LABEL maintainer="jv.moraiscb@gmail.com"
LABEL version="1.1.0"
LABEL description="ROS2 Novint Falcon Package Docker image"

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install -y git

RUN mkdir -p /colcon_ws/src

RUN cd /tmp && \
git clone https://github.com/jvmoraiscb/ros2-libnifalcon.git && cd ros2-libnifalcon && \
. install.sh && \
cp -R ros2-falcon /colcon_ws/src

RUN . /opt/ros/humble/setup.sh && \
cd /colcon_ws && \
rosdep install -i --from-path src --rosdistro humble -y && \
colcon build

CMD . /opt/ros/humble/setup.sh && \
. /colcon_ws/install/local_setup.sh && \
ros2 run ros2-falcon main
