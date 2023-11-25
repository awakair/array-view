#include "array_3d_view.h"

namespace uint17 {

Array3DView::Array3DView(size_t height, size_t width,
                         size_t length)
  : data_(height * width * length) {}

} // namespace uint17
