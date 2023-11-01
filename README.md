# SkySnowEngine
Mobile rendering engine, cool effects and cutting-edge rendering technology

### 1.Compile Engine

#### 1.0 Prebuild Depend

- fbxsdk

  - Window&MacOS

    Please read this path (SkySnowEngine/Source/ThirdParty/fbxsdk/fbxsdk下载使用说明.txt) about FBXSDK configuration instructions

#### 1.1 Window Visual Studio

firt cd to "Build/Window"directory

then,open the command line tool,input order：

```
cmake ../..
```

final,open SkySnow.sln project

#### 1.2  MacOS Xcode

First cd “Build/Mac”directory

then,open the command line tool ,input order:

```
cmake -G "Xcode" ../..
```

