
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARSessionNotPausedException: ApplicationException
    {
        public ARSessionNotPausedException() : base() { }
        public ARSessionNotPausedException(string message) : base(message) { }

        public ARSessionNotPausedException(string message, Exception innerException) : base(message, innerException) { }
        protected ARSessionNotPausedException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
