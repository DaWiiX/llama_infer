#include "base/base.h"
#include "op/kernels/kernels_interface.h"

#include "op/kernels/cpu/add_kernel.h"
#include "op/kernels/cuda/add_kernel.cuh"

#include "op/kernels/cpu/matmul_kernel.h"
#include "op/kernels/cuda/matmul_kernel.cuh"

#include "op/kernels/cpu/emb_kernel.h"
#include "op/kernels/cuda/emb_kernel.cuh"

#include "op/kernels/cpu/rope_kernel.h"
#include "op/kernels/cuda/rope_kernel.cuh"

#include "op/kernels/cpu/swiglu_kernel.h"
#include "op/kernels/cuda/swiglu_kernel.cuh"

#include "op/kernels/cpu/rmsnorm_kernel.h"
#include "op/kernels/cuda/rmsnorm_kernel.cuh"

#include "op/kernels/cpu/scale_kernel.h"
#include "op/kernels/cpu/scale_sum_kernel.h"
#include "op/kernels/cpu/softmax_kernel.h"

#include "op/kernels/cpu/mha_kernel.h"
#include "op/kernels/cuda/mha_kernel.cuh"



namespace kernel
{
    AddKernel get_add_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return add_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return add_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    MatmulKernel get_matmul_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return matmul_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return matmul_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    MatmulKernelQuant get_matmul_kernel_quant8(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCUDA:
            {
                return matmul_kernel_cu_qint8;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    EmbeddingKernel get_emb_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return emb_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return emb_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    RoPEKernel get_rope_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return rope_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return rope_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    SwigluKernel get_swiglu_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return swiglu_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return swiglu_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    RMSNormKernel get_rmsnorm_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return rmsnorm_kernel_cpu;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return rmsnorm_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }
    SoftmaxInplaceKernel get_softmax_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return softmax_inplace_cpu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    ScaleKernel get_scale_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return scale_inplace_cpu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    ScaleSumKernel get_scale_sum_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return scale_sum_kernel_cpu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }

    MHAKernel get_mha_kernel(base::DeviceType device_type)
    {
        switch (device_type)
        {
            case base::DeviceType::DeviceCPU:
            {
                return mha_kernel;
            }
            case base::DeviceType::DeviceCUDA:
            {
                return mha_kernel_cu;
            }
            default:
            {
                LOG(FATAL) << "Unsupported device type: " << device_type;
                return nullptr;
            }
        }
    }
    
}