#pragma once
#include <set>
#include <map>
#include "assert.h"


namespace ec_impl {

  enum class EP_REGISTRATION_ID { 
    EP_A,
    EP_B,
    EP_UNKNOWN
  };

  using EP_Register = std::set<EP_REGISTRATION_ID>;

}

