#ifndef UTIL_STREAM_IO__
#define UTIL_STREAM_IO__

#include "util/exception.hh"
#include "util/file.hh"
#include "util/stream/chain.hh"

#include <cstddef>

#include <assert.h>
#include <stdint.h>

namespace util {
namespace stream {

class ReadSizeException : public util::Exception {
  public:
    ReadSizeException() throw();
    ~ReadSizeException() throw();
};

class ReadThread {
  public:
    ReadThread(const ChainPosition &position, int fd) :
        file_(fd),
        entry_size_(position.GetChain().EntrySize()),
        block_size_(position.GetChain().BlockSize()),
        thread_(position, this) {}

    void Process(Block &block);

  private:
    int file_;
    const std::size_t entry_size_, block_size_;
    LinkThread thread_;
};

class WriteThread {
  public:
    WriteThread(const ChainPosition &position, int fd) :
        file_(fd), thread_(position, this) {}

    void Process(Block &block) {
      util::WriteOrThrow(file_, block.Get(), block.ValidSize());
    }

  private:
    int file_;
    LinkThread thread_;
};

} // namespace stream
} // namespace util
#endif // UTIL_STREAM_IO__