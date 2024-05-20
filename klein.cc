#include <cctype>
#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>

/*** data ***/
termios ORIGINAL_TERMIOS;

/*** terminal ***/
void die(const std::string error) {
  std::cerr << error << std::endl;
  exit(1);
}

void exitRawMode()
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &ORIGINAL_TERMIOS)) die("tcsetattr");
}

void enterRawMode()
{
  if(tcgetattr(STDIN_FILENO, &ORIGINAL_TERMIOS)) die("tcgetattr");

  atexit(exitRawMode);  // Set program to exit raw mode at program termination

  termios raw = ORIGINAL_TERMIOS;

  /*  BRKINT will have a break condition cause a SIGINT signal to be sent to the program, like pressing Ctrl-C
   *  ICRNL causes the terminal to translate any carriage returns (13, '\r') inputted by the user into newlines (10, '\n')
   *  INPCK enables parity checking
   *  ISTRIP causes the 8th bit of each input byte to be stripped
   *  IXON causes Ctrl-S to stop data from being transmitted to the terminal until you press Ctrl-Q
   */
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

  /* OPOST enables output processing
   */
  raw.c_oflag &= ~(OPOST);

  /* CS8 sets the character size (CS) to 8 bits per byte
   */
  raw.c_cflag |= (CS8);
  
  /*  ECHO causes each key you type to be printed to the terminal, so you can see what you’re typing
   *  ICANON causes input to be read line-by-line instead of byte-by-byte
   *  IEXTEN which on some systems causes Ctrl-V/Ctrl-O to make the terminal wait for you to type another character and then sends that character literally
   *  ISIG causes Ctrl-C to terminate the process and Ctrl-Z to suspend it
   */
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)) die("tcsetattr");
}

/*** init ***/
int main()
{
  enterRawMode();
  char ch;
  while (std::cin.get(ch) && ch != 'q')
  {
    if (std::cin.fail()) die("cin failed");

    std::cout << ch << "\r\n";
  }
  
  std::cout << std::endl;

  return 0;
}