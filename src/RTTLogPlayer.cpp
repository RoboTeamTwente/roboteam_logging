//
// Created by rolf on 21-12-20.
//

#include "RTTLogPlayer.h"
void RTTLogPlayer::setPlaySpeedFactor(double factor) {
  playSpeedFactor = std::clamp(factor,0.01,25.0);
}
void RTTLogPlayer::togglePlay() {
  isPlaying = !isPlaying;
}
void RTTLogPlayer::stepBackward() {

}
void RTTLogPlayer::stepForward() {
  sendPacket(reader.readNext());
}
void RTTLogPlayer::sendPacket(const RTTLogMessage& message) {
  pub->send(message.message);
}
void RTTLogPlayer::openFile(const QString& filename) {
  bool success = reader.open(filename);
  if(success){
    opened_file_path = filename;
  }else{
    opened_file_path = "";
  }
}
RTTLogPlayer::RTTLogPlayer() {
  pub = new proto::Publisher<proto::State>(proto::WORLD_CHANNEL);

}
bool RTTLogPlayer::atEOF() const{
  return reader.currentPacket() == reader.numberPackets()-1;
}
