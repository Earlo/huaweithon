namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;

    public class ARUnavailableConnectServerTimeOutException: ARUnavailableException
    {
        public ARUnavailableConnectServerTimeOutException() : base() { }
        public ARUnavailableConnectServerTimeOutException(string message) : base(message) { }

        public ARUnavailableConnectServerTimeOutException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableConnectServerTimeOutException(SerializationInfo info, StreamingContext context) : base(info, context) { }

    }
}
