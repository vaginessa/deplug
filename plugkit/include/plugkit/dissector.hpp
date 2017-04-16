#ifndef PLUGKIT_DISSECTOR_H
#define PLUGKIT_DISSECTOR_H

#include "variant.hpp"
#include <memory>
#include <vector>
#include <regex>
#include <v8.h>

namespace plugkit {

class Layer;
using LayerPtr = std::shared_ptr<Layer>;
using LayerConstPtr = std::shared_ptr<const Layer>;

class Frame;
using FrameConstPtr = std::shared_ptr<const Frame>;

struct SessionContext;

class Dissector {
public:
  virtual ~Dissector();

public:
  class Worker {
  public:
    virtual ~Worker();
    virtual LayerPtr analyze(const LayerConstPtr &layer) = 0;
  };
  using WorkerPtr = std::unique_ptr<Worker>;

public:
  virtual WorkerPtr createWorker() = 0;
  virtual std::vector<std::regex> namespaces() const = 0;
};

using DissectorPtr = std::unique_ptr<Dissector>;

class DissectorFactory;
using DissectorFactoryConstPtr = std::shared_ptr<const DissectorFactory>;

class DissectorFactory {
public:
  struct TestData {
    LayerConstPtr parent;
    LayerConstPtr result;
  };

public:
  virtual ~DissectorFactory();
  virtual DissectorPtr create(const SessionContext &context) const = 0;
  virtual std::vector<TestData> testData() const;
  static v8::Local<v8::Object> wrap(const DissectorFactoryConstPtr &factory);
};
}

#endif