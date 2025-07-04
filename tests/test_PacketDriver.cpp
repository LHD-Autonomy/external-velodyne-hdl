#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/shared_ptr.hpp>

#include "velodyne_cpp/PacketDriver.h"

using namespace std;

int main()
{
  PacketDriver driver(DATA_PORT);

  std::string* data = new std::string();
  unsigned int* dataLength = new unsigned int();
  while (true) {
    driver.GetPacket(data, dataLength);
    std::cout << "Length of packet: " << (*data).length() << std::endl;
  }

  return 0;
}
