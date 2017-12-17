#pragma once

#include <thread>

#include <ros/ros.h>

#include "sbus_bridge/sbus_msg.h"

namespace sbus_bridge
{

class SBusSerialPort
{
public:

  SBusSerialPort();
  SBusSerialPort(const std::string port, const bool start_receiver_thread);
  virtual ~SBusSerialPort();

protected:

  bool connectSerialPort(const std::string port);
  void disconnectSerialPort();

  bool startReceiverThread();
  bool stopReceiverThread();

  void sendSBusMessage(const SBusMsg& sbus_msg) const;
  virtual void handleReceivedSbusMessage(const SBusMsg& received_sbus_msg) const = 0;

private:

  static constexpr int kSbusFrameLengh_ = 25;
  static constexpr uint8_t kSbusHeaderByte_ = 0x0F;
  static constexpr uint8_t kSbusFooterByte_ = 0x00;

  bool configureSerialPortForSBus() const;
  void serialPortReceiveThread() const;
  SBusMsg parseSbusMessage(uint8_t sbus_msg_bytes[kSbusFrameLengh_]) const;

  std::thread receiver_thread_;

  int serial_port_fd_;
  bool receiver_thread_should_exit_;
};

} // namespace sbus_bridge
