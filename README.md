# The VisionGal Visual Novel Engine
VisionGal 是一个功能强大的视觉小说引擎，专为创建高质量视觉小说和交互式叙事体验而设计。引擎采用 C++ 开发，具有良好的跨平台性和可扩展性。

## 功能特点
- 提供完善的可视化编辑器，支持实时预览编辑效果，方便创作和管理视觉小说内容
- 全部自定义的UI界面，用类似Html和Css的语法来定义界面，用Lua脚本定义界面的行为
- 支持丰富功能的剧情脚本语言，支持中文编写剧情脚本，优雅的追加语法编写剧情
- 支持跨平台，目前已经在Windows上测试通过，Macos和Linux上的测试正在进行中
- 完全开源的MIT协议，开发的游戏版权属于个人所有，你也可以修改引擎源代码，完全不受限制

## 构建与安装
VisionGal 引擎使用 CMake构建，库依赖使用 vcpkg 管理，所以需要使用 [vcpkg](https://vcpkg.io/en/getting-started.html) 来安装依赖库

### vcpkg
vcpkg 是一个 C++ 库管理器，用于管理 C++ 库的依赖关系。在构建 VisionGal 引擎之前，需要先安装 [vcpkg](https://vcpkg.io/en/getting-started.html)

### 安装依赖库
```
vcpkg install freetype
vcpkg install sdl3
vcpkg install sdl3-image[jpeg,png,tiff,webp]
vcpkg install rmlui[freetype]
vcpkg install ffmpeg
```
安装ffmpeg的时间可能会比较长，需要耐心等待，因为需要编译ffmpeg的源代码。

### 构建
安装完依赖库后，使用Git和CMake按以下命令构建VisonGal

```
git clone https://github.com/DarlingZeroX/VisionGal
cd VisionGal
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"
cmake --build Build
```
path-to-vcpkg 替换为你实际的vcpkg安装路径，例如：C:\vcpkg

## 快速开始
1.使用 VGLauncher 启动示例项目

## 目录结构
VisionGal/  <br>
├── Application/         # 应用程序模块 <br>
│   ├── VGDesktopApplication/  # 桌面应用<br>
│   ├── VGLauncher/            # 启动器<br>
│   └── VGPackageTool/         # 打包工具<br>
├── Editor/              # 编辑器模块<br>
│   ├── VGEditor/              # 主编辑器<br>
│   └── VGEditorFramework/     # 编辑器框架<br>
├── Runtime/             # 运行时模块<br>
│   ├── HCore/                 # 核心系统<br>
│   ├── VGEngine/              # 引擎核心<br>
│   ├── VGImgui/               # ImGui 集成<br>
│   ├── VGLua/                 # Lua 脚本支持<br>
│   └── VGPackager/            # 资产打包库<br>
└── Resource/            # 资源文件<br>

## 贡献指南
欢迎任何形式的贡献！如果您想为 VisionGal 做出贡献，请：
1. Fork 项目仓库
2. 创建一个新的分支
3. 提交您的更改
4. 提交 Pull Request

## 许可证
VisionGal 采用 MIT 许可证 ，允许个人和商业使用。





