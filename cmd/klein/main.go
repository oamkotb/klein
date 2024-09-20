package main

import (
	"log"
	"os"

	e "github.com/oamkotb/klein/internal/editor"
	"golang.org/x/term"
)

/** terminal **/

var orig_state *term.State

func disableRawMode() {
	// Restore terminal to its original state
	if orig_state != nil {
		term.Restore(int(os.Stdin.Fd()), orig_state)
	}
}

func enableRawMode() {
	// Set terminal to raw mode
	old_state, err := term.MakeRaw(int(os.Stdin.Fd()))
	if err != nil {
		log.Fatal(err)
	}

	orig_state = old_state
}

/** input **/

/** init **/

func main() {
	enableRawMode()
	defer disableRawMode()

	var editor e.Editor

	err := editor.Init()
	if err != nil {
		log.Fatal(err)
	}

	for {
		editor.RefreshScreen()
		editor.DrawRows()
		if editor.ProcessKeypress() {
			break
		}
	}
	editor.RefreshScreen()
}
