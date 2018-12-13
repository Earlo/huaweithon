
namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    public class ARUnavailableServiceNotInstalledException:ARUnavailableException
	{
        public ARUnavailableServiceNotInstalledException() : base() { }
        public ARUnavailableServiceNotInstalledException(string message) : base(message) { }

        public ARUnavailableServiceNotInstalledException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableServiceNotInstalledException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}

