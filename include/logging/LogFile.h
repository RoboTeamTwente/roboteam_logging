//
// Created by rolf on 18-12-20.
//

#ifndef RTT_ROBOTEAM_LOGGING_INCLUDE_LOGFILE_H_
#define RTT_ROBOTEAM_LOGGING_INCLUDE_LOGFILE_H_

static constexpr char * RTT_LOGFILE_HEADER_NAME = "RTT_LOG_FILE"; //In order to check if the file format is right.
static constexpr char * SSL_LOGFILE_HEADER_NAME = "SSL_LOG_FILE";

struct LogFileHeader{
  char name[12]; //
  int version; // Default format is version 0
};
enum MessageType :uint32_t{
  MESSAGE_BLANK = 0,
  MESSAGE_UNKNOWN = 1,
  MESSAGE_SSL_VISION_2010 = 2,
  MESSAGE_SSL_REFBOX_2013 = 3,
  MESSAGE_SSL_VISION_2014 = 4,

  MESSAGE_RTT_STATE=15

};

struct LogDataHeader{
  long long int timestamp;
  MessageType type;
  int messageSize;
};
#endif //RTT_ROBOTEAM_LOGGING_INCLUDE_LOGFILE_H_
