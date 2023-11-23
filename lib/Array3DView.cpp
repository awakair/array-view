#include "Array3DView.h"

Array3DView::Array3DView(size_t height, size_t width,
                         size_t length)
    : data_(height * width * length) {}

