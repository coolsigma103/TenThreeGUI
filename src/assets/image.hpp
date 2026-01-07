#pragma once

#include <pybind11/pybind11.h>
#include <stb/stb_image.h>
#include <string>

namespace py = pybind11;

struct Image
{
    Image(const std::string& filePath)
    {
        stbi_set_flip_vertically_on_load(true);
        bytes = stbi_load(filePath.c_str(), &w, &h, &channels, 4);
    }
    ~Image()
    {
        if (bytes)
            stbi_image_free(bytes);
    }
    int getWidth() const { return w; }
    int getHeight() const { return h; }
    int getChannels() const { return channels; }
    unsigned char* getBytes() const { return bytes; }

private:
    int w, h, channels;
    unsigned char* bytes = nullptr;
};

inline void PY_IMAGE_HPP(py::module_& m)
{
    py::class_<Image>(m, "Image")
        .def(py::init<std::string>(), py::arg("filePath"))
        .def("getWidth", &Image::getWidth)
        .def("getHeight", &Image::getHeight)
        .def("getChannels", &Image::getWidth);
}