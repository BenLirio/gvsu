package analysis

import (
	"time"
	"os"
	"fmt"
)

var baseTime int64 = getUnixMicroTime()
var logFileName string = "analysis.tsv"

func LogData(data string) {
	var logFile *os.File
	var err error
	logFile, err = os.Create(logFileName)
	if err != nil {
		fmt.Printf("Failed to open %s\n", logFileName)
		os.Exit(1)
	}
	defer logFile.Close()
	fmt.Printf("%d\t%s\n", getMicroPassed(), data)
	logFile.Write([]byte(fmt.Sprintf("%d\t%s\n", getMicroPassed(), data)))
}

func getMicroPassed() (int64) {
	return getUnixMicroTime() - baseTime
}

func getUnixMicroTime() (int64) {
	return time.Now().UnixNano() / 1000
}

func Test() int64 {
	return getMicroPassed()
}
