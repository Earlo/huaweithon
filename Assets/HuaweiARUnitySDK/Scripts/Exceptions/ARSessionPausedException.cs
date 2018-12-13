

namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARSessionPausedException:ApplicationException
    {
        public ARSessionPausedException() : base() { }
        public ARSessionPausedException(string message) : base(message) { }

        public ARSessionPausedException(string message, Exception innerException) : base(message, innerException) { }
        protected ARSessionPausedException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
