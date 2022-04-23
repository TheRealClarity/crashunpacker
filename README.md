# CRASHUNPACKER

Unpacks crash reports acquired from NVRAM's variable "appl-panicinfo"

Get the output in XML format from the nvram executable (use -x), get the value from the "appl-panicinfo" key and throw it into a base64 to file decoder (like https://base64.guru/converter/decode/file). 

Feed it into this tool. Profit.


## Usage:
```crashunpacker [file]```


## Build: 
```gcc crashunpacker.c -o crashunpacker```


## Credits:
Apple for XNU

Jonathan Levin for the *OS Internals books.