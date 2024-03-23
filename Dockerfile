FROM ros:humble

LABEL maintainer="jv.moraiscb@gmail.com"
LABEL version="1.1.0"
LABEL description="ROS2 Novint Falcon Package Docker image"

ARG DEBIAN_FRONTEND=noninteractive

RUN mkdir -p /colcon_ws/src

COPY . /colcon_ws/src

RUN cd /colcon_ws/src && . install.sh

RUN . /opt/ros/humble/setup.sh && \
cd /colcon_ws && \
rosdep install -i --from-path src --rosdistro humble -y && \
colcon build

CMD . /colcon_ws/install/setup.sh && \
ros2 run ros2-falcon main
