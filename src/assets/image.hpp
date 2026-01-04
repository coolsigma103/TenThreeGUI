#pragma once

#include "module.hpp"
#include <pybind11/pybind11.h>

struct Image
{
    int w, h, channels;
    unsigned char* bytes = nullptr;
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
};

inline void PY_IMAGE_HPP(pybind11::module_& m)
{
    pybind11::class_<Image>(m, "Image")
        .def(pybind11::init<const std::string&>(), py::arg("filePath"))
        .def_readonly("width", &Image::w)
        .def_readonly("height", &Image::h)
        .def_readonly("channels", &Image::channels);
}