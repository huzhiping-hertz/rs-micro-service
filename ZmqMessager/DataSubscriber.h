#ifndef DATASUBSCRIBER_H
#define DATASUBSCRIBER_H

#include <string>
#include <gflags/gflags.h>

namespace RS {

using namespace std;

class DataSubscriber {

private:
  void *ctx;
  void *subscriber;
public:
  DataSubscriber(string address);
  void SetTopicFilter(std::vector<string> topics);
  void SetNoTopicFilter();
  int GetMsg(char *bufData,int bufLen);
  ~DataSubscriber();
};
} // namespace ZmqMessager

#endif
