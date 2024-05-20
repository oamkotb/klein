#include "Editor.h"

Editor::Editor()
{
  terminal::enterRawMode();
}

Editor::~Editor()
{
  terminal::exitRawMode();
}

void Editor::run()
{
  char ch;
  while (std::cin.get(ch) && ch != CTRL_KEY('q'))
  {
    if (std::cin.fail()) die("cin failed");

    std::cout << ch << "\r\n";
  }
  
  std::cout << std::endl;
}