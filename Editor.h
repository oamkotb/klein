#pragma once

#include "internal.h"

#define CTRL_KEY(k) (k & 0x1f)

class Editor
{
public:
  Editor();
  ~Editor();

  void run();
private:

};
