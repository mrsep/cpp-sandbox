#pragma once

template <typename Type, typename Config>
class Singleton {
  private:
    // private data
    static Type* instance = nullptr;
    static bool destroyed;
    static Config current_config;

  public:
    // public static interface
    Type& Instance() {
      if (instance == nullptr) {
        instance = new Type(current_config);
      }
      return *instance;
    };

    Type& Instance(Config& config) { 
      if (config != current_config) {
        Destroy();
        Create(config);
      }
      return Instance(); 
    }

  private:
    // helper functions
    void Create(Config& config);
    void Destroy() { };

  private:
    // disabled features
    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    ~Singleton() = delete;
}



