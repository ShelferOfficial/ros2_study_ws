import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer

from action_tutorial_interface import Fibonacci

class FibonacciServer(Node):
    def __init__(self):
        super().__init__("fibonacci_server")
        self._action_server = ActionServer(self, Fibonacci, "fibonacci", self.execute_callback)

    def executable_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')

        feedback_msg = Fibonacci.Feedback()
        feedback_msg.partial_sequence = [0, 1]        

        
        
