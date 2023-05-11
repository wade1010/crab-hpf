## 先编译插件，复制下面命令，在根目录执行即可

g++ --shared -fPIC -I ./utility/logger -I ./utility plugin/EchoPlugin.cpp utility/logger/Logger.cpp utility/System.cpp -o  plugin/echoplugin.so