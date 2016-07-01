#pragma once

namespace ec_impl {
  struct DATASOURCE {
    struct PXCA{};
    struct PXCB{};
  };

  // forward declare EventProvider template
  template <typename DS>
  class EventProvider;

  // types
  struct EMPTY_TYPE { };

  struct Config_A{};
  struct Config_B{};

  template <typename DS>
  struct selectDS {
    using Config_t = EMPTY_TYPE;
    using EventProvider_t = EMPTY_TYPE;
  };

  template <>
  struct selectDS<DATASOURCE::PXCA> {
    using Config_t = Config_A;
    using EventProvider_t = EventProvider<DATASOURCE::PXCA>;
  };

  template <>
  struct selectDS<DATASOURCE::PXCB> {
    using Config_t = Config_B;
    using EventProvider_t = EventProvider<DATASOURCE::PXCB>;
  };
}
