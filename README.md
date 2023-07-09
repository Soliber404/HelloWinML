# Hello Windows Machine Learning!

## ���̼�¼

### ʹ��Windows ML API��ǰ�᣿

��[�̳�](https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/api-reference)���жԽ̳��������������Ƕ�WindowsML������������
1. �������ߣ�VS2017 15.7.4������
2. ����ϵͳ��WIndows 10 1809������
3. Windows SDK�汾17763������
4. C++/WinRT Visual Studio��չ

��[����ģ��](https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/integrate-model#using-winml-apis-in-c)��˵��WinML API��C++/CX��C++/WinRT�ж���ʹ��

���ʹ��WinRT�Ļ�����ҪC++17��׼

### C++/WinRT��ʲô����C++/CX��ʲô����

C++/WinRT��һ�����ڿ���WindowsӦ�ó�����ִ�C++�⡣���ṩ��һ�ּ򻯵ķ�ʽ��ʹ��Windows Runtime (WinRT) API���Դ��������ܡ��ɿ�������ά����Ӧ�ó���

��C++/CX��ȣ�C++/WinRT��һ�ָ��������Ľ��������C++/CX��һ����չC++�﷨�����ԣ�������WinRT���н�������������һЩ�µĹؼ��ֺ��﷨�����Ա���C++������ʹ��WinRT API�����֮�£�C++/WinRT���ӽ���׼��C++�﷨������Ҫ�����µĹؼ��ֻ��﷨����

C++/WinRT����Ҫ��������������������ʹ�á����ṩ��һ���ִ�����C++ API��ʹ������Ա�ܹ�ֱ��ʹ�ñ�׼C++�﷨�����ʺͲ���WinRT API����ʹ�ÿ�����Ա���Ը����ɵر�д��ά�����룬���ҿ��Ը��õ������е�C++���뼯�ɡ�

�ܽ�������C++/WinRT��һ���ִ�����C++�⣬���ڿ���WindowsӦ�ó������ṩ��һ��������������ʹ�õķ�ʽ�����ʺͲ���WinRT API����C++/CX��ȣ�C++/WinRT���ӽ���׼��C++�﷨��ʹ������Ա�ܹ������ɵر�д��ά�����롣

Ӧ�ó�����Ҫ�У�
1. ����WindowsӦ�õ�UI����
2. �����豸���ܣ����������ͷ����������
3. �����ļ�������

### Ϊʲô�޷�`using namespace Windows`?

�̳������д���ˣ������ǰ汾���ԣ�������Ҫ������Windows�����ռ�֮ǰ��`using namespace winrt`����

### ����onnxģ�͵ļ�Ҫ����

#### 1. ����ģ��

��ҪONNX 1.2�����ϰ汾��ģ��
֧����ʽ���أ��������

2. �����Ự

�����Ựʹ��`LearningModelSession`��������һ����ָ��ģ��������ʲô�豸��
����[LearningModelDeviceKind ö������](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodeldevicekind?view=winrt-22621)���壬����ѡ�������豸��
	1. CPU
	2. Default����ϵͳָ��
	3. ʹ�� GPU ������ DirectX �豸
	4. DirectXHighPerformance��ʹ��ϵͳ���Զ�����豸ʵ�ָ����ܡ�
	5. DirectXMinPower����ϵͳ���Զ�����豸������С��Դ��

3. ��ģ��

�󶨾��ǽ�ģ�͵������������������ָ�������û�������ڴ��໥�󶨣��û��ڴ�ͨ��[ImageFeatureDescriptor](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.imagefeaturedescriptor?view=winrt-22621)����������
����[LearningModelFeatureKind ö��](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelfeaturekind?view=winrt-22621)��֧�ֵ�Feature���������¼��֣�
	1. Tensor������
	2. Sequance������
	3. Map��ӳ�䣨��ֵ�ԣ�
	4. Image��ͼ��

4. ����ģ��

����ģ��Ҳ��������ģ�ͣ�֧��[ͬ��](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelsession.evaluate?view=winrt-22621)��[�첽](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelsession.evaluateasync?view=winrt-22621)ִ�С�
ÿ������ǰ������Ҫ���°�ʱ��Ӧ������Feature����TODO: ��ʵ����֤
������ɺ�᷵��һ��[LearningModelEvaluationResult ��](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelevaluationresult?view=winrt-22621)��ͨ��[LearningModelEvaluationResult.Succeeded ����](https://learn.microsoft.com/zh-cn/uwp/api/windows.ai.machinelearning.learningmodelevaluationresult.outputs?view=winrt-22621)�������ֵ���ʽ��ȡ���ɸ���������

### ʲô��DirectX��

DirectX����΢��˾�����Ķ�ý���̽ӿڣ���һ��Ӧ�ó���ӿڣ�API������ּ��ʹ����Windows�ļ������Ϊ���к���ʾ���зḻ��ý��Ԫ�أ�����ȫɫͼ�Ρ���Ƶ��3D�����ͷḻ��Ƶ����Ӧ�ó��������ƽ̨��
DirectX��������WindowsΪƽ̨����Ϸ���ý������ø��ߵ�ִ��Ч�ʣ���ǿ3Dͼ�κ�����Ч�������ṩ�����Աһ����ͬ��Ӳ��������׼������Ϸ�����߲���ΪÿһƷ�Ƶ�Ӳ����д��ͬ����������Ҳ�����û���װ������Ӳ���ĸ��Ӷȡ�

DirectX�������API��������õ���Direct3D������һ������Windowsƽ̨�ϵ�3Dͼ��API��

## TODO: WinML/ONNXRuntime/TensorRT���ܶԱ�ʵ��

## �ο�����

�̳�: https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/get-started-desktop
API�ο���https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/api-reference
APIָ�ϣ�https://learn.microsoft.com/zh-cn/windows/ai/windows-ml/integrate-model