namespace HuaweiARUnitySDK
{
    public enum ARAvailability
    {
        UNKNOWN_ERROR = 0,
        UNKNOWN_CHECKING = 1,
        UNKNOWN_TIMED_OUT = 2,
        UNSUPPORTED_DEVICE_NOT_CAPABLE = 100,
        UNSUPPORTED_EMUI_NOT_CAPABLE = 5000,
        SUPPORTED_NOT_INSTALLED = 201,
        SUPPORTED_APK_TOO_OLD = 202,
        SUPPORTED_INSTALLED = 203
    }
}
