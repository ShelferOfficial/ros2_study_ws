/*  callback 関数を使用したsubscriber
    準備
$ cd ~/ros2_studies_ws
$ ros2 pkg crete minimal_sybscriber_ros1_like -dependencies rclcpp example_interfaces

メモ

topic : topicとはpublisherとsubscriberのやりとりである．
    ROSシステムでは同時に複数のtopicが存在するので区別するために名前が付けられる．これをtopic名と呼ぶ．
    関係はpublisherが主でありsubscriberが従である．topic名もpublisherが指定し，subscriberはpublisherが公開しているtopic名を見ていて
    情報が発信されたら受け取り処理が生じるようになっている．

msg : やりとりするデータそのものはmsgなどと表記する．または，topic messageなど？
    利用できる変数の種類は About ROS2 interfaces にある．https://index.ros.org/doc/ros2/Concepts/About-ROS-Interfaces/

    msgはmsgファイルというテキストファイルで記述する．変数の型と変数名を適切にテキスト形式で記述することで，ROS2が勝手にクラス化し使えるようにしてくれる．

    ROS2がデフォルトで(とりあえずぱっと使えるように)提供するexample_interfacesプロジェクトにはmsgとして文字stringを扱うメッセージを使える．この時，

    example_interfacesの中のmsgディレクトリの中のString.msgを使う
    と考え，利用のためにインクルードするファイルは

    #include "example_interfaces/msg/string.hpp"

    となる．大文字・小文字の扱いはROS2独自メッセージの作成にて説明する．
    またソースの中では，

    example_interfaces::msg::String
    
    で表されるクラスとして利用する．    


*/


#include <rclcpp/rclcpp.hpp>
#include <rclcpp/qos.hpp>
#include <example_interfaces/msg/string.hpp>

rclcpp::Node::SharedPtr node = nullptr;

/*main関数とcallback関数(topic_callback)の両方でnodeを使用するので5行目のようにglobal変数にしてヌルポインタを代入しておく*/
void topic_callback(const example_interfaces::msg::string::SharedPtr msg) {
    RCLCPP_INFO(node->get_logger(), "Iheard: %s", msg->data.c_str()); /*msg を出力するだけ  c_str : C言語の文字列に変換 */
}

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    /* node作成*/
    node=rclcpp::Node::make_shared("ros1_like_subscriber_test");
    
    /*node をsubscriberとして使用するための設定
    ・<>内はsubscriberとして(publisherから)受け取るメッセージの種類の設定
    auto型で定義しているが、本来はSubscription型のスマートポインタ*/
    auto subscription = node->criate_usbscription<example_interfaces::msg::String>(
        "topic_test",
        /* rclcpp::QoS(n) -> historyをnほど持つ(適当でおk)　*/
        rclcpp::QoS(10),
        std::bind(topic_callback, std::placeholders::_1)
    );

    /*nodeの実行*/
    rclcpp::spin(node);
    rclcpp::shutdown();

    subscription = nullptr;
    node=nullptr;
    
    return 0;
}