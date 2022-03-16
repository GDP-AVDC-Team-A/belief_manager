#include "belief_manager_process.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  BeliefManagerProcess belief_manager;

  belief_manager.setUp();
  belief_manager.start();
  
  ros::spin();
}
