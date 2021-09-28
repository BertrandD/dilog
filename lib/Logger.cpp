//
// Created by bertrand on 28/09/2021.
//

#include "dilog/Logger.h"

#include <sstream>
#include <ctime>
#include <iomanip>

namespace dilog {
  enum Level : int {
    trace = 0,
    debug = 1,
    info = 2,
    notice = 3,
    warning = 4,
    error = 5,
    fatal = 6

  };

  const constexpr char * LevelStr(Level lvl) {
    switch (lvl) {
      case trace:
        return " [TRACE]  ";
      case debug:
        return " [DEBUG]  ";
      case info:
        return " [INFO]   ";
      case notice:
        return " [NOTICE] ";
      case warning:
        return " [WARNING]";
      case error:
        return " [ERROR]  ";
      case fatal:
        return " [FATAL]  ";
    }
    return "[UNKNOWN]";
  }

  struct LogStreamImpl {
    Level lvl;
    std::ostream *out;
    std::stringbuf buffer;
    std::list<std::string> ctx;
  };

  struct Builder : LogStream {
    static LogStream Build(Level level, std::ostream &out, std::list<std::string> ctx) {
      return LogStream(std::make_shared<LogStreamImpl>(LogStreamImpl{
        .lvl = level,
        .out = &out,
        .ctx = std::move(ctx)
      }));
    }
  };

  LogStream::~LogStream() {
    std::time_t time = std::time(nullptr);
    (*mImpl->out) << std::put_time(std::localtime(&time), "%c %Z") << LevelStr(mImpl->lvl);
    for (const auto &ctx: mImpl->ctx) {
      (*mImpl->out) << "[" << ctx <<"]";
    }
    (*mImpl->out) << this->rdbuf() << std::endl;
  }

  LogBuf::LogBuf(std::shared_ptr<LogStreamImpl>impl): mImpl(std::move(impl)) {}

  LogStream::LogStream(std::shared_ptr<LogStreamImpl> impl) : LogBuf(std::move(impl)), std::ostream(&mImpl->buffer) {
    std::ostream::operator<<(std::boolalpha);
  }

  LogStream Logger::Trace() const {
    return Builder::Build(trace, mBase, mCtx);
  }

  LogStream Logger::Debug() const {
    return Builder::Build(debug, mBase, mCtx);
  }

  LogStream Logger::Info() const {
    return Builder::Build(info, mBase, mCtx);
  }

  LogStream Logger::Notice() const {
    return Builder::Build(notice, mBase, mCtx);
  }

  LogStream Logger::Warning() const {
    return Builder::Build(warning, mBase, mCtx);
  }

  LogStream Logger::Error() const {
    return Builder::Build(error, mBase, mCtx);
  }

  LogStream Logger::Fatal() const {
    return Builder::Build(fatal, mBase, mCtx);
  }

  Logger Logger::operator()(std::string c) const {
    Logger logger = *this;
    logger.mCtx.emplace_back(std::move(c));
    return logger;
  }

  Logger::Logger(std::ostream &base) : mBase(base) {}
}

