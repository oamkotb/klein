package editor

import (
	"bufio"
	"os"

	"golang.org/x/term"
)

type Editor struct {
	Cols, Rows int
}

func (e *Editor) Init() error {
	var err error
	e.Cols, e.Rows, err = term.GetSize(int(os.Stdin.Fd()))
	return err
}

func (e *Editor) ReadKey() byte {
	reader := bufio.NewReader(os.Stdin)
	// Read one byte from os.Stdin
	b, _ := reader.ReadByte()
	return b
}

func (e *Editor) ProcessKeypress() bool {
	b := e.ReadKey()
	switch b {
	case 113:
		return true
	}
	return false
}

func (e *Editor) DrawRows() {
	for y := 0; y < e.Rows; y++ {
		os.Stdout.Write([]byte("~\r\n"))
	}
	os.Stdout.Write([]byte("\x1b[H"))
}

func (e *Editor) RefreshScreen() {
	// Escape sequence to clear the screen and reset cursor
	os.Stdout.Write([]byte("\x1b[2J"))
	os.Stdout.Write([]byte("\x1b[H"))
}
