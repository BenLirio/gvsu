package main

import (
	"./analysis"
	"fmt"
	"math"
)

func main() {
	value := []int{1,3,5,8}
	maxValue(value, 3)
}

func maxValue(p []int, n int) int {
	if n == 0 {
		return 0
	}
	var q int = math.MinInt64
	for i := 1; i < n; i++ {
		var cutVal int
		if n < len(p) {
			cutVal = p[n]
		}
		var curVal int = cutVal + maxValue(p, n-i)
		if curVal > q {
			q = curVal
		}
	}
	analysis.LogData(fmt.Sprintf("%d", q))
	return q
}
