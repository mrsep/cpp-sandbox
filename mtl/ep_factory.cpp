#include "type_list.h"
#include "dlist.h"
#include <iostream>
#include <memory>
#include <list>
#include <set>

enum class EP { BLINK, HEART };

struct EventProvider {
  EventProvider() = default;
  EventProvider(EventProvider&& other) {}
  virtual ~EventProvider() = default;

  virtual void update(float) = 0;
  virtual float read() = 0;

  const static EP epkind;
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
  const static EP epkind;

  void update(float state) override { data.current_state = state; }
  float read() override { return pata.pata + data.current_state; }
};

struct HeartProvider : public EventProvider, public dlist<HeartProvider> {

  HeartProvider(const Config& config) : pata(config), data() {}
  HeartProvider(HeartProvider&& other) : pata(other.pata), data(other.data) {}
  BlinkPata pata;
  BlinkData data;
  const static EP epkind;

  void update(float state) override { data.current_state = state; }
  float read() override { return pata.pata + data.current_state; }
};

const EP BlinkProvider::epkind = EP::BLINK;
const EP HeartProvider::epkind = EP::HEART;

template <typename T, typename Container, typename Conf, typename Pred>
struct Fill_pred {
  void operator()(Container& container, const Conf& config, const Pred& pred) {
    if (pred.count(T::epkind) > 0 ) {
      container.emplace_back(typename Container::value_type(new T(config)));
    }
  }
};

template <typename T, typename Container, typename Conf>
struct Fill {
  void operator()(Container& container, const Conf& config) {
    container.emplace_back(typename Container::value_type(new T(config)));
  }
};

template <typename T>
struct Clear {
  void operator()() {
    T::Clear();
  }
};

std::set<EP> eps{EP::BLINK};

int main() {
  using ep_tlist = type_list<HeartProvider, BlinkProvider>;
  using ptr_t = EventProvider*;
  //using ptr_t = std::unique_ptr<EventProvider>;
  using ep_container = std::list<ptr_t>;
  using ep_pred = std::set<EP>;

  ep_container provider;

  //provider.push_back(ptr_t(new HeartProvider(Config{true})));
  //Fill<HeartProvider,ep_container,Config>()(provider, Config{true});

  Config ca{true};
  Config cb{false};
  
  for (int i=0; i < 1000; ++i) {
    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, ca);
    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, cb);
  }

  std::cout << "providers: " << provider.size() << std::endl;
  std::cout << "BP: " << BlinkProvider::Size() << std::endl;
  std::cout << "HP: " << HeartProvider::Size() << std::endl;

  for (int i=0; i < 1000; ++i) {
    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, ca);
    for_each_type<ep_tlist,Fill,ep_container,Config>(provider, cb);
  }

  //for_each_type<ep_tlist,Clear>();
  for (auto it = provider.begin(); it != provider.end(); ++it) {
    delete *it;
  }
  provider.clear();

  std::cout << "providers: " << provider.size() << std::endl;
  std::cout << "BP: " << BlinkProvider::Size() << std::endl;
  std::cout << "HP: " << HeartProvider::Size() << std::endl;

  for (int i=0; i < 1000; ++i) {
    for_each_type<ep_tlist,Fill_pred,ep_container,Config,ep_pred>(provider, ca, eps);
    for_each_type<ep_tlist,Fill_pred,ep_container,Config,ep_pred>(provider, cb, eps);
  }

  std::cout << "providers: " << provider.size() << std::endl;
  std::cout << "BP: " << BlinkProvider::Size() << std::endl;
  std::cout << "HP: " << HeartProvider::Size() << std::endl;

  return 0;
}

