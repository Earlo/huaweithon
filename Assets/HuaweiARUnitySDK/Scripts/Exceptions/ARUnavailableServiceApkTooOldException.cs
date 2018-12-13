
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    class ARUnavailableServiceApkTooOldException:ARUnavailableException
    {
        public ARUnavailableServiceApkTooOldException() : base() { }
        public ARUnavailableServiceApkTooOldException(string message) : base(message) { }

        public ARUnavailableServiceApkTooOldException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableServiceApkTooOldException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
