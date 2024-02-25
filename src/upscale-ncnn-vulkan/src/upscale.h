// upscale implemented with ncnn library

#ifndef UPSCALE_H
#define UPSCALE_H

#include <string>

// ncnn
#include "net.h"
#include "gpu.h"
#include "layer.h"

class UPSCALE {
public:
    UPSCALE(int gpuid, bool tta_mode = false);

    ~UPSCALE();

#if _WIN32
    int load(const std::wstring& parampath, const std::wstring& modelpath);
#else

    int load(const std::string &parampath, const std::string &modelpath);

#endif

    int process(const ncnn::Mat &inimage, ncnn::Mat &outimage) const;

    int process_cpu(const ncnn::Mat &inimage, ncnn::Mat &outimage) const;

public:
    // upscale parameters
    int scale;
    int tilesize;
    int prepadding;

private:
    ncnn::VulkanDevice *vkdev;
    ncnn::Net net;
    ncnn::Pipeline *upscale_preproc;
    ncnn::Pipeline *upscale_postproc;
    ncnn::Layer *bicubic_2x;
    ncnn::Layer *bicubic_3x;
    ncnn::Layer *bicubic_4x;
    bool tta_mode;
};

#endif // UPSCALE_H
