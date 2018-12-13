
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARNotTrackingException:ApplicationException
    {
        public ARNotTrackingException() : base() { }
        public ARNotTrackingException(string message) : base(message) { }

        public ARNotTrackingException(string message, Exception innerException) : base(message, innerException) { }
        protected ARNotTrackingException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
