
#include <dilog/Logger.h>

void ASampleFunction(const dilog::Logger &logger) {
  logger.Info() << "Multiple logs lines";
  logger.Info() << "can share";
  logger.Info() << "the same category";
  logger.Info() << "with no repetition";
  logger.Info() << "e.g. if logger is passed in parameter";
}

int main()
{
  dilog::Logger logger;

  logger.Warning() << "A log without" << "category";

  logger("main").Info() << "A log can have a category";

  logger("cat")("subcat").Info() << "Categories can be chained";

  ASampleFunction(logger("sampleFunction"));
}