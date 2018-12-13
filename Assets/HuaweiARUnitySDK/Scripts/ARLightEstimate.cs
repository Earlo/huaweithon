
namespace HuaweiARUnitySDK
{
    public class ARLightEstimate
    {
        public float PixelIntensity { get; private set; }
        public bool Valid { get; private set; }

        public ARLightEstimate(bool valid,float intensity)
        {
            Valid = valid;
            PixelIntensity = intensity;
        }
    }
}
