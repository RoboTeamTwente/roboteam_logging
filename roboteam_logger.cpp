//
// Created by rolf on 21-12-20.
//

#include <logging/RTTLogWriter.h>
#include <Subscriber.h>
#include <roboteam_utils/Time.h>

class application{
 public:
  void start(){
    log_writer.open("test.log");
    subscriber = new proto::Subscriber<proto::State>(proto::WORLD_CHANNEL,&application::log_data,this);
  };
  void close(){
    delete subscriber;
    subscriber = nullptr;
    log_writer.close();
  }
 private:
  RTTLogWriter log_writer;

  proto::Subscriber<proto::State> * subscriber;
  void log_data(proto::State& state){
    log_writer.writeMessage(state,Time::now().asNanoSeconds());
  }
};
int main(){
  application app;
  app.start();
  Time start = Time::now();
  while((Time::now()-start).asSeconds()<5.0){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  app.close();
  return 0;
}