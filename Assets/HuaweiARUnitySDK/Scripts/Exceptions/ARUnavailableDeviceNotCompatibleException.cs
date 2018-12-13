namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    public class ARUnavailableDeviceNotCompatibleException: ARUnavailableException
    {
		public ARUnavailableDeviceNotCompatibleException ():base(){	}
        public ARUnavailableDeviceNotCompatibleException(string message):base(message) { }

        public ARUnavailableDeviceNotCompatibleException(string message, Exception innerException) : base(message, innerException) { }
        protected ARUnavailableDeviceNotCompatibleException(SerializationInfo info, StreamingContext context) : base(info, context) { }

    }
}

