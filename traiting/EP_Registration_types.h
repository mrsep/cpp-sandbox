#pragma once
#include <map>
#include "type_list.h"
#include "EventProvider.h"


namespace ec_impl {

  // events
  struct EA : public EventProvider<DATASOURCE::PXCA>{
    static const EP_REGISTRATION_ID epkind = EP_REGISTRATION_ID::EP_A;
  };
  struct EB : public EventProvider<DATASOURCE::PXCB>{
    static const EP_REGISTRATION_ID epkind = EP_REGISTRATION_ID::EP_B;
  };

  using empty_list = type_list<int>;
  using A_Register = type_list<EA>;
  using B_Register = type_list<EB>;

  template <typename T, typename Container, typename Conf, typename Pred>
  struct Fill_pred {
    void operator()(Container& container, Conf& config, const Pred& pred) {
      if (pred.count(T::epkind) > 0 ) {
        container.emplace(typename Container::value_type(new T(config)));
      }
    }
  };
}
