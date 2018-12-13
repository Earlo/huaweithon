
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARUnSupportedConfigurationException:ApplicationException
    {
        public ARUnSupportedConfigurationException() : base() { }
        public ARUnSupportedConfigurationException(string message) : base(message) { }

        public ARUnSupportedConfigurationException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnSupportedConfigurationException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
