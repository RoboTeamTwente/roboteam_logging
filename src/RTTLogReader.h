//
// Created by rolf on 18-12-20.
//

#ifndef RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_
#define RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_

#include <QString>
#include <memory>
#include "unordered_map"
class RTTLogReader {
 public:
  bool open(const QString& file_name);

 private:
  bool indexFile();
  std::unique_ptr<std::ifstream> file_in_stream;
  std::unordered_map<int,long> file_index;
  long startPosition;
};

#endif //RTT_ROBOTEAM_LOGGING_SRC_RTTLOGREADER_H_
