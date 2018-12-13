namespace HuaweiARUnitySDK
{
    using System;
    using System.Runtime.Serialization;
    public class ARMissingGlContextException:ApplicationException
    {
        public ARMissingGlContextException() : base() { }
        public ARMissingGlContextException(string message) : base(message) { }

        public ARMissingGlContextException(string message, Exception innerException) : base(message, innerException) { }
        protected ARMissingGlContextException(SerializationInfo info, StreamingContext context) : base(info, context) { }
    }
}
