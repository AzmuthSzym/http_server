# http_server

This is a project that implements a simple HTTP web server using Winsock library in C++. Made for learning purposes.

## Build info

In order to build and run this program on Windows (suing CMake) execute following commands:
Firstly download and unpack the repository.
Then open Command Prompt or Windows PowerShell and navigate to a folder where you have this repo.

Commands you should use:
1. PS E:\http_server\build> cmake --build .
2. PS E:\http_server\build> .\Debug\http_server.exe

In order to test it you can open browser (could be incognito mode for convinience):
http://localhost:27015/ - paste this link into the browser to run the application

### Tests
Some Winsock functions are hard to test because of some linking error while compiling...
In order to run tests execute following commands:

1. cmake --build . --target tests
2. .\Debug\tests.exe

## Additional information

Currently the main program (server) is set to run for 20 seconds accepting connetions and displaing "Hello World" message, after this time connection stops.