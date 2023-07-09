// hello_ml.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>

using namespace winrt;  // 使用Windows namespace
using namespace Windows::AI::MachineLearning;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Media;
using namespace Windows::Storage;

using namespace std;

// Global variables
hstring modelPath = L"C:\\Users\\lucas.lv\\source\\repos\\Windows-Machine-Learning\\SharedContent\\models\\SqueezeNet.onnx";
string deviceName = "default";
hstring imagePath = L"C:\\Users\\lucas.lv\\source\\repos\\Windows-Machine-Learning\\SharedContent\\media\\kitten_224.png";
LearningModel model = nullptr;
LearningModelDeviceKind deviceKind = LearningModelDeviceKind::Default;
LearningModelSession session = nullptr;
LearningModelBinding binding = nullptr;
VideoFrame imageFrame = nullptr;
string labelsFilePath = "C:\\Users\\lucas.lv\\source\\repos\\Windows-Machine-Learning\\Samples\\SqueezeNetObjectDetection\\Desktop\\cpp\\Labels.txt";
vector<string> labels;

// Forward declarations
void LoadModel();
VideoFrame LoadImageFile(hstring filePath);
void BindModel();
void EvaluateModel();
void PrintResults(IVectorView<float> results);
void LoadLabels();


void LoadModel()
{
    // load the model
    printf("Loading modelfile '%ws' on the '%s' device\n", modelPath.c_str(), deviceName.c_str());
    DWORD ticks = GetTickCount();
    model = LearningModel::LoadFromFilePath(modelPath);
    ticks = GetTickCount() - ticks;
    printf("model file loaded in %d ticks\n", ticks);
}

VideoFrame LoadImageFile(hstring filePath)
{
    printf("Loading the image...\n");
    DWORD ticks = GetTickCount();
    VideoFrame inputImage = nullptr;

    try
    {
        // open the file
        StorageFile file = StorageFile::GetFileFromPathAsync(filePath).get();
        // get a stream on it
        auto stream = file.OpenAsync(FileAccessMode::Read).get();
        // Create the decoder from the stream
        BitmapDecoder decoder = BitmapDecoder::CreateAsync(stream).get();
        // get the bitmap
        SoftwareBitmap softwareBitmap = decoder.GetSoftwareBitmapAsync().get();
        // load a videoframe from it
        inputImage = VideoFrame::CreateWithSoftwareBitmap(softwareBitmap);
    }
    catch (...)
    {
        printf("failed to load the image file, make sure you are using fully qualified paths\r\n");
        exit(EXIT_FAILURE);
    }

    ticks = GetTickCount() - ticks;
    printf("image file loaded in %d ticks\n", ticks);
    // all done
    return inputImage;
}

void BindModel()
{
    printf("Binding the model...\n");
    DWORD ticks = GetTickCount();

    // now create a session and binding
    session = LearningModelSession{ model, LearningModelDevice(deviceKind) };
    binding = LearningModelBinding{ session };
    // bind the intput image
    binding.Bind(L"data_0", ImageFeatureValue::CreateFromVideoFrame(imageFrame));
    // bind the output
    vector<int64_t> shape({ 1, 1000, 1, 1 });
    binding.Bind(L"softmaxout_1", TensorFloat::Create(shape));

    ticks = GetTickCount() - ticks;
    printf("Model bound in %d ticks\n", ticks);
}

void EvaluateModel()
{
    // now run the model
    printf("Running the model...\n");
    DWORD ticks = GetTickCount();

    auto results = session.Evaluate(binding, L"RunId");

    ticks = GetTickCount() - ticks;
    printf("model run took %d ticks\n", ticks);

    // get the output
    auto resultTensor = results.Outputs().Lookup(L"softmaxout_1").as<TensorFloat>();
    auto resultVector = resultTensor.GetAsVectorView();
    PrintResults(resultVector);
}

void PrintResults(IVectorView<float> results)
{
    // load the labels
    LoadLabels();
    // Find the top 3 probabilities
    vector<float> topProbabilities(3);
    vector<int> topProbabilityLabelIndexes(3);
    // SqueezeNet returns a list of 1000 options, with probabilities for each, loop through all
    for (uint32_t i = 0; i < results.Size(); i++)
    {
        // is it one of the top 3?
        for (int j = 0; j < 3; j++)
        {
            if (results.GetAt(i) > topProbabilities[j])
            {
                topProbabilityLabelIndexes[j] = i;
                topProbabilities[j] = results.GetAt(i);
                break;
            }
        }
    }
    // Display the result
    for (int i = 0; i < 3; i++)
    {
        printf("%s with confidence of %f\n", labels[topProbabilityLabelIndexes[i]].c_str(), topProbabilities[i]);
    }
}

void LoadLabels()
{
    // Parse labels from labels file.  We know the file's entries are already sorted in order.
    ifstream labelFile{ labelsFilePath, ifstream::in };
    if (labelFile.fail())
    {
        printf("failed to load the %s file.  Make sure it exists in the same folder as the app\r\n", labelsFilePath.c_str());
        exit(EXIT_FAILURE);
    }

    std::string s;
    while (std::getline(labelFile, s, ','))
    {
        int labelValue = atoi(s.c_str());
        if (labelValue >= labels.size())
        {
            labels.resize(labelValue + 1);
        }
        std::getline(labelFile, s);
        labels[labelValue] = s;
    }
}

int main()
{
    LoadModel();
    imageFrame = LoadImageFile(imagePath);
    BindModel();
    EvaluateModel();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
