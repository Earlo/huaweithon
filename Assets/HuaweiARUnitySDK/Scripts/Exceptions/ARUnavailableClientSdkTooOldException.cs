

namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;

    public class ARUnavailableClientSdkTooOldException:ARUnavailableException
    {
        public ARUnavailableClientSdkTooOldException() : base() { }
        public ARUnavailableClientSdkTooOldException(string message) : base(message) { }

        public ARUnavailableClientSdkTooOldException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableClientSdkTooOldException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
