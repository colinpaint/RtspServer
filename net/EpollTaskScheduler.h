// PHZ
// 2018-5-15
#pragma once
//{{{  includes
#include "TaskScheduler.h"
#include <mutex>
#include <unordered_map>
//}}}

namespace xop {
  class EpollTaskScheduler : public TaskScheduler {
  public:
    EpollTaskScheduler(int id = 0);
    virtual ~EpollTaskScheduler();

    void UpdateChannel (ChannelPtr channel);
    void RemoveChannel (ChannelPtr& channel);

    // timeout: ms
    bool HandleEvent (int timeout);

  private:
    void Update (int operation, ChannelPtr& channel);

    int epollfd_ = -1;
    std::mutex mutex_;
    std::unordered_map<int, ChannelPtr> channels_;
    };
  }
