
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARTextureNotSetException:ApplicationException
    {
        public ARTextureNotSetException() : base() { }
        public ARTextureNotSetException(string message) : base(message) { }

        public ARTextureNotSetException(string message, Exception innerException) : base(message, innerException) { }
        protected ARTextureNotSetException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
