@ECHO OFF
ECHO ===================Building util-ui c-huff.exe===========================.
mkdir build
set root=%cd%\util-lib\sources
g++ -g %root%\data\./*cpp %root%\utils\utils.cpp  %root%\cmpdcp.cpp -o %cd%\build\cmpdcp.dll -D CMPDCPLIB_EXPORT -s -shared -I %cd%\util-lib\include
ECHO ===================c-huff.exe build successfully=========================.
ECHO ===================Building util-lib cmpdcp.dll==========================.
set root=%cd%\util-ui
g++ -g %root%\./*cpp -o %cd%\build\c-huff.exe -I %root% -I %cd%\util-lib\include -mwindows -L%root% -lole32 -luuid -lgdi32 %root%\./*res -L%cd%\build -lcmpdcp
ECHO **Project build successfully, Launch the application in the build folder**.