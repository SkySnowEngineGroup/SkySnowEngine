# [ImGUI调研](https://github.com/ocornut/imgui)

## 一、ImGUI简洁

```ImGUI```是一个基于```C++```的图形用户界面库，它输出的优化后的顶点缓冲区可以在3D渲染管线中使用。特点是快速、可移植、且无外部依赖。

```ImGUI```非常适合集成到游戏引擎、实时渲染的3D应用程序、嵌入式应用程序等。

## 二、集成

```ImGUI```的核心文件位于根目录，具体如下所示：

- imconfig.h

- imgui.h

- imgui.cpp

- imgui_demo.cpp

- imgui_draw.cpp

- imgui_internal.h

- imgui_widgets.cpp

  集成到工程时，直接将上述文件拷贝到工程目录。```ImGUI```不直接接触GPU命令，它输出顶点缓冲区和命令列表，通过渲染API将界面渲染出来。

## 三、使用

```
// Display some text
ImGui::Text("This is a text.");

//create checkbox
ImGui::Checkbox("Demo Window", &show_demo_window); 

//create slider
ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

//create button
ImGui::Button("Button");
```

