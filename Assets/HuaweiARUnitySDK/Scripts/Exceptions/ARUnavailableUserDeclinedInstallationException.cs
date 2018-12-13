namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;

    class ARUnavailableUserDeclinedInstallationException:ARUnavailableException
    {
        public ARUnavailableUserDeclinedInstallationException() : base() { }
        public ARUnavailableUserDeclinedInstallationException(string message) : base(message) { }

        public ARUnavailableUserDeclinedInstallationException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableUserDeclinedInstallationException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
