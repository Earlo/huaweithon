
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    public class ARUnavailableEmuiNotCompatibleException:ARUnavailableException
    {
        public ARUnavailableEmuiNotCompatibleException() : base() { }
        public ARUnavailableEmuiNotCompatibleException(string message) : base(message) { }

        public ARUnavailableEmuiNotCompatibleException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableEmuiNotCompatibleException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
