//
// Created by bertrand on 28/09/2021.
//

#pragma once

#include <iostream>
#include <list>
#include <memory>

namespace dilog {
  struct LogStreamImpl;

  struct LogBuf {
  protected:
    explicit LogBuf(std::shared_ptr<LogStreamImpl>);

    std::shared_ptr<LogStreamImpl> mImpl;

    friend class LogStream;
  };

  class LogStream : private LogBuf, std::ostream {
  public:
    explicit LogStream(std::shared_ptr<LogStreamImpl>);

    LogStream(const LogStream &) = delete;

    LogStream(LogStream &&) = delete;

    ~LogStream() override;

    template<class T>
    inline LogStream &operator<<(const T &stream) {
      (*static_cast<std::ostream *>(this)) << " " << stream;
      return *this;
    }

  protected:
    friend class Logger;

    friend class Builder;
  };

  class Logger {
    std::list<std::string> mCtx;
    std::ostream &mBase;
  public:
    explicit Logger(std::ostream &base = std::cout);

    /// Append category to logger
    Logger operator()(std::string c) const;

    [[maybe_unused]] [[nodiscard]] LogStream Trace() const;

    [[maybe_unused]] [[nodiscard]] LogStream Debug() const;

    [[maybe_unused]] [[nodiscard]] LogStream Info() const;

    [[maybe_unused]] [[nodiscard]] LogStream Notice() const;

    [[maybe_unused]] [[nodiscard]] LogStream Warning() const;

    [[maybe_unused]] [[nodiscard]] LogStream Error() const;

    [[maybe_unused]] [[nodiscard]] LogStream Fatal() const;
  };

}