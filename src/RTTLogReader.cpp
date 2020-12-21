//
// Created by rolf on 18-12-20.
//

#include "RTTLogReader.h"
#include "LogFile.h"
#include <fstream>
#include <iostream>

bool RTTLogReader::open(const QString &file_name) {
  QByteArray fileNameBytes = file_name.toUtf8();
  const char* fname = fileNameBytes.data();
  file_in_stream = new std::ifstream(std::ifstream(fname, std::ios_base::in | std::ios_base::binary));
  if (! file_in_stream->is_open()) {
    std::cerr << "Error opening log file \"" + file_name.toStdString() + "\"!" << std::endl;
    return false;
  }
  LogFileHeader fileHeader;
  file_in_stream->read((char*) &fileHeader, sizeof(fileHeader));
  if (strncmp(fileHeader.name,RTT_LOGFILE_HEADER_NAME , sizeof(fileHeader.name)) != 0) {
    std::cerr << "Unrecognized logfile header! : " << fileHeader.name<< std::endl;
    return false;
  }
  else if (fileHeader.version != 0) {
    std::cerr << "Invalid log version!" << std::endl;
    return false;
  }
  std::cout << "Opened " + file_name.toStdString() + " as log version "
      + QString::number(fileHeader.version).toStdString() + " (default is 0)" << std::endl;
  return indexFile();
}
bool RTTLogReader::indexFile() {
  startPosition = file_in_stream->tellg();
  LogDataHeader dataHeader;
  file_index.clear();
  int packetNumber = 0;
  // get the packet offsets for all packets
  bool firstLoop = true;
  long long int lastTime = -1;
  while (! file_in_stream->eof() && file_in_stream->is_open()) {
    file_index[packetNumber] = file_in_stream->tellg();
    file_in_stream->read((char*) &dataHeader, sizeof(dataHeader));
    if (file_in_stream->bad()) {
      std::cerr << "Error indexing file: bad read" << std::endl;
      return false;
    }
    if (file_in_stream->eof()) {
      break; //note that we have also indexed the very end of the file, so our index is exactly one longer than
      //the amount of messages
    }
    if(dataHeader.type != MessageType::MESSAGE_RTT_STATE){
      std::cerr<<"Message type was not the RTT_STATE! Are you sure you picked the right log file?"<<std::endl;
      return false;
    }
    if(firstLoop){
      startTime = dataHeader.timestamp;
    }
    lastTime = dataHeader.timestamp;
    file_in_stream->seekg(long(file_in_stream->tellg()) + dataHeader.messageSize);
    packetNumber ++;
  }
  endTime = lastTime;
  file_in_stream->clear();
  file_in_stream->seekg(startPosition);
  currentPacketNr = -1;
  std::cout<<"File contains: "<< numberPackets() << " packets"<<std::endl;
  return true;
}
RTTLogMessage RTTLogReader::readNext() {
  RTTLogMessage message = RTTLogMessage();
  if (! file_in_stream->eof()) {
    LogDataHeader dataHeader;
    file_in_stream->read((char*) &dataHeader, sizeof(dataHeader));

    //very last data point is invalid at eof
    if (file_in_stream->eof()) {
      file_in_stream->clear();
      return message;
    }
    //Convert endian
    //read protobuf file data.
    char buffer[dataHeader.messageSize];
    file_in_stream->read(buffer, dataHeader.messageSize);
    ++currentPacketNr;
    QByteArray data = QByteArray(buffer, dataHeader.messageSize);//set data
    bool success = message.message.ParseFromArray(data.data(), data.size());
    if (success) {
      message.timestamp = dataHeader.timestamp;
    }
    else {
      return message;
    }
  }
  file_in_stream->clear();
  return message;
}
void RTTLogReader::placePosition(int packetNumber) {
  file_in_stream->seekg(file_index[packetNumber]);
}
RTTLogMessage RTTLogReader::readPacket(int packetNumber) {
  placePosition(packetNumber);
  currentPacketNr = packetNumber;
  return readNext();
}
int RTTLogReader::numberPackets() const{
  return (int)file_index.size()-1;
}
RTTLogMessage RTTLogReader::readPrevious() {
  currentPacketNr--;
  if(currentPacketNr<0){
    currentPacketNr = 0;
  }
  placePosition(currentPacketNr);
  return readNext();
}
int RTTLogReader::currentPacket() const {
  return currentPacketNr;
}
long long int RTTLogReader::startingTime() const {
  return startTime;
}
long long int RTTLogReader::endingTime() const {
  return endTime;
}
void RTTLogReader::close() {
  file_in_stream = nullptr;
  file_index.clear();
  startPosition = 0;
  startTime = 0;
  endTime = 0;
  currentPacketNr = 0;
}

