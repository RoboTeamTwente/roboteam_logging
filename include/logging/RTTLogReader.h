//
// Created by rolf on 18-12-20.
//

#ifndef RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_
#define RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_

#include <QString>
#include <memory>
#include "unordered_map"
#include <roboteam_proto/State.pb.h>

struct RTTLogMessage{
  long long int timestamp = -1;
  proto::State message;
};
class RTTLogReader {
 public:
  bool open(const QString& file_name);
  void close();
  RTTLogMessage readNext();
  RTTLogMessage readPrevious();
  RTTLogMessage readPacket(int packetNumber);
  int numberPackets() const;
  int currentPacket() const; //returns the nr of last packet sent
  long long int startingTime() const;
  long long int endingTime() const;
 private:
  void placePosition(int packetNumber);
  bool indexFile();
  std::ifstream * file_in_stream;
  std::unordered_map<int,long> file_index;
  long startPosition;
  long long int startTime;
  long long int endTime;
  int currentPacketNr;
};

#endif //RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_
