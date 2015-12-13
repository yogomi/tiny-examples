// Copyright 2015 Makoto Yano

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <list>

class HydraHead {
 public:
  HydraHead():counter_(0), beat_(false) {
    hart_beats_.push_back(&beat_);
  }
  void Beat();
  void HartBeat();
  bool Continue() {return !finish_;}
  void Finish() {finish_ = true;}
 private:
  int counter_;
  bool beat_;
  static bool finish_;
  static std::list<bool *> hart_beats_;
  static std::mutex m_;
  static std::mutex hart_beat_mutex_;
  static std::condition_variable cv_;
};

void HydraHead::Beat() {
  std::unique_lock<std::mutex> uniq_lk(hart_beat_mutex_);
  cv_.wait(uniq_lk, [&]{return beat_;});
  std::cout << std::this_thread::get_id() << " : Wait Finish" << std::endl;

  for (int i = 0; i < 20000; i++) {
    int f;
  }
  // このmutexは文字列を整然と表記させるものなのでただのHartBeatには不要
  std::lock_guard<std::mutex> lock(m_);
  counter_++;
  std::cout << std::this_thread::get_id() << " : " << counter_ << std::endl;
  beat_ = false;
}

void HydraHead::HartBeat() {
  {
    std::unique_lock<std::mutex> uniq_lk(hart_beat_mutex_);
    std::cout << std::this_thread::get_id() << " : Beat" << std::endl;
    for_each(hart_beats_.begin(), hart_beats_.end(), [](bool *b){
      *b = true;
    });
    cv_.notify_all();
  }

  while (std::any_of(hart_beats_.begin()
      , hart_beats_.end()
      , [](bool *b){return *b;})) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool HydraHead::finish_ = false;
std::mutex HydraHead::m_;
std::mutex HydraHead::hart_beat_mutex_;
std::condition_variable HydraHead::cv_;
std::list<bool *> HydraHead::hart_beats_;

void worker(HydraHead &h) {
  while (h.Continue()) {
    h.Beat();
  }
}

int main() {
  std::cout << "maaa" << std::endl;
  HydraHead h1, h2, h3, h4, h5;
  std::thread th(worker, std::ref(h1));
  th.detach();

  th = std::thread(worker, std::ref(h2));
  th.detach();

  th = std::thread(worker, std::ref(h3));
  th.detach();

  th = std::thread(worker, std::ref(h4));
  th.detach();

  th = std::thread(worker, std::ref(h5));
  th.detach();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  for (int i = 0; i < 50000; i++) {
    h1.HartBeat();
  }
  h1.Finish();

  return 0;
}
