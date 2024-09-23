#ifndef INCLUDE_OP_ADD_H
#define INCLUDE_OP_ADD_H
#include "base/base.h"
#include "layer.h"

namespace op
{
    class VecAddLayer : public Layer
    {
        explicit VecAddLayer(base::DeviceType device_type);

        base::Status check() const override;

        base::Status forward() override;
    };
}  // namespace op

#endif // INCLUDE_OP_ADD_H