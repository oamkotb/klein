package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"unicode"

	"golang.org/x/term"
)

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

func main() {
	enableRawMode()
	defer disableRawMode()

	reader := bufio.NewReader(os.Stdin)
	for {
		// Read one byte from os.Stdin
		r, _, err := reader.ReadRune()
		if err != nil || r == 'q' {
			break
		}

		if unicode.IsControl(r) {
			fmt.Printf("%d\r\n", r)
		} else {
			fmt.Printf("%d ('%c')\r\n", r, r)
		}
	}
}
