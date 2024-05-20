#pragma once

#include <cctype>
#include <iostream>
#include <termios.h>
#include <unistd.h>

/*** error handling ***/
void die(const std::string error);

/*** terminal ***/
namespace terminal
{
  void exitRawMode();

  void enterRawMode();
}
