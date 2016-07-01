#pragma once
#include "EFselectDS.h"
#include "EventProvider.h"

#include <set>

namespace ec_impl {

  // the comperator functor for comparing EventProviders according to their priority
  template <typename DS>
  struct EP_comp_priority : public selectDS<DS> {
    bool operator()(selectDS<DS>::EventProvider_t* lhs, selectDS<DS>::EventProvider_t* rhs) const {
      // in the case the priority is equal, the order does not matter
      // thus use the comparison of the pointers
      // this is also important to guarantee, that two different EP
      // are not regarded as equivalent only because their priority is equal
      if (lhs->priority() == rhs->priority()) { return lhs < rhs; }
      else { return lhs->priority() > rhs->priority(); }
    }
  };


  template <typename DS>
  class EventFactory : public selectDS<DS> {

  std::set<EventProvider_t*> inactive_providers;
  std::set<EventProvider_t*, EP_comp_priority<DS>> active_providers;

  public:
    // ctor & dtor
    EventFactory() : LTA_log(filename), active_providers() {}
    virtual ~EventFactory() override;

    // low level EventProvider management
    bool activateEP(EventProvider_t* ep);
    bool deactivateEP(EventProvider_t* ep);
    bool registerEP(EventProvider_t* ep);
    bool unregisterEP(EventProvider_t* ep);
  };
}

#include "EventFactory.cpp"
