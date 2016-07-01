#include "EventFactory.h"

namespace ec_impl {


  template <typename DS>
  EventFactory<DS>::~EventFactory() {
    for (EventProvider_t* ep : active_providers){
      delete ep;
    }
  }

  template <typename DS>
  bool EventFactory<DS>::registerEP(EventProvider_t* ep) {
    inactive_providers.insert(ep);
    return true; // check!!
  }

  template <typename DS>
  bool EventFactory<DS>::unregisterEP(EventProvider_t* ep) {
    inactive_providers.erase(ep);
    active_providers.erase(ep);
    delete ep;
    return true; // check!!
  }

  // find the EP in the inactive set of providers and 
  // move it to the set of active providers
  template <typename DS>
  bool EventFactory<DS>::activateEP(EventProvider_t* ep) {
    auto it = inactive_providers.find(ep);
    if (it != inactive_providers.end()) {
      active_providers.insert(*it);
      inactive_providers.erase(*it);
      return true;
    }
    return false;
  }

  // find the EP in the active set of providers and 
  // move it to the set of inactive providers
  template <typename DS>
  bool EventFactory<DS>::deactivateEP(EventProvider_t* ep) {
    auto it = active_providers.find(ep);
    if (it != active_providers.end()) {
      inactive_providers.insert(*it);
      active_providers.erase(*it);
      return true;
    }
    return false;
  }

}
