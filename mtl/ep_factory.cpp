#include "type_list.h"
#include "dlist.h"
#include <iostream>
#include <memory>
#include <list>

struct EventProvider {
  EventProvider() = default;
  EventProvider(EventProvider&& other) {}
  virtual ~EventProvider() = default;

  virtual void update(float) = 0;
  virtual float read() = 0;
};

struct Config {
  bool param;
};

struct BlinkData { float current_state; };
struct BlinkPata {
  int pata;
  BlinkPata(const Config& c) {
    if (c.param) { pata = 42; }
    else { pata = 23; }
  }
};

struct BlinkProvider : public EventProvider, public dlist<BlinkProvider> {

  BlinkProvider(const Config& config) : pata(config), data() {}
  BlinkProvider(BlinkProvider&& other) : pata(other.pata), data(other.data) {}
  BlinkPata pata;
  BlinkData data;

  void update(float state) override { data.current_state = state; }
  float read() override { return pata.pata + data.current_state; }
};

struct HeartProvider : public EventProvider, public dlist<HeartProvider> {

  HeartProvider(const Config& config) : pata(config), data() {}
  HeartProvider(HeartProvider&& other) : pata(other.pata), data(other.data) {}
  BlinkPata pata;
  BlinkData data;

  void update(float state) override { data.current_state = state; }
  float read() override { return pata.pata + data.current_state; }
};

template <typename T, typename Container, typename Conf>
struct Fill {
  void operator()(Container& container, const Conf& config) {
    container.emplace_back(typename Container::value_type(new T(config)));
  }
};

int main() {
  using ep_tlist = type_list<HeartProvider, BlinkProvider>;
  using ptr_t = EventProvider*;
  //using ptr_t = std::unique_ptr<EventProvider>;
  using ep_container = std::list<ptr_t>;

  ep_container provider;

  //provider.push_back(ptr_t(new HeartProvider(Config{true})));
  Fill<HeartProvider,ep_container,Config>()(provider, Config{true});
  
  for (int i=0; i < 1000; ++i) {
    //provider.clear();

    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, Config{true});
    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, Config{false});
  }

  std::cout << provider.size() << std::endl;
  for (auto& ep : provider) {
    std::cout << ep->read() << std::endl;
  }

  BlinkProvider::Clear();

  std::cout << "BP: " << BlinkProvider::Size() << std::endl;
  std::cout << "HP: " << HeartProvider::Size() << std::endl;

  return 0;
}

