# Debuger

HPP file: **[debug.hpp](./debug.hpp)**

## Usage

```cpp
#include "debug.hpp"
```

### Namespace

- `namespace CM` colorful output in terminal
  - `t_` for text color
  - `b_` for background color
  - `ty_` for text typo

- `namespace logger` colorful log output
  - `SetFile(file)` to set output file, default stderr
  - `Log(content),Err(content),Warn(content)`  
    <pre><font color="green"><b>LOG: </b></font>It&apos;s log.
    <font color="red"><b>ERR: </b></font>It&apos;s Error.
    <font color="orange"><b>WARN: </b></font>It&apos;s Warn.
    </pre>


### Functions

- `string fmt(string format, Args ...args)` C like format function

- `Assert(expr)` like C assert(), but with color. for example:  
  <pre><font color="red"><b>ERR: </b></font><font color="green">tree.cpp</font>: <font color="blue">44</font>: <font color="orange">main</font>:  Assertion `<font color="cyan">n != 0</font>` failed.</pre>

- `Seearr(a, l, r)` show Array a[l, r], **return a string**

- `See(...)` show Values, **return a string**
