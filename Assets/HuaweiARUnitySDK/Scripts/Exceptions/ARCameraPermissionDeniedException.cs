
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARCameraPermissionDeniedException : ApplicationException
    {
        public ARCameraPermissionDeniedException() : base() { }
        public ARCameraPermissionDeniedException(string message) : base(message) { }

        public ARCameraPermissionDeniedException(string message, Exception innerException) : base(message, innerException) { }
        protected ARCameraPermissionDeniedException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
