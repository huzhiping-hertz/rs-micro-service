#ifndef DATAPUBLISHER_H
#define DATAPUBLISHER_H

#include <string>

#include <gflags/gflags.h>

namespace RS {
using namespace std;

class DataPublisher {

private:
  static DataPublisher *ptrInstance;
  static string m_address;
  void *ctx;
  void *publisher;
  DataPublisher(string address, bool isXPub);

public:
  static DataPublisher *GetInstance(string address, bool isXPub);
  void SendMsg(char *data, int length, string topic="");
  ~DataPublisher();
};

} // namespace ZmqMessager
#endif
