from conan import ConanFile
from conan.errors import ConanInvalidConfiguration

class RMInterface(ConanFile):
    name = "RMInterface"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    default_options={"drogon/*:with_ctl":True}
    
    def validate(self):
        if self.info.settings.os == "Windows":
            raise ConanInvalidConfiguration("This package is not compatible with Windows")

    def layout(self):
        self.folders.build = f"build/{str(self.settings.build_type)}"
        self.folders.generators = "build"
        
    def requirements(self):
        
        self.requires("jsoncpp/1.9.5")
        self.requires("trantor/1.5.8")
        self.requires("drogon/1.8.3")   
        self.requires("poco/1.12.4")
        self.requires("openssl/1.1.1s", override=True)
        self.requires("zlib/1.2.13")
        self.requires("gflags/2.2.2")
        self.requires("catch2/3.1.0")
        self.requires("pugixml/1.13")
        self.requires("nlohmann_json/3.11.2")