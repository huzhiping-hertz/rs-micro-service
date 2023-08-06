0. Install Python3 and pip

1. pip install conan

2. 安装cmake
    Linux 安装后设置环境变量
    windows下vs提供了cmake，如果安装的话会冲突，导致编译出问题，可以直接设置环境变量
    例如：C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\

3. conan profile detect

   linux下会生成: /home/hz/.conan2/profiles/default 文件
   关于Linux下找不到conan命令,运行source ~/.profile

   windows下会生成: C:\Users\Administrator\.conan2\profiles\default
  
   修改 profiles\default 文件
   compiler.cppstd=gnu17，部分软件需要c++17

   注意：Linux 下用到了drogon_ctl,生成view用，所有将drogon_ctl拷贝到了 /usr/local/bin下,drogon_ctl 是conanfile.py中配置生成
        Windows 下用到drogon_ctl,,生成view用，所有将drogon_ctl拷贝到了 c:/work/drogon/下,drogon_ctl 是conanfile.py中配置生成

   其实：drogon 生成view 有些不太合适目前的项目，只需要生产api就可以，所以可以删除drogon_ctl 的依赖

2.cd rm-api-service

3.mkdir build

Release模式 
4.conan install . --build=missing

6.采用visual studio 编译时，配置编译文件为conan-debug/conan-release

Debug模式 
5.conan install . -s build_type=Debug --build=missing


编译器IDE目前都是用的vscode

windows 下用vs2022  在vscode编译成功后也成功编译了


關於x86  x64 版本的編譯
X86 Debug模式 
conan install . -s build_type=Debug  -s arch=x86 --build=missing

x86 Release  模式 
conan install . -s build_type=Debug  -s arch=x86 --build=missing

X64 模式
arch=x86_64

引入第三方庫時注意調用約定(call convention)
x86下調用約定 cdecl stdcall fastcall,默認cdecl
windows api默認stdcall
x64下做了統一

查看第三方庫調用約定