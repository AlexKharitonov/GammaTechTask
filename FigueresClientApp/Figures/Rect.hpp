#pragma once

#include "FigureBase.hpp"

namespace figures_client_app {

  struct Rect : public FigureBase {
    int width_{ 0 };
    int height_{ 0 };
  };

}