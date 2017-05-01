# astlib
Eurocontrol Asterix decoder framework based on XML declarations

Project is inspired by: https://github.com/vitorafsr/asterixed

Dependencies
- Modern C++11 compiler, gcc 5.x, Visual Studio 2015
- Cmake 3.3 or above
- Poco library 1.7.0 or above
- Gtest (optional) 
- Node.js (optional) (+v8pp +mocha)

Building - Windows [Debug]
1. <checkout source somewhere into astlib directory>
2. mkdir debug
3. cd debug
4. cmake -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug ..
5. msbuild astlib.sln  /t:Rebuild /p:Configuration=Debug
6. cd ..
7. bin/Debug/testunit.exe

Building - Windows [NMake][Debug]
1. <checkout source somewhere into astlib directory>
2. mkdir debug
3. cd debug
4. cmake -G"NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Debug ..
5. jom /j9
6. cd ..
7. bin/testunit.exe

Building - Windows [Release]
1. <checkout source somewhere into astlib directory>
2. mkdir release
3. cd release
4. cmake -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release ..
5. msbuild astlib.sln /t:Rebuild /p:Configuration=Release
6. cd ..
7. bin/Release/testunit.exe

Node.js support (or https://www.npmjs.com/package/node-cmake)
 1. install nodejs package
 2. npm install --save bindings
 2. sudo npm install -g cmake-js [https://www.npmjs.com/package/cmake-js]
 
 1. cmake-js build