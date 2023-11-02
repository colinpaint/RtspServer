// PHZ 2018-6-10
#pragma once
#include <cstdint>
#include <utility>

namespace xop {

  typedef std::pair<uint8_t*, uint8_t*> Nal; // <nal begin, nal end>

  class H264Parser {
  public:
    static Nal findNal(const uint8_t *data, uint32_t size);
  private:
    };
  }
