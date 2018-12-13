
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    public class ARUnavailableException:ApplicationException
    {
        public ARUnavailableException() : base() { }
        public ARUnavailableException(string message) : base(message) { }

        public ARUnavailableException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
