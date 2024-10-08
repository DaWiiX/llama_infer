#ifndef INCLUDE_BASE_BASE_H_
#define INCLUDE_BASE_BASE_H_
#include <glog/logging.h>
#include <cstdint>
#include <string>
#define UNUSED(x)  \
    do {           \
        (void)(x); \
    } while (0)


namespace model
{
    enum class ModelBufferType
    {
        InputTokens = 0,
        InputEmbeddings = 1,
        OutputRMSNorm = 2,
        KeyCache = 3,
        ValueCache = 4,
        Query = 5,
        InputPos = 6,
        ScoreStorage = 7,
        OutputMHA = 8,
        AttnOutput = 9,
        W1Output = 10,
        W2Output = 11,
        W3Output = 12,
        FFNRMSNorm = 13,
        ForwardOutput = 15,
        ForwardOutputCPU = 16,
        SinCache = 17,
        CosCache = 18,
    };
}

namespace base
{
    enum class DeviceType : uint8_t
    {
        DeviceUnknown = 0,
        DeviceCPU = 1,
        DeviceCUDA = 2,
    };

    enum class DataType: uint8_t
    {
        DataTypeUnknown = 0,
        DataTypeFp32 = 1,
        DataTypeInt8 = 2,
        DataTypeInt32 = 3,
    };

    enum class ModelType: uint8_t
    {
        ModelTypeUnknown = 0,
        ModelTypeLLama2 = 1,
    };

    inline std::string DeviceTypeToString(DeviceType device_type)
    {
        if (device_type == DeviceType::DeviceCPU) return "CPU";
        if (device_type == DeviceType::DeviceCUDA) return "CUDA";
        else return "Unknown";
    }

    inline size_t DataTypeSize(DataType data_type)
    {
        if (data_type == DataType::DataTypeFp32) return sizeof(float);
        else if (data_type == DataType::DataTypeInt8) return sizeof(int8_t);
        else if (data_type == DataType::DataTypeInt32) return sizeof(int32_t);
        else 
        {
            LOG(FATAL) << "Unknown data type: " << static_cast<int>(data_type);
            return 0;
        }
    }

    std::ostream& operator<<(std::ostream& os, const DeviceType& x);

    class NoCopyable
    {
        protected:
            NoCopyable() = default;

            ~NoCopyable() = default;

            NoCopyable(const NoCopyable&) = delete;

            NoCopyable& operator=(const NoCopyable&) = delete;
    };

    enum StatusCode : uint8_t
    {
        Success = 0,
        FunctionNotImplement = 1,
        PathNotValid = 2,
        ModelParseError = 3,
        InternalError = 5,
        KeyValueHasExist = 6,
        InvalidArgument = 6,
    };

    class Status
    {
        public:
            Status(int code = StatusCode::Success, std::string err_message = "");

            Status(const Status& other) = default;
            
            Status& operator=(const Status& other) = default;

            Status& operator=(int code);

            bool operator==(int code) const;

            bool operator!=(int code) const;

            operator int() const;

            operator bool() const;

            int32_t get_err_code() const;

            const std::string& get_err_msg() const;

            void set_err_msg(const std::string& err_msg);
        
        private:
            int code_ = StatusCode::Success;
            std::string message_;
    };

    namespace error
    {
        #define STATUS_CHECK(call)                                                                       \
            do                                                                                           \
            {                                                                                            \
                const base::Status &status = call;                                                       \
                if (!status)                                                                             \
                {                                                                                        \
                    const size_t buf_size = 512;                                                         \
                    char buf[buf_size];                                                                  \
                    snprintf(buf, buf_size - 1,                                                          \
                            "Infer error\n File:%s Line:%d\n Error code:%d\n Error msg:%s\n", __FILE__,  \
                            __LINE__, int(status), status.get_err_msg().c_str());                        \
                    LOG(FATAL) << buf;                                                                   \
                }                                                                                        \
            } while (0)

        Status Success(const std::string& err_msg = "success");

        Status FunctionNotImplement(const std::string& err_msg = "function not implement");

        Status PathNotValid(const std::string& err_msg = "path not valid");

        Status ModelParseError(const std::string& err_msg = "model parse error");

        Status InternalError(const std::string& err_msg = "internal error");

        Status KeyValueHasExist(const std::string& err_msg = "key value has existed");

        Status InvalidArgument(const std::string& err_msg = "invalid argument");
    }

    std::ostream& operator<<(std::ostream& os, const Status& x);

}

#endif  // INCLUDE_BASE_BASE_H_