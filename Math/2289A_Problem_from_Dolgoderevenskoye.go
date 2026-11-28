/*
	{
	    "problem_name": "Problem from Dolgoderevenskoye",
	    "category": "Math / Number Theory / Game Theory",
	    "time_complexity": "O(1) per test case -> Single bitwise AND check.",
	    "space_complexity": "O(1) -> Fixed 64KB I/O buffers, zero heap allocations per query.",
	    "formula_used": "O == E iff v2(x) == 1 iff (x & 3) == 2; Artem wins iff (x & 3) != 2"
	}
*/
package main

import (
	"bufio"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1<<16)
var out = bufio.NewWriterSize(os.Stdout, 1<<16)

func readUint64() uint64 {
	var c byte
	var err error
	for {
		c, err = in.ReadByte()
		if err != nil {
			return 0
		}
		if c >= '0' && c <= '9' {
			break
		}
	}
	var val uint64
	for c >= '0' && c <= '9' {
		val = val*10 + uint64(c-'0')
		c, err = in.ReadByte()
		if err != nil {
			break
		}
	}
	return val
}

func main() {
	defer out.Flush()

	t := readUint64()
	for i := uint64(0); i < t; i++ {
		x := readUint64()
		if x&3 == 2 {
			out.WriteString("No\n")
		} else {
			out.WriteString("Yes\n")
		}
	}
}
