# Hello Windows Machine Learning!

## 过程记录

### 使用Windows ML API的前提？

在[教程](https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/api-reference)中有对教程声明（但好像不是对WindowsML的声明？）：
1. 开发工具：VS2017 15.7.4及以上
2. 操作系统：WIndows 10 1809及以上
3. Windows SDK版本17763及以上
4. C++/WinRT Visual Studio扩展

在[集成模型](https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/integrate-model#using-winml-apis-in-c)中说，WinML API在C++/CX和C++/WinRT中都可使用

如果使用WinRT的话，需要C++17标准

### C++/WinRT是什么？和C++/CX有什么区别？

C++/WinRT是一种用于开发Windows应用程序的现代C++库。它提供了一种简化的方式来使用Windows Runtime (WinRT) API，以创建高性能、可靠且易于维护的应用程序。

与C++/CX相比，C++/WinRT是一种更轻量级的解决方案。C++/CX是一种扩展C++语法的语言，用于与WinRT进行交互。它引入了一些新的关键字和语法规则，以便在C++代码中使用WinRT API。相比之下，C++/WinRT更接近标准的C++语法，不需要引入新的关键字或语法规则。

C++/WinRT的主要优势是其轻量级和易于使用。它提供了一个现代化的C++ API，使开发人员能够直接使用标准C++语法来访问和操作WinRT API。这使得开发人员可以更轻松地编写和维护代码，并且可以更好地与现有的C++代码集成。

总结起来，C++/WinRT是一种现代化的C++库，用于开发Windows应用程序，它提供了一种轻量级和易于使用的方式来访问和操作WinRT API。与C++/CX相比，C++/WinRT更接近标准的C++语法，使开发人员能够更轻松地编写和维护代码。

应用场景主要有：
1. 创建Windows应用的UI界面
2. 访问设备功能，如控制摄像头、传感器等
3. 操作文件和数据

### 为什么无法`using namespace Windows`?

教程里可能写错了（或者是版本不对？），需要在引用Windows命名空间之前先`using namespace winrt`才行

### 集成onnx模型的简要步骤

#### 1. 加载模型

需要ONNX 1.2及以上版本的模型
支持流式加载，允许加密

2. 创建会话

创建会话使用`LearningModelSession`对象，在这一步会指定模型运行在什么设备上
根据[LearningModelDeviceKind 枚举类型](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodeldevicekind?view=winrt-22621)定义，可以选择以下设备：
	1. CPU
	2. Default，由系统指定
	3. 使用 GPU 或其他 DirectX 设备
	4. DirectXHighPerformance，使用系统策略定义的设备实现高性能。
	5. DirectXMinPower，将系统策略定义的设备用于最小电源。

3. 绑定模型

绑定就是将模型的输入输出（用名称来指定）与用户分配的内存相互绑定，用户内存通过[ImageFeatureDescriptor](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.imagefeaturedescriptor?view=winrt-22621)对象来管理
根据[LearningModelFeatureKind 枚举](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelfeaturekind?view=winrt-22621)，支持的Feature类型有以下几种：
	1. Tensor，张量
	2. Sequance，序列
	3. Map，映射（键值对）
	4. Image，图像

4. 评估模型

评估模型也就是推理模型，支持[同步](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelsession.evaluate?view=winrt-22621)和[异步](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelsession.evaluateasync?view=winrt-22621)执行。
每次推理前，都需要更新绑定时对应的输入Feature对象？TODO: 待实验验证
推理完成后会返回一个[LearningModelEvaluationResult 类](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelevaluationresult?view=winrt-22621)，通过[LearningModelEvaluationResult.Succeeded 属性](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelevaluationresult.outputs?view=winrt-22621)可以以字典形式获取若干个输出结果。

### 什么是DirectX？

DirectX是由微软公司创建的多媒体编程接口，是一种应用程序接口（API）。它旨在使基于Windows的计算机成为运行和显示具有丰富多媒体元素（例如全色图形、视频、3D动画和丰富音频）的应用程序的理想平台。
DirectX可以让以Windows为平台的游戏或多媒体程序获得更高的执行效率，加强3D图形和声音效果，并提供设计人员一个共同的硬件驱动标准，让游戏开发者不必为每一品牌的硬件来写不同的驱动程序，也降低用户安装及设置硬件的复杂度。

DirectX包含多个API，其中最常用的是Direct3D，它是一种用于Windows平台上的3D图形API。

## TODO: WinML/ONNXRuntime/TensorRT性能对比实验

## 参考资料

教程: https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/get-started-desktop
API参考：https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/api-reference
API指南：https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/integrate-model