#pragma once
#include "assert.h"
#include <iostream>

template <typename Type, typename Config>
class Singleton {
  private:
    // private data
    static Type* instance;
    static bool destroyed;
    static Config current_config;

  public:
    // public static interface
    static Type& Instance(Config& config) {
      std::cout << "Instance()" << std::endl;
      if (destroyed) {
        OnDeadReference();
      }
      else {
        Create(config);
      }
      assert(instance != nullptr);
      return *instance;
    };

    static Type& Instance() { 
      std::cout << "Instance(config)" << std::endl;
      return Instance(current_config); 
    }

  private:
    // helper functions
    static void Create(Config& config) { 
      std::cout << "Create(config)" << std::endl;
      if (instance == nullptr) {
        current_config = config;
        std::cout << "new" << std::endl;
        instance = new Type(current_config); 
      }
      else if (current_config != config) {
        Destroy();
        current_config = config;
        std::cout << "new config" << std::endl;
        new(instance) Type(current_config); 
      }
      std::cout << instance << std::endl;
      destroyed = false;
    };

    static void Destroy() { 
      std::cout << "Destroy()" << std::endl;
      delete instance; 
      destroyed = true;
    };

    static void OnDeadReference() {
      // Obtain the shell of the destroyed singleton
      Create(current_config);
      // Now pInstance_ points to the "ashes" of the singleton
      // - the raw memory that the singleton was seated in.
      // Create a new singleton at that address
      new(instance) Type(current_config);
      // Queue this new object's destruction
      atexit(KillPhoenixSingleton);
      // Reset destroyed_ because we're back in business
      destroyed = false;
    }

    static void Singleton::KillPhoenixSingleton() {
      // Make all ashes again
      // - call the destructor by hand.
      // It will set pInstance_ to zero and destroyed_ to true
      instance->~Type();
    }

  protected:
    virtual ~Singleton() {std::cout << "~Singleton" << std::endl;}
    Singleton() {std::cout << "Singleton" << std::endl;}

  private:
    // disabled features
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

template <typename Type, typename Config>
Type* Singleton<Type,Config>::instance = nullptr;

template <typename Type, typename Config>
bool Singleton<Type,Config>::destroyed = false;

template <typename Type, typename Config>
Config Singleton<Type,Config>::current_config = Config();

