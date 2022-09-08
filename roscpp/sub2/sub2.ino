#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

void msgCB(const geometry_msgs::Twist& twist) {
    int x = int( twist.linear.x * 100);
    char buf[100];
    sprintf(buf, "x = %d", x);
    nh.loginfo(buf);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &msgCB);

void setup() {
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub);
}

void loop() {
    nh.spinOnce();
    delay(1);
}
