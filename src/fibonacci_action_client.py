import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from action_tutorial_interface import Fibonacci

class FibonacciActionClient(Node):
    def __init__(self):
        super().__init__("action_client")
        self._action_client = ActionClient(self, Fibonacci, "fibonacci")

    def send_goal(self, order):
        goal_msg = Fibonocci.Goal()
        
