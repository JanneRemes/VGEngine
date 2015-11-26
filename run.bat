call "%VS120COMNTOOLS%vsvars32.bat"
@echo ...............
@echo compiling Win32
"%VS120COMNTOOLS%..\IDE\devenv.exe" VGEngine\VGEngine.sln /build "Debug|Win32"
@echo ...............
@echo compiling Android
"%VS120COMNTOOLS%..\IDE\devenv.exe" VGEngine\VGEngine.sln /build "Debug|Tegra-Android"
@echo ...............
@echo Starting StaticLibraryMaker.jar
java -jar "StaticLibraryMaker.jar" %~dp0..\VGEngine
@echo Done!
::"C:\Windows\Microsoft.NET\Framework64\v4.0.30319\MSBuild.exe" VGEngine.sln /build "Debug"
pause