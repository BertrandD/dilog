# DiLog, a very simple c++ stream logger

## Usage
One way of using this logger is to add it as a submodule 
```shell
> git submodule add https://github.com/BertrandD/dilog.git
```
Then in your CMakeLists.txt add
```cmake
add_subdirectory(dilog)

# ...

target_link_libraries(yourapp dilog)
```

And then in your c++ code, here is an example

```c++
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
```

will output 

```
Tue Sep 28 21:55:50 2021 CEST [WARNING] A log without category
Tue Sep 28 21:55:50 2021 CEST [INFO]   [main] A log can have a category
Tue Sep 28 21:55:50 2021 CEST [INFO]   [cat][subcat] Categories can be chained
Tue Sep 28 21:55:50 2021 CEST [INFO]   [sampleFunction] Multiple logs lines
Tue Sep 28 21:55:50 2021 CEST [INFO]   [sampleFunction] can share
Tue Sep 28 21:55:50 2021 CEST [INFO]   [sampleFunction] the same category
Tue Sep 28 21:55:50 2021 CEST [INFO]   [sampleFunction] with no repetition
Tue Sep 28 21:55:50 2021 CEST [INFO]   [sampleFunction] e.g. if logger is passed in parameter
```