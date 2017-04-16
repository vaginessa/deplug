#ifndef PLUGKIT_SLICE_H
#define PLUGKIT_SLICE_H

#include <memory>
#include <string>

namespace plugkit {

class Slice final {
public:
  using Buffer = std::shared_ptr<const std::string>;

public:
  Slice();
  ~Slice();
  Slice(const Buffer &buf, size_t offset = 0);
  Slice(const Buffer &buf, size_t offset, size_t length = 0);
  Slice(const char *data, size_t length);
  Slice(const Slice &slice);
  Slice &operator=(const Slice &slice);
  const char *data() const;
  size_t size() const;
  const Buffer &buffer() const;
  Slice slice(size_t offset, size_t length) const;

private:
  class Private;
  std::unique_ptr<Private> d;
};
}

#endif