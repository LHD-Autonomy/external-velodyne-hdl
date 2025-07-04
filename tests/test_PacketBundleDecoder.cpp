#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <deque>

#include "velodyne_cpp/PacketDriver.h"
#include "velodyne_cpp/PacketBundler.h"
#include "velodyne_cpp/PacketBundleDecoder.h"

using namespace std;

int main()
{
  PacketDriver driver;
  driver.InitPacketDriver(DATA_PORT);
  PacketBundler bundler;
  PacketBundleDecoder bundleDecoder;

  std::string* data = new std::string();
  unsigned int* dataLength = new unsigned int();
  std::deque<std::string> bundles;
  std::string latest_bundle;
  unsigned int latest_bundle_length;
  PacketBundleDecoder::HDLFrame latest_frame;
  while (true) {
    driver.GetPacket(data, dataLength);
    bundler.BundlePacket(data, dataLength);
    bundles = bundler.GetBundles();
    if (bundler.GetLatestBundle(&latest_bundle, &latest_bundle_length)) {
      std::cout << "Bundle length: " << latest_bundle_length << std::endl;
      std::cout << "Bundle number of packets: " << (latest_bundle_length/1206) << std::endl;
      bundleDecoder.DecodeBundle(&latest_bundle, &latest_bundle_length);
      if (bundleDecoder.GetLatestFrame(&latest_frame)) {
        std::cout << "Number of points: " << latest_frame.x.size() << std::endl;
      }
    }
  }

  return 0;
}
