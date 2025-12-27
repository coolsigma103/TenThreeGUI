#pragma once
#include "module.hpp"
#include <pybind11/pybind11.h>

class Frame {
  int width, height;
  std::string title;

public:
  Frame();
  ~Frame();
};