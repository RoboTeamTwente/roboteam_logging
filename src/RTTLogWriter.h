//
// Created by rolf on 18-12-20.
//

#ifndef RTT_ROBOTEAM_LOGGING_SRC_RTTLOGWRITER_H_
#define RTT_ROBOTEAM_LOGGING_SRC_RTTLOGWRITER_H_

#include <memory>
#include <iostream>
#include <QString>
#include "LogFile.h"
#include <roboteam_proto/State.pb.h>

class RTTLogWriter {
 public:
  bool open(const QString& filename);
  void close();
  bool writeMessage(const proto::State& message, long long int timestamp);
 private:
  std::unique_ptr<std::ofstream> file_stream;
};

#endif //RTT_ROBOTEAM_LOGGING_SRC_RTTLOGWRITER_H_
