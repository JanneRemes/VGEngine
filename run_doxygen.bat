@echo off
cd VGEngine
doxygen.exe doxyfile
start file:///%~dp0VGEngine\Documents\html\index.html