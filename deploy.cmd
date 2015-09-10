set PATH=%PATH%;C:\Program Files (x86)\Android\android-sdk\platform-tools
adb uninstall com.test.vgengine
cd .\VGEngine\Tegra-Android\Release\
adb install Test.apk
pause