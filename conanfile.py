from conan import ConanFile
from conan.errors import ConanInvalidConfiguration

class MicroServiceInterface(ConanFile):
    name = "MicroServiceInterface"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    options = {"shared": [True, False], "fPIC": [True, False]}

    default_options={"drogon/*:with_ctl":True,"shared": False, "fPIC": True}
    
    def validate(self):
        if self.info.settings.os == "Macos":
            raise ConanInvalidConfiguration("This package is not compatible with Macos")

    def layout(self):
        self.folders.build = f"build/{str(self.settings.arch)}/{str(self.settings.build_type)}/"
        self.folders.generators = f"build/{str(self.settings.arch)}/{str(self.settings.build_type)}/"
        
    def requirements(self):
        
        self.requires("jsoncpp/1.9.5")
        self.requires("spdlog/1.11.0")
        self.requires("drogon/1.8.3")   
        self.requires("poco/1.12.4")
        self.requires("openssl/1.1.1s", override=True)
        self.requires("zlib/1.2.13")
        self.requires("gflags/2.2.2")
        self.requires("catch2/3.1.0")
        self.requires("pugixml/1.13")
        self.requires("nlohmann_json/3.11.2")
        self.requires("zeromq/4.3.4")
    
    def configure(self):
        if self.settings.compiler == 'msvc':
            del self.options.fPIC