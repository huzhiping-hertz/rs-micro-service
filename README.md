0.Install Python3 and pip

1.pip install conan
  关于Linux下找不到conan命令
  运行source ~/.profile
  然后执行conan profile detect
  会生成/home/hz/.conan2/profiles/default 文件
  修改 compiler.cppstd=gnu17，部分软件需要c++17
  注意：用到了drogon_ctl,生成view用，所有将drogon_ctl拷贝到了
  /usr/local/bin下,drogon_ctl 是conanfile.py中配置生成

2.cd rm-api-service

3.mkdir build

Release模式 
4.conan install . --build=missing

Debug模式 
5.conan install . -s build_type=Debug --build=missing


