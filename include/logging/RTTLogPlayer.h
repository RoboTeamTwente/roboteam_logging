//
// Created by rolf on 21-12-20.
//

#ifndef RTT_ROBOTEAM_LOGGING_SRC_RTTLOGPLAYER_H_
#define RTT_ROBOTEAM_LOGGING_SRC_RTTLOGPLAYER_H_

#include "RTTLogReader.h"
#include <Publisher.h>
class RTTLogPlayer {
 public:
  RTTLogPlayer();
  void eventLoop();
  void openFile(const QString& fileName);
  bool atEOF() const;
  void stepForward();
 private:
  void stepBackward();
  void togglePlay();
  void setPlaySpeedFactor(double factor);
  void sendPacket(const RTTLogMessage& message);


  proto::Publisher<proto::State> * pub;
  RTTLogReader reader;
  QString opened_file_path ="";
  bool isPlaying = false;
  double playSpeedFactor = 1.0;
  long long int replayTime = -1;
};

#endif //RTT_ROBOTEAM_LOGGING_SRC_RTTLOGPLAYER_H_
