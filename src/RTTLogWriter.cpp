//
// Created by rolf on 18-12-20.
//

#include "RTTLogWriter.h"
#include <fstream>

bool RTTLogWriter::open(const QString &filename) {
  QByteArray fileNameBytes = filename.toUtf8();
  const char * file_name_chars = fileNameBytes.constData();
  file_stream = new std::ofstream(std::ofstream(file_name_chars,std::ios_base::out | std::ios_base::binary));
  if(!file_stream->is_open()){
    std::cerr<<"Error opening log file \""<< file_name_chars<<"\"!"<<std::endl;
    return false;
  }else{
    std::cout<<"Writing to log file \"" << file_name_chars <<"\""<<std::endl;
  }
  LogFileHeader fileHeader;
  fileHeader.version = 0; // 0 is the default for now
  strncpy(fileHeader.name, RTT_LOGFILE_HEADER_NAME, sizeof(fileHeader.name));
  file_stream->write((char *) &fileHeader, sizeof(fileHeader));
  return true;
}
void RTTLogWriter::close() {
  file_stream->clear();
  file_stream->close();
}
bool RTTLogWriter::writeMessage(const proto::State &state, long long int timestamp) {
  QByteArray data;
  data.resize(state.ByteSizeLong());
  if(!state.IsInitialized()){
    std::cerr<<"Cannot write uninitialized Log Frame to logfile! Did you set all required fields?"<<std::endl;
    return false;
  }
  if(!state.SerializeToArray(data.data(),data.size())){
    std::cerr<<"Failed to serialize logFrame"<<std::endl;
    return false;
  }

  LogDataHeader dataHeader{
    .timestamp = timestamp,
    .type = MESSAGE_RTT_STATE,
    .messageSize = data.size()
  };

  //Write header to file, followed by data
  file_stream->write((char *) &dataHeader,sizeof(dataHeader));
  file_stream->write(data.data(), data.size());
  return true;
}
