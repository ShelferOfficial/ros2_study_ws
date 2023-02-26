/* ROS1風subscriber のcallback関数のかわりにlambda関数を用いたver.

*/

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/qos.hpp>
#include <example_interface/msg/string.hpp>

int main (int argc, char argv[]) {
    rclcpp::init(argc, argv);

    node = rclcpp::Node::make_shared("ros1_like_subscriber_test");
    auto subscription = node->create_subscription<example_interfaces::msg::String>(
        "topic_test",
        rclcpp::QoS(10),
        //返り値がvoidで引数がconst example_interfaces::msg::String::SharedPtr msgのlambda関数．
        [](const example_interfaces::msg::String::SharedPtr msg) -> void {
            RCLCPP_INFO(node->get_logger(), "I heard: %s", msg->data.c_str());
        }
    );

    rclcpp::spin(node);
    rclcpp::shutdown();


    return 0;

} 