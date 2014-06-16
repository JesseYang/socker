require "socker/version"
require "socker_in_c/socker_in_c"

module Socker
  def self.send_request(remote_ip, port, content)
    send_request_in_c(remote_ip, port, content)
  end

  def self.start_server(port)
    start_server_in_c(port)
  end

  def self.test_callback
    test_callback_in_c
  end

  def self.test_thread
    test_thread_in_c
  end

  def self.say_hi
    Test.say_hi
  end

  def self.recv_cb(ip, content)
    Deivce.recv_loc_info(ip, content)
    puts ip.inspect
    puts content.inspect
    puts "---------------------------------------------------"
  end

  def self.loc_info_recvd(content)
    
  end

  def self.heart_beat_recvd(content)
    
  end
end
