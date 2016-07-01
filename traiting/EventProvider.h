#pragma once
#include "EFselectDS.h"
#include "EP_Registration.h"

namespace ec_impl {

  template <typename DS>
  class EventProvider : public selectDS<DS> {
  public:
    static const EP_REGISTRATION_ID epkind = EP_REGISTRATION_ID::EP_UNKNOWN;

  public:
    // ctor & dtor
    EventProvider() {}
    virtual ~EventProvider() { }

  public:
    // initialization
    virtual void initResources(Config_t*) = 0;
  };
}

