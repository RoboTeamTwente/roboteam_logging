//
// Created by rolf on 21-12-20.
//

#include <logging/RTTLogPlayer.h>



int main(){
  RTTLogPlayer player;
  player.openFile("test.log");

  while(!player.atEOF()) {
    player.stepForward();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}